#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "basic.h"

#include "utils.h"
#include "tuntap_if.h"

int main(int argc, char** argv) {
    int tun_fd;
    char buf[1024];

    char *dev = calloc(10, 1);
    tun_fd = tun_alloc(dev);
    CLEAR(buf);
    if (set_if_up(dev) != 0) {
        printf("ERROR when setting up if\n");
    }

    if (set_if_address(dev, "10.0.0.5/24") != 0) {
        printf("ERROR when setting address for if\n");
    };

    // if (set_if_route(dev, "10.0.0.0/24") != 0) {
    //     printf("ERROR when setting route for if\n");
    // }
    if (set_if_route(dev, "default via 10.0.0.1") != 0) {
        printf("ERROR when setting default route for if\n");
    }
    while (1)
    {
        int size = read(tun_fd, buf, 1024);
        printf("Return size:%d\n", size);
        print_hexdump(buf, size);
    }
    free(dev);
}
