#include "zuc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
int main() {
    const uint64_t BUFFER_SIZE = 4096 / sizeof(uint32_t);
    uint8_t key[16], iv[16];
    uint32_t * buffer = calloc(BUFFER_SIZE, sizeof(uint32_t));
    zuc_context context;
    memset(key, 0, 16);
    memset(iv, 0, 16);
    zuc_generate_keystream(zuc_init(&context, key, iv), buffer, 1024 / 4);
    printf("%x, %x\n", buffer[0], buffer[1]); // 27bede74, 18082da
    if (buffer[0] == 0x27bede74 && buffer[1] == 0x18082da) {
        puts("Implemented correctly.");
    }
    else {
        puts("Wrong output");
        exit(EXIT_FAILURE);
    }
    puts("Benchmarking performance.");
    
    const uint64_t TEST_SIZE = 10 * 1024; // 10 * 1024 MiB.
    const uint64_t BEGIN_TIME = GetTickCount64();
    for (uint64_t i = 0; i < (TEST_SIZE * 1024 * 1024) / (sizeof(uint32_t) * BUFFER_SIZE); ++i) {
        zuc_generate_keystream(&context, buffer, BUFFER_SIZE);
    }
    const int64_t TIME_USED = GetTickCount64() - BEGIN_TIME;
    
    printf("Speed: %lfMiB/s\n",((double) TEST_SIZE) / (((double)TIME_USED) / 1000));
    free(buffer);
}
