/* Bai tap 3_2 - Minh hoa giai thuat Knuth - Morris - Pratt */
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX 256

int KMP(char *source, char *find);

void main()
{
  char source[MAX], find[MAX];
  int f;

  printf("\nNhap vao chuoi nguon : ");
  gets(source);
  printf("Nhap vao chuoi tim kiem : ");
  gets(find);

  if ((f = KMP(source, find)) >= 0)
    printf("chuoi tim thay tai chi so %d", f);
  getch();
}

int KMP(char *source, char *find)
{
  int next[MAX], i = 0, len, j=-1, lensource;

  len = strlen(find);
  lensource = strlen(source);
  next[0] = -1;
  do {
    if (j == -1 || find[i] == find[j])
    {
      i++;
      j++;
      next[i] = j;
    }
    else
      j = next[j];
  } while (i < len-1);
  i = j = 0;
  do {
    if (j==0 || source[i] == find[j])
    {
      i++;
      j++;
    }
    else
      j = next[j];
  } while (j<len && i<lensource);
  if (j>=len)
    return i-len;
  else
    return -1;
}