#include <stdio.h>
#include <string.h>

int main() {
   FILE *fp;
   const char *str = "Hello, World!";

   fp = fopen("example3.txt", "w");
   if (fp == NULL) {
      perror("Error opening file");
      return 1;
   }

   size_t written = fwrite(str, sizeof(char), strlen(str), fp);
   printf("Number of elements written: %zu\n", written);

   fclose(fp);
   return 0;
}
