#ifndef TUN_TAP_H_
#define TUN_TAP_H_

void tun_init(char* dev);
int tun_read(char* buf, int len);
int tun_write(char* buf, int len);

#endif // TUN_TAP_H_