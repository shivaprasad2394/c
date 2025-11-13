# Step 1-3: ESP-AT Integration with ESP-Hosted-MCU UART Transport
## Complete Implementation for ESP-AT

---

## FILE 1: esp_hosted_uart.h
### UART Transport Layer Header

```c
#ifndef ESP_HOSTED_UART_H
#define ESP_HOSTED_UART_H

#include "driver/uart.h"
#include "esp_err.h"
#include <stddef.h>
#include <stdint.h>

// UART Configuration
#define ESP_HOSTED_UART_NUM           UART_NUM_1
#define ESP_HOSTED_UART_TX_GPIO       17
#define ESP_HOSTED_UART_RX_GPIO       18
#define ESP_HOSTED_UART_BAUD          921600
#define ESP_HOSTED_UART_BUF_SIZE      4096
#define ESP_HOSTED_RX_TASK_STACK      4096

// Frame Header Constants
#define ESP_HOSTED_FRAME_HDR_SIZE     16
#define ESP_HOSTED_MAX_PAYLOAD_SIZE   2048
#define ESP_HOSTED_CRC_SIZE           2

// Frame Start/End Markers (for UART framing)
#define ESP_HOSTED_FRAME_START        0xFE
#define ESP_HOSTED_FRAME_END          0xFD
#define ESP_HOSTED_FRAME_ESCAPE       0xFC

// Interface Types
typedef enum {
    ESP_INVALID_IF = 0,
    ESP_STA_IF = 1,
    ESP_AP_IF = 2,
    ESP_SERIAL_IF = 3,      // Control/RPC commands
    ESP_HCI_IF = 4,         // Bluetooth HCI
    ESP_PRIV_IF = 5,        // Private host-slave communication
    ESP_TEST_IF = 6,
    ESP_MAX_IF = 8
} esp_hosted_if_type_t;

// ESP-Hosted Frame Header Structure (16 bytes)
typedef struct {
    uint8_t if_type : 4;        // Interface type (bits 0-3)
    uint8_t if_num : 4;         // Interface number (bits 4-7)
    uint8_t flags;              // Flags byte
    uint16_t len;               // Payload length (little-endian)
    uint16_t offset;            // Payload offset (little-endian)
    uint16_t checksum;          // CRC16 checksum (little-endian)
    uint16_t seq_num;           // Sequence number (little-endian)
    uint8_t reserved[4];        // Reserved for future use
} __attribute__((packed)) esp_hosted_header_t;

// Callback for received complete frames
typedef void (*esp_hosted_rx_callback_t)(
    uint8_t if_type,
    uint8_t if_num,
    const uint8_t *payload,
    size_t payload_len
);

// ============ UART Transport Functions ============

/**
 * Initialize UART for esp-hosted communication
 * @return ESP_OK on success
 */
esp_err_t esp_hosted_uart_init(void);

/**
 * Deinitialize UART transport
 * @return ESP_OK on success
 */
esp_err_t esp_hosted_uart_deinit(void);

/**
 * Send a complete frame to slave
 * @param if_type Interface type (ESP_SERIAL_IF for RPC)
 * @param if_num Interface number (0 for control)
 * @param payload Payload data pointer (or NULL)
 * @param payload_len Payload length in bytes
 * @return ESP_OK on success
 */
esp_err_t esp_hosted_uart_send_frame(
    uint8_t if_type,
    uint8_t if_num,
    const uint8_t *payload,
    uint16_t payload_len
);

/**
 * Register callback for received frames
 * @param callback Function to call when frame received
 * @return ESP_OK on success
 */
esp_err_t esp_hosted_uart_register_rx_callback(
    esp_hosted_rx_callback_t callback
);

/**
 * Calculate CRC16 checksum
 * @param data Data buffer
 * @param len Data length
 * @return Calculated CRC16 value
 */
uint16_t esp_hosted_crc16(const uint8_t *data, uint16_t len);

#endif // ESP_HOSTED_UART_H
```

---

## FILE 2: esp_hosted_uart.c
### UART Transport Layer Implementation

