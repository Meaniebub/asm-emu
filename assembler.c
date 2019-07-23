#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#define MAXCHAR 15

int main(int argc, char const *argv[]) {
    char ch;
    FILE *fp;
    hashtable *ht = new_hashtable();
    char str[MAXCHAR];
    char * token;

    fp = fopen("opcode.txt", "r");

    if (!fp) {
        printf("Couldn't find opcode table\n");
        return 1;
    }

    while (fgets(str, MAXCHAR, fp) != NULL){
        strtok(str, "\n");
        char* token = strtok(str, " ");
        char* array[2];
        int i = 0;
        array[i] = token;

        while (token){
            array[i++] = token;
            token = strtok(NULL, " ");
        }

        ht_insert(ht, array[0], (int)strtol(array[1], NULL, 0));
    }

    printf("0x%X\n", ht_search(ht, "pushq"));

    del_hashtable(ht);
    fclose(fp);

    return 0;
}
