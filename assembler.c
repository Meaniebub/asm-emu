#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  char ch;
  FILE *fp;

  fp = fopen("C:\\Users\\zbjb8f\\CProjects\\assembler\\test.txt", "r");

  if (!fp) {
    printf("Invalid filepath\n");
    return 1;
  }

  while (1) {
    ch = fgetc(fp);
    if (feof(fp)) {
      break;
    }
    printf("%c", ch);
  }
  return 0;
}