```c
#include "esp_hosted_uart.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "string.h"

static const char *TAG = "ESP_HOSTED_UART";

// Global RX callback
static esp_hosted_rx_callback_t g_rx_callback = NULL;

// RX task handle
static TaskHandle_t g_uart_rx_task_handle = NULL;

// ============ CRC16 Implementation ============
static const uint16_t crc16_table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x5295, 0x42B4, 0x72D7, 0x62F6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD39D, 0xC3BC, 0xF3DF, 0xE3FE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64C6, 0x74E7, 0x4484, 0x54A5,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5CE, 0xF5EF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76F7, 0x66D6, 0x56B5, 0x4694,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A51, 0x0A70, 0x3A13, 0x2A32,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC31D, 0xD33C, 0xE35F, 0xF37E,
    0x0240, 0x1261, 0x2202, 0x3223, 0x42E4, 0x52C5, 0x62A6, 0x7287,
    0xB2BD, 0xA29C, 0x92FF, 0x82DE, 0xF219, 0xE238, 0xD25B, 0xC27A,
    0x5305, 0x4324, 0x7347, 0x6366, 0x53A1, 0x4380, 0x73E3, 0x63C2,
    0xAF41, 0xBF60, 0x8F03, 0x9F22, 0xEFC5, 0xFFE4, 0xCF87, 0xDFA6,
    0x91A8, 0x8189, 0xB1EA, 0xA1CB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC31D, 0xD33C, 0xE35F, 0xF37E,
    0x0240, 0x1261, 0x2202, 0x3223, 0x42E4, 0x52C5, 0x62A6, 0x7287,
    0xB2BD, 0xA29C, 0x92FF, 0x82DE, 0xF219, 0xE238, 0xD25B, 0xC27A,
    0x5305, 0x4324, 0x7347, 0x6366, 0x53A1, 0x4380, 0x73E3, 0x63C2,
    0xAF41, 0xBF60, 0x8F03, 0x9F22, 0xEFC5, 0xFFE4, 0xCF87, 0xDFA6,
    0x1676, 0x0657, 0x3634, 0x2615, 0x56D2, 0x46F3, 0x7690, 0x66B1,
    0xE70E, 0xF72F, 0xC74C, 0xD76D, 0xA7AA, 0xB78B, 0x87E8, 0x97C9
};

uint16_t esp_hosted_crc16(const uint8_t *data, uint16_t len)
{
    uint16_t crc = 0;
    for (uint16_t i = 0; i < len; i++) {
        uint8_t idx = (crc >> 8) ^ data[i];
        crc = ((crc << 8) ^ crc16_table[idx]) & 0xFFFF;
    }
    return crc;
}

// ============ UART Initialization ============

esp_err_t esp_hosted_uart_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = ESP_HOSTED_UART_BAUD,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 0,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Configure UART parameters
    esp_err_t err = uart_param_config(ESP_HOSTED_UART_NUM, &uart_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure UART params: %s", esp_err_to_name(err));
        return err;
    }

    // Set UART pins
    err = uart_set_pin(ESP_HOSTED_UART_NUM, 
                       ESP_HOSTED_UART_TX_GPIO,
                       ESP_HOSTED_UART_RX_GPIO,
                       UART_PIN_NO_CHANGE,
                       UART_PIN_NO_CHANGE);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set UART pins: %s", esp_err_to_name(err));
        return err;
    }

    // Install UART driver (RX buffer=4KB, TX buffer=0, no event queue)
    err = uart_driver_install(ESP_HOSTED_UART_NUM,
                             ESP_HOSTED_UART_BUF_SIZE * 2,
                             0,
                             0,
                             NULL,
                             0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install UART driver: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "UART initialized at %d baud on pins TX=%d RX=%d",
             ESP_HOSTED_UART_BAUD,
             ESP_HOSTED_UART_TX_GPIO,
             ESP_HOSTED_UART_RX_GPIO);

    return ESP_OK;
}

esp_err_t esp_hosted_uart_deinit(void)
{
    return uart_driver_delete(ESP_HOSTED_UART_NUM);
}

// ============ Frame Transmission ============

esp_err_t esp_hosted_uart_send_frame(
    uint8_t if_type,
    uint8_t if_num,
    const uint8_t *payload,
    uint16_t payload_len)
{
    if (payload_len > ESP_HOSTED_MAX_PAYLOAD_SIZE) {
        ESP_LOGE(TAG, "Payload too large: %d > %d", payload_len, ESP_HOSTED_MAX_PAYLOAD_SIZE);
        return ESP_ERR_INVALID_SIZE;
    }

    // Allocate buffer for complete frame
    uint8_t *frame = malloc(ESP_HOSTED_FRAME_HDR_SIZE + payload_len + 2 + 2);
    if (!frame) {
        ESP_LOGE(TAG, "Failed to allocate frame buffer");
        return ESP_ERR_NO_MEM;
    }

    uint8_t *ptr = frame;

    // Start marker
    *ptr++ = ESP_HOSTED_FRAME_START;

    // Build header
    esp_hosted_header_t *hdr = (esp_hosted_header_t *)ptr;
    memset(hdr, 0, ESP_HOSTED_FRAME_HDR_SIZE);
    
    hdr->if_type = if_type & 0x0F;
    hdr->if_num = if_num & 0x0F;
    hdr->flags = 0;
    hdr->len = payload_len;
    hdr->offset = 0;
    hdr->seq_num = 0;

    // Calculate CRC16 over header + payload
    uint16_t crc = esp_hosted_crc16((const uint8_t *)hdr, ESP_HOSTED_FRAME_HDR_SIZE);
    if (payload && payload_len > 0) {
        crc = esp_hosted_crc16_continue(crc, payload, payload_len);
    }
    hdr->checksum = crc;

    ptr += ESP_HOSTED_FRAME_HDR_SIZE;

    // Copy payload
    if (payload && payload_len > 0) {
        memcpy(ptr, payload, payload_len);
        ptr += payload_len;
    }

    // End marker
    *ptr++ = ESP_HOSTED_FRAME_END;

    // Send frame to UART
    int bytes_sent = uart_write_bytes(ESP_HOSTED_UART_NUM, frame, ptr - frame);
    
    free(frame);

    if (bytes_sent < 0) {
        ESP_LOGE(TAG, "Failed to send frame via UART");
        return ESP_FAIL;
    }

    ESP_LOGD(TAG, "Sent frame: type=%d num=%d len=%d checksum=0x%04X",
             if_type, if_num, payload_len, crc);

    return ESP_OK;
}

// Helper function for continued CRC calculation
uint16_t esp_hosted_crc16_continue(uint16_t crc, const uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++) {
        uint8_t idx = (crc >> 8) ^ data[i];
        crc = ((crc << 8) ^ crc16_table[idx]) & 0xFFFF;
    }
    return crc;
}

// ============ Frame Reception Task ============

static void esp_hosted_uart_rx_task(void *arg)
{
    uint8_t *data = (uint8_t *)malloc(ESP_HOSTED_UART_BUF_SIZE);
    if (!data) {
        ESP_LOGE(TAG, "Failed to allocate RX buffer");
        vTaskDelete(NULL);
        return;
    }

    uint8_t *frame_buf = (uint8_t *)malloc(ESP_HOSTED_FRAME_HDR_SIZE + ESP_HOSTED_MAX_PAYLOAD_SIZE);
    if (!frame_buf) {
        ESP_LOGE(TAG, "Failed to allocate frame buffer");
        free(data);
        vTaskDelete(NULL);
        return;
    }

    uint16_t frame_pos = 0;
    bool in_frame = false;
    uint16_t expected_len = 0;

    while (1) {
        int len = uart_read_bytes(ESP_HOSTED_UART_NUM, data, ESP_HOSTED_UART_BUF_SIZE, pdMS_TO_TICKS(100));
        
        if (len <= 0) {
            continue;
        }

        for (int i = 0; i < len; i++) {
            uint8_t byte = data[i];

            if (!in_frame) {
                // Look for frame start marker
                if (byte == ESP_HOSTED_FRAME_START) {
                    in_frame = true;
                    frame_pos = 0;
                    expected_len = 0;
                }
            } else {
                // Handle frame escape sequences
                if (byte == ESP_HOSTED_FRAME_ESCAPE && i + 1 < len) {
                    i++;  // Skip escape character
                    frame_buf[frame_pos++] = data[i];
                } else if (byte == ESP_HOSTED_FRAME_END) {
                    // End of frame
                    in_frame = false;

                    if (frame_pos >= ESP_HOSTED_FRAME_HDR_SIZE) {
                        esp_hosted_header_t *hdr = (esp_hosted_header_t *)frame_buf;
                        uint16_t payload_len = hdr->len;
                        uint8_t *payload = frame_buf + ESP_HOSTED_FRAME_HDR_SIZE;

                        // Verify CRC
                        uint16_t expected_crc = esp_hosted_crc16(frame_buf, frame_pos);
                        if (expected_crc != hdr->checksum) {
                            ESP_LOGW(TAG, "CRC mismatch: got 0x%04X expected 0x%04X",
                                    hdr->checksum, expected_crc);
                        } else {
                            // Valid frame received
                            if (g_rx_callback) {
                                g_rx_callback(hdr->if_type,
                                            hdr->if_num,
                                            payload,
                                            payload_len);
                            }
                        }
                    }
                    frame_pos = 0;
                } else {
                    frame_buf[frame_pos++] = byte;

                    if (frame_pos >= ESP_HOSTED_FRAME_HDR_SIZE) {
                        // Check if we have complete payload
                        esp_hosted_header_t *hdr = (esp_hosted_header_t *)frame_buf;
                        if (frame_pos >= ESP_HOSTED_FRAME_HDR_SIZE + hdr->len) {
                            // Wait for end marker (will be processed in next iteration)
                        }
                    }

                    // Prevent buffer overflow
                    if (frame_pos >= ESP_HOSTED_FRAME_HDR_SIZE + ESP_HOSTED_MAX_PAYLOAD_SIZE) {
                        in_frame = false;
                        frame_pos = 0;
                        ESP_LOGW(TAG, "Frame buffer overflow, discarding");
                    }
                }
            }
        }
    }

    free(data);
    free(frame_buf);
    vTaskDelete(NULL);
}

esp_err_t esp_hosted_uart_register_rx_callback(esp_hosted_rx_callback_t callback)
{
    g_rx_callback = callback;

    // Start RX task if not already running
    if (g_uart_rx_task_handle == NULL) {
        BaseType_t ret = xTaskCreate(
            esp_hosted_uart_rx_task,
            "esp_hosted_uart_rx",
            ESP_HOSTED_RX_TASK_STACK,
            NULL,
            10,  // Priority
            &g_uart_rx_task_handle
        );

        if (ret != pdPASS) {
            ESP_LOGE(TAG, "Failed to create UART RX task");
            return ESP_ERR_NO_MEM;
        }

        ESP_LOGI(TAG, "UART RX task created");
    }

    return ESP_OK;
}
```

