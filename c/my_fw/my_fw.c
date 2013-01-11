#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#include "my_fw.h"

//#define HOOK_PRE_ROUTING
#define HOOK_LOCAL_IN
//#define HOOK_FORWARD
#define HOOK_LOCAL_OUT
//#define HOOK_POST_ROUTING

static int g_cnt;

static unsigned int ipv4_aton(const char *ip)
{
    unsigned int n_ip;
    unsigned int buf[4];

    sscanf(ip, "%u.%u.%u.%u", &buf[0], &buf[1], &buf[2], &buf[3]);
    n_ip = (buf[0]<<0) + (buf[1]<<8) + (buf[2]<<16) + (buf[3]<<24);

    return n_ip;
}

static char *ipv4_ntoa(unsigned int ip)
{
    static char buf[16];

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%u.%u.%u.%u", (ip>>0) & 0xff, (ip>>8) & 0xff, (ip>>16) & 0xff, (ip>>24) & 0xff);

    return buf;
}

static void print_sk_buff(unsigned int hooknum, struct sk_buff *skb)
{
    struct ethhdr *ethh = eth_hdr(skb);
    struct iphdr *iph = ip_hdr(skb);
    struct tcphdr *tcph = NULL;
    struct udphdr *udph = NULL;
    int i;
    unsigned short tcp_data_len = 0;
    unsigned char *tcp_data = NULL;
    unsigned short udp_data_len = 0;
    unsigned char *udp_data = NULL;

#if 1
    if (iph->protocol != IPPROTO_TCP)
    {
        return;
    }
#endif

    switch (hooknum)
    {
    case NF_INET_PRE_ROUTING:
        printk("\nPre Routing <%d>\n", ++g_cnt);
        break;

    case NF_INET_LOCAL_IN:
        printk("\nLocal In <%d>\n", ++g_cnt);
        break;

    case NF_INET_FORWARD:
        printk("\nForward <%d>\n", ++g_cnt);
        break;

    case NF_INET_LOCAL_OUT:
        printk("\nLocal Out <%d>\n", ++g_cnt);
        break;

    case NF_INET_POST_ROUTING:
        printk("\nPost Routing <%d>\n", ++g_cnt);
        break;

    default:
        return;
    }

    //mac
    if (ethh)
    {
        printk("Src MAC: <%x:%x:%x:%x:%x:%x>\n", \
            ethh->h_source[0], ethh->h_source[1], ethh->h_source[2], \
            ethh->h_source[3], ethh->h_source[4], ethh->h_source[5]);
        printk("Dest MAC: <%x:%x:%x:%x:%x:%x>\n", \
            ethh->h_dest[0], ethh->h_dest[1], ethh->h_dest[2], \
            ethh->h_dest[3], ethh->h_dest[4], ethh->h_dest[5]);
    }
    else
    {
        printk("ethh = NULL\n");
    }

    //ip
    if (iph)
    {
        printk("Src Ip: <%s>\n", ipv4_ntoa(iph->saddr));
        printk("Dest Ip: <%s>\n", ipv4_ntoa(iph->daddr));

        //TCP、UDP、ICMP、IGMP
        switch (iph->protocol)
        {
        case IPPROTO_ICMP:
            printk("ICMP:\n");
            break;

        case IPPROTO_IGMP:
            printk("IGMP:\n");
            break;

        case IPPROTO_TCP:
            printk("TCP:\n");
            tcph = (struct tcphdr *)(skb->data + iph->ihl * 4);
            printk("Src port: <%u>\n", ntohs(tcph->source));
            printk("Dest port: <%u>\n", ntohs(tcph->dest));
            printk("Seq: <%u>\n", ntohl(tcph->seq));
            printk("Ack seq: <%u>\n", ntohl(tcph->ack_seq));
            printk("urg: <%d>, ack: <%d>\n", tcph->urg, tcph->ack);
            printk("psh: <%d>, rst: <%d>\n", tcph->psh, tcph->rst);
            printk("syn: <%d>, fin: <%d>\n", tcph->syn, tcph->fin);
            //printk("tot len = <%u>\n", ntohs(iph->tot_len));
            //printk("ihl * 4 = <%u>\n", iph->ihl * 4);
            //printk("doff * 4 = <%u>\n", tcph->doff * 4);
            tcp_data_len = ntohs(iph->tot_len) - iph->ihl * 4 - tcph->doff * 4;
            printk("tcp data len = <%u>\n", tcp_data_len);
            if (tcp_data_len > 0)
            {
                tcp_data = skb->data + iph->ihl * 4 + tcph->doff * 4;
                printk("tcp data: ");
                for (i = 0; i < tcp_data_len; i++)
                {
                    printk("%x ", tcp_data[i]);
                }
                printk("\n");
            }
            break;

        case IPPROTO_UDP:
            printk("UDP:\n");
            udph = (struct udphdr *)(skb->data + iph->ihl * 4);
            printk("Src port = <%u>\n", ntohs(udph->source));
            printk("Dest port = <%u>\n", ntohs(udph->dest));
            udp_data_len = ntohs(iph->tot_len) - iph->ihl * 4 - 8;
            printk("udp data len = <%u>\n", udp_data_len);
            if (udp_data_len > 0)
            {
                udp_data = skb->data + iph->ihl * 4 + 8;
                printk("udp data: ");
                for (i = 0; i < udp_data_len; i++)
                {
                    printk("%x ", udp_data[i]);
                }
                printk("\n");
            }
            break;

        default:
            printk("Others protocol <%u>\n", iph->protocol);
        }
    }
    else
    {
        printk("iph = NULL\n");
    }
}

