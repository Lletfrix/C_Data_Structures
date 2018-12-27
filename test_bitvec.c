#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "bitvec/bitvec.h"
/*Compile: gcc test_bitvec.c bitvec/bitvec.c -o test_bitvec */
void main(){
    bitvec *v;
    v = bitvec_init(bitvec_new(), 500);
    bitvec_set(v, 255);
    printf("%d\n", bitvec_test(v, 255));
    bitvec_clear(v, 255);
    printf("%d\n", bitvec_test(v, 255));
    bitvec_toggle(v, 255);
    printf("%d\n", bitvec_test(v, 255));
    bitvec_toggle(v, 255);
    printf("%d\n", bitvec_test(v, 255));
    bitvec_destroy(v);
    bitvec_delete(v);
}
