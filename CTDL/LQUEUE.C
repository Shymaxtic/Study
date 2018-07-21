/* Bai tap 3_61 - Quan ly QUEUE bang danh sach lien ket */
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <stdlib.h>

typedef struct tagqueue {
  int value;
  struct tagqueue *next;
} QUEUE;

QUEUE *first;

int isempty()
{
  return (first->next == NULL);
}

void push(int value)
{
  QUEUE *f;

  f = (QUEUE *)malloc(sizeof(QUEUE));
  f->value = value;
  f->next = first->next;
  first->next = f;
}

int pop()
{
  QUEUE *f;
  int value;
  if (!isempty())
  {
    f = first->next;
    first->next = first->next->next;
    value = f->value;
  }
  else
    value = -1;
  return value;
}

void initqueue()
{
  first = (QUEUE *)malloc(sizeof(QUEUE));
  first->next = NULL;
}

void release(QUEUE *f)
{
  if (f->next != NULL)
    release(f->next);
  free(f);
}

void cleanup()
{
  release(first);
}

void main()
{
  int i, n;
  clrscr();
  initqueue();
  randomize();
  for (i=0; i<20; i++)
  {
    n = random(20);
    printf("\nPUSH %d vao queue", n);
    push(n);
  }
  printf("\nLay cac phan tu tu QUEUE : ");
  while (!isempty())
    printf("%3d", pop());
  getch();
}
