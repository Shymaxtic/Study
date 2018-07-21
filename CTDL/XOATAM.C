/* Xoa tam 1 phan tu trong DSLK */
#include <stdio.h>

typedef int element_type;
struct node {
  element_type element;
  struct node *next;
  int signature;
};

void khoi_tao_ds(struct node **first, struct node **last)
{
  *first = *last = NULL;
}

void insert(element_type e, struct node **first, struct node **last)
{
  struct node *tmp;
  tmp = (struct node*) malloc(sizeof(struct node));
  tmp->element = e;
  tmp->signature = 0;
  tmp->next = NULL;
  if (*first == NULL)
    *first = *last = tmp;
  else
  {
    (*last)->next = tmp;
    (*last) = (*last)->next;
  }
}

void delete_node(element_type e, struct node *first)
{
  struct node *tmp;
  tmp = first;
  while (tmp != NULL && tmp->element != e)
    tmp = tmp->next;
  if (tmp != NULL)
    tmp->signature = 1;
}

void recover_node(element_type e, struct node *first)
{
  struct node *tmp;
  tmp = first;
  while (tmp != NULL && tmp->element != e)
    tmp = tmp->next;
  if (tmp != NULL)
    tmp->signature = 0;
}

void xoa_ds(struct node **first, struct node **last)
{
  struct node *tmp;
  tmp = *first;
  while (tmp != NULL)
  {
    tmp = (*first)->next;
    free(*first);
    *first = tmp;
  }
  *first = *last = NULL;
}

void nhap_ds(struct node **first, struct node **last)
{
  element_type e;
  printf("\nNhap cac gia tri so (-1) de ket thuc : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e, first, last);
  } while (e != -1);
}

void print_ds(struct node *first)
{
  struct node *tmp;

  tmp = first;
  printf("\nCac gia tri cua danh sach : ");
  while (tmp != NULL)
  {
    if (tmp->signature == 0)
      printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

void main()
{
  struct node *first, *last;
  element_type e;

  khoi_tao_ds(&first, &last);
  nhap_ds(&first, &last);
  print_ds(first);
  do {
    printf("\nNhap cac gia tri can xoa tam (-1 de ket thuc) : ");
    scanf("%d", &e);
    if (e != -1)
      delete_node(e, first);
  } while (e != -1);
  print_ds(first);
  do {
    printf("\nNhap cac gia tri can phuc hoi (-1 de ket thuc) : ");
    scanf("%d", &e);
    if (e != -1)
      recover_node(e, first);
  } while (e != -1);
  print_ds(first);
  getch();
}