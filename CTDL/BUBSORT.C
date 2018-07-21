/* Cai dat thuat toan Bubble Sort */
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

void bubblesort()
{
  int i, j, x;
  for (i=1; i< MAX; i++)
    for (j=MAX-1; j>=i; j--)
    {
      if (mang[j-1] > mang[j])
      {
        x = mang[j-1];
        mang[j-1] = mang[j];
        mang[j] = x;
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
  bubblesort();
  printf("\nSau khi sap : ");
  in_mang(mang);
  getch();
}