#include <stdio.h>
#include <stdlib.h>

#include "../src/ndarray.h"


int 
main(void)
{
    ND_Array(float) * t = 
        ndarray(
            float
            , 2, ((uint32_t[]){2, 5})
            , ndarray_delete_default);

    printf(
        "ND_Array(float) {type_size = %ld, ndim = %d, shape = ["
        , ND_ARRAY(t)->type_size
        , ND_ARRAY(t)->ndim);
        
    for(uint32_t i = 0; i < ND_ARRAY(t)->ndim; i++)
        printf((i == 0 ? "%d" : ", %d"), ND_ARRAY(t)->shape[i]);

    printf("], data = [");

    for(uint32_t i = 0; i < ND_ARRAY(t)->shape[0]; i++)
    {
        printf("[");

        for(uint32_t j = 0; j < ND_ARRAY(t)->shape[1]; j++)
            printf((j == 0 ? "%f" : ", %f"), ((float (*)[5]) t)[i][j]);

        printf(i < (ND_ARRAY(t)->shape[0]-1) ? "], " : "]");
    }

    printf("]}\n");

    ndarray_delete(ND_ARRAY(t));
    
    printf("program exit...\n");
    return EXIT_SUCCESS;
}
