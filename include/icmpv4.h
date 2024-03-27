#ifndef ICMPV4_H_
#define ICMPV4_H_

#include "syshead.h"
#include "netdev.h"

void icmpv4_incoming(struct netdev* dev, struct eth_hdr* hdr);

#endif // ICMPV4_H_