#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Initialize vector */
void vector_init(vector_t *v)
{
    v->data = NULL;
    v->size = 0;
    v->count = 0;
    v->free_slot = 0;
}

/* Push element to vector, returns index */
int32_t vector_push(vector_t *v, void *ptr)
// What does this function do?
// Adds an element (ptr) to v
{
    // Execute when v->size == 0
    if (!v->size) {
        v->size = VECTOR_MIN_SIZE;
        v->data = /* A01 */;
        // What does this line do?
        // Allocates memory for the first level of data
    }

    /* Reuse free slot if available */
    if (v->free_slot && v->free_slot < v->count) {
        size_t idx = /* A02 */;
        v->data[idx] = ptr;
        // Where do I store ptr within data?
        // Store into the available space in data
        v->free_slot = 0;
        return idx;
    }

    /* Resize if needed */
    // Execute when space is insufficient
    if (v->count == v->size) {
        v->size *= 2;
        // If size doubles, data space must also double
        v->data = /* A03 */;
        memset(v->data + v->count, 0, (v->size - v->count) * sizeof(void *));
    }

    // Normally enters this block
    v->data[v->count] = ptr;
    return v->count++;
}

/* Pop last element */
void *vector_pop(vector_t *v)
{
    if (!v->count)
        return NULL;
    void *last = /* A04 */;
    v->data[v->count] = NULL;
    return last;
}

/* Get element at index */
void *vector_get_at(vector_t *v, size_t index)
{
    return (index < v->count) ? v->data[index] : NULL;
}

/* Set element at index (replaces existing) */
void *vector_set_at(vector_t *v, size_t index, void *ptr)
{
    if (index >= v->count)
        return NULL;
    v->data[index] = ptr;
    return ptr;
}

/* Get last element */
void *vector_get_end(vector_t *v)
{
    return v->count ? v->data[v->count - 1] : NULL;
}

/* Delete at index (creates hole) */
void vector_delete_at(vector_t *v, size_t index)
{
    if (index < v->count) {
        v->data[index] = NULL;
        v->free_slot = index;
    }
}

/* Iterate over elements */
void *vector_for_each(vector_t *v, vector_foreach_callback_t cb, void *data)
{
    if (!cb)
        return NULL;

    for (size_t i = 0; i < v->count; i++) {
        if (! /* A05 */ )
            continue;

        void *ret = /* A06 */;
        if (ret)
            return ret;
    }
    return NULL;
}

/* Delete all elements */
void vector_delete_all(vector_t *v, vector_delete_callback_t dc)
{
    for (void *p; (/* A07 */);) {
        if (dc)
            /* A08 */;
    }
}

/* Free vector memory */
void vector_free(vector_t *v)
{
    if (!v->data)
        return;

    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->count = 0;
    v->free_slot = 0;
}

/* Get number of elements */
size_t vector_used(vector_t *v)
{
    return v->count;
}
