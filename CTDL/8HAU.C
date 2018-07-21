/* Bai toan tam hoang hau */
#include <stdio.h>

int dong[8], cot[8], cheoxuoi[15], cheonguoc[15];

void print ()
{
  int i;
  printf("\n");
  for (i=0; i<8; i++)
    printf("%3d", dong[i]);
}

void thu(int i)
{
  int j;
  for (j=0; j<8; j++)
  {
    if (cot[j] == 1 && cheoxuoi[i+j] ==1 && cheonguoc[i-j+7] == 1)
    {
      dong[i] = j;
      cot[j] = 0;
      cheoxuoi[i+j] = 0;
      cheonguoc[i-j+7] = 0;
      if (i<7)
        thu(i+1);
      else
        print();
      cot[j] = 1;
      cheoxuoi[i+j] = 1;
      cheonguoc[i-j+7] = 1;
    }
  }
}

void tim()
{
   int i, q;

   for (i=0; i<8; i++)
   {
     cot[i] = 1;
     dong[i] = -1;
   }
   for (i=0; i<15; i++)
   {
     cheoxuoi[i] = 1;
     cheonguoc[i] = 1;
   }
   thu(0);
}

void main()
{
  tim();
  getch();
}