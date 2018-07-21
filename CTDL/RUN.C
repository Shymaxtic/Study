/* Bai tap 3_17 - Rut cac run tu nhien tu mot danh sach lien ket */
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#include <stdlib.h>

#define MAX 25

typedef struct tag {
  int key;
  struct tag *next;
} SL;

SL *first;

typedef struct tagds {
  SL *s;
  struct tagds *next;
} SL2;

SL2 *firstSL;

void tachrun()
{
  SL *a, *b;
  SL2 *fa, *fb;

  if (first != NULL)
  {
    a = first;
    do {
      fa = (SL2 *)malloc(sizeof(SL2));
      fa->next = NULL;
      fa->s    = a;
      b = a->next;
      while (b != NULL)
      {
        if (b->key < a->key)
          break;
        a = b;
        b = b->next;
      }
      a->next = NULL;
      a = b;
      if (firstSL == NULL)
      {
        firstSL = fa;
        fb = fa;
      }
      else
      {
        fb->next = fa;
        fb = fa;
      }
    } while (b != NULL);
  }
}

void insert(int key)
{
  SL *s, *b;

  s = (SL *)malloc(sizeof(SL));
  s->key = key;
  s->next = NULL;
  if (first == NULL)
    first = s;
  else
  {
    b = first;
    while (b->next != NULL)
      b = b->next;
    b->next = s;
  }
}

void initialize()
{
  int i;
  randomize();
  first = NULL;
  for (i=0; i<MAX; i++)
    insert(random(100));
  firstSL = NULL;
}

void release(SL *s)
{
  if (s->next != NULL)
    release(s->next);
  free(s);
}

void cleanup()
{
  release(first);
}

void in_ds(SL *first)
{
  SL *s;
  printf("\n");
  s = first;
  while (s != NULL)
  {
    printf("%3d", s->key);
    s = s->next;
  }
}

void inds(SL2 *f)
{
  in_ds(f->s);
}

void inrun()
{
  SL2 *f;
  if (firstSL != NULL)
  {
    f = firstSL;
    while (f != NULL)
    {
      inds(f);
      f = f->next;
    }
  }
}

void main()
{
  initialize();
  in_ds(first);
  tachrun();
  inrun();
  getch();
  cleanup();
}