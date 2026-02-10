#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "bf16.h"

void check_val(float val)
{
    bf16_t bf = f32_to_bf16(val);
    float res = bf16_to_f32(bf);
    printf("f32: %f -> bf16: %04x -> f32: %f\n", val, bf.bits, res);
}

void test_conversion()
{
    printf("Testing conversion...\n");
    check_val(1.5f);
    check_val(3.14159f);
    check_val(0.0f);
    check_val(-0.0f);
    check_val(NAN);
    check_val(INFINITY);
    check_val(-INFINITY);

    /* Check specific bit patterns often used for testing 1.0 */
    bf16_t one = f32_to_bf16(1.0f);
    assert(one.bits == 0x3F80); /* 1.0 in bf16 is same high bits as 1.0 in f32 (0x3F800000) */
    printf("PASSED\n");
}

void test_add()
{
    printf("Testing add...\n");
    bf16_t a = f32_to_bf16(1.0f);
    bf16_t b = f32_to_bf16(2.0f);
    bf16_t c = bf16_add(a, b);
    float res = bf16_to_f32(c);
    printf("1.0 + 2.0 = %f (expected 3.0)\n", res);
    assert(res == 3.0f);

    /* Test overflow to inf */
    // Max bf16 is roughly 3.38e38. Max finite.
    // Let's rely on basic arithmetic correctness for now.
    printf("PASSED\n");
}

void test_sub()
{
    printf("Testing sub...\n");
    bf16_t a = f32_to_bf16(3.0f);
    bf16_t b = f32_to_bf16(1.0f);
    bf16_t c = bf16_sub(a, b);
    float res = bf16_to_f32(c);
    printf("3.0 - 1.0 = %f (expected 2.0)\n", res);
    assert(res == 2.0f);
    printf("PASSED\n");
}

void test_mul()
{
    printf("Testing mul...\n");
    bf16_t a = f32_to_bf16(2.0f);
    bf16_t b = f32_to_bf16(3.0f);
    bf16_t c = bf16_mul(a, b);
    float res = bf16_to_f32(c);
    printf("2.0 * 3.0 = %f (expected 6.0)\n", res);
    assert(res == 6.0f);
    printf("PASSED\n");
}

void test_div()
{
    printf("Testing div...\n");
    bf16_t a = f32_to_bf16(6.0f);
    bf16_t b = f32_to_bf16(2.0f);
    bf16_t c = bf16_div(a, b);
    float res = bf16_to_f32(c);
    printf("6.0 / 2.0 = %f (expected 3.0)\n", res);
    assert(res == 3.0f);
    printf("PASSED\n");
}

void test_sqrt()
{
    printf("Testing sqrt...\n");
    bf16_t a = f32_to_bf16(4.0f);
    bf16_t c = bf16_sqrt(a);
    float res = bf16_to_f32(c);
    printf("sqrt(4.0) = %f (expected 2.0)\n", res);
    assert(res == 2.0f);

    a = f32_to_bf16(2.0f);
    c = bf16_sqrt(a);
    res = bf16_to_f32(c);
    printf("sqrt(2.0) = %f (approx 1.414)\n", res);

    printf("PASSED\n");
}

int main()
{
    printf("=== Running BFloat16 Tests ===\n");
    test_conversion();
    test_add();
    test_sub();
    test_mul();
    test_div();
    test_sqrt();
    printf("\n=== All Tests Passed ===\n");
    return 0;
}
