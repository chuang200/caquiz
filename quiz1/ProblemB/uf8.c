#include "uf8.h"

/* Count Leading Zeros */
static inline unsigned clz(uint32_t x)
{
    int n = 32, c = 16;
    do {
        uint32_t y = x >> c;
        if (y) {
            n -= c;
            x = y;
        }
        c >>= 1;
    } while (c);
    return n - x;
}

/* Decode uf8 to uint32_t */
uint32_t uf8_decode(uf8 fl)
{
    uint32_t mantissa = fl & 0x0f;
    uint8_t exponent = fl >> /* B02 */ 4;
    /* B01: Calculate shift for the offset.
     * The offset formula is (2^e - 1) * 16.
     * 0x7FFF is 0111 1111 1111 1111.
     * This bit manipulation seems to construct the term (2^e - 1).
     * 15 - exponent shift gives the mask.
     */
    uint32_t offset = (0x7FFF >> (/* B01 */)) << 4;
    return (/* B03 */ mantissa) + offset;
}

/* Encode uint32_t to uf8 */
uf8 uf8_encode(uint32_t value)
{
    /* Use CLZ for fast exponent calculation */
    if (value < 16)
        return value;

    /* Find appropriate exponent using CLZ hint */
    int lz = clz(value);
    int msb = 31 - lz;

    /* Start from a good initial guess */
    uint8_t exponent = 0;
    uint32_t overflow = 0;

    if (msb >= 5) {
        /* Estimate exponent - the formula is empirical */
        exponent = msb - 4;
        if (exponent > 15)
            exponent = 15;

        /* Calculate overflow for estimated exponent */
        for (uint8_t e = 0; e < exponent; e++)
            overflow = (overflow << 1) + 16;

        /* Adjust if estimate was off */
        while (exponent > 0 && value < overflow) {
            overflow = (/* B04 */ overflow) >> 1;
            exponent--;
        }
    }

    /* Find exact exponent */
    while (exponent < 15) {
        uint32_t next_overflow = (/* B05 */ overflow) + 16;
        if (value < next_overflow)
            break;
        overflow = next_overflow;
        exponent++;
    }

    uint8_t mantissa = /* B06 */ (value - overflow) >> exponent;

    return (/* B07 */ exponent) | mantissa;
}
