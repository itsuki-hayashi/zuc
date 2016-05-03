#include "zuc.h"
#include <stdio.h>
#include <string.h>
#include <immintrin.h>
#include <Windows.h>
int main() {
    uint8_t key[16], iv[16];
    uint32_t buffer[1024 / 4];
    zuc_context context;
    /*
    _rdseed64_step((uint64_t*)&key[0]);
    _rdseed64_step((uint64_t*)&key[8]);
    _rdseed64_step((uint64_t*)&iv[0]);
    _rdseed64_step((uint64_t*)&iv[8]);
    */
    memset(key, 0, 16);
    memset(iv, 0, 16);
    /*
    const uint64_t begin = GetTickCount64();
    for (uint64_t i = 0; i < 1024 * 10240; ++i) {
        zuc_generate_keystream(&context, buffer, 1024 / 4);
    }
    const int64_t end = GetTickCount64();
    
        printf("%llu\n", end - begin);
    */
    zuc_generate_keystream(zuc_init(&context, key, iv), buffer, 1024 / 4);
    printf("%x, %x\n", buffer[0], buffer[1]); // 27bede74, 18082da
    
}
