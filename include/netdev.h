#ifndef NET_DEV_H_
#define NET_DEV_H_

#include "syshead.h"
#include "ethernet.h"

struct netdev {
    uint32_t addr;
    uint8_t hwaddr[6];
};

void netdev_init(struct netdev* dev, char* addr, char* hwaddr);
void netdev_transmit(struct netdev* dev, struct eth_hdr* hdr, uint16_t ethertype, int len, uint8_t* dst);
#endif // NET_DEV_H_