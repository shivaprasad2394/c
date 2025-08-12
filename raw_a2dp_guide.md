# Raw Bluetooth A2DP Sink Implementation Guide

## 1. Introduction
This document explains the concepts and practical steps required to build a **Bluetooth Classic A2DP sink** on Linux **without relying on D-Bus / BlueZ high-level APIs**. Instead, we communicate directly with the kernel **HCI** and **L2CAP** layers using raw sockets, implement the **AVDTP** state-machine in userspace, decode **SBC** audio, and play it via **ALSA**.

---

## 2. Essential Theory

### 2.1 Bluetooth Classic Architecture
| Layer | Purpose | Key Protocols |
|-------|---------|---------------|
| Application | Audio playback, UI | Your program, ALSA |
| Profiles | A2DP (Advanced Audio Distribution) | A2DP Sink / Source |
| Transport | AVDTP (signalling), RTP (media) | Defines stream setup & packets |
| Adaptation | **L2CAP** | Reliable & connection-oriented channels (PSM 0x19, 0x1B) |
| Host Ctrl | **HCI** | Commands, events, ACL/SCO data |
| Controller | Link Manager, Baseband, Radio | Firmware in BT chipset |

### 2.2 Key Specifications to Read
* Bluetooth Core Spec v5.x – Vol 2 (HCI), Vol 3 (L2CAP), Vol 4 (Profiles)
* A2DP v1.3 spec – stream setup, SBC codec caps
* AVDTP v1.3 spec – discover, get_caps, set_config, open, start
* SBC codec spec (ETSI TS 101 699)

### 2.3 Important Protocol Numbers
| Protocol | PSM / Channel | Direction |
|----------|---------------|-----------|
| SDP | 0x0001 | query services |
| AVDTP Signalling | **0x0019** | configuration |
| A2DP Media | **0x001B** | RTP + SBC frames |
| HID Control | 0x0011 | (if needed) |

### 2.4 Socket Types
* **HCI raw/user socket** – `socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)`
* **L2CAP seqpacket** – `socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP)`

### 2.5 State Machines
1. **HCI**: init adapter, enable scan, handle Connect Complete, encryption.
2. **SDP**: register A2DP sink record (local) so phones see it.
3. **AVDTP** (sink role):
   * **Discover** → **Get Capabilities** → **Set Configuration** → **Open** → **Start**.
4. **Streaming**: receive RTP packets, strip 12-byte header, decode SBC, feed ALSA.

---

## 3. Development Environment
* Linux kernel ≥ 5.4 with `CONFIG_BT` + `CONFIG_BT_RFCOMM` + `CONFIG_BT_SCO`.
* Packages: `libbluetooth-dev` (for headers), `libsbc-dev`, `libasound2-dev`, `pthread`.
* Run as **root** or give CAP_NET_RAW to binary for HCI raw socket.

### 3.1 Tools
* `btmon` – trace HCI/L2CAP packets.
* `hcitool` / `hciconfig` – quick manual commands.
* `rfkill` – unblock radio.

---

## 4. Coding Walk-Through

### 4.1 Raw HCI Control
```c
int hci_sock = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI);
struct sockaddr_hci addr = { .hci_family = AF_BLUETOOTH,
                             .hci_dev    = 0, // hci0
                             .hci_channel= HCI_CHANNEL_RAW };
bind(hci_sock, (void*)&addr, sizeof(addr));

/* Enable Inquiry + Page scan */
uint8_t enable = 0x03;
hci_send_cmd(hci_sock, OGF_HOST_CTL, OCF_WRITE_SCAN_ENABLE, 1, &enable);
```

### 4.2 Manual SDP Record
```c
record = sdp_record_alloc();
sdp_uuid16_create(&svc_uuid, AUDIO_SINK_SVCLASS_ID);
sdp_set_service_classes(record, sdp_list_append(NULL,&svc_uuid));
/* L2CAP + AVDTP proto desc list omitted for brevity */
sdp_record_register(sess, record, 0);
```

### 4.3 L2CAP Sockets
```c
/* Signalling */
int sig_srv = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
struct sockaddr_l2 loc = { AF_BLUETOOTH, htobs(0x0019), *BDADDR_ANY };
bind(sig_srv,(void*)&loc,sizeof(loc)); listen(sig_srv,1);
int sig_cli = accept(sig_srv,NULL,NULL); // phone connects
```

### 4.4 Parsing AVDTP Messages
```c
uint8_t hdr = pkt[0];
uint8_t msg_type = hdr & 0x03;      // Command / Response
uint8_t signal_id = pkt[1] >> 2;    // Discover=1, GetCaps=2, ...
```
Respond with properly-formatted headers (`label`, `packet_type`, etc.).

### 4.5 Opening Media Channel
1. On **OPEN** command, create or accept a second L2CAP channel on PSM 0x1B.
2. Store MTU for packet boundaries.

### 4.6 SBC Decoding → ALSA
```c
sbc_init(&sbc, 0);
ssize_t n = recv(media_sock, buf, mtu, 0);
if (n>12) {
    size_t decoded;
    sbc_decode(&sbc, buf+12, n-12, pcm_buf, sizeof(pcm_buf), &decoded);
    snd_pcm_writei(pcm, pcm_buf, decoded/(2*channels));
}
```

### 4.7 Thread Model
* **Main thread**: HCI + SDP setup.
* **Signalling thread**: manage AVDTP state.
* **Media thread**: decode & play audio.
* Protect shared flags (`streaming`) with mutex or atomic.

### 4.8 Error Handling Tips
* Handle `EPIPE` underrun from ALSA → `snd_pcm_prepare()`.
* Re-init `sbc` on configuration changes.
* MTU > 672? ensure buffer large enough.

---

## 5. Building & Running
```bash
sudo apt-get install build-essential libbluetooth-dev libsbc-dev libasound2-dev

gcc raw_a2dp.c -lbluetooth -lasound -lsbc -lpthread -o raw_a2dp
sudo setcap cap_net_raw+ep ./raw_a2dp   # or run as root
sudo ./raw_a2dp
```
On the phone: Settings → Bluetooth → select **Linux_A2DP_Sink** → Pair → Play YouTube.

---

## 6. Testing Checklist
- [ ] Device advertises A2DP service in SDP (`sdptool records local`)
- [ ] Phone connects L2CAP PSM 0x19 then 0x1B (see `btmon`)
- [ ] AVDTP `Start` received, media thread running
- [ ] ALSA playback buffer fills; hear audio

Common Problems | Fix
-----------------|----
`Host is down`   | Check rfkill, power on adapter
No audio         | Verify SBC decode path, ALSA device name
Choppy sound     | Increase ALSA buffer, prioritize thread, use real-time scheduling

---

## 7. Further Reading
* **Bluetooth Core Spec** (esp. Vol 4, Part B – AVDTP)
* **BlueKitchen BTstack** – has minimal A2DP example in C
* **libsbc source** – reference SBC decoder
* **ALSA PCM API Guide** – low-latency audio

---

© 2025 Raw A2DP Guide. Free to use and modify.