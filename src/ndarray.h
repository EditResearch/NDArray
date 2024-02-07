#ifndef _NDARRAY_H_
#define _NDARRAY_H_

#include <stdint.h>
#include <stddef.h>


#define ND_Array(T) T


typedef struct ND_Array ND_Array;


struct ND_Array
{
    size_t dtype;
    uint32_t ndim;
    size_t size;
    uint32_t * shape;
};


#define ND_ARRAY(T)((ND_Array*) T-1)


ND_Array(void) * 
ndarray_new(
     size_t dtype
    , uint32_t ndim
    , uint32_t * shape);


#define ndarray(type, shape) \
    ndarray_new(sizeof(type), sizeof(shape)/sizeof(*shape), shape)


ND_Array(void) *
ndarray_new_from_array(
    size_t dtype
    , uint32_t ndim
    , uint32_t * shape
    , void * data);


#define ndarray_from_array(shape, data)   \
    ndarray_new_from_array(               \
        sizeof(*data)                     \
        , (sizeof(shape)/sizeof(*shape))  \
        , shape                           \
        , data)



ND_Array(void) *
ndarray_clone(ND_Array * self);


void
ndarray_delete(ND_Array * self);


#endif
