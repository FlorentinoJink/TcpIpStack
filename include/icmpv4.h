#ifndef ICMPV4_H_
#define ICMPV4_H_

#include "syshead.h"
#include "netdev.h"

#define ICMP_V4_REPLY           0x00
#define ICMP_V4_DST_UNREACHABLE 0x03
#define ICMP_V4_SRC_QUENCH      0x04
#define ICMP_V4_REDIRECT        0x05
#define ICMP_V4_ECHO            0x08
#define ICMP_V4_ROUTER_ADV      0x09
#define ICMP_V4_ROUTER_SOL      0x0a
#define ICMP_V4_TIMEOUT         0x0b
#define ICMP_V4_MALFORMED       0x0c

struct icmp_v4 {
    uint8_t type;
    uint8_t code;
    uint16_t csum;
    uint8_t data[];
} __attribute__((packed));

struct icmp_v4_echo {
    uint16_t id;
    uint16_t seq;
    uint8_t data[];
} __attribute__((packed));

struct icmp_v4_dst_unreachable {
    uint8_t unused;
    uint8_t len;
    uint16_t var;
    uint8_t data[];
} __attribute__((packed));

void icmpv4_incoming(struct netdev* netdev, struct eth_hdr* hdr);
void icmpv4_reply(struct netdev* netdev, struct eth_hdr* hdr);

#endif // ICMPV4_H_