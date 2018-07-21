/* Bai tap 3_34 - Tim phan hieu cua hai danh sach lien ket */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>

typedef struct tagsl {
  int key;
  struct tagsl *next;
} SL;

SL *L1, *L2, *L;

void initialize()
{
  L1 = L2 = L = NULL;
  clrscr();
  randomize();
}

void cleanup()
{
  SL *f;

  while (L1 != NULL)
  {
    f = L1;
    L1 = L1->next;
    free(f);
  }
  while (L2 != NULL)
  {
    f = L2;
    L2 = L2->next;
    free(f);
  }
  while (L != NULL)
  {
    f = L;
    L = L->next;
    free(f);
  }
  L1 = L2 = L = NULL;
}

void insert(SL **l, int key)
{
  SL *s, *a, *b;

  s = (SL *)malloc(sizeof(SL));
  s->key = key;
  s->next = NULL;
  if (*l==NULL)
    *l = s;
  else
  {
    a = NULL;
    b = *l;
    while (b!=NULL && b->key < key)
    {
      a = b;
      b = b->next;
    }
    if (a == NULL)
    {
      s->next = *l;
      *l = s;
    }
    else
    {
      a->next = s;
      s->next = b;
    }
  }
}

void inds(SL *l)
{
  SL *f;
  printf("\nDanh sach : ");
  f = l;
  while (f != NULL)
  {
    printf("%3d", f->key);
    f = f->next;
  }
}

void taods(SL **l)
{
  int i, j, trung[50];
  for (j=0; j<50; j++)
    trung[j] = 0;
  i = 0;
  while(i<10)
  {
    do {
      j = random(50);
    } while(trung[j] == 1);
    trung[j] = 1;
    insert(l, j);
    i++;
  }
}

void hieusl(SL *l1, SL *l2, SL **l)
{
  while (l1 != NULL && l2 != NULL)
  {
    while (l2->key < l1->key && l2 != NULL)
      l2 = l2->next;
    if (l2 != NULL)
    {
      if (l1->key != l2->key)
      {
        insert(l, l1->key);
        l1 = l1->next;
      }
      else
      {
        l1 = l1->next;
        l2 = l2->next;
      }
    }
  }
  while (l1 != NULL)
  {
    insert(l, l1->key);
    l1 = l1->next;
  }
}
/*
    if (l1->key < l2->key)
    {
      insert(l, l1->key);
      l1 = l1->next;
    }
    else if(l1->key > l2->key)
    {
      insert(l, l2->key);
      l2 = l2->next;
    }
    else if(l1->key == l2->key)
    {
      insert(l, l1->key);
      l2 = l2->next;
      l1 = l1->next;
    }
  }
  if (l1 != NULL)
  {
    while (l1 != NULL)
    {
      insert(l, l1->key);
      l1 = l1->next;
    }
  }
  if (l2 != NULL)
  {
    while (l2 != NULL)
    {
      insert(l, l2->key);
      l2 = l2->next;
    }
*/
void main()
{
  initialize();
  taods(&L1);
  taods(&L2);
  inds(L1);
  inds(L2);
  printf("\nHieu cua danh sach L1 voi L2  = ");
  hieusl(L1, L2, &L);
  inds(L);
  cleanup();
  getch();
}