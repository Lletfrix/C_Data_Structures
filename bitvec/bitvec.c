#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitvec.h"

#define BITS 8

struct bitvec {
    size_t size;
    size_t wordsz;
    char *arr;
};

bitvec * bitvec_new(){
    return malloc(sizeof(bitvec));
}

void bitvec_delete(bitvec *v){
    if(v){
        free(v);
    }
}

bitvec * bitvec_init(bitvec *v, size_t size, char *arr){
    if(v){
        if(size){
            v->arr = calloc(1 + (size-1)/BITS, sizeof(char));
            if(arr)
                memcpy(v->arr, arr, (1 + (size-1)/BITS) * sizeof(char));
            if(!v->arr) v->size = 0;
            v->size = size;
            v->wordsz = sizeof(char)*BITS;
        }else{
            *v = (bitvec){0};
        }
    }
    return v;
}

bitvec * bitvec_destroy(bitvec *v){
    if(v){
        free(v->arr);
        bitvec_init(v, 0, NULL);
    }
    return v;
}

bitvec * bitvec_resize(bitvec *v, size_t newsz){
    if (v){
        size_t old_sz = (1 + (v->size-1)/BITS) * sizeof(char);
        size_t new_sz = (1 + (newsz-1)/BITS) * sizeof(char);
        v->arr = realloc(v->arr, (1 + (newsz-1)/BITS) * sizeof(char));
        v->size = newsz;
        if (new_sz > old_sz){
            memset(v->arr+old_sz, 0, new_sz-old_sz);
        }
    }
}

void bitvec_set(bitvec *v, size_t k){
    if(!v || k >= v->size) return;
    if(v->arr) v->arr[k/v->wordsz] |= 1 << (v->wordsz-(k%v->wordsz)-1);
}

void bitvec_clear(bitvec *v, size_t k){
    if(!v || k >= v->size) return;
    if(v->arr) v->arr[k/v->wordsz] &= ~(1 << (v->wordsz-(k%v->wordsz)-1));
}

void bitvec_clear_all(bitvec *v){
    if(v){
        if(v->arr){
            memset(v->arr, 0, (1 + (v->size-1)/BITS) * sizeof(char));
        }
    }
}

void bitvec_set_all(bitvec *v){
    if(v){
        if(v->arr){
            memset(v->arr, -1, (1 + (v->size-1)/BITS) * sizeof(char));
        }
    }
}

void bitvec_toggle_all(bitvec *v){
    if(v){
        if(v->arr){
            size_t sz = (1 + (v->size-1)/BITS) * sizeof(char);
            for (size_t i = 0; i < sz; i++) {
                v->arr[i] = ~v->arr[i];
            }
        }
    }
}

int bitvec_test(bitvec *v, size_t k){
    if(!v || k >= v->size || !v->arr){
        return 0;
    }
    if(v->arr){
        if((v->arr[k/v->wordsz] & (1 << (v->wordsz-(k%v->wordsz)-1)))){
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

size_t bitvec_size(bitvec *v){
    if(v){
        return v->size;
    }
    return 0;
}

size_t bitvec_arr_sz(bitvec *v){
    if(v){
        return (1 + (v->size-1)/BITS) * sizeof(char);
    }
    return 0;
}

char * bitvec_arr(bitvec *v, size_t *ret){
    if(v){
        size_t sz = (1 + (v->size-1)/BITS) * sizeof(char);
        if (ret) *ret = sz;
        return memcpy(malloc(sz), v->arr, sz);
    }
    return NULL;
}
