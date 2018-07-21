/* Tim vi tri xuat hien cuoi cung cua mot chuoi con trong mot chuoi */
#include <stdio.h>
#include <string.h>

int xhcuoi (char *source, char *substr)
{
  char *found, *tmpstr;
  tmpstr = found = source;
  while ((found = strstr(found, substr)) != NULL)
  {
    tmpstr = found;
    found++;
  }
  return tmpstr - source;
}
void main()
{
  char source[250], substr[250];

  printf("\nNhap chuoi nguon : ");
  gets(source);
  printf("\nNhap chuoi tim kiem : ");
  gets(substr);
  printf("\nVi tri xuat hien cuoi cung = %d", xhcuoi(source, substr));
  getch();
}