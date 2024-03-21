#include "syshead.h"
#include "basic.h"
#include "ethernet.h"

struct eth_hdr* init_eth_hdr(char* buf) {
    struct eth_hdr* hdr = (struct eth_hdr* )buf;
    // Convert ethertype from host to network byte order
    hdr->ethertype = htons(hdr->ethertype);
    return hdr;
}