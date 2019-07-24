#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

unsigned long hash(const char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % MAXSIZE;
}

static entry* new_entry(const char* k, int v){
    entry* i = malloc(sizeof(entry));

    i -> key = strdup(k);
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

void del_entry(entry * i){
    free(i -> key);
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

void ht_insert(hashtable* ht, const char* key, int value){
    int index = hash(key);
    entry* entry = new_entry(key, value);
    if (ht -> items[index] == NULL) {
        ht -> items[index] = entry;
    }
    else{
        printf("Collision detected, %s, %i\n", key, index);
    }
}

int ht_search(hashtable* ht, const char* key1){
  int index = hash(key1);
  entry* entry = ht -> items[index];

  if (entry && strcmp(entry -> key, key1) == 0) {
    return entry -> value;
  }

  return -1;
}
