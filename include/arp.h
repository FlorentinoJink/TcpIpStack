#ifndef ARP_H_
#define ARP_H_

#include "syshead.h"
#include "ethernet.h"

void arp_incoming(struct eth_hdr* hdr);

#endif // ARP_H_