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
  while (tmp != NULL)
  {
    printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

struct node *daonguocds(struct node **first, struct node **last)
{
   struct node *tmp;

   if (*first != NULL)
   {
     if ((*first)->next != NULL)
     {
       tmp = daonguocds(&((*first)->next), last);
       (*last)->next = *first;
       *last = *first;
       (*last)->next = NULL;
       *first = tmp;
     }
     return *first;
   }
   else
     return NULL;
}

void main()
{
  struct node *first, *last;

  khoi_tao_ds(&first, &last);
  nhap_ds(&first, &last);
  printf("Danh sach ban dau : ");
  print_ds(first);
  daonguocds(&first, &last);
  printf("\nSau khi dao nguoc : ");
  print_ds(first);
  xoa_ds(&first, &last);
  getch();
}