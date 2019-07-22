#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

unsigned long hash(const char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

static entry* new_entry(const char* k, int* v){
    entry* i = malloc(sizeof(entry));

    i -> key = hash(k);
    i -> value = v;

    return i;
}

hashtable* new_hashtable(){
    hashtable* ht = malloc(sizeof(hashtable));
    ht -> size = MAXSIZE;
    ht -> count = 0;
    ht -> items = calloc((size_t)(ht -> size), sizeof(entry*));

    return ht;
}

static void del_entry(entry * i){
    free(i -> key);
    free(i -> value);
    free(i);
}

void del_hashtable(hashtable* ht){
    for (int i = 0; i < ht -> size; i++) {
        entry* e = ht -> items[i];
        if (e != NULL) {
            del_entry(e);
        }
    }
    free(ht -> items);
    free(ht);
}

void ht_insert(hashtable* ht, const char* key, int* value){
    int index = hash(key);
    entry* entry = new_entry(key, value);

    ht -> items[index] = entry;
}