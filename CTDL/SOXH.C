#include <stdio.h>
#include <string.h>

void main()
{
  char source[250], substr[250], *found;
  int count = 0;

  printf("\nNhap chuoi nguon : ");
  gets(source);
  printf("\nNhap chuoi tim kiem : ");
  gets(substr);
  found = source;
  while ((found = strstr(found, substr)) != NULL)
  {
    count++;
    found++;
  }
  printf("\nSo lan xuat hien = %d", count);
  getch();
}