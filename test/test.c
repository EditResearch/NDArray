#include <stdio.h>
#include <stdlib.h>

#include "../src/ndarray.h"


int 
main(void) {
    ND_Array(float) (*t)[5] =  ndarray_from_array(
                                    ((uint32_t[]){2, 5}), 
                                    ((float[]) {1,2,3,4,5
                                              ,2,5,4,5,8}));

    printf(
        "ND_Array(float) {dtype = %ld, ndim = %d, size = %ld, shape = ["
        , ND_ARRAY(t)->dtype
        , ND_ARRAY(t)->ndim
        , ND_ARRAY(t)->size);
        
    for(uint32_t i = 0; i < ND_ARRAY(t)->ndim; i++)
        printf((i == 0 ? "%d" : ", %d"), ND_ARRAY(t)->shape[i]);

    printf("], data = [");

    for(uint32_t i = 0; i < ND_ARRAY(t)->shape[0]; i++) {
        printf("[");

        for(uint32_t j = 0; j < ND_ARRAY(t)->shape[1]; j++)
            printf((j == 0 ? "%f" : ", %f"), t[i][j]);

        printf(i < (ND_ARRAY(t)->shape[0]-1) ? "], " : "]");
    }

    printf("]}\n");

    ndarray_delete(ND_ARRAY(t));
    
    printf("program exit...\n");
    return EXIT_SUCCESS;
}


