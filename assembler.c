#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main(int argc, char const *argv[]) {
    char ch;
    FILE *fp;

    fp = fopen("C:\\Users\\prate\\CProjects\\asm-emu\\test.txt", "r");

    if (!fp) {
      printf("Invalid filepath\n");
      return 1;
    }

    while (1) {
        ch = fgetc(fp);
        if (feof(fp)){
            break;
        }
        printf("%c", ch);
    }

    printf("hello");
    int x = 1010;

    hashtable *ht = new_hashtable();
    ht_insert(ht, "ADD", &x);

    return 0;
}