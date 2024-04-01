#include "ipv4.h"
#include "arp.h"
#include "netdev.h"
#include "icmpv4.h"
#include "utils.h"

void ipv4_incoming(struct netdev* netdev, struct eth_hdr* hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;
    uint16_t csum = -1;

    // char str_ip[INET_ADDRSTRLEN]; // INET_ADDRSTRLEN定义了一个IPv4地址所需的最大字符串长度

    // // 使用inet_ntop函数进行转换
    // if (inet_ntop(AF_INET, &iphdr->saddr, str_ip, sizeof(str_ip)) == NULL) {
    //     perror("inet_ntop failed"); // 如果转换失败，输出错误信息
    // } else {
    //     printf("The string representation of the IP address is: %s\n", str_ip);
    // }

    if (iphdr->version != IPV4)
    {
        perror("Datagram version was not Ipv4\n");
        return;
    }

    if (iphdr->ihl < 5)
    {
        perror("IPv4 header length must be as least 5\n");
        return;
    }
    
    if (iphdr->ttl == 0) {
        //TODO: Send ICMP error
        perror("Time to live of datagram reached 0\n");
        return;
    }

    csum = checksum(iphdr, iphdr->ihl * 4);
    
    if (csum != 0)
    {
        printf("Checksum failed\n");
        // Invalid checksum drop packet handing
        return;
    }

    // TODO: Check fragmentation, possibly reassemble
    iphdr->len = ntohs(iphdr->len);

    switch (iphdr->proto) {
    case ICMPV4:
        printf("icmpv4_incoming: succeed.");
        icmpv4_incoming(netdev, hdr);
        break;
    default:
        // perror("Unknown IP header proto\n");
        return;
    }
}

void ipv4_outgoing(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct iphdr *iphdr = (struct iphdr *)hdr->payload;
    uint32_t tmpaddr;
    uint16_t csum;
    uint8_t len = iphdr->len;

    /* Just swap the source and destination IP addresses,
     * don't bother with ARP lookup just now
     */
    tmpaddr = iphdr->saddr;
    iphdr->daddr = tmpaddr;
    iphdr->saddr = netdev->addr; 

    /*
     * Switch back the necessary fields to Network Byte Order
     */
    iphdr->len = htons(iphdr->len);

    /* Calculate and set datagram checksum */
    iphdr->csum = 0;
    csum = checksum(iphdr, iphdr->ihl * 4);
    iphdr->csum = csum;
    
    netdev_transmit(netdev, hdr, ETH_P_IP, len, hdr->smac);
}