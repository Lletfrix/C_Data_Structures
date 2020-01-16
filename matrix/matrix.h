#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
typedef struct _matrix {
    size_t total;
    size_t dim;
    size_t *space;
    size_t membsz;
    void *mtx;
} matrix;

matrix * matrix_new();

matrix * matrix_init(matrix * m, size_t dim, size_t *space, size_t membsz, void *mtx);

matrix * matrix_destroy(matrix *m);

void matrix_delete(matrix *m);

void *matrix_element(matrix *m, size_t *indexes);

matrix *matrix_reshape(matrix *m, size_t dim, size_t *space);

int matrix_print(FILE *fout, matrix *m, char *(*to_str)(void *, size_t));
#endif
