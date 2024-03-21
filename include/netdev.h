#ifndef NET_DEV_H_
#define NET_DEV_H_

#include "syshead.h"

struct netdev {
    struct in_addr addr;
    unsigned char hw_addr[6];
};

void netdev_init(struct netdev* dev, char* addr, char* hwaddr);

#endif // NET_DEV_H_