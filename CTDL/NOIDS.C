#include <stdio.h>

typedef int element_type;
struct node {
  element_type element;
  struct node *next;
} *first1 = NULL, *first2 = NULL, *first3 = NULL;

void insert(element_type e, struct node **first)
{
  struct node *tmp, *t;
  tmp = (struct node*) malloc(sizeof(struct node));
  tmp->element = e;
  tmp->next = NULL;
  if (*first == NULL)
    *first = tmp;
  else
  {
    t = *first;
    while (t->next != NULL)
      t = t->next;
    t->next = tmp;
  }
}

void xoads(struct node **first)
{
  struct node *tmp;

  tmp = *first;
  while (tmp != NULL)
  {
    tmp = (*first)->next;
    free(*first);
    *first = tmp;
  }
}

void print_list(struct node *first)
{
  struct node *tmp;

  tmp = first;
  while (tmp != NULL)
  {
    printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

void noids(struct node *first1, struct node *first2, struct node **first3)
{
  struct node *tmp, *tmp1, *tmp2;

  tmp1 = first1;
  tmp2 = first2;
  if (first2 == NULL)
  {
    *first3 = first1;
    tmp = *first3;
    while (first1 != NULL)
    {
      first1 = first1->next;
      tmp->next = first1;
      tmp = tmp->next;
    }
  }
  else if (first1 == NULL)
  {
    *first3 = first1;
    tmp = *first3;
    while (first1 != NULL)
    {
      first1 = first1->next;
      tmp->next = first1;
      tmp = tmp->next;
    }
  }
  else
  {
    if (first1->element < first2->element)
    {
      *first3 = first1;
      tmp1 = first1->next;
    }
    else
    {
      *first3 = first2;
      tmp2 = first2->next;
    }
    tmp = *first3;
    while (tmp1 != NULL && tmp2 != NULL)
    {
      if (tmp1->element < tmp2->element)
      {
        tmp->next = tmp1->element;
        tmp1 = tmp1->next;
      }
      else
      {
        tmp->next = tmp2->element;
        tmp2 = tmp2->next;
      }
    }
    if (tmp1 == NULL)
    {

    }
    else
    {
    }
  }
}

void main()
{
  element_type e;

  printf("\nNhap cac gia tri tang dan cho danh sach 1 (-1 de ket thuc) : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e, &first1);
  } while (e != -1);
  printf("\nNhap cac gia tri tang dan cho danh sach 2 (-1 de ket thuc) : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e, &first2);
  } while (e != -1);
  printf("\nTruoc khi noi DS 1 co : ");
  print_list(first1);
  printf("\nTruoc khi noi DS 2 co : ");
  print_list(first2);
  noids(first1, first2, &first3);
  printf("\nSau khi noi DS 3 co : ");
  print_list(first3);

  xoads(&first1);
  xoads(&first2);
}