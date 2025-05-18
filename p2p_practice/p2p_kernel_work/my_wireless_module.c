#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netlink.h>
#include <net/genetlink.h>
#include <linux/netdevice.h> // For struct net_device
#include <net/cfg80211.h>    // For struct wiphy and wireless_dev

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name"); // Replace with your name
MODULE_DESCRIPTION("A basic kernel module for wireless Netlink interaction");
MODULE_VERSION("0.1");

/* Define the Generic Netlink family */
enum my_wireless_commands {
    MY_CMD_UNSPEC,
    MY_CMD_FIND_WIPHY, /* A simple command to find a wiphy */
    /* Add more commands as needed later */
    __MY_CMD_MAX,
};
#define MY_CMD_MAX (__MY_CMD_MAX - 1)

/* Attributes for the Generic Netlink family (optional for this example) */
enum my_wireless_attributes {
    MY_ATTR_UNSPEC,
    MY_ATTR_MESSAGE, /* A simple message attribute */
    /* Add more attributes as needed later */
    __MY_ATTR_MAX,
};
#define MY_ATTR_MAX (__MY_ATTR_MAX - 1)

/* Command definition */
static const struct genl_ops my_wireless_ops[] = {
    {
        .cmd = MY_CMD_FIND_WIPHY,
        .flags = 0, // Or GENL_ADMIN_PERM for root-only commands
        .policy = NULL, // Attribute policy (not needed for this simple cmd)
        .doit = my_netlink_rx, // The function to handle this command
        .dumpit = NULL, // For dump commands
    },
};

/* Generic Netlink family definition */
static struct genl_family my_wireless_family = {
    .hdrsize = 0,
    .name = "my_wireless_family", // Name of the family
    .version = 1,
    .maxattr = MY_ATTR_MAX,
    .ops = my_wireless_ops,
    .n_ops = ARRAY_SIZE(my_wireless_ops),
};


/*
 * Netlink receive callback function
 * This function is called when a message for MY_CMD_FIND_WIPHY arrives
 */
static int my_netlink_rx(struct sk_buff *skb, struct genl_info *info)
{
    struct sk_buff *msg_skb;
    void *msg_head;
    int rc = 0;
    struct wiphy *wiphy;

    printk(KERN_INFO "my_wireless_module: Received MY_CMD_FIND_WIPHY command from userspace.\n");

    // --- Example Interaction with Wireless Subsystem (Finding a wiphy) ---
    // This is a very basic example. Real interaction for interface creation
    // is much more involved and requires using cfg80211/mac80211 APIs correctly.

    wiphy = NULL;
    rc = -ENODEV; // Assume no device found initially

    // Iterate through all registered wiphy devices
    for_each_wiphy(wiphy) {
        if (wiphy) {
            printk(KERN_INFO "my_wireless_module: Found wiphy device: %s\n", wiphy_name(wiphy));
            rc = 0; // Found at least one
            // In a real scenario, you'd match a specific device or capability
            // break; // Uncomment if you only need the first one
        }
    }

    if (rc != 0) {
         printk(KERN_INFO "my_wireless_module: No wireless devices (wiphy) found.\n");
         // If you need to return an error to userspace, you'd send a status message.
    }


    // --- Example: Sending a simple response back to userspace ---
    msg_skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
    if (!msg_skb) {
        printk(KERN_ERR "my_wireless_module: Failed to allocate Netlink response buffer.\n");
        return -ENOMEM;
    }

    msg_head = genlmsg_put(msg_skb, info->snd_portid, info->snd_seq, &my_wireless_family, 0, MY_CMD_FIND_WIPHY);
    if (!msg_head) {
        printk(KERN_ERR "my_wireless_module: Failed to put Netlink response header.\n");
        nlmsg_free(msg_skb);
        return -ENOMEM;
    }

    // Add an attribute to the response
    rc = nla_put_string(msg_skb, MY_ATTR_MESSAGE, "Processed MY_CMD_FIND_WIPHY");
    if (rc) {
         printk(KERN_ERR "my_wireless_module: Failed to put attribute in response.\n");
         nlmsg_free(msg_skb);
         return rc;
    }


    genlmsg_end(msg_skb, msg_head);

    // Send the message back to the originating userspace process
    // rc = genlmsg_unicast(&init_net, msg_skb, info->snd_portid);
    // Or broadcast to a group if defined
    // rc = genlmsg_multicast_netns(&my_wireless_family, &init_net, 0, MY_NL_MCAST_GROUP, GFP_KERNEL);

    // For this simple example, let's assume we unicast back.
    rc = genlmsg_unicast(genl_info_net(info), msg_skb, info->snd_portid);

    if (rc < 0) {
        printk(KERN_ERR "my_wireless_module: Failed to unicast Netlink response: %d\n", rc);
        // genlmsg_unicast frees the skb on success or error <= 0
        // so we don't need nlmsg_free here if unicast handles it.
    }

    return 0; // Return 0 on success
}


/*
 * Module initialization function
 */
static int __init my_wireless_module_init(void)
{
    int rc;
    printk(KERN_INFO "my_wireless_module: Initializing.\n");

    // Register the generic Netlink family
    rc = genl_register_family(&my_wireless_family);
    if (rc < 0) {
        printk(KERN_ERR "my_wireless_module: Failed to register Netlink family: %d\n", rc);
        return rc;
    }

    printk(KERN_INFO "my_wireless_module: Netlink family '%s' registered (id: %d).\n",
           my_wireless_family.name, my_wireless_family.id);

    return 0;
}

/*
 * Module exit function
 */
static void __exit my_wireless_module_exit(void)
{
    printk(KERN_INFO "my_wireless_module: Exiting.\n");

    // Unregister the generic Netlink family
    genl_unregister_family(&my_wireless_family);
    printk(KERN_INFO "my_wireless_module: Netlink family '%s' unregistered.\n",
           my_wireless_family.name);
}

module_init(my_wireless_module_init);
module_exit(my_wireless_module_exit);
