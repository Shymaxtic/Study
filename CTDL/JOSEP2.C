/* Bai tap 3_42 - Bai toan Josephus nguoc */
#include <stdio.h>
#include <conio.h>

#define MIN 5
#define MAX 26
int y;

int Josephus(int tongso, int sodem, int vitri)
{
  int ds[MAX], i, oldtongso, start = 0;

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
      break;
  if (vitri >= i)
    start = vitri - i;
  else
    start = oldtongso - i + vitri;
  return start;
}

void main()
{
  int n, m, k, nguoichon;

  printf("\nCho biet so luong binh si (%d -> %d) : ", MIN, MAX);
  do {
    scanf("%d", &m);
  } while (m<MIN || m>MAX);
  printf("\nCho biet vi tri binh si muon di : ");
  scanf("%d", &k);
  printf("\nCho biet gia tri dem : ");
  scanf("%d", &n);
  printf("\nCac binh si gom : \n");
  for (nguoichon = 0; nguoichon < m; nguoichon++)
    printf("%c ", nguoichon+'A');
  y = wherey();
  nguoichon = Josephus(m, n, k);
  printf("\nNguoi phai duoc dem dau tien la binh si %c", nguoichon+'A');
  getch();
}