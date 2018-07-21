/* Tim mot phan tu trong mot DSLK khong de quy */
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

struct node *tim(struct node *first, element_type e)
{
  if (first == NULL)
    return NULL;
  else
  {
    while (first->element != e && first != NULL)
      first = first->next;
    return first;
  }
}

void main()
{
  struct node *first, *last, *tmp;
  element_type e;

  khoi_tao_ds(&first, &last);
  nhap_ds(&first, &last);
  print_ds(first);
  printf("\nNhap gia tri can tim : ");
  scanf("%d", &e);
  tmp = tim(first, e);
  if (tmp)
    printf("Tim thay");
  else
    printf("Khong tim thay");
  getch();
}