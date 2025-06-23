#ifndef H_HASH_MAP
#define H_HASH_MAP

#include <stddef.h> // for size_t

typedef struct Entry 
{
    char *key;
    void *value;
    struct Entry *next; // separate chaining
} Entry;

typedef struct HashMap 
{
    Entry **buckets;
    size_t capacity;
    size_t size;
} HashMap;

void init_map(HashMap *map, size_t capacity);
int insert_map(HashMap *map, const char *key, void *value);
void *get_map(const HashMap *map, const char *key);
int remove_map(HashMap *map, const char *key);
void free_map(HashMap *map, void (*free_value)(void *));

#endif