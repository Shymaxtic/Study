/* Giai thuat tim kiem chuoi Brute-Force */
#include <stdio.h>

char *Brute_Force(char *source, char *substr, int *k)
{
   int  i = 0, j = 0, m, n;
   n = strlen(source) - 1;
   m = strlen(substr) - 1;
   do {
     if (source[i] == substr[j])
     {
       i++;
       j++;
     }
     else
     {
        i = i - j + 2;
        j = 0;
     }
   } while (j <= m && i <= n);
   if (j > m)
   {
     *k = i - m - 1;
     return source + i - m - 1;
   }
   else
     return NULL;
}

void main()
{
   char source[255], substr[50], *found;
   int k;

   printf("\nNhap chuoi nguon : ");
   gets(source);
   printf("\nNhap chuoi tim kiem : ");
   gets(substr);
   found = Brute_Force(source, substr, &k);
   if (found)
   {
     printf("\nTim thay tai vi tri : %d", k);
     printf("\nChuoi tim thay : %s", found);
   }
   else
     printf("\nKhong tim thay chuoi.");
   getch();
}