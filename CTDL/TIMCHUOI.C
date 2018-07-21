#include <stdio.h>
#include <string.h>
#include <alloc.h>

void timchuoi(char *source, char *substr, int *k)
{
  char *stmp, *dtmp, *found;

  stmp = strupr(strdup(source));
  dtmp = strupr(strdup(substr));
  found = strstr(stmp, dtmp);
  if (found)
    *k = found - stmp;
  else
    *k = -1;
  free(stmp);
  free(dtmp);
}

void main()
{
  char source[255], substr[50];
  int k;

  printf("\nNhap chuoi nguon : ");
  gets(source);
  printf("\nNhap chuoi tim kiem : ");
  gets(substr);
  timchuoi(source, substr, &k);
  if (k != -1)
    printf("\nChuoi tim thay tai vi tri : %d", k);
  else
    printf("\nKhong tim thay chuoi da cho");

  getch();
}