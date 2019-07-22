#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main(int argc, char const *argv[]) {
    char ch;
    FILE *fp;

    fp = fopen("C:\\Users\\zbjb8f\\CProjects\\assembler\\test.txt", "r");

    if (!fp) {
      printf("Couldn't find opcode table\n");
      return 1;
    }

    while (1) {
        ch = fgetc(fp);
        if (feof(fp)){
            break;
        }
        printf("%c", ch);
    }

    int x = 0xFF;

    hashtable *ht = new_hashtable();
    ht_insert(ht, "ADD", x);

    int result = ht_search(ht, "ADD");
    printf("\n%d\n", result);
    del_hashtable(ht);
    fclose(fp);

    return 0;
}
