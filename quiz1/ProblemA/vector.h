#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdint.h>

#define VECTOR_MIN_SIZE 16

typedef struct {
    void **data;
    size_t size;      /* Allocated size */
    size_t count;     /* Number of elements */
    size_t free_slot; /* Index of a known hole */
} vector_t;

typedef void (*vector_delete_callback_t)(void *);
typedef void *(*vector_foreach_callback_t)(void *, void *);

/* Initialize vector */
void vector_init(vector_t *v);

/* Push element to vector, returns index */
int32_t vector_push(vector_t *v, void *ptr);

/* Pop last element */
void *vector_pop(vector_t *v);

/* Get element at index */
void *vector_get_at(vector_t *v, size_t index);

/* Set element at index (replaces existing) */
void *vector_set_at(vector_t *v, size_t index, void *ptr);

/* Get last element */
void *vector_get_end(vector_t *v);

/* Delete at index (creates hole) */
void vector_delete_at(vector_t *v, size_t index);

/* Iterate over elements */
void *vector_for_each(vector_t *v, vector_foreach_callback_t cb, void *data);

/* Delete all elements */
void vector_delete_all(vector_t *v, vector_delete_callback_t dc);

/* Free vector memory */
void vector_free(vector_t *v);

/* Get number of elements */
size_t vector_used(vector_t *v);

#endif /* VECTOR_H */
