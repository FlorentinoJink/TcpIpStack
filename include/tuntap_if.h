#ifndef TUN_TAP_H_
#define TUN_TAP_H_

int set_if_route(char *dev, char *cidr);
int set_if_address(char *dev, char *cidr);
int set_if_up(char *dev);
int tun_alloc(char *dev);

#endif // TUN_TAP_H_