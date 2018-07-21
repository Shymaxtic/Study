/* Bai tap 3_2 - Minh hoa giai thuat Boyer - Moore */
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX 256

int BoyerMoore(char *source, char *find);

void main()
{
  char source[MAX], find[MAX];
  int f;

  printf("\nNhap vao chuoi nguon : ");
  gets(source);
  printf("Nhap vao chuoi tim kiem : ");
  gets(find);

  if ((f = BoyerMoore(source, find)) > 0)
    printf("chuoi tim thay tai chi so %d", f);
  else
    printf("Khong tim thay chuoi da cho", f);
  getch();
}

int BoyerMoore(char *source, char *find)
{
  int skip[MAX], i = 0, len, j=-1, lensource;

  len = strlen(find);
  lensource = strlen(source);
  for (i=0; i<MAX; i++)
    skip[i] = len-1;
  for (i=0; i<len; i++)
    if (skip[find[i]] == len-1)
       skip[find[i]] = len-i-1;

  i = j = len-1;
  do {
    if (source[i] == find[j])
    {
      i--;
      j--;
    }
    else
    {
      if (len-j+1 > skip[source[i]])
        i += len-j+1;
      else
        i += skip[source[i]];
      j = len-1;
    }
  } while (j>0 && i<lensource);

  if (j<=0)
    return i;
  else
    return -1;
}