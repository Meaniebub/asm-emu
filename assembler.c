#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "hash.h"
#define MAXCHAR 30

void buffer_check();
int length_check(int opcode);
char* get_dir(char* buffer, char* dir_number, int* i);

int main(int argc, char const *argv[]) {
    clock_t start = clock();
    hashtable *ht = new_hashtable();
    char str[MAXCHAR];
    FILE *fp;

    fp = fopen("opcode.txt", "r");

    if (!fp) {
        printf("Couldn't find opcode table\n");
        return 1;
    }

    while (fgets(str, MAXCHAR, fp) != NULL){
        strtok(str, "\n");
        char* token = strtok(str, " ");
        char* array[3];
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
    int loc_counter = 0;
    char ch;
    char buffer[MAXCHAR];
    hashtable* st = new_hashtable();

    do {
        ch = fgetc(fp);
        switch (ch) {
            case ':':
                buffer[index++] = '\0';
                ht_insert(st, buffer, loc_counter);
                printf("%s, %X\n", buffer, loc_counter);
                break;
            case '\t':
                break;
            case ' ':
                buffer_check(buffer, &index, &loc_counter, 0, ht, st, fp);
                break;
            case '\n':
                buffer_check(buffer, &index, &loc_counter, 0, ht, st, fp);
                break;
            case ',':
                if (buffer[0] == '$') {
                    char num[17];
                    for (int i = 0; i < strlen(buffer); i++) {
                        num[i] = buffer[i+1];
                    }
                    ht_insert(st, buffer, strtol(num, NULL, 16));
                }
                buffer_check(buffer, &index, &loc_counter, 0, ht, st, fp);
                break;
            case '(':
                if (buffer[0] != '\0') {
                    char num[17];
                    buffer[index++] = '\0';
                    if (buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X')) {
                        for (int i = 0; i < strlen(buffer); i++) {
                            num[i] = buffer[i];
                        }
                    }
                    else{
                        for (int i = 0; i < strlen(buffer); i++) {
                            num[i] = buffer[i];
                        }
                    }
                    printf("%s\n", num);
                    int value = strtol(num, NULL, 16);
                    printf("%x\n", value);
                    ht_insert(st, buffer, value);
                }
                break;
            default:
                buffer[index++] = ch;
        }
    } while(ch != EOF);

    rewind(fp);

    do{
        ch = fgetc(fp);
        switch (ch) {
            case '\t':
                break;
            case ' ':
                buffer_check(buffer, &index, &loc_counter, 1, ht, st, fp);
                break;
            case '\n':
                buffer_check(buffer, &index, &loc_counter, 1, ht, st, fp);
                printf("\n");
                break;
            case ',':
                buffer_check(buffer, &index, &loc_counter, 1, ht, st, fp);
                break;
            case '(':
                buffer_check(buffer, &index, &loc_counter, 1, ht, st, fp);
                break;
            default:
                buffer[index++] = ch;
        }
     }while(ch != EOF);

    fclose(fp);
    del_hashtable(ht);
    del_hashtable(st);

    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Assembly finished in ms: %f", elapsed);

    return 0;
}

int length_check(int opcode){
    char temp[5];
    sprintf(temp, "%x", opcode);
    unsigned char c = temp[0];

    if (c == '0' || c == '1' || c == '9') {
        return 1;
    }
    else if (c == '3' || c == '4' || c == '5') {
        return 10;
    }
    else if (c == '7' || c == '8') {
        return 9;
    }
    else if(c == '2' || c == '6' || c == 'A' || c == 'B'){
        return 2;
    }
    else{
        return 0;
    }
}

char* get_dir(char buffer[], char dir_number[], int* i){
    int j = 0;
    while (buffer[(*i)] != ' ' && buffer[(*i)] != '\n'){
        dir_number[j] = buffer[(*i)];
        j++;
        (*i)++;
        dir_number[j] = '\0';
    }
    memset(buffer, 0, strlen(buffer));
    return dir_number;
}

void buffer_check(char buffer[], int* index, int* loc_counter,
    int final_pass, hashtable* ht, hashtable* st, FILE* fp){
    if (buffer[0] != 0) {
        buffer[(*index)++] = '\0';
        int result = ht_search(ht, buffer);
        if (buffer[0] == '.') {
            fgets(buffer, MAXCHAR, fp);
            int i = 0;
            char dir_number[MAXCHAR];
            int value;
            switch (result) {
                case 0xFE:
                    get_dir(buffer, dir_number, &i);
                    value = strtol(dir_number, NULL, 16);
                    (*loc_counter) = value;
                    break;
                case 0xFD:
                    get_dir(buffer, dir_number, &i);
                    value = strtol(dir_number, NULL, 16);
                    (*loc_counter) += 8;
                    break;
                case 0xFC:
                    get_dir(buffer, dir_number, &i);
                    value = strtol(dir_number, NULL, 16);
                    if ((*loc_counter) % value != 0) {
                        (*loc_counter) += ((*loc_counter) % value);
                    }
                    break;
            }
        }
        if (result != -1 && final_pass) {
            printf("%X ", result);
        }
        else if(result != -1 && !final_pass && buffer[0] != '%'){
            (*loc_counter) += length_check(result);
            printf("%X\n", (*loc_counter));
        }
        else if (result == -1 && final_pass) {
            int symbol = ht_search(st, buffer);
            if (symbol != -1) {
                printf("%X ", symbol);
            }
        }
    }
    memset(buffer, 0, strlen(buffer));
    (*index) = 0;
}
