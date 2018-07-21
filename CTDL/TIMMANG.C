#include <stdio.h>

#define MAX 10

int tim_nhi_phan(int mang[], int x)
{
  int i, start = 0, end = MAX;

  do {
    i = (end - start) / 2;
    if (mang[i] < x)
      start = i;
    else if (mang[i] > x)
      end = i;
  } while (mang[i] != x && end > start);
  return i;
}

void main()
{
  int mang[MAX], i, x, n;

  printf("\nNhap vao 10 phan tu tang dan cua mang");
  for (i=0; i<MAX; i++)
    scanf("%d", &mang[i]);
  printf("\nNhap vao gia tri can tim : ");
  scanf("%d", &x);
  n = tim_nhi_phan(mang, x);
  if (n)
    printf("\nGia tri tim thay tai chi so %d", n);
  else
    printf("\nKhong tim thay trong mang");
  getch();
}