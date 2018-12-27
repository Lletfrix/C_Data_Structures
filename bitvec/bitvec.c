#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "bitvec.h"

struct bitvec {
    size_t size;
    size_t wordsz;
    int *arr;
};

bitvec *bitvec_new(){
    return malloc(sizeof(bitvec));
}

void bitvec_delete(bitvec *v){
    if(v){
        free(v);
    }
}

bitvec *bitvec_init(bitvec *v, size_t size, int *arr){
    if(v){
        if(size){
            if(arr){
                v->arr = arr;
            }else{
                v->arr = calloc(1,(size+1)/sizeof(int));
                if(!v->arr) v->size = 0;
            }
            v->size = size;
            v->wordsz = sizeof(int)*8;
        }else{
            *v = (bitvec){0};
        }
    }
    return v;
}

void bitvec_destroy(bitvec *v){
    if(v){
        free(v->arr);
        bitvec_init(v, 0);
    }
}

void bitvec_set(bitvec *v, size_t k){
    if(!v || k >= v->size) return;
    if(v->arr) v->arr[k/v->wordsz] |= 1 << (k%v->wordsz);
}

void bitvec_clear(bitvec *v, size_t k){
    if(!v || k >= v->size) return;
    if(v->arr) v->arr[k/v->wordsz] &= ~(1 << (k%v->wordsz));
}

void bitvec_clear_all(bitvec *v){
    if(v){
        if(v->arr){
            memset(v->arr, 0, (size+1)/sizeof(int));
        }
    }
}

int bitvec_test(bitvec *v, size_t k){
    if(!v || k >= v->size || !v->arr){
        errno = EINVAL;
        perror("bitvec_test");
        return 0;
    }
    if(v->arr){
        if((v->arr[k/v->wordsz] & (1 << (k%v->wordsz)))){
            return 1;
        }else{
            return 0;
        }
    }
}
void bitvec_toggle(bitvec *v, size_t k){
    if(v){
        if(bitvec_test(v, k)){
            bitvec_clear(v, k);
        }else{
            bitvec_set(v, k);
        }
    }
}

size_t bitvec_len(bitvec *v){
    if(v){
        return v->size;
    }
    return 0;
}

size_t bitvec_size(bitvec *v){
    if(v){
        return (v->size+1)/sizeof(int);
    }
    return 0;
}

int *bitvec_arr(bitvec *v){
    if(v){
        return memcpy(malloc((size+1)/sizeof(int)),v->arr,(size+1)/sizeof(int));
    }
    return NULL;
}
