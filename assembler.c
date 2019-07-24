#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#define MAXCHAR 30

void buffer_check();

int main(int argc, char const *argv[]) {
    FILE *fp;
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
        printf("Couldn't find source code\n");
        return 1;
    }

    int index = 0;
    char ch;
    char buffer[MAXCHAR];
    hashtable* st = new_hashtable();

    void buffer_check(int final_pass){
        if (buffer[0] != 0) {
            buffer[index++] = '\0';
            int result = ht_search(ht, buffer);
            if (result != -1 && final_pass) {
                printf("%X ", result);
            }
            else if(result != -1 && !final_pass){
                printf("%X ", result);
            }
        }
        memset(buffer, 0, sizeof(buffer));
        index = 0;
    }

    do {
        ch = fgetc(fp);
        switch (ch) {
            case ':':
                ht_insert(st, )
        }
    } while(ch != EOF);

    fclose(fp);
    fp = fopen("test.asm", "r");

    do{
        ch = fgetc(fp);
        switch (ch) {
            case '\t':
                break;
            case ' ':
                buffer_check(1);
                break;
            case '\n':
                buffer_check(1);
                printf("\n");
                break;
            case ',':
                buffer_check(1);
                break;
            default:
                buffer[index++] = ch;
        }
     }while(ch != EOF);

    fclose(fp);
    del_hashtable(ht);
    return 0;
}

int length_check(int opcode){
    char* temp;
    unsigned char c;

    if (c == '0' || c == '1' || c == '9') {
        return 1;
    }
    else if (c == '3' || c == '4' || c == '5') {
        return 10;
    }
    else if (c == '7' || c == '8') {
        return 10;
    }
    else if(c == '2' || c == '6' || c == 'A' || c == 'B'){
        return 4;
    }
}
