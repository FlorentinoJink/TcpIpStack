#include "netdev.h"
#include "syshead.h"
#include "basic.h"
#include "ethernet.h"
#include "tuntap_if.h"

void netdev_init(struct netdev* dev, char* addr, char* hwaddr)
{
    CLEAR(*dev);

    if (inet_pton(AF_INET, addr, &dev->addr) != 1)
    {
        perror("ERR: Parsing inet addr failed\n");
        exit(1);
    }
    sscanf(hwaddr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &dev->hwaddr[0],
                                                &dev->hwaddr[1],
                                                &dev->hwaddr[2],
                                                &dev->hwaddr[3],
                                                &dev->hwaddr[4],
                                                &dev->hwaddr[5]);
    printf("ipaddr: %s hwaddr: %s\n", addr, hwaddr);
}

void netdev_transmit(struct netdev* dev, struct eth_hdr* hdr, uint16_t ethertype, int len, unsigned char* dst){
    hdr->ethertype = htons(ethertype);

    memcpy(hdr->smac, dev->hwaddr, 6);
    memcpy(hdr->dmac, dst, 6);

    len += sizeof(struct eth_hdr);

    tun_write((char*)hdr, len);
}