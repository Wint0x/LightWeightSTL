#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hash_map.h"

static unsigned long hash(const char *str) 
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

void init_map(HashMap *map, size_t capacity)
{
    if (!map || capacity == 0)
        return;

    map->buckets = (Entry **)calloc(capacity, sizeof(Entry *)); // calloc initializes memory with 0
    map->capacity = capacity;
    map->size = 0;
}

int insert_map(HashMap *map, const char *key, void *value)
{
    if (!map || !key)
        return -1;

    unsigned long index = hash(key) % map->capacity;

    // Check for existing key
    Entry *current = map->buckets[index];
    while (current) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            // Overwrite value (optional)
            current->value = value;
            return 0;
        }
        current = current->next;
    }

    Entry *new_entry = malloc(sizeof(Entry));
    if (!new_entry)
        return -1;


    new_entry->key = strdup(key);  // Make a copy of the key
    new_entry->value = value;
    new_entry->next = map->buckets[index];  // Insert at front

    map->buckets[index] = new_entry;
    map->size++;

    return 0;
}

void *get_map(const HashMap *map, const char *key) 
{
    if (!map || !key || !map->buckets)
        return NULL;

    unsigned long index = hash(key) % map->capacity;

    Entry *current = map->buckets[index];
    while (current) 
    {
        if (strcmp(current->key, key) == 0) 
        {
            return current->value;
        }
        current = current->next;
    }

    return NULL;  // Not found
}

int remove_map(HashMap *map, const char *key) 
{
    if (!map || !key || !map->buckets)
        return -1;

    unsigned long index = hash(key) % map->capacity;
    Entry *current = map->buckets[index];
    Entry *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) 
        {
            if (prev)
                prev->next = current->next;
            else
                map->buckets[index] = current->next;

            free(current->key);
            // Only free value if you own it
            // free(current->value);  // Optional
            free(current);

            map->size--;
            return 0;
        }

        prev = current;
        current = current->next;
    }

    return -1; // Key not found
}

void free_map(HashMap *map, void (*free_value)(void *)) 
{
    if (!map || !map->buckets)
        return;

    for (size_t i = 0; i < map->capacity; ++i) 
    {
        Entry *current = map->buckets[i];
        while (current) 
        {
            Entry *next = current->next;
            
            free(current->key);    // strdup'd key
            // Do NOT free current->value unless ownership is managed here
            if (free_value)
                free_value(current->value);

            free(current);         // free the entry itself
            current = next;
        }
    }

    free(map->buckets);
    map->buckets = NULL;
    map->capacity = 0;
    map->size = 0;
}