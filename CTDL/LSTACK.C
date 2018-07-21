#include <stdio.h>

typedef struct node *node_ptr;
typedef int element_type;

struct node {
  element_type element;
  node_ptr next;
};

typedef node_ptr STACK;
STACK S;

STACK khoi_tao_stack()
{
  STACK S;
  S = (STACK) malloc(sizeof(struct node));
  if (S == NULL)
  {
    printf("\nKhong du bo nho!!!");
    exit(1);
  }
  else
    S->next = NULL;
  return S;
}

int is_empty(STACK S)
{
  return (S->next == NULL);
}

node_ptr push(element_type e, STACK S)
{
  node_ptr tmp_cell;

  tmp_cell = (node_ptr) malloc(sizeof(struct node));
  if (tmp_cell != NULL)
  {
    tmp_cell->element = e;
    tmp_cell->next = S->next;
    S->next = tmp_cell;
  }
  return tmp_cell;
}

node_ptr pop(STACK S)
{
  node_ptr cell;

  if (is_empty(S))
    return NULL;
  else
  {
    cell = S->next;
    S->next = S->next->next;
    return cell;
  }
}

void main()
{
  element_type k;
  node_ptr cell;

  S = khoi_tao_stack();
  printf("\nNhap cac phan tu vao stack (-1 de ket thuc) : ");
  do {
    scanf("%d", &k);
    if (k != -1)
      push(k, S);
  } while (k != -1);
  printf("\n\nLay cac phan tu tu stack ra : ");
  while (!is_empty(S))
    if ((cell = pop(S)) != NULL)
      printf("%d ", cell->element);
  getch();
}