/* Bai tap 3_86 - Tim tat ca cac hoan vi cua mot mang 5 phan tu */
#include <stdio.h>

int mang[5];

void swap (int *x, int *y)
{
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void hoanvi(int k)
{
  int j;

  if (k==1)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%d ", mang[j]);
  }
  else
    for (j=k-1; j>=0; j--)
    {
      swap(&mang[k-1], &mang[j]);
      hoanvi(k-1);
      swap(&mang[j], &mang[k-1]);
    }
}

void main()
{
  int i;

  for (i=0; i<5; i++)
    mang[i] = i;
  hoanvi(5);
  getch();
}