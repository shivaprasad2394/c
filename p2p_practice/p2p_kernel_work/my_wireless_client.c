#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// Netlink headers
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>

// Define the same family and command enums as in the kernel module
// In a real project, these would ideally be in a shared header file.
enum my_wireless_commands {
    MY_CMD_UNSPEC,
    MY_CMD_FIND_WIPHY,
    __MY_CMD_MAX,
};
#define MY_CMD_MAX (__MY_CMD_MAX - 1)

enum my_wireless_attributes {
    MY_ATTR_UNSPEC,
    MY_ATTR_MESSAGE,
    __MY_ATTR_MAX,
};
#define MY_ATTR_MAX (__MY_ATTR_MAX - 1)


// Callback function for receiving messages from the kernel
static int msg_handler(struct nl_msg *msg, void *arg)
{
    struct nlattr *attrs[MY_ATTR_MAX + 1];
    struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));

    printf("Received message from kernel (command: %d):\n", gnlh->cmd);

    // Parse attributes if any
    genlmsg_parse(gnlh, 0, attrs, MY_ATTR_MAX, NULL);

    if (attrs[MY_ATTR_MESSAGE]) {
        printf("  Attribute MY_ATTR_MESSAGE: %s\n", nla_get_string(attrs[MY_ATTR_MESSAGE]));
    }

    // In a real application, you would process the data here.

    return NL_OK; // Continue processing messages
}

int main(int argc, char *argv[])
{
    struct nl_sock *sock;
    struct nl_msg *msg;
    int family_id;
    int rc;

    printf("Starting Netlink client...\n");

    // Allocate a new Netlink socket
    sock = nl_socket_alloc();
    if (!sock) {
        fprintf(stderr, "ERROR: Failed to allocate Netlink socket.\n");
        return -1;
    }

    // Connect the socket to the generic Netlink family
    rc = genl_connect(sock);
    if (rc < 0) {
        fprintf(stderr, "ERROR: Failed to connect to generic Netlink: %s\n", nl_geterror(rc));
        nl_socket_free(sock);
        return -1;
    }

    // Resolve the Netlink family ID for our custom family name
    family_id = genl_ctrl_resolve(sock, "my_wireless_family");
    if (family_id < 0) {
        fprintf(stderr, "ERROR: Failed to resolve Netlink family 'my_wireless_family': %s\n", nl_geterror(family_id));
        fprintf(stderr, "Ensure the kernel module 'my_wireless_module' is loaded.\n");
        nl_socket_free(sock);
        return -1;
    }
    printf("Resolved family 'my_wireless_family' ID: %d\n", family_id);


    // Allocate a new Netlink message
    msg = nlmsg_alloc();
    if (!msg) {
        fprintf(stderr, "ERROR: Failed to allocate Netlink message.\n");
        nl_socket_free(sock);
        return -1;
    }

    // Add the generic Netlink header to the message
    // genlmsg_put(msg, pid, seq, family_id, hdrlen, flags, cmd, version)
    genlmsg_put(msg, 0, 0, family_id, 0, 0, MY_CMD_FIND_WIPHY, 0);


    // (Optional) Add attributes to the message if the command requires them
    // int nla_put_u32(struct nl_msg *msg, int attrtype, u32 value);
    // int nla_put_string(struct nl_msg *msg, int attrtype, const char *str);
    // rc = nla_put_string(msg, MY_ATTR_MESSAGE, "Hello from userspace!");
    // if (rc < 0) {
    //     fprintf(stderr, "ERROR: Failed to put attribute in message: %s\n", nl_geterror(rc));
    //     nlmsg_free(msg);
    //     nl_socket_free(sock);
    //     return -1;
    // }


    // Send the message to the kernel
    rc = nl_send_auto(sock, msg);
    if (rc < 0) {
        fprintf(stderr, "ERROR: Failed to send Netlink message: %s\n", nl_geterror(rc));
        nlmsg_free(msg); // nl_send_auto frees on success, but explicitly free on send error
        nl_socket_free(sock);
        return -1;
    }
    printf("Netlink message sent successfully (bytes: %d).\n", rc);
    nlmsg_free(msg); // Message is freed by nl_send_auto after successful send


    // Set the message handler for receiving responses
    nl_socket_modify_cb(sock, NL_CB_MSG_IN, NL_CB_CUSTOM, msg_handler, NULL);

    // Receive messages from the kernel
    printf("Waiting for response from kernel...\n");
    rc = nl_recvmsgs_default(sock);
    if (rc < 0) {
        fprintf(stderr, "ERROR: Failed to receive Netlink messages: %s\n", nl_geterror(rc));
        // Continue to cleanup
    }

    // Clean up
    nl_socket_free(sock);
    printf("Client finished.\n");

    return 0;
}
