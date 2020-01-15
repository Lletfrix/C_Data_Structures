
typedef struct bitvec bitvec;

/* Returns an uninitialised bitvec pointer */
bitvec * bitvec_new();

/* Frees bitvec's pointer memory */
void bitvec_delete(bitvec *v);

/* Initialise an uninitialised bitvec pointer */
bitvec * bitvec_init(bitvec *v, size_t size, char *arr);

/* Free's the initialised memory in bitvec_init */
bitvec * bitvec_destroy(bitvec *v);

/* Resize bitvec pointer */
bitvec * bitvec_resize(bitvec *v, size_t newsz);

/* Sets bitvec pos to 1 */
void bitvec_set(bitvec *v, size_t pos);

/* Sets bitvec pos to 0 */
void bitvec_clear(bitvec *v, size_t pos);

/* Toggle bitvec pos */
void bitvec_toggle(bitvec *v, size_t pos);

/* Checks value of bitvec pos */
int bitvec_test(bitvec *v, size_t pos);

/* Get bitvec size */
size_t bitvec_size(bitvec *v);

/* Gets a copy bitvec inner array */
char * bitvec_arr(bitvec *v, size_t *sz);

/* Sets all bitvec to 0 */
void bitvec_clear_all(bitvec *v);

/* Sets all bitvec to 1 */
void bitvec_set_all(bitvec *v);
