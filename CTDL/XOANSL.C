/* Bai tap 3_31 - Xoa phan tu thu N trong mot danh sach lien ket */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>

typedef struct tagsl {
  int key;
  struct tagsl *next;
} SL;

SL *first, *last;

void initialize()
{
  first = last = NULL;
}

void cleanup()
{
  SL *f;

  while (first != NULL)
  {
    f = first;
    first = first->next;
    free(f);
  }
  first = last = NULL;
}

void insert(int key)
{
  SL *s;

  s = (SL *)malloc(sizeof(SL));
  s->key = key;
  s->next = NULL;
  if (first == NULL)
    first = last = s;
  else
  {
    last->next = s;
    last = last->next;
  }
}

void inds()
{
  SL *f;
  printf("\nDanh sach : ");
  f = first;
  while (f != NULL)
  {
    printf("%3d", f->key);
    f = f->next;
  }
}

int xoa_n(int n)
{
  SL *f, *a;
  int i = 0;
  a = NULL;
  f = first;
  while (i<n && f!= NULL)
  {
    i++;
    a = f;
    f = f->next;
  }
  if (f == NULL)
    return 0;
  else
  {
    if (a == NULL)
    {
      first  = f->next;
      free(f);
    }
    else if (f->next == NULL)
    {
      last = a;
      last->next = NULL;
      free(f);
    }
    else
    {
      a->next = f->next;
      free(f);
    }
    return 1;
  }
}

void main()
{
  int i, n;
  initialize();
  randomize();
  for (i=0; i<20; i++)
    insert(random(20));
  inds();
  do {
    printf("\nXoa phan tu thu (<0 de thoat) : ");
    scanf("%d", &n);
    if (n>-1)
    {
      if (xoa_n(n))
        inds();
      else
        printf("Danh sach co it hon %d phan tu", n+1);
    }
  } while (n > -1);
  cleanup();
}