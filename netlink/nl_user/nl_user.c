#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> //user sa_family_t
#include <linux/netlink.h>

int main(void)
{
    int ret;
    int sockfd;
    struct sockaddr_nl nl_user_addr;
    struct sockaddr_nl nl_kernel_addr;
    socklen_t nl_kernel_addr_len = sizeof(nl_kernel_addr);
    struct nl_msg {
        struct nlmsghdr hdr;
        char data[10];
    } msg;

    printf("pid = <%d>\n", getpid());

    sockfd = socket(AF_NETLINK, SOCK_RAW, 27);
    if (sockfd < 0)
    {
        fprintf(stderr, "Create socket error!\n");
        return -1;
    }

    memset(&nl_user_addr, 0, sizeof(nl_user_addr));
    nl_user_addr.nl_family = AF_NETLINK;
    nl_user_addr.nl_pid =  getpid();
    nl_user_addr.nl_groups = 0;
    if (bind(sockfd, (struct sockaddr *)&nl_user_addr, sizeof(nl_user_addr)))
    {
        fprintf(stderr, "Bind error\n");
        return -1;
    }

    memset(&nl_kernel_addr, 0, sizeof(nl_kernel_addr));
    nl_kernel_addr.nl_family = AF_NETLINK;
    nl_kernel_addr.nl_pid = 0;
    nl_kernel_addr.nl_groups = 0;

    memset(&msg, 0, sizeof(msg));
    msg.hdr.nlmsg_len = NLMSG_LENGTH(sizeof(msg.data));
    msg.hdr.nlmsg_flags = 0;
    msg.hdr.nlmsg_type = 1;
    msg.hdr.nlmsg_pid = nl_user_addr.nl_pid;
    memcpy(msg.data, "user", 5);

    ret = sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&nl_kernel_addr, sizeof(nl_kernel_addr));
    if (ret < 0)
    {
        fprintf(stderr, "Send error\n");
        return -1;
    }

    ret = recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&nl_kernel_addr, &nl_kernel_addr_len);
    if (ret < 0)
    {
        fprintf(stderr, "Recv error\n");
        return -1;
    }

    printf("======Recv from kernel======\n");
    printf("nlmsg_len = <%u>\n", msg.hdr.nlmsg_len);
    printf("nlmsg_type = <%u>\n", msg.hdr.nlmsg_type);
    printf("nlmsg_flags = <%u>\n", msg.hdr.nlmsg_flags);
    printf("nlmsg_seq = <%u>\n", msg.hdr.nlmsg_seq);
    printf("nlmsg_pid = <%u>\n", msg.hdr.nlmsg_pid);
    printf("nlmsg_data = <%s>\n", msg.data);

    return 0;
}
