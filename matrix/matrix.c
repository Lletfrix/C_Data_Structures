#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

matrix * matrix_new(){
    return calloc(1, sizeof(matrix));
}

matrix * matrix_init(matrix * m, size_t dim, size_t *space, size_t membsz, void *mtx){
    if (m){
        if (space) {
            m->dim = dim;
            memcpy((m->space = calloc(dim, sizeof(size_t))), space, dim * sizeof(size_t));
            m->membsz = membsz;
            m->total = 1;
            for (size_t i = 0; i < dim; m->total *= space[i++]);
            m->mtx = calloc(m->total, membsz);
            if (mtx) {
                memcpy(m->mtx, mtx, m->total*membsz);
            }
            return m;
        } else {
            *m = (matrix) {0};
            return m;
        }
    }
    fprintf(stderr, "No matrix pointer or no spaces defined\n");
    return NULL;
}

matrix * matrix_destroy(matrix *m){
    free(m->mtx);
    free(m->space);
    matrix_init(m, 0, NULL, 0, NULL);
    return m;
}

void matrix_delete(matrix *m){
    if (m) free(m);
}

void * matrix_element(matrix *m, size_t *indexes){
    if (!m || !indexes)
        return NULL;
    size_t abs = indexes[0];
    for (int i = 1; i < m->dim; i++) abs = abs*m->space[i] + indexes[i];
    if (abs < m->total)
        return m->mtx + abs*m->membsz;
    return NULL;
}

matrix * matrix_reshape(matrix *m, size_t dim, size_t *space){
    size_t n_total = 1;
    for (size_t i = 0; i < dim; n_total *= space[i++]);
    if (n_total != m->total)
        return NULL;
    free(m->space);
    m->dim = dim;
    memcpy((m->space = calloc(dim, sizeof(size_t))), space, dim * sizeof(size_t));
    return m;
}

int matrix_print(FILE *fout, matrix *m, char *(*to_str)(void *, size_t)){
    int ret;
    ret = fprintf(fout, "[ ");
    for(int i = 0; i < m->total; i++){
        char *str = to_str(m->mtx + (i*m->membsz), m->membsz);
        ret += fprintf(fout, "%s ", str);
        free(str);
    }
    ret += fprintf(fout, "]\n");
    return ret;
}
