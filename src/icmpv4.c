#include "icmpv4.h"
#include "ipv4.h"
#include "utils.h"

void icmpv4_incoming(struct netdev* netdev, struct eth_hdr* hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;
    struct icmp_v4* icmp = (struct icmp_v4*)iphdr->data;

    //TODO: checksum
    char str_ip[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN定义了一个IPv4地址所需的最大字符串长度

    switch (icmp->type)
    {
    // case ICMP_V4_REPLY:
    //     printf("ICMP_V4_REPLY");
    //     if (inet_ntop(AF_INET, &iphdr->saddr, str_ip, sizeof(str_ip)) == NULL) {
    //         perror("inet_ntop failed"); // 如果转换失败，输出错误信息
    //     } else {
    //         printf("ICMP_V4_REPLY: src addr: %s\n", str_ip);
    //     }
    //     break;

    case ICMP_V4_ECHO:
        // 使用inet_ntop函数进行转换
        if (inet_ntop(AF_INET, &iphdr->saddr, str_ip, sizeof(str_ip)) == NULL) {
            perror("inet_ntop failed"); // 如果转换失败，输出错误信息
        } else {
            printf("ICMP_V4_ECHO: src addr: %s\n", str_ip);
        }
        icmpv4_reply(netdev, hdr);
        break;
    default:
        perror("ICMPv4 did not match supported types");
        break;
    }
}

void icmpv4_reply(struct netdev* netdev, struct eth_hdr* hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;
    struct icmp_v4* icmp = (struct icmp_v4*)iphdr->data;

    uint16_t icmp_len = iphdr->len - (iphdr->ihl * 4);
    
    icmp->type = ICMP_V4_REPLY;
    icmp->csum = 0;
    icmp->csum = checksum(icmp, icmp_len);
    
    ipv4_outgoing(netdev, hdr);
}