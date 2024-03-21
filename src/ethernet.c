#include "syshead.h"
#include "basic.h"
#include "ethernet.h"

struct eth_hdr* init_eth_hdr(char* buf) {
    struct eth_hdr* hdr = (struct eth_hdr* )buf;
    // Convert ethertype from host to network byte order
    hdr->ethertype = htons(hdr->ethertype);
    return hdr;
}

void print_eth_hdr(struct eth_hdr* hdr) {
    printf("\nPrinting Ethernet hdr:\n");
    printf("Source Mac: ");
    for (int i = 0; i < 6; ++i)
    {
        printf("%x", hdr->src_mac[i]);
    }
    printf("\nDest Mac: ");
    for (int i = 0; i < 6; ++i)
    {
        printf("%x", hdr->dst_mac[i]);
    }
    
    printf("\nEthernet type: %x\n", hdr->ethertype);
}