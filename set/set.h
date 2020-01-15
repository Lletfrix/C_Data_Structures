/**
 * @brief interface of a set
 *
 * contains the functions to initialise, interact and destroy a set.
 *
 * @file set.h
 * @author Rafael Sánchez
 * @version 1.0
 * @date 27-12-2018
 */
typedef struct set set;

/* Returns an uninitialised set pointer */
set * set_new();

/* Frees set's pointer memory */
void set_delete(set *s);

/* Initialise an uninitialised set pointer */
set * set_init(set *s, size_t size, size_t(*hash)(void *), char *vec);

/* Free's the initialised memory in set_init */
set * set_destroy(set *s);

/**
 * @brief number of elements in set s (cardinality)
 *
 * gets the cardinality of set s.
 *
 * @param s set to get cardinality
 * @return set's cardinality
 */
size_t set_cardinality(set *s);

bool set_in(set *s, void *x);

bool set_subset(set *s, set *t);

set * set_union(set *s, set *t);

set * set_intersec(set *s, set *t);

set * set_complement(set *s);

set * set_diff(set *s, set *t);

set * set_copy(set *s);

void set_add(set *s, void *x);

void set_rm(set *s, void *x);

void set_clear(set *s);

void set_fill(set *s);

int set_print(FILE *f, set *s);
