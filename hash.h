#define MAXSIZE 500;

typedef struct{
    char* key;
    int value;
}entry;

typedef struct{
    int size;
    int count;
    entry** items;
}hashtable;

unsigned long hash(const char *str);

static entry* new_entry(const char* k, int v);

void ht_insert(hashtable* ht, const char* key, int value);

int ht_search(hashtable* ht, const char* key);

void ht_delete(hashtable* h, const char* key);

static void del_entry(entry * i);

hashtable* new_hashtable();

void del_hashtable(hashtable* ht);
