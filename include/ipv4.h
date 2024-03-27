#ifndef IPV4_H_
#define IPV4_H_

#include "syshead.h"
#include "netdev.h"

#define IPV4 0x04

#define ICMPV4 0x01

struct iphdr {
    uint8_t ihl: 4; /* TODO: Support Big Endian hosts*/
    uint8_t version: 4;
    uint8_t tos;
    u_int16_t len;
    uint16_t id;
    uint16_t flags: 3;
    uint16_t flag_offset: 13;
    uint8_t ttl;
    uint8_t proto;
    uint16_t csum;
    uint32_t saddr;
    uint32_t daddr;
    uint8_t data[];
}__attribute__((packed));

void ipv4_incoming(struct netdev* netdev, struct eth_hdr* hdr);

#endif // IPV4_H_