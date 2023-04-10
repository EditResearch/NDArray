#ifndef _NDARRAY_H_
#define _NDARRAY_H_

#include <stdint.h>
#include <stddef.h>


#define ND_Array(T) T


typedef struct ND_Array ND_Array;


typedef void (*ND_ArrayDelete)(ND_Array *);


#define ND_ARRAY_DELETE(T)((ND_ArrayDelete) T)


struct ND_Array
{
    size_t type_size;
    uint32_t ndim;
    uint32_t * shape;
    size_t length;

    ND_ArrayDelete delete;
};


#define ND_ARRAY(T)((ND_Array*) T-1)


ND_Array(void) * 
ndarray_new(
     size_t type_size
    , uint32_t ndim
    , uint32_t * shape
    , ND_ArrayDelete delete);


#define ndarray(type, ndim, shape, delete) \
    ndarray_new(sizeof(type), ndim, shape, delete)


ND_Array(void) *
ndarray_new_from_array(
    size_t type_size
    , uint32_t ndim
    , uint32_t * shape
    , void * data
    , ND_ArrayDelete delete);


#define ndarray_from_array(ndim, shape, data, delete)   \
    ndarray_new_from_array(                             \
        sizeof(*data)                                   \
        , ndim                                          \
        , shape                                         \
        , data                                          \
        , delete)


size_t 
ndarray_length(ND_Array * self);


ND_Array(void) *
ndarray_clone(ND_Array * self);


void
ndarray_delete(ND_Array * self);


void
ndarray_delete_default(ND_Array * self);


#endif
