#include <stdio.h>
#include <string.h>

int main() {
   FILE *fp;
   char str[10] = "";
   int num         = 0;
   fp = fopen("example3.txt", "r");
   if (fp == NULL) {
      perror("Error opening file");
      return 1;
   }

   fscanf(fp, "%d", num);
   printf("%d", num);
   fscanf(fp, "%s", str);
   printf("%s", str);

   fclose(fp);
   return 0;
}
