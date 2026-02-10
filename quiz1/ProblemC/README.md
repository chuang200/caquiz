# Problem C: BFloat16

## Description

The `bfloat16` format (16-bit, from Google Brain) preserves float32’s dynamic range by keeping the same 8-bit exponent, but reduces precision to a 7-bit significand (vs. 23).

### Bit Layout

```text
┌─────────┬──────────────┬──────────────┐
│Sign (1) │ Exponent (8) │ Mantissa (7) │
└─────────┴──────────────┴──────────────┘
    15      14           7 6             0

S: Sign bit (0 = positive, 1 = negative)
E: Exponent bits (8 bits, bias = 127)
M: Mantissa/fraction bits (7 bits)
```

The value $v$ of a BFloat16 number is calculated as:

$$
v = (-1)^S \times 2^{E-127} \times \left(1 + \frac{M}{128}\right)
$$

Where:
-   $S \in \{0, 1\}$ is the sign bit
-   $E \in [1, 254]$ is the biased exponent
-   $M \in [0, 127]$ is the mantissa value

### Special Cases

-   **Zero**: $E = 0, M = 0 \Rightarrow v = (-1)^S \times 0$
-   **Infinity**: $E = 255, M = 0 \Rightarrow v = (-1)^S \times \infty$
-   **NaN**: $E = 255, M \neq 0$
-   **Denormals**: Not supported (flush to zero in this implementation)

## Usage

### Building

To build the test executable, run:

```bash
make
```

### Running Tests

To run the tests:

```bash
./test
```

Expect:

```text
=== Running BFloat16 Tests ===
Testing conversion...
f32: 1.500000 -> bf16: 3fc0 -> f32: 1.500000
f32: 3.141590 -> bf16: 4049 -> f32: 3.140625
f32: 0.000000 -> bf16: 0000 -> f32: 0.000000
f32: -0.000000 -> bf16: 8000 -> f32: -0.000000
f32: nan -> bf16: 7fc0 -> f32: nan
f32: inf -> bf16: 7f80 -> f32: inf
f32: -inf -> bf16: ff80 -> f32: -inf
PASSED
Testing add...
1.0 + 2.0 = 3.000000 (expected 3.0)
PASSED
Testing sub...
3.0 - 1.0 = 2.000000 (expected 2.0)
PASSED
Testing mul...
2.0 * 3.0 = 6.000000 (expected 6.0)
PASSED
Testing div...
6.0 / 2.0 = 3.000000 (expected 3.0)
PASSED
Testing sqrt...
sqrt(4.0) = 2.000000 (expected 2.0)
sqrt(2.0) = 1.414062 (approx 1.414)
PASSED

=== All Tests Passed ===
```

### Cleaning

To clean up build artifacts:

```bash
make clean
```
