#include <stdio.h>

typedef int element_type;
struct node {
  element_type element;
  struct node *next;
} *first = NULL;

void insert(element_type e)
{
  struct node *tmp, *t;
  tmp = (struct node*) malloc(sizeof(struct node));
  tmp->element = e;
  tmp->next = NULL;
  if (first == NULL)
    first = tmp;
  else
  {
    t = first;
    while (t->next != NULL)
      t = t->next;
    t->next = tmp;
  }
}

struct node *nutcuoi(struct node *first)
{
  struct node *tmp;
  tmp = first;
  while (tmp != NULL && tmp->next != NULL)
    tmp = tmp->next;
  return tmp;
}

void main()
{
  element_type e;
  struct node *tmp;

  printf("\nNhap cac gia tri so (-1) de ket thuc : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e);
  } while (e != -1);

  tmp = nutcuoi(first);
  if (tmp)
    printf("Nut cuoi co gia tri = %d", tmp->element);
  getch();

  tmp = first;
  while (tmp != NULL)
  {
    tmp = first->next;
    free(first);
    first = tmp;
  }
}