---

## FILE 3: esp_hosted_rpc.h
### RPC Handler Header

```c
#ifndef ESP_HOSTED_RPC_H
#define ESP_HOSTED_RPC_H

#include "esp_err.h"
#include <stdint.h>

// RPC Command Types
typedef enum {
    ESP_HOSTED_RPC_WIFI_INIT = 1,
    ESP_HOSTED_RPC_WIFI_CONNECT = 2,
    ESP_HOSTED_RPC_WIFI_DISCONNECT = 3,
    ESP_HOSTED_RPC_SOCKET_CREATE = 4,
    ESP_HOSTED_RPC_SOCKET_SEND = 5,
    ESP_HOSTED_RPC_SOCKET_RECV = 6,
    ESP_HOSTED_RPC_SOCKET_CLOSE = 7,
    ESP_HOSTED_RPC_GET_STATUS = 100
} esp_hosted_rpc_cmd_t;

// WiFi Connection Parameters
typedef struct {
    const char *ssid;
    const char *password;
    uint8_t bssid[6];  // Optional, set to 0x00 if not used
} esp_hosted_wifi_connect_params_t;

// Socket Create Parameters
typedef struct {
    int domain;      // AF_INET, AF_INET6
    int type;        // SOCK_STREAM, SOCK_DGRAM
    int protocol;    // IPPROTO_TCP, IPPROTO_UDP
} esp_hosted_socket_create_params_t;

// Socket Address Structure
typedef struct {
    uint16_t port;
    uint8_t ip[4];   // IPv4 address
} esp_hosted_socket_addr_t;

// Response Callback
typedef void (*esp_hosted_rpc_response_callback_t)(
    uint32_t req_id,
    esp_hosted_rpc_cmd_t cmd,
    int32_t result,
    const uint8_t *response_data,
    uint16_t response_len
);

// ============ RPC Functions ============

/**
 * Initialize RPC handler
 */
esp_err_t esp_hosted_rpc_init(void);

/**
 * Send WiFi connect RPC command
 */
esp_err_t esp_hosted_rpc_wifi_connect(
    const char *ssid,
    const char *password,
    uint32_t *req_id
);

/**
 * Send WiFi disconnect RPC command
 */
esp_err_t esp_hosted_rpc_wifi_disconnect(uint32_t *req_id);

/**
 * Send socket create RPC command
 */
esp_err_t esp_hosted_rpc_socket_create(
    int domain,
    int type,
    int protocol,
    uint32_t *req_id
);

/**
 * Send socket connect RPC command
 */
esp_hosted_rpc_socket_connect(
    int socket_id,
    const char *server_ip,
    uint16_t port,
    uint32_t *req_id
);

/**
 * Send socket send RPC command
 */
esp_err_t esp_hosted_rpc_socket_send(
    int socket_id,
    const uint8_t *data,
    uint16_t data_len,
    uint32_t *req_id
);

/**
 * Send socket recv RPC command
 */
esp_err_t esp_hosted_rpc_socket_recv(
    int socket_id,
    uint16_t max_len,
    uint32_t *req_id
);

/**
 * Send socket close RPC command
 */
esp_err_t esp_hosted_rpc_socket_close(
    int socket_id,
    uint32_t *req_id
);

/**
 * Register RPC response callback
 */
esp_err_t esp_hosted_rpc_register_callback(
    esp_hosted_rpc_response_callback_t callback
);

#endif // ESP_HOSTED_RPC_H
```

