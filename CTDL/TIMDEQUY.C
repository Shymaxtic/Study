/* Tim mot phan tu trong mot DSLK bang de quy */
#include <stdio.h>

typedef int element_type;
struct node {
  element_type element;
  struct node *next;
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
  tmp->next = NULL;
  if (*first == NULL)
    *first = *last = tmp;
  else
  {
    (*last)->next = tmp;
    (*last) = (*last)->next;
  }
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
  printf("Cac gia tri cua danh sach : ");
  while (tmp != NULL)
  {
    printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

struct node *timdequy(struct node *first, element_type e)
{
  if (first == NULL)
    return NULL;
  else
    if (first->element == e)
       return first;
    else
      return timdequy(first->next, e);
}

void main()
{
  struct node *first, *last, *tim;
  element_type e;

  khoi_tao_ds(&first, &last);
  nhap_ds(&first, &last);
  print_ds(first);
  printf("\nNhap gia tri can tim : ");
  scanf("%d", &e);
  tim = timdequy(first, e);
  if (tim)
    printf("Tim thay");
  else
    printf("Khong tim thay");
  getch();
}