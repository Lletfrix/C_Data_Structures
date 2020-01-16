#include <stdio.h>
#include <stdlib.h>
#include "matrix2d.h"

matrix2d * m2d_new(){
    return matrix_new();
}

matrix2d * m2d_init(matrix2d * m, size_t x, size_t y, size_t membsz, void *mtx){
    size_t space[2] = {x, y};
    return matrix_init(m, 2, space, membsz, mtx);
}

matrix2d * m2d_destroy(matrix2d *m){
    return matrix_destroy(m);
};

void matrix2d_delete(matrix2d *m){
    matrix_delete(m);
}

void *m2d_element(matrix2d *m, size_t x, size_t y){
    size_t space[2] = {x, y};
    return matrix_element(m, space);
}

matrix2d *m2d_reshape(matrix2d *m, size_t x, size_t y){
    size_t space[2] = {x, y};
    return matrix_reshape(m, 2, space);
}

int m2d_print(FILE *fout, matrix2d *m, char *(*to_str)(void *, size_t)){
    matrix *gen = m;
    char *str;
    int ret=0;
    size_t x = m->space[0];
    size_t y = m->space[1];
    for (size_t i = 0; i < x; i++) {
        ret = fprintf(fout, "[ ");
        for (size_t j = 0; j < y; j++) {
            str = to_str(m2d_element(m, i, j), m->membsz);
            ret += fprintf(fout, "%s ", str);
        }
        ret += fprintf(fout, "]\n");
    }
    return ret;
}
