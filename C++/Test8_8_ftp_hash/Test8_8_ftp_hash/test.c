#include"hash.h"

/*
typedef struct hash hash_t;

typedef unsigned int (*hashfunc_t)(unsigned int, void*);

hash_t* hash_alloc(unsigned int buckets, hashfunc_t hash_func);

void* hash_lookup_entry(hash_t *hash, void* key, unsigned int key_size);

void hash_add_entry(hash_t *hash, void *key, unsigned int key_size,void *value, unsigned int value_size);

void hash_free_entry(hash_t *hash, void *key, unsigned int key_size);

*/

unsigned int hash_func(unsigned int bucket_size, void *p_key)
{
	//³ıÁôÓàÊı·¨
	return (*(unsigned int *)p_key) % bucket_size;
}

void main()
{
	//map<int, int> mp1;
	//map<int, string> mp2;

	struct hash *ip_count_hash = hash_alloc(17, hash_func);
	struct hash *pid_ip_hash   = hash_alloc(191, hash_func);

	int key = 1;
	int value = 100;
	hash_add_entry(ip_count_hash, &key, sizeof(int), &value, sizeof(int));
}