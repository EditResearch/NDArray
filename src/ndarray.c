#include "ndarray.h"

#include <stdlib.h>
#include <string.h>


static size_t
__compute_size(
    uint32_t ndim
    , uint32_t * shape) {
    size_t size = shape[0];

    for(uint32_t i = 1; i < ndim; i++)
        size *= shape[i];

    return size;
}   


ND_Array(void) * 
ndarray_new(
    size_t dtype
    , uint32_t ndim
    , uint32_t * shape) {
    size_t size     = __compute_size(ndim, shape);
    ND_Array * self = malloc(sizeof(ND_Array) + (dtype*size) + (sizeof(uint32_t) * ndim));

    if(self != NULL) {
        *self = (ND_Array) {
                .dtype   = dtype
                , .size  = size
                , .ndim  = ndim
                , .shape = (uint32_t *) (((char*) self) + sizeof(ND_Array) + (size * dtype))
            };

        memcpy(self->shape, shape, sizeof(uint32_t) * ndim); 
    }

    return self + 1;
}

#include <stdio.h>

ND_Array(void) *
ndarray_new_from_array(
    size_t dtype
    , uint32_t ndim
    , uint32_t * shape
    , void * data) {
    /*
    size_t size     = __compute_size(ndim, shape);
    ND_Array * self = malloc(sizeof(ND_Array) + (dtype*size) + (sizeof(uint32_t) * ndim));

    if(self != NULL) {
        *self = (ND_Array) {
                .dtype   = dtype
                , .size  = size
                , .ndim  = ndim
                , .shape = (uint32_t*) (((char *) self) + (dtype * size))
            };

        memcpy(self->shape, shape, sizeof(uint32_t) * ndim); 
        memcpy(self+1, data, dtype*size);
    }
    */
    printf("%d\n", shape[1]);

    ND_Array(void) * self = ndarray_new(dtype, ndim, shape);
 
    memcpy(self, data, ND_ARRAY(self)->size * dtype);

    return self;
}


ND_Array(void) *
ndarray_clone(ND_Array * self)
{
    if(self == NULL)
        return NULL;

    return ndarray_new_from_array(
            self->dtype
            , self->ndim
            , self->shape
            , self+1);
}


void
ndarray_delete(ND_Array * self)
{
    if(self != NULL)
        free(self);
}



