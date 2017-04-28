struct listnode{
	char *key;
	int value;

	struct listnode *next;
};

unsigned int hashtab_hash(char *key);
unsigned add_hash(char *key, int len);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, int value, int *col);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);