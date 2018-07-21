/* Dem so nut trong mot danh sach lien ket */
#include <stdio.h>

typedef int element_type;
struct node {
  element_type element;
  struct node *next;
} *first = NULL, *last = NULL;

void insert(element_type e)
{
  struct node *tmp;
  tmp = (struct node*) malloc(sizeof(struct node));
  tmp->element = e;
  tmp->next = NULL;
  if (first == NULL)
    first = last = tmp;
  else
  {
    last->next = tmp;
    last = last->next;
  }
}

void main()
{
  element_type e;
  int count = 0;
  struct node *tmp;

  printf("\nNhap cac gia tri so (-1) de ket thuc : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e);
  } while (e != -1);

  tmp = first;
  while (tmp != NULL)
  {
    count++;
    tmp = tmp->next;
  }

  printf("\nSo node trong danh sach = %d", count);
  getch();

  tmp = first;
  while (tmp != NULL)
  {
    tmp = first->next;
    free(first);
    first = tmp;
  }
}