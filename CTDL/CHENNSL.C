/* Chen nut vao vi tri thu N trong DSLK */
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

struct node *insert_at_n(element_type e, int n)
{
  long count = 0;
  struct node *tmp, *t, *before = NULL;

  tmp = first;

  while (tmp != NULL && count <= n)
  {
    count++;
    before = tmp;
    tmp = tmp->next;
  }
  if (before != NULL)
  {
    t = (struct node*)malloc(sizeof(struct node));
    t->element = e;
    if (before == NULL)
    {
       t->next = first;
       first = t;
    }
    else
    {
      before->next = t;
      t->next = tmp;
    }
  }
  else
  {
    printf("Vi tri khong tim thay! Thu tuc chen that bai");
    return NULL;
  }
  return t;
}

void print_list()
{
  struct node *tmp;

  tmp = first;
  while (tmp != NULL)
  {
    printf("%d ", tmp->element);
    tmp = tmp->next;
  }
}

void main()
{
  element_type e;
  int vitri;
  struct node *tmp;

  printf("\nNhap cac gia tri so (-1) de ket thuc : ");
  do {
    scanf("%d", &e);
    if (e != -1)
      insert(e);
  } while (e != -1);

  printf("Nhap gia tri can chen : ");
  scanf("%d", &e);
  printf("Nhap vi tri can chen : ");
  scanf("%d", &vitri);

  printf("\nTruoc khi chen, danh sach gom : \n");
  print_list();
  insert_at_n(e, vitri);
  printf("\nSau khi chen, danh sach gom : \n");
  print_list();

  getch();

  tmp = first;
  while (tmp != NULL)
  {
    tmp = first->next;
    free(first);
    first = tmp;
  }
}