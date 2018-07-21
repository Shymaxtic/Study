#include <stdio.h>

typedef struct node *node_ptr;
typedef int element_type;

struct node {
  element_type element;
  node_ptr next;
};

void initialize(node_ptr *list)
{
  *list = NULL;
}

node_ptr insert_before(element_type e, node_ptr *list)
{
  node_ptr p;
  p = (node_ptr)malloc(sizeof(struct node));
  p->element = e;
  p->next = *list;
  return p;
}

node_ptr insert_after(element_type e, node_ptr *list)
{
  node_ptr p, tmp_cell;
  if (*list == NULL)
    return (*list = insert_before(e, *list));
  else
  {
     tmp_cell = *list;
     while (tmp_cell->next)
       tmp_cell = tmp_cell->next;
     p = (node_ptr)malloc(sizeof(struct node));
     p->element = e;
     p->next = *list;
     p->next = NULL;
     tmp_cell->next = p;
     return p;
  }
}

void main()
{
   element_type e;
   node_ptr L, P, xp, xl;
   int i, n, k;

   initialize(&L);
   initialize(&P);
   printf("\nNhap vao cac phan tu cua danh sach (-1 de ket thuc) : ");
   do {
     scanf("%d", &e);
     if (e != -1)
       insert_after(e, &L);
   } while (e != -1);
   printf("\nNhap vao cac gia tri chi thu tu can lay trong danh sach L (-1 de ket thuc) : ");
   do {
     scanf("%d", &e);
     if (e != -1)
       insert_after(e, &P);
   } while (e != -1);
   n = 1;
   xl = L;
   xp = P;
   do {
     k = xp->element;
     for (i=0; i<k-n; i++)
       if (xl)
         xl = xl->next;
     if (xl)
       printf("\nPhan tu thu %d = %d", k, xl->element);
     xp = xp->next;
     n = k;
   } while ((xp != NULL) && (xl != NULL));
  getch();
}