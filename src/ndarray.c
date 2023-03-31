#include "ndarray.h"

#include <stdlib.h>
#include <string.h>


#define ND_ARRAY_NO_EXPORT static


ND_ARRAY_NO_EXPORT size_t
ndarray_compute_length(
    uint32_t ndim
    , uint32_t * shape)
{
    size_t length = shape[0];

    for(uint32_t i = 1; i < ndim; i++)
        length *= shape[i];

    return length;
}   


ND_Array(void) * 
ndarray_new(
    size_t type_size
    , uint32_t ndim
    , uint32_t * shape
    , ND_ArrayDelete delete)
{
    size_t length   = ndarray_compute_length(ndim, shape);
    ND_Array * self = malloc(sizeof(ND_Array) + (type_size*length));

    if(self != NULL)
    {
        *self = (ND_Array)
            {
                .type_size = type_size
                , .ndim      = ndim
                , .delete    = delete
                , .shape     = malloc(sizeof(uint32_t) * ndim)
            };

        memcpy(self->shape, shape, sizeof(uint32_t) * ndim); 
    }

    return self + 1;
}


ND_Array(void) *
ndarray_new_from_array(
    size_t type_size
    , uint32_t ndim
    , uint32_t * shape
    , void * data
    , ND_ArrayDelete delete)
{
    size_t length   = ndarray_compute_length(ndim, shape);
    ND_Array * self = malloc(sizeof(ND_Array) + (type_size*length));

    if(self != NULL)
    {
        *self = (ND_Array) 
            {
                .type_size = type_size
                , .ndim      = ndim
                , .delete    = delete
                , .shape     = malloc(sizeof(uint32_t) * ndim)
            };

        memcpy(self->shape, shape, sizeof(uint32_t) * ndim); 
        memcpy(self+1, data, type_size*length);
    }

    return self + 1;
}


size_t 
ndarray_length(ND_Array * self)
{
    return ndarray_compute_length(self->ndim, self->shape);
}


ND_Array(void) *
ndarray_clone(ND_Array * self)
{
    if(self == NULL)
        return NULL;

    return ndarray_new_from_array(
            self->type_size
            , self->ndim
            , self->shape
            , self+1
            , self->delete);
}


void
ndarray_delete(ND_Array * self)
{
    if(self != NULL)
        self->delete(self);
}


void
ndarray_delete_default(ND_Array * self)
{
    free(self->shape);
    free(self);
}


