/* Quan ly SV bang DSLK */
#include <stdio.h>
#include <ctype.h>
#include <mem.h>
#include <string.h>

#define MAX 100
#define TOAN 0
#define LY   1
#define HOA  2

struct sinhvien {
  char mslop[5];
  char hoten[35];
  float diem[3];
  struct sinhvien *next;
} *first, *last;

int n = 0;

void nhapmoi()
{
  char mslop[5], tmp[3];
  int i;
  float diem[3];
  struct sinhvien *svtmp;

  do {
    printf("\nCho biet ma so lop : ");
    gets(mslop);
    if (strlen(mslop))
    {
      svtmp = (struct sinhvien *) malloc(sizeof(struct sinhvien));
      strcpy(svtmp->mslop, mslop);
      printf("\nCho biet ho ten : ");
      gets(svtmp->hoten);
      printf("\nCho biet diem so : ");
      for (i=0; i<3; i++)
      {
        scanf("%f", &diem[i]);
        svtmp->diem[i] = diem[i];
      }
      gets(tmp);
      n++;
      svtmp->next = NULL;
      if (first == NULL)
        first = last = svtmp;
      else
      {
        last->next = svtmp;
        last = last->next;
      }
    }
  } while (strlen(mslop));
}

void timkiem()
{
  char mslop[5];
  int found = 0;
  struct sinhvien *svtmp;

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  printf("\nCho biet ma so lop : ");
  gets(mslop);
  if (strlen(mslop))
    while (svtmp != NULL)
      if (stricmp(svtmp->mslop, mslop) == 0)
      {
         printf("\nMa so lop : %s", svtmp->mslop);
         printf("\nHo va ten : %s", svtmp->hoten);
         printf("\nDiem Toan : %f", svtmp->diem[TOAN]);
         printf("\nDiem Ly   : %f", svtmp->diem[LY]);
         printf("\nDiem Hoa  : %f", svtmp->diem[HOA]);
         found = 1;
         break;
      }
      else
        svtmp = svtmp->next;
  if (!found)
    printf("\nKhong tim thay!!!");
}

void xoa()
{
  char mslop[5], traloi;
  int i = 0, j;
  struct sinhvien *svtmp, *before = NULL;

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  printf("\nCho biet ma so lop : ");
  gets(mslop);
  if (strlen(mslop))
    while (i<n)
      if (stricmp(svtmp->mslop, mslop) == 0)
      {
         printf("\nMa so lop : %s", svtmp->mslop);
         printf("\nHo va ten : %s", svtmp->hoten);
         printf("\nDiem Toan : %f", svtmp->diem[TOAN]);
         printf("\nDiem Ly   : %f", svtmp->diem[LY]);
         printf("\nDiem Hoa  : %f", svtmp->diem[HOA]);
         printf("\nCo muon xoa khong (C/K)? ");
         do {
           traloi = toupper(getch());
         } while (traloi != 'C' && traloi != 'K');
         putc(traloi, stdout);
         if (traloi == 'C')
         {
           n--;
           if (before == NULL)
           {
             before = first;
             first = first->next;
           }
           else
             before->next = svtmp->next;
           free(svtmp);
           break;
         }
      }
      else
      {
        before = svtmp;
        svtmp = svtmp->next;
      }
}

void menu()
{
  printf("\n***************");
  printf("\n* 1. Them     *");
  printf("\n* 2. Xoa      *");
  printf("\n* 3. Tim kiem *");
  printf("\n* 0. Thoat    *");
  printf("\n***************");
  printf("\nChon lua ? ");
}

void main()
{
  char traloi;
  first = last = NULL;
  do {
    menu();
    do {
      traloi = getch();
    } while (traloi < '0' || traloi > '3');
    putc(traloi, stdout);
    switch (traloi)
    {
       case '1' : nhapmoi();
                  break;
       case '2' : xoa();
                  break;
       case '3' : timkiem();
                  break;
    }
  } while (traloi != '0');
}