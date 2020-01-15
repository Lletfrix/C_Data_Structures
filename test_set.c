#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set/set.h"

/*Compile:
gcc -c -g bitvec/bitvec.c -o bitvec/bitvec.o
gcc -c -g set/set.c -o set/set.o
gcc -g test_set.c set/set.o bitvec/bitvec.o -o test_set
*/

size_t hash(void * elem){
    int e = *(int *)elem;
    return e%37;
}

int main(int argc, char const *argv[]) {
    set *s, *t;
    int x = 10;

    /* Initialization */
    s = set_init(set_new(), 37, hash, NULL);
    t = set_init(set_new(), 37, hash, NULL);
    set_print(stdout, s);
    set_print(stdout, t);

    /* set_add */
    set_add(s, &x);
    set_add(t, &x);
    x = 3;
    set_add(s, &x);
    set_add(t, &x);
    x = 2;
    set_add(s, &x);
    set_add(t, &x);
    x = 1;
    set_add(s, &x);
    set_add(t, &x);
    set_print(stdout, s);
    set_print(stdout, t);

    /* set_in */
    x=3;
    if(set_in(t, &x)){
        printf("set_in works!\n");
    }else{
        printf("set_in explodes :C\n");
    }

    /* set_cardinality */
    x = 5;
    set_add(t, &x);
    x = 1;
    set_add(s, &x);
    printf("#(s) = %ld, expected 4\n", set_cardinality(s));

    /* set_subset */
    printf("s: "); set_print(stdout, s);
    printf("t: "); set_print(stdout, t);
    if(set_subset(s, t)){
        printf("s is subset of t\n");
    }else{
        printf("s is not subset of t\n");
    }

    /* set_rm */
    x = 1;
    set_rm(s, &x);
    x = 7;
    set_add(s, &x);
    printf("s: "); set_print(stdout, s);
    printf("t: "); set_print(stdout, t);
    if(set_subset(s, t)){
        printf("s is subset of t\n");
    }else{
        printf("s is not subset of t\n");
    }

    /* set_union */
    set *sut = set_union(s, t);
    printf("sUt: "); set_print(stdout, sut);


    /* set_intersec */
    set *sat = set_intersec(s, t);
    printf("s^t: "); set_print(stdout, sat);

    /* set_complement */
    set_complement(sut);
    printf("complement(sUt): "); set_print(stdout, sut);

    /* set_difference */
    set *sdef = set_diff(sat, s);
    printf("(s^t\\s): "); set_print(stdout, sdef);

    /* set_clear */
    set_clear(sut);
    printf("cleared sUt: "); set_print(stdout, sut);

    /* set_fill */
    set_fill(sut);
    printf("filled sUt: "); set_print(stdout, sut);

    set_delete(set_destroy(s));
    set_delete(set_destroy(t));
    set_delete(set_destroy(sut));
    set_delete(set_destroy(sat));
    set_delete(set_destroy(sdef));
    return 0;
}
