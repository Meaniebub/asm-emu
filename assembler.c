#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#define MAXCHAR 15

int main(int argc, char const *argv[]) {
    FILE *fp;
    char ch;
    hashtable *ht = new_hashtable();
    char str[MAXCHAR];

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
    fclose(fp);

    fp = fopen("test.asm", "r");

    if (!fp) {
        printf("Couldn't find y86 assembly source\n");
        return 1;
    }

    while(1)
     {
        ch = fgetc(fp);
        if(ch == EOF)
            break;
        else
            printf("%c", ch);
     }

    fclose(fp);
    del_hashtable(ht);
    return 0;
}