---

## FILE 4: esp_hosted_rpc.c (Minimal Implementation - Step 2)

```c
#include "esp_hosted_rpc.h"
#include "esp_hosted_uart.h"
#include "esp_log.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

static const char *TAG = "ESP_HOSTED_RPC";

// Global state
static uint32_t g_req_id_counter = 0;
static esp_hosted_rpc_response_callback_t g_response_callback = NULL;

// ============ RPC Message Structure ============

// Minimal protobuf encoding for WiFi connect command
typedef struct {
    uint8_t cmd_id;      // Command ID
    uint32_t req_id;     // Request ID
    union {
        struct {
            char ssid[32];
            char password[64];
        } wifi_connect;
        struct {
            int socket_id;
            uint16_t len;
            uint8_t data[512];
        } socket_send;
    } payload;
} esp_hosted_rpc_message_t;

// ============ Protobuf Encoding Functions ============

// Simple protobuf varint encoder
static int encode_varint(uint8_t *buf, uint32_t value)
{
    int len = 0;
    while (value >= 0x80) {
        buf[len++] = (value & 0x7F) | 0x80;
        value >>= 7;
    }
    buf[len++] = value & 0x7F;
    return len;
}

// Simple protobuf string encoder (field 1: string ssid)
static int encode_string_field(uint8_t *buf, uint8_t field_num, const char *str)
{
    int len = 0;
    int str_len = strlen(str);

    // Field header: (field_num << 3) | 2 (wire type for length-delimited)
    len += encode_varint(buf + len, (field_num << 3) | 2);

    // String length
    len += encode_varint(buf + len, str_len);

    // String data
    memcpy(buf + len, str, str_len);
    len += str_len;

    return len;
}

// ============ RPC Implementation ============

esp_err_t esp_hosted_rpc_init(void)
{
    ESP_LOGI(TAG, "RPC handler initialized");
    return ESP_OK;
}

esp_err_t esp_hosted_rpc_wifi_connect(
    const char *ssid,
    const char *password,
    uint32_t *req_id)
{
    if (!ssid || !password) {
        return ESP_ERR_INVALID_ARG;
    }

    // Generate request ID
    *req_id = ++g_req_id_counter;

    // Build RPC message payload using protobuf encoding
    uint8_t payload[256] = {0};
    int payload_len = 0;

    // Command ID (varint: field 1)
    payload_len += encode_varint(payload + payload_len, (1 << 3) | 0);  // field 1, wire type 0
    payload_len += encode_varint(payload + payload_len, ESP_HOSTED_RPC_WIFI_CONNECT);

    // Request ID (varint: field 2)
    payload_len += encode_varint(payload + payload_len, (2 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, *req_id);

    // SSID (string: field 3)
    payload_len += encode_string_field(payload + payload_len, 3, ssid);

    // Password (string: field 4)
    payload_len += encode_string_field(payload + payload_len, 4, password);

    // Send via UART
    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_SERIAL_IF,    // Use serial interface for RPC commands
        0,                // Interface number
        payload,
        payload_len
    );

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send WiFi connect RPC");
        return err;
    }

    ESP_LOGI(TAG, "WiFi connect RPC sent: req_id=%lu ssid=%s", *req_id, ssid);
    return ESP_OK;
}

esp_err_t esp_hosted_rpc_wifi_disconnect(uint32_t *req_id)
{
    *req_id = ++g_req_id_counter;

    uint8_t payload[32] = {0};
    int payload_len = 0;

    // Command ID
    payload_len += encode_varint(payload + payload_len, (1 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, ESP_HOSTED_RPC_WIFI_DISCONNECT);

    // Request ID
    payload_len += encode_varint(payload + payload_len, (2 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, *req_id);

    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_SERIAL_IF, 0, payload, payload_len
    );

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "WiFi disconnect RPC sent: req_id=%lu", *req_id);
    }
    return err;
}

esp_err_t esp_hosted_rpc_socket_create(
    int domain,
    int type,
    int protocol,
    uint32_t *req_id)
{
    *req_id = ++g_req_id_counter;

    uint8_t payload[32] = {0};
    int payload_len = 0;

    // Command ID
    payload_len += encode_varint(payload + payload_len, (1 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, ESP_HOSTED_RPC_SOCKET_CREATE);

    // Request ID
    payload_len += encode_varint(payload + payload_len, (2 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, *req_id);

    // Domain
    payload_len += encode_varint(payload + payload_len, (3 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, domain);

    // Type
    payload_len += encode_varint(payload + payload_len, (4 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, type);

    // Protocol
    payload_len += encode_varint(payload + payload_len, (5 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, protocol);

    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_SERIAL_IF, 0, payload, payload_len
    );

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Socket create RPC sent: req_id=%lu", *req_id);
    }
    return err;
}

esp_err_t esp_hosted_rpc_socket_send(
    int socket_id,
    const uint8_t *data,
    uint16_t data_len,
    uint32_t *req_id)
{
    if (!data || data_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    *req_id = ++g_req_id_counter;

    // For socket_send, we send data directly without RPC encoding
    // Use PRIV_IF interface for private data communication
    uint8_t header[8] = {0};
    int header_len = 0;

    // Request ID (field 1)
    header_len += encode_varint(header + header_len, (1 << 3) | 0);
    header_len += encode_varint(header + header_len, *req_id);

    // Socket ID (field 2)
    header_len += encode_varint(header + header_len, (2 << 3) | 0);
    header_len += encode_varint(header + header_len, socket_id);

    // Combine header and data
    uint8_t *combined = malloc(header_len + data_len);
    if (!combined) {
        return ESP_ERR_NO_MEM;
    }

    memcpy(combined, header, header_len);
    memcpy(combined + header_len, data, data_len);

    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_PRIV_IF,           // Private interface for data
        socket_id,             // Use socket_id as interface number
        combined,
        header_len + data_len
    );

    free(combined);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Socket send RPC sent: req_id=%lu socket=%d len=%d", 
                 *req_id, socket_id, data_len);
    }
    return err;
}

esp_err_t esp_hosted_rpc_socket_recv(
    int socket_id,
    uint16_t max_len,
    uint32_t *req_id)
{
    *req_id = ++g_req_id_counter;

    uint8_t payload[32] = {0};
    int payload_len = 0;

    // Command ID
    payload_len += encode_varint(payload + payload_len, (1 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, ESP_HOSTED_RPC_SOCKET_RECV);

    // Request ID
    payload_len += encode_varint(payload + payload_len, (2 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, *req_id);

    // Socket ID
    payload_len += encode_varint(payload + payload_len, (3 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, socket_id);

    // Max length
    payload_len += encode_varint(payload + payload_len, (4 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, max_len);

    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_SERIAL_IF, 0, payload, payload_len
    );

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Socket recv RPC sent: req_id=%lu socket=%d", *req_id, socket_id);
    }
    return err;
}

esp_err_t esp_hosted_rpc_socket_close(
    int socket_id,
    uint32_t *req_id)
{
    *req_id = ++g_req_id_counter;

    uint8_t payload[32] = {0};
    int payload_len = 0;

    // Command ID
    payload_len += encode_varint(payload + payload_len, (1 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, ESP_HOSTED_RPC_SOCKET_CLOSE);

    // Request ID
    payload_len += encode_varint(payload + payload_len, (2 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, *req_id);

    // Socket ID
    payload_len += encode_varint(payload + payload_len, (3 << 3) | 0);
    payload_len += encode_varint(payload + payload_len, socket_id);

    esp_err_t err = esp_hosted_uart_send_frame(
        ESP_SERIAL_IF, 0, payload, payload_len
    );

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Socket close RPC sent: req_id=%lu socket=%d", *req_id, socket_id);
    }
    return err;
}

esp_err_t esp_hosted_rpc_register_callback(
    esp_hosted_rpc_response_callback_t callback)
{
    g_response_callback = callback;
    return ESP_OK;
}
```

