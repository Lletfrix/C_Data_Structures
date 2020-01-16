#include "../matrix.h"

typedef matrix matrix2d;

matrix2d * m2d_new();

matrix2d * m2d_init(matrix2d * m, size_t x, size_t y, size_t membsz, void *mtx);

matrix2d * m2d_destroy(matrix2d *m);

void m2d_delete(matrix2d *m);

void *m2d_element(matrix2d *m, size_t x, size_t y);

matrix2d *m2d_reshape(matrix2d *m, size_t x, size_t y);

int m2d_print(FILE *fout, matrix2d *m, char *(*to_str)(void *, size_t));
