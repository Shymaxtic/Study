#include <stdio.h>
#include <mem.h>

#define MAX 100

void in_mang(int mang[], int n)
{
  int i;
  for (i=0; i<n; i++)
    printf("%d ", mang[i]);
}

void loc_mang(int mang[], int *n)
{
   int i, j, tmpn;
   tmpn = *n;
   for (i=0; i<*n-1; i++)
     for (j=i+1; j<*n; j++)
     {
       if (mang[i] == mang[j])
       {
         memmove(&mang[j], &mang[j+1], MAX - j);
         tmpn--;
       }
     }
   *n = tmpn;
}

void main()
{
   int mang[MAX], i, n;

   printf("\nCho biet so phan tu cua mang : ");
   scanf("%d", &n);
   printf("\nNhap cac phan tu cua mang : ");
   for (i=0; i<n; i++)
     scanf("%d", &mang[i]);
   printf("\nTruoc khi loc mang co : ");
   in_mang(mang, n);
   loc_mang(mang, &n);
   printf("\nSau khi loc mang co : ");
   in_mang(mang, n);
   getch();
}