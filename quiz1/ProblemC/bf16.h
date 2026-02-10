#ifndef BF16_H
#define BF16_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t bits;
} bf16_t;

bf16_t f32_to_bf16(float val);
float bf16_to_f32(bf16_t val);

bf16_t bf16_add(bf16_t a, bf16_t b);
bf16_t bf16_sub(bf16_t a, bf16_t b);
bf16_t bf16_mul(bf16_t a, bf16_t b);
bf16_t bf16_div(bf16_t a, bf16_t b);
bf16_t bf16_sqrt(bf16_t a);

bool bf16_isnan(bf16_t a);
bool bf16_isinf(bf16_t a);
bool bf16_iszero(bf16_t a);

#endif /* BF16_H */
