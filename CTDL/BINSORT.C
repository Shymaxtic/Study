/* Chen nhi phan */
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

void binarysort()
{
  int i, j, x, l, r, m;
  for (i=1; i<MAX; i++)
  {
    x = mang[i];
    l = 0;
    r = i-1;
    while (l <= r)
    {
      m = (l + r) / 2;
      if (x < mang[m])
        r = m - 1;
      else
        l = m + 1;
    }
    if (x < mang[l])
    {
      for (j=i-1; j>=l; j--)
        mang[j+1] = mang[j];
      mang[l] = x;
    }
  }
}

void main()
{
  int i;

  randomize();
  for (i=0; i<MAX; i++)
    mang[i] = random(100);
  printf("\nTruoc khi sap : ");
  in_mang(mang);
  binarysort();
  printf("\nSau khi sap : ");
  in_mang(mang);
  getch();
}