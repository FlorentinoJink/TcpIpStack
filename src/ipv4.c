#include "ipv4.h"
#include "netdev.h"
#include "icmpv4.h"

void ipv4_incoming(struct netdev* netdev, struct eth_hdr* hdr)
{
    struct iphdr* iphdr = (struct iphdr*)hdr->payload;

    if (iphdr->version != IPV4)
    {
        perror("Datagram version was not Ipv4\n");
        return;
    }
    iphdr->len = ntohs(iphdr->len);
    iphdr->id = ntohs(iphdr->id);
    iphdr->flags = ntohs(iphdr->flags);
    iphdr->csum = ntohs(iphdr->csum);
    iphdr->saddr = ntohs(iphdr->saddr);
    iphdr->daddr = ntohs(iphdr->daddr);
    // printf("%d\n", iphdr->tot_len);
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

    //TODO: Check fragmentation, possibly reassemble

    switch (iphdr->proto)
    {
    case ICMPV4:
        icmpv4_incoming(netdev, hdr);
        break;
    default:
        perror("Unknown IP header proto\n");
        break;
    }
}