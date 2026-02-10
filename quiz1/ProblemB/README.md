# Problem B: uf8 Codec

## Description

Assume `uf8` implements a logarithmic 8-bit codec that maps 20-bit unsigned integers $[0, 1,015,792]$ to 8-bit symbols via logarithmic quantization, delivering 2.5:1 compression and $\le 6.25\%$ relative error.

The `uf8` encoding scheme is ideal for sensor data applications such as temperature and distance measurements where range is more important than precision. In graphics applications, it efficiently represents level-of-detail (LOD) distances and fog density values. The scheme is also well-suited for timer implementations that use exponential backoff strategies. However, the `uf8` encoding should not be used for financial calculations where exact precision is required and rounding errors are unacceptable. It is inappropriate for cryptographic applications that require uniform distribution of values for security purposes.

### Decode

$$
D(b) = m \cdot 2^e + (2^e - 1) \cdot 16
$$

Where:
- $e = \lfloor b/16 \rfloor$
- $m = b \bmod 16$

### Encode

$$
E(v) = \begin{cases}
v, & \text{if } v < 16 \\
16e + \lfloor(v - \text{offset}(e))/2^e\rfloor, & \text{otherwise}
\end{cases}
$$

Where:
$$
\text{offset}(e) = (2^e - 1) \cdot 16
$$

### Error Analysis

-   **Absolute Error**: $\Delta_{\max} = 2^e - 1$
-   **Relative Error**: $\varepsilon_{\max} = 1/16 = 6.25\%$
-   **Expected Error**: $\mathbb{E}[\varepsilon] \approx 3\%$

### Information Theory

-   **Input Entropy**: 20 bits
-   **Output Entropy**: 8 bits
-   **Theoretical Minimum**: 7.6 bits (for 6.25% error bound)
-   **Efficiency**: 8/7.6 = 95% optimal

### Range Table

| Exponent | Range | Step Size |
| :--- | :--- | :--- |
| 0 | [0, 15] | 1 |
| 1 | [16, 46] | 2 |
| 2 | [48, 108] | 4 |
| 3 | [112, 232] | 8 |
| ... | ... | ... |
| 15 | [524,272, 1,015,792] | 32768 |

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
=== Running uf8 Tests ===
All tests passed.
```

### Cleaning

To clean up build artifacts:

```bash
make clean
```
