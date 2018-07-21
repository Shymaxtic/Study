/* Bai tap 3_41 - Bai toan Josephus */
#include <stdio.h>
#include <conio.h>

#define MIN 5
#define MAX 26
int y;

int Josephus(int tongso, int start, int sodem)
{
  int ds[MAX], i, oldtongso;

  oldtongso = tongso;

  for (i=0; i<tongso; i++)
    ds[i] = 1;
  for (i=tongso; i<MAX; i++)
    ds[i] = 0;
  do {
    i = 1;
    while (i<sodem)
    {
      i++;
      start++;
      if (start > oldtongso-1)
        start = 0;
      while (ds[start] == 0)
      {
        start++;
        if (start > oldtongso-1)
          start = 0;
      }
    }
    ds[start++] = 0;
    while(ds[start] == 0)
    {
      start++;
      if (start > oldtongso-1)
        start = 0;
    }
    tongso--;
  } while (tongso > 1);
  for (i=0; i<MAX; i++)
    if (ds[i] == 1)
      return i;
  return 0;
}

void main()
{
  int n, m, k, nguoichon;

  printf("\nCho biet so luong binh si (%d -> %d) : ", MIN, MAX);
  do {
    scanf("%d", &m);
  } while (m<MIN || m>MAX);
  printf("\nCho biet so thu tu binh si duoc chon : ");
  scanf("%d", &k);
  printf("\nCho biet gia tri dem : ");
  scanf("%d", &n);
  printf("\nCac binh si gom : \n");
  for (nguoichon = 0; nguoichon < m; nguoichon++)
    printf("%c ", nguoichon+'A');
  y = wherey();
  nguoichon = Josephus(m, n, k);
  printf("\nNguoi duoc chon la binh si %c", nguoichon+'A');
  getch();
}