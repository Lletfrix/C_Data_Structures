#include "../matrix.h"

typedef matrix m2d;

m2d * m2d_new();

m2d * m2d_init(m2d * m, size_t x, size_t y, size_t membsz, void *mtx);

m2d * m2d_destroy(m2d *m);

void m2d_delete(m2d *m);

void *m2d_get(m2d *m, size_t x, size_t y);

m2d *m2d_reshape(m2d *m, size_t x, size_t y);

int m2d_print(FILE *fout, m2d *m, char *(*to_str)(void *, size_t));
