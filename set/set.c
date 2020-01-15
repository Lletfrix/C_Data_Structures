#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../bitvec/bitvec.h"
#include "set.h"

set * __set_by_bits();
void __get_szarr(set *s, set *t, char **lrg_vec, char **sml_vec, size_t *lrg_sz, size_t *sml_sz, set **lrg, set **sml);

struct set{
    size_t len;
    size_t size;
    bitvec *vec;
    size_t(*hash)(void *);
};

set * set_new(){
    return malloc(sizeof(set));
}

void set_delete(set *s){
    if(s){
        free(s);
    }
}

set * set_init(set *s, size_t size, size_t(*hash)(void *), char *vec){
    if(s){
        if(hash){
            s->hash = hash;
            s->vec = bitvec_init(bitvec_new(), size, vec);
            s->size = size;
            if(!s->vec){
                s->hash = NULL;
                s->size = 0;
            }
        }else{
            *s = (set){0};
        }
    }
    return s;
}
set * set_destroy(set *s){
    if(s){
        if(s->vec){
            bitvec_delete(bitvec_destroy(s->vec));
            set_init(s, 0, NULL, NULL);
        }
    }
    return s;
}

size_t set_cardinality(set *s){
    if(s){
        size_t total=0;
        for (size_t i = 0; i < s->size; i++) {
            if (bitvec_test(s->vec, i)) total++;
        }
        return total;
    }
    return 0;
}

bool set_in(set *s, void *x){
    if(s && x){
        if(s->hash){
            size_t idx = s->hash(x);
            return bitvec_test(s->vec, idx);
        }
    }
    return false;
}

bool set_subset(set *s, set *t){
    if(s && t && s->vec && t->vec){
        size_t s_sz = bitvec_size(s->vec);
        size_t t_sz = bitvec_size(t->vec);

        for (size_t i = 0; i < s_sz; i++) {
            if (bitvec_test(s->vec, i)){
                if (!bitvec_test(t->vec, i)){
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}

void set_clear(set *s){
    if(s){
        if(s->vec){
            bitvec_clear_all(s->vec);
        }
    }
}

void set_fill(set *s){
    if(s){
        if(s->vec){
            bitvec_set_all(s->vec);
        }
    }
}

set * set_union(set *s, set *t){
    if(s && t && s->vec && t->vec){
        if(s->hash != t->hash){
            return NULL;
        }
        char *lrg_p, *sml_p;
        size_t lrg_sz, sml_sz;
        set *lrg, *sml;

        __get_szarr(s, t, &lrg_p, &sml_p, &lrg_sz, &sml_sz, &lrg, &sml);

        for(size_t i = 0; i < sml_sz; ++i){
            lrg_p[i] |= sml_p[i];
        }

        set *ret = __set_by_bits(lrg->size, lrg_p, s->hash);
        free(sml_p);
        free(lrg_p);
        return ret;
    }
    return NULL;
}

set *set_intersec(set *s, set *t){
    if(s && t && s->vec && t->vec){
        if(s->hash != t->hash){
            return NULL;
        }
        char *lrg_p, *sml_p;
        size_t lrg_sz, sml_sz;
        set *lrg, *sml;

        __get_szarr(s, t, &lrg_p, &sml_p, &lrg_sz, &sml_sz, &lrg, &sml);

        for(size_t i = 0; i < sml_sz; ++i){
            lrg_p[i] &= sml_p[i];
        }
        set *ret = __set_by_bits(lrg->size, lrg_p, s->hash);
        free(sml_p);
        free(lrg_p);
        return ret;
    }
    return NULL;
}

set * set_diff(set *s, set *t){
    set * ret=NULL;
    if(s && t && s->vec && t->vec){
        size_t s_sz = bitvec_size(s->vec);
        size_t t_sz = bitvec_size(t->vec);
        ret = set_copy(s);
        for (size_t i = 0; i < t_sz; i++) {
            if (bitvec_test(t->vec, i)){
                bitvec_clear(ret->vec, i);
            }
        }
    }
    return ret;
};

set * set_complement(set *s){
    if(s){
        bitvec_toggle_all(s->vec);
    }
    return s;
}

set * set_copy(set *src){
    set *dst;
    size_t sz;
    char *bits = bitvec_arr(src->vec, &sz);
    dst = __set_by_bits(src->size, bits, src->hash);
    free(bits);
    return dst;
}

void set_add(set *s, void *x){
    if(s && x){
        if(s->hash){
            size_t idx = s->hash(x);
            bitvec_set(s->vec, idx);
        }
    }
}

void set_rm(set *s, void *x){
    if(s && x){
        if(s->hash){
            size_t idx = s->hash(x);
            bitvec_clear(s->vec, idx);
        }
    }
}

set * __set_by_bits(size_t sz, char *p, size_t(*hash)(void *)){
    set *ret = set_new();
    set_init(ret, sz, hash, p);
    return ret;
}

void __get_szarr(set *s, set *t, char **lrg_vec, char **sml_vec, size_t *lrg_sz, size_t *sml_sz, set **lrg, set **sml){
    if(s->size > t->size){
        *lrg=s; *sml=t;
    }else{
        *lrg=t; *sml=s;
    }
    *lrg_vec = bitvec_arr((*lrg)->vec, lrg_sz);
    *sml_vec = bitvec_arr((*sml)->vec, sml_sz);
}

int set_print(FILE *f, set *s){
    int total;
    total = fprintf(f, "{ ");
    for (size_t i = 0; i < s->size; i++) {
        if (bitvec_test(s->vec, i)){
            total += fprintf(f, "%ld ", i);
        }
    }
    total += fprintf(f, "}\n");
    return total;
}
