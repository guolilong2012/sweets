#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <linux/skbuff.h>

struct sock *g_nl_kernel_sock = NULL;

void nl_kernel_recv(struct sk_buff *skb)
{
    struct nlmsghdr *nlh = nlmsg_hdr(skb);
    unsigned int skb_data_len = skb->len;
    struct sk_buff *nl_skb = NULL;
    const char msg[] = "kernel";
    unsigned int dest_pid = 0;

    printk("=======Recv from user=======\n");

    if (NLMSG_OK(nlh, skb_data_len))
    {
        printk("nlmsg_len = <%u>\n", nlh->nlmsg_len);
        printk("nlmsg_type = <%u>\n", nlh->nlmsg_type);
        printk("nlmsg_flags = <%u>\n", nlh->nlmsg_flags);
        printk("nlmsg_seq = <%u>\n", nlh->nlmsg_seq);
        printk("nlmsg_pid = <%u>\n", nlh->nlmsg_pid);
        printk("nlmsg_data = <%s>\n", (char *)NLMSG_DATA(nlh));
        dest_pid = nlh->nlmsg_pid;
    }
    else
    {
        printk("Recv nlmsghdr len error\n");
        return;
    }

    nl_skb = alloc_skb(NLMSG_SPACE(sizeof(msg)), GFP_ATOMIC);
    if (!nl_skb)
    {
        printk("alloc_skb error\n");
        return;
    }

    nlh = nlmsg_put(nl_skb, 0, 0, 0, NLMSG_ALIGN(sizeof(msg)), 0);
    if (!nlh)
    {
        printk("nlmsg_put error\n");
        return;
    }
    NETLINK_CB(nl_skb).pid = 0;
    memcpy((char *)NLMSG_DATA(nlh), msg, sizeof(msg));

    netlink_unicast(g_nl_kernel_sock, nl_skb, dest_pid, MSG_DONTWAIT);

    return;
}

static int nl_kernel_init(void)
{
    g_nl_kernel_sock = netlink_kernel_create(&init_net, 27, 1, nl_kernel_recv, NULL, THIS_MODULE);
    if (!g_nl_kernel_sock)
    {
        printk("nl_kernel init failed!\n");
        return -1;
    }
    printk("nl_kernel init ok!\n");

    return 0;
}

static void nl_kernel_exit(void)
{
    if (g_nl_kernel_sock)
    {
        sock_release(g_nl_kernel_sock->sk_socket);
        netlink_kernel_release(g_nl_kernel_sock);
        g_nl_kernel_sock = NULL;
    }
    printk("nl_kernel exit ok!\n");
}

module_init(nl_kernel_init);
module_exit(nl_kernel_exit);

MODULE_LICENSE("Dual BSP/GPL");
MODULE_AUTHOR("Guo Lilong");
MODULE_DESCRIPTION("");
MODULE_VERSION("");
MODULE_ALIAS("");