#ifdef HOOK_LOCAL_IN
static unsigned int nf_hook_local_in(unsigned int hooknum,
                                struct sk_buff *skb,
                                const struct net_device *in,
                                const struct net_device *out,
                                int (*okfn)(struct sk_buff *)
                                )
{
    struct iphdr *iph = ip_hdr(skb);
    struct tcphdr *tcph;
    struct udphdr *udph;

    print_sk_buff(hooknum, skb);
    switch (iph->protocol)
    {
    case IPPROTO_ICMP:
        return NF_DROP;

    case IPPROTO_TCP:
        //tcph = tcp_hdr(skb);
        tcph = (struct tcphdr *)(skb->data + iph->ihl * 4);
        if (tcph->dest == htons(667))
        {
            printk("Drop tcp OK!\n");
            return NF_DROP;
        }
        break;

    case IPPROTO_UDP:
        //udph = udp_hdr(skb);
        udph = (struct udphdr *)(skb->data + iph->ihl * 4);
        if (udph->dest == htons(667))
        {
            printk("Drop udp OK!\n");
            return NF_DROP;
        }
        break;

    default:
        return NF_ACCEPT;
    }

    return NF_ACCEPT;
}
#endif

#ifdef HOOK_LOCAL_OUT
static unsigned int nf_hook_local_out(unsigned int hooknum,
                                struct sk_buff *skb,
                                const struct net_device *in,
                                const struct net_device *out,
                                int (*okfn)(struct sk_buff *)
                                )
{
    struct iphdr *iph = ip_hdr(skb);

    print_sk_buff(hooknum, skb);
    if (iph->daddr == ipv4_aton("192.168.1.102"))
    {
        printk("Drop tcp OK!\n");
        return NF_DROP;
    }

    return NF_ACCEPT;
}
#endif

#ifdef HOOK_FORWARD
static unsigned int nf_hook_forward(unsigned int hooknum,
                                    struct sk_buff *skb,
                                    const struct net_device *in,
                                    const struct net_device *out,
                                    int (*okfn)(struct sk_buff *)
                                    )
{
    print_sk_buff(hooknum, skb);

    return NF_ACCEPT;
}
#endif

#ifdef HOOK_PRE_ROUTING
static unsigned int nf_hook_pre_routing(unsigned int hooknum,
                                    struct sk_buff *skb,
                                    const struct net_device *in,
                                    const struct net_device *out,
                                    int (*okfn)(struct sk_buff *)
                                    )
{

    print_sk_buff(hooknum, skb);

    return NF_ACCEPT;
}
#endif

#ifdef HOOK_POST_ROUTING
static unsigned int nf_hook_post_routing(unsigned int hooknum,
                                    struct sk_buff *skb,
                                    const struct net_device *in,
                                    const struct net_device *out,
                                    int (*okfn)(struct sk_buff *)
                                    )
{
    print_sk_buff(hooknum, skb);

    return NF_ACCEPT;
}
#endif

static struct nf_hook_ops hooks[] =
{
    //local in
    #ifdef HOOK_LOCAL_IN
    {
        .hook = nf_hook_local_in,
        .hooknum = NF_INET_LOCAL_IN,
        .pf = PF_INET,
        .priority = NF_IP_PRI_FIRST,
    },
    #endif

    //local out
    #ifdef HOOK_LOCAL_OUT
    {
        .hook = nf_hook_local_out,
        .hooknum = NF_INET_LOCAL_OUT,
        .pf = PF_INET,
        .priority = NF_IP_PRI_FIRST,
    },
    #endif

    //forward
    #ifdef HOOK_FORWARD
    {
        .hook = nf_hook_forward,
        .hooknum = NF_INET_FORWARD,
        .pf = PF_INET,
        .priority = NF_IP_PRI_FIRST,
    },
    #endif

    //pre routing
    #ifdef HOOK_PRE_ROUTING
    {
        .hook = nf_hook_pre_routing,
        .hooknum = NF_INET_PRE_ROUTING,
        .pf = PF_INET,
        .priority = NF_IP_PRI_FIRST,
    },
    #endif

    //post routing
    #ifdef HOOK_POST_ROUTING
    {
        .hook = nf_hook_post_routing,
        .hooknum = NF_INET_POST_ROUTING,
        .pf = PF_INET,
        .priority = NF_IP_PRI_FIRST,
    },
    #endif
};

static int __init init(void)
{
    nf_register_hooks(hooks, sizeof(hooks) / sizeof(struct nf_hook_ops));
    printk("my_fw init successfully !\n");

    return 0;
}

static void __exit exit(void)
{
    nf_unregister_hooks(hooks, sizeof(hooks) / sizeof(struct nf_hook_ops));
    printk("my_fw exit successfully !\n");
}

module_init(init);
module_exit(exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Lilong Guo");
MODULE_DESCRIPTION("Netfilter demo");
MODULE_VERSION("0.0.0.0");

