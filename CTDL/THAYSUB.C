/* Thay the chuoi con trong mot chuoi bang mot chuoi con khac */
#include <stdio.h>
#include <string.h>
#include <alloc.h>

char *tim_thay(char *source, char *substr, char *replace)
{
  char *found, *temp, *stemp;
  int pos = 0;

  stemp = strdup(source);
  found = strstr(stemp + pos, substr);
  while (found)
  {
    pos = found - stemp + strlen(replace) - strlen(substr) + 1;
    temp = (char *) malloc(sizeof(stemp) + strlen(replace) - strlen(substr) + 1);
    strncpy(temp, stemp, found - stemp);
    temp[found-stemp] = 0;
    strcat(temp, replace);
    strcat(temp, found + strlen(substr));
    free(stemp);
    stemp = (char *)malloc(sizeof(temp) + 1);
    strcpy(stemp, temp);
    free(temp);
    found = strstr(stemp + pos, substr);
  }
  return stemp;
}

void main()
{
   char source[255], substr[50], replace[50], *result;

   printf("\nNhap chuoi nguon : ");
   gets(source);
   printf("\nNhap chuoi tim kiem : ");
   gets(substr);
   printf("\nNhap chuoi thay the : ");
   gets(replace);
   result = tim_thay(source, substr, replace);
   printf("\nKet qua = %s", result);
   getch();
}