---

## FILE 5: Integration Example for ESP-AT

```c
// File: components/esp_hosted_transport/example_integration.c

#include "esp_hosted_uart.h"
#include "esp_hosted_rpc.h"
#include "esp_at.h"
#include "esp_log.h"
#include "string.h"

static const char *TAG = "ESP_AT_HOSTED";

// Global state for tracking RPC requests
typedef struct {
    uint32_t req_id;
    esp_hosted_rpc_cmd_t cmd;
    uint32_t timeout_ms;
    uint8_t completed;
    int32_t result;
} esp_hosted_rpc_tracking_t;

#define MAX_PENDING_RPC 10
static esp_hosted_rpc_tracking_t g_pending_rpc[MAX_PENDING_RPC];
static uint8_t g_pending_rpc_count = 0;

// ============ RPC Response Handler ============

static void esp_hosted_handle_frame_received(
    uint8_t if_type,
    uint8_t if_num,
    const uint8_t *payload,
    size_t payload_len)
{
    if (if_type == ESP_SERIAL_IF) {
        // RPC response from slave
        if (payload_len >= 8) {
            uint32_t req_id = *(uint32_t *)(payload);
            int32_t result = *(int32_t *)(payload + 4);

            ESP_LOGI(TAG, "RPC Response: req_id=%lu result=%ld", req_id, result);

            // Find and update tracking entry
            for (int i = 0; i < g_pending_rpc_count; i++) {
                if (g_pending_rpc[i].req_id == req_id) {
                    g_pending_rpc[i].result = result;
                    g_pending_rpc[i].completed = 1;
                    break;
                }
            }
        }
    } else if (if_type == ESP_PRIV_IF) {
        // Private data received from socket
        ESP_LOGI(TAG, "Socket data received: if_num=%d len=%d", if_num, payload_len);
        // Handle socket data here
    }
}

// ============ Custom AT Commands ============

// AT+HCONNECT=<ssid>,<password>
static uint8_t at_setup_cmd_hconnect(uint8_t para_num)
{
    uint8_t *ssid = NULL;
    uint8_t *password = NULL;

    // Parse SSID
    if (esp_at_get_para_as_str(0, &ssid) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }

    // Parse password
    if (esp_at_get_para_as_str(1, &password) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }

    uint32_t req_id;
    esp_err_t err = esp_hosted_rpc_wifi_connect((char *)ssid, (char *)password, &req_id);

    if (err == ESP_OK) {
        // Track RPC request
        if (g_pending_rpc_count < MAX_PENDING_RPC) {
            g_pending_rpc[g_pending_rpc_count].req_id = req_id;
            g_pending_rpc[g_pending_rpc_count].cmd = ESP_HOSTED_RPC_WIFI_CONNECT;
            g_pending_rpc[g_pending_rpc_count].completed = 0;
            g_pending_rpc_count++;
        }

        esp_at_port_write_data((uint8_t *)"\r\nOK\r\n", 6);
        return ESP_AT_RESULT_CODE_OK;
    }

    return ESP_AT_RESULT_CODE_ERROR;
}

// AT+HSEND=<data>
static uint8_t at_setup_cmd_hsend(uint8_t para_num)
{
    uint8_t *data = NULL;

    if (esp_at_get_para_as_str(0, &data) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }

    // Send data to co-processor (socket_id = 0 for now)
    uint32_t req_id;
    esp_err_t err = esp_hosted_rpc_socket_send(0, data, strlen((char *)data), &req_id);

    if (err == ESP_OK) {
        esp_at_port_write_data((uint8_t *)"\r\nOK\r\n", 6);
        return ESP_AT_RESULT_CODE_OK;
    }

    return ESP_AT_RESULT_CODE_ERROR;
}

// AT+HSTATUS
static uint8_t at_query_cmd_hstatus(uint8_t *cmd_name)
{
    char response[128];
    snprintf(response, sizeof(response), 
             "\r\n+HSTATUS: pending_rpc=%d\r\nOK\r\n",
             g_pending_rpc_count);
    
    esp_at_port_write_data((uint8_t *)response, strlen(response));
    return ESP_AT_RESULT_CODE_OK;
}

// Register custom AT commands
static const esp_at_cmd_struct at_hosted_cmd[] = {
    {"+HCONNECT", NULL, NULL, at_setup_cmd_hconnect, NULL},
    {"+HSEND", NULL, at_query_cmd_hstatus, at_setup_cmd_hsend, NULL},
    {"+HSTATUS", NULL, at_query_cmd_hstatus, NULL, NULL},
};

bool esp_at_custom_cmd_register(void)
{
    return esp_at_custom_cmd_array_regist(
        at_hosted_cmd,
        sizeof(at_hosted_cmd) / sizeof(esp_at_cmd_struct)
    );
}

// ============ Component Initialization ============

esp_err_t esp_hosted_transport_init(void)
{
    // Initialize UART
    esp_err_t err = esp_hosted_uart_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize UART");
        return err;
    }

    // Register RX callback
    err = esp_hosted_uart_register_rx_callback(esp_hosted_handle_frame_received);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register UART callback");
        return err;
    }

    // Initialize RPC handler
    err = esp_hosted_rpc_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize RPC");
        return err;
    }

    ESP_LOGI(TAG, "ESP-Hosted transport initialized successfully");
    return ESP_OK;
}

// Weak function called by AT application
void __attribute__((weak)) app_main_init(void)
{
    esp_hosted_transport_init();
}
```

