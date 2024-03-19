#ifndef UTILS_H_
#define UTILS_H_

#define CMDBUFLEN 100

int run_cmd(char* cmd, ...);
void print_hexdump(char* str, int len);

#endif // UTILS_H_