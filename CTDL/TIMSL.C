/* Tim mot phan tu trong mot DSLK */
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
  printf("Cac gia tri cua danh sach (tang dan) : ");
  while (tmp != NULL)
  {
    printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

int tim(struct node *first, int x)
{
  int n = 0;
  while (first != NULL && first->element < x)
  {
    n++;
    first = first->next;
  }
  if (first->x != x)
    return -1;
  return n;
}

void main()
{
  struct node *first, *last;
  int n, x;

  khoi_tao_ds(&first, &last);
  nhap_ds(&first, &last);
  print_ds(first);
  printf("\nNhap vao gia tri can tim : ");
  scanf("%d", &x);
  n = tim(first, x);
  if (n!=-1)
    printf("\nGia tri %d tim thay tai nut thu %d", x, n);
  else
    printf("\nKhong tim thay gia tri %d", x);
  getch();
}