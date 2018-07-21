#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int mang[MAX];

void in_mang(int *mang)
{
  int i;
  for (i=0; i<MAX; i++)
    printf("%d ", mang[i]);
}

void sort(int l, int r)
{
  int i, j, x, w;
  i = l;
  j = r;
  x = mang[(l+r)/2];
  do {
    while (mang[i] < x)
      i++;
    while (x < mang[j])
      j--;
    if (i <= j)
    {
      w = mang[i];
      mang[i] = mang[j];
      mang[j] = w;
      i++;
      j--;
    }
  } while (i<=j);
  if (l < j)
    sort(l, j);
  if (i < r)
    sort(i, r);
}

void quicksort()
{
  sort(0, MAX-1);
}

void main()
{
  int i;

  randomize();
  for (i=0; i<MAX; i++)
    mang[i] = random(100);
  printf("\nTruoc khi sap : ");
  in_mang(mang);
  quicksort();
  printf("\nSau khi sap : ");
  in_mang(mang);
  getch();
}