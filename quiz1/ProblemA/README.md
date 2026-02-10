# Problem A: Vector API

## Description

Let's implement a small vector API (Application Programming Interface) that stores arbitrary `void *` values. It makes no assumptions about what the pointers reference or who owns them. If an element points to heap memory, you are responsible for freeing it. The API centers on simple push/pop semantics plus callbacks for processing and destroying elements.

**Notes:**

-   Ownership is explicit: `vector_pop` returns the stored pointer without freeing it; `vector_delete_at` and `vector_delete_all` invoke the optional destructor.
-   `vector_get_end` returns the one-past-the-last index (i.e., current length), which aligns with typical "end" semantics.
-   Growth is automatic and amortized; no assertions are used.

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
=== Running Vector Tests ===
Testing vector_init... PASSED
Testing vector_push and vector_pop... PASSED
Testing vector_get_at... PASSED
Testing vector_delete_at... PASSED
Testing vector_for_each... PASSED
Testing vector_delete_all... PASSED
Testing vector automatic resize... PASSED
Testing vector_get_end... PASSED
Testing vector_set_at... PASSED

=== All Tests Passed ===
```

### Cleaning

To clean up build artifacts:

```bash
make clean
```
