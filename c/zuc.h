#ifndef __ZUC_H__
#define __ZUC_H__
#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    uint32_t lfsr[16];  // The state registers of LFSR.
    uint32_t r[2];      // The registers of F.
    uint32_t x[4];      // The outputs of the bit-reorganization.
} zuc_context, *pzuc_context;
void zuc_init(pzuc_context context, const uint8_t* key, const uint8_t* iv);
void zuc_generate_keystream(pzuc_context context, uint32_t keystream_buffer[], const size_t keystream_length);
void zuc_encrypt(pzuc_context context, size_t length, const uint8_t* in, uint8_t* out);
#ifdef __cplusplus
}
#endif
#endif
