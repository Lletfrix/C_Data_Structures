#ifndef MATRIX_H
#define MATRIX_H

typedef struct _matrix matrix;

matrix * matrix_new();

matrix * matrix_init(matrix * m, size_t dim, size_t *space, size_t membsz, void *mtx);

matrix * matrix_destroy(matrix *m);

void matrix_delete(matrix *m);

void *matrix_element(matrix *m, size_t *indexes);

matrix *matrix_reshape(matrix *m, size_t dim, size_t *space);

int matrix_print(FILE *fout, matrix *m, char *(*to_str)(void *, size_t));
#endif
