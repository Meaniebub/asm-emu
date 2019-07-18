#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  float floatValue[5] = { 1.1F, 2.2F, 3.3F, 4.4F, 5.5F };
  int i;

  if((fp=fopen("test", "wb"))==NULL) {
    printf("Cannot open file.\n");
  }

  if(fwrite(floatValue, sizeof(float), 5, fp) != 5)
    printf("File read error.");
  fclose(fp);

  /* read the values */
  if((fp=fopen("test", "rb"))==NULL) {
    printf("Cannot open file.\n");
  }

  if(fread(floatValue, sizeof(float), 5, fp) != 5) {
    if(feof(fp))
       printf("Premature end of file.");
    else
       printf("File read error.");
  }
  fclose(fp);

  for(i=0; i<5; i++)
    printf("%f ", floatValue[i]);

  return 0;
}
