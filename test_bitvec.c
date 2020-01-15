#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "bitvec/bitvec.h"
/*Compile: gcc test_bitvec.c bitvec/bitvec.c -o test_bitvec */
void main(){
    bitvec *v;
    v = bitvec_init(bitvec_new(), 500, NULL);
    bitvec_set(v, 255);
    printf("%d, expected 1\n", bitvec_test(v, 255));
    bitvec_clear(v, 255);
    printf("%d, expected 0\n", bitvec_test(v, 255));
    bitvec_toggle(v, 255);
    printf("%d, expected 1\n", bitvec_test(v, 255));
    bitvec_toggle(v, 255);
    printf("%d, expected 0\n", bitvec_test(v, 255));
    bitvec_set(v, 7);
    bitvec_set(v, 8);
    bitvec_set(v, 9);
    printf("%d, expected 1\n", bitvec_test(v, 7));
    printf("%d, expected 1\n", bitvec_test(v, 8));
    printf("%d, expected 1\n", bitvec_test(v, 9));
    bitvec_set(v, 499);
    printf("%d, expected 1\n", bitvec_test(v, 499));
    bitvec_resize(v, 501);
    printf("%d, expected 1\n", bitvec_test(v, 499));
    printf("%d, expected 0\n", bitvec_test(v, 500));
    bitvec_delete(bitvec_destroy(v));
}
