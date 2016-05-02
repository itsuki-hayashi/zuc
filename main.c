#include "zuc.h"
#include <stdio.h>
int main() {
    uint8_t key[16], iv[16];
    uint32_t buffer[16];
    zuc_context context;
    for (int i = 0; i < 16; ++i) {
        key[i] = 0;
        iv[i] = 0;
        buffer[i] = 0;
    }
    zuc_init(&context, key, iv);
    zuc_generate_keystream(&context, buffer, 16);
    printf("%08x,%08x\n", buffer[0], buffer[1]); // Expect: "27bede74,018082da"
}
