#ifndef UF8_H
#define UF8_H

#include <stdint.h>

typedef uint8_t uf8;

/* Decode uf8 to uint32_t */
uint32_t uf8_decode(uf8 fl);

/* Encode uint32_t to uf8 */
uf8 uf8_encode(uint32_t value);

#endif /* UF8_H */
