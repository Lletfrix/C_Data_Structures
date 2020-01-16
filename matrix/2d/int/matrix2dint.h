#include "../matrix2d.h"

typedef m2d m2d_int;

m2d_int * m2d_int_new();

m2d_int * m2d_int_init(m2d_int * m, size_t x, size_t y, int *mtx);

m2d_int * m2d_int_destroy(m2d_int *m);

void m2d_int_delete(m2d_int *m);

int m2d_int_get(m2d_int *m, size_t x, size_t y);

m2d_int * m2d_int_set(m2d_int *m, size_t x, size_t y, int val);

m2d_int *m2d_int_reshape(m2d_int *m, size_t x, size_t y);

int m2d_int_print(FILE *fout, m2d_int *m);
