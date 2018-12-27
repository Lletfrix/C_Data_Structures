#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../bitvec/bitvec.h"
#include "set.h"

#ifndef SETSZ
#define  SETSZ 32
#endif

set *__set_by_ints();
void __get_szarr(set *s, set *t, int **lrg, int **sml, size_t *lrg_sz, size_t *sml_sz);

struct set{
    size_t len;
    size_t size;
    bitvec *vec;
    size_t(*hash)(void *);
};

set *set_new(){
    return malloc(sizeof(set));
}

void set_delete(set *s){
    if(s){
        free(s);
    }
}

set *set_init(set *s, size_t(*maptoidx)(void *)){
    if(s){
        if(maptoidx){
            set->len = 0;
            set->hash = maptoidx;
            set->vec = bitvec_init(bitvec_new(), SETSZ);
            set->size = SETSZ;
            if(!set->vec){
                errno=EAGAIN;
                perror("set_init");
                set->hash = NULL;
                set->size = 0;
            }
        }else{
            *s = (set){0};
        }
    }
    return s;
}
void set_destroy(set *s){
    if(s){
        if(s->vec){
            free(s->vec);
            set_init(s, NULL);
        }
    }
}

size_t set_len(set *s){
    if(s){
        return s->len;
    }
    errno = EINVAL;
    perror("set_len");
    return 0;
}

size_t set_in(set *s, void *x){
    if(s && x){
        if(s->hash){
            size_t idx = s->hash(x);
            if(bitvec_test(s->vec, idx)){
                return idx+1;
            }
        }
    }
    errno=EINVAL;
    perror("set_in");
    return 0;
}

bool set_subset(set *s, set *t){
    if(s && t && s->vec && t->vec){
        int *vt = bitvec_arr(t->vec);
        int *vs = bitvec_arr(s->vec);
        if(vs && vt){
            for(size_t i = 0; i < s->size/sizeof(int); ++i){
                if((vs[i] ^ vt[i]) != 0){
                    free(vs);
                    free(vt);
                    return false;
                }
            }
            free(vs);
            free(vt);
            return true;
        }
    }
    if (vs) free(vs);
    if (vt) free(vt);
    errno = EINVAL;
    perror("set_subset");
    return false;
}

void set_clear(set *s){
    if(s){
        if(s->vec){
            bitvec_clear_all(s->vec);
        }
    }
}

set *set_union(set *s, set *t){
    if(s && t && s->vec && t->vec){
        if(s->hash != t->hash){
            errno=EINVAL;
            perror("set_union");
            return NULL;
        }
        int *lrg_p, *sml_p;
        size_t lrg_sz, sml_sz;

        __get_szarr(s, t, &lrg_p, &sml_p, &lrg_sz, &sml_sz);

        for(size_t i = 0; i < sml_sz; ++i){
            lrg_p[i] |= sml_p[i];
        }
        free(sml_p);
        set *ret = __set_by_ints(lrg_sz, lrg_p, s->hash);
        return ret;
    }
    errno=EINVAL;
    perror("set_union");
    return NULL;
}

set * __set_by_ints(size_t sz, int *p, size_t(*hash)(void *)){
    bitvec *vec = bitvec_init(bitvec_new(), sz, p);
    set *ret = set_new();
    set_init(ret, hash);
    memcpy(ret->vec, vec, lrg_sz);
    return ret;
}

void __get_szarr(set *s, set *t, int **lrg, int **sml, size_t *lrg_sz, size_t *sml_sz){
    set *lrg, *sml;
    if(s->len > t->len){
        lrg=s; sml=t;
    }else{
        lrg=t; sml=s;
    }
    *lrg = bitvec_arr(lrg->vec);
    *sml = bitvec_arr(sml->vec);
    *lrg_sz = bitvec_size(lrg->vec);
    *sml_sz = bitvec_size(sml->vec);
}
