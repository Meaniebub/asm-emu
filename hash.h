#define MAXSIZE 500;

typedef struct{
    int* key;
    int* value;
}entry;

typedef struct{
    int size;
    int count;
    entry** items;
}hashtable;

unsigned long hash(const char *str);

void ht_insert(hashtable* ht, const char* key, int* value);

char* ht_search(hashtable* ht, const char* key);

void ht_delete(hashtable* h, const char* key);

static void del_entry(entry * i);

hashtable* new_hashtable();

static void del_entry(entry * i);

void del_hashtable(hashtable* ht);