#include "syshead.h"
#include "basic.h"
#include "utils.h"
#include "tuntap_if.h"
#include "ethernet.h"
#include "arp.h"

#define BUFLEN 100

void handle_frame(int tun_fd, struct eth_hdr* hdr) {
    switch (hdr->ethertype)
    {
    case ETH_P_ARP:
        arp_incoming(tun_fd, hdr);
        break;
    case ETH_P_IP:
        printf("Found IPv4\n");
        break;
    case ETH_P_IPV6:
        printf("Found IPv6\n");
        break;
    default:
        printf("Unrecognized ethertype %x\n", hdr->ethertype);
        break;
    }
}

int main(int argc, char** argv) {
    int tun_fd;
    char buf[BUFLEN];

    char *dev = calloc(10, 1);
    tun_fd = tun_alloc(dev);
    CLEAR(buf);
    if (set_if_up(dev) != 0) {
        print_error("ERROR when setting up if\n");
    }

    if (set_if_address(dev, "10.0.0.5/24") != 0) {
        print_error("ERROR when setting address for if\n");
    };

    if (set_if_route(dev, "10.0.0.0/24") != 0) {
        printf("ERROR when setting route for if\n");
    }
    // if (set_if_route(dev, "default via 10.0.0.1") != 0) {
    //     print_error("ERROR when setting default route for if\n");
    // }
    arp_init();
    while (1)
    {
        read(tun_fd, buf, BUFLEN);
        struct eth_hdr* eth_hdr = init_eth_hdr(buf);
        handle_frame(tun_fd, eth_hdr);
    }
    free(dev);
}
