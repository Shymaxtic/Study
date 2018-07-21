/* Chen truc tiep */
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

void straightinsertsort()
{
  int i, j, x;
  for (i=1; i<MAX; i++)
  {
    x = mang[i];
    j = i-1;
    while (x < mang[j] && j >= 0)
    {
      mang[j+1] = mang[j];
      j--;
    }
    mang[j+1] = x;
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
  straightinsertsort();
  printf("\nSau khi sap : ");
  in_mang(mang);
  getch();
}