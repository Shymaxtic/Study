/* Sap bang phuong phap chon lua truc tiep */
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

void sssort()
{
  int i, j, k, x, mx;
  for (i=0; i<MAX-1; i++)
  {
    mx = mang[i];
    k = i;
    for (j=i+1; j<MAX; j++)
      if (mang[j] < mx)
      {
        mx = mang[j];
        k = j;
      }
    x = mang[k];
    mang[k] = mang[i];
    mang[i] = x;
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
  sssort();
  printf("\nSau khi sap : ");
  in_mang(mang);
  getch();
}