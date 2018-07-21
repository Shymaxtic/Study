/* Bai tap 3_13 - Quan ly danh sach sinh vien bang danh sach da lien ket */
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

typedef struct tagsinhvien {
  char hoten[40];
  char mslop[6];
  struct tagsinhvien *nexthoten, *nextmslop;
} SINHVIEN;

SINHVIEN *headht, *headms;

void initialize()
{
  headht = (SINHVIEN *)malloc(sizeof(SINHVIEN));
  headht->nexthoten = NULL;
  headms = (SINHVIEN *)malloc(sizeof(SINHVIEN));
  headms->nextmslop = NULL;
}

void release(SINHVIEN *s)
{
  if (s->nexthoten)
    release(s->nexthoten);
  free(s);
}

void cleanup()
{
  if (headht->nexthoten)
    release(headht->nexthoten);
  free(headht);
  free(headms);
}

void inds_ht(SINHVIEN *s)
{
  if (s == NULL)
    return;
  printf("\n%-6s %-40s", s->mslop, s->hoten);
  inds_ht(s->nexthoten);
}

void inds_ms(SINHVIEN *s)
{
  if (s == NULL)
    return;
  printf("\n%-6s %-40s", s->mslop, s->hoten);
  inds_ms(s->nextmslop);
}

void in_hoten()
{
  if (headht->nexthoten)
    inds_ht(headht->nexthoten);
}

void in_mslop()
{
  if (headms->nextmslop)
    inds_ms(headms->nextmslop);
}

void insert_hoten(SINHVIEN *s)
{
  SINHVIEN *a, *b;
  if (headht->nexthoten == NULL)
    headht->nexthoten = s;
  else
  {
    a = headht;
    b = headht->nexthoten;
    while (strcmp(b->hoten, s->hoten)<0 && b!= NULL)
    {
      a = a->nexthoten;
      b = b->nexthoten;
    }
    a->nexthoten = s;
    s->nexthoten = b;
  }
}

void insert_mslop(SINHVIEN *s)
{
  SINHVIEN *a, *b;
  if (headms->nextmslop == NULL)
    headms->nextmslop = s;
  else
  {
    a = headms;
    b = headms->nextmslop;
    while (strcmp(b->mslop, s->mslop)<0 && b!= NULL)
    {
      a = a->nextmslop;
      b = b->nextmslop;
    }
    a->nextmslop = s;
    s->nextmslop = b;
  }
}

void insert(char *hoten, char *mslop)
{
  SINHVIEN *s;

  s = (SINHVIEN *)malloc(sizeof(SINHVIEN));
  strncpy(s->hoten, hoten, 40);
  strncpy(s->mslop, mslop, 6);
  s->nexthoten = s->nextmslop = NULL;
  insert_hoten(s);
  insert_mslop(s);
}

void nhapds()
{
  int done = 0;
  char hoten[40], mslop[6];
  do {
    printf("\nNhap ho ten (trong de thoat) : ");
    gets(hoten);
    if (strcmp(hoten, "") == 0)
      done = 1;
    else
    {
      printf("\nNhap ma so lop : ");
      gets(mslop);
      insert(hoten, mslop);
    }
  } while (!done);
}

void main()
{
  initialize();
  nhapds();
  printf("\nDanh sach theo ho ten : ");
  in_hoten();
  printf("\nDanh sach theo ma so lop : ");
  in_mslop();
  getch();
  cleanup();
}