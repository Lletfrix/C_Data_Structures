
typedef struct bitvec bitvec;

/* Returns an uninitialised bitvec pointer */
bitvec *bitvec_new();

/* Frees bitvec's pointer memory */
void bitvec_delete(bitvec *v);

/* Initialise an uninitialised bitvec pointer */
bitvec *bitvec_init(bitvec *v, size_t size, int *arr);

/* Free's the initialised memory in bitvec_init */
void bitvec_destroy(bitvec *v);

void bitvec_set(bitvec *v, size_t pos);

void bitvec_clear(bitvec *v, size_t pos);

void bitvec_toggle(bitvec *v, size_t pos);

int bitvec_test(bitvec *v, size_t pos);

size_t bitvec_len(bitvec *v);

int *bitvec_arr(bitvec *v);

void bitvec_clear_all(bitvec *v);