---

## Step-by-Step Usage

### 1. Integration into esp-at

Copy the files to your esp-at project:

```bash
esp-at/
├── components/
│   └── esp_hosted_transport/
│       ├── CMakeLists.txt
│       ├── esp_hosted_uart.h
│       ├── esp_hosted_uart.c
│       ├── esp_hosted_rpc.h
│       ├── esp_hosted_rpc.c
│       └── example_integration.c
```

### 2. CMakeLists.txt for Component

```cmake
idf_component_register(
    SRCS "esp_hosted_uart.c" "esp_hosted_rpc.c"
    INCLUDE_DIRS "."
    REQUIRES "driver" "freertos" "esp_common"
)
```

### 3. Building

```bash
python build.py menuconfig
# Set UART pins and baud rate
python build.py build
```

### 4. Testing with AT Commands

After flashing:

```
AT+HCONNECT="MySSID","MyPassword"
+HCONNECT: OK
```

Send data to co-processor:

```
AT+HSEND="Hello from ESP-AT"
+HSEND: OK
```

Check status:

```
AT+HSTATUS
+HSTATUS: pending_rpc=0
OK
```

---

## Notes

- CRC16 is implemented for frame integrity
- Protobuf encoding is minimal but functional
- RPC requests are tracked with IDs
- UART frame format: [START][HEADER][PAYLOAD][END]
- RX task runs at priority 10 continuously monitoring UART
- Baud rate 921600 for optimal reliability

