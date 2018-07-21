#include <stdio.h>
#include <alloc.h>

typedef int element_type;
typedef struct node {
  element_type element;
  struct node *left, *right;
} NODE;

NODE *root;

void khoi_tao_cay(NODE ** root)
{
  *root = NULL;
}

void insert(NODE *tmp, NODE **root)
{

  if (tmp->element < (*root)->element)
    if ((*root)->left)
      insert(tmp, &(*root)->left);
    else
       (*root)->left = tmp;
  else
    if ((*root)->right)
      insert(tmp, &(*root)->right);
    else
       (*root)->right = tmp;
}

void insert_node(element_type e, NODE **root)
{
   NODE *tmp;

   tmp = (NODE *)malloc(sizeof(NODE));
   tmp->element = e;
   tmp->left = NULL;
   tmp->right = NULL;
   if (*root == NULL)
     *root = tmp;
   else
     insert(tmp, root);
}

void nhap_cay(NODE **root)
{
  element_type e;
  do {
    printf("\nNhap element (-1 de ket thuc) : ");
    scanf("%d", &e);
    if (e != -1)
      insert_node(e, root);
  } while (e != -1);
}

int dem_nut_la(NODE *root)
{
  if (root == NULL)
    return 0;
  else
    if (root->left != NULL || root->right != NULL)
      return dem_nut_la(root->left) + dem_nut_la(root->right);
    else
      return 1;
}

void main()
{
   int tong_nut_la;
   khoi_tao_cay(&root);
   nhap_cay(&root);
   tong_nut_la = dem_nut_la(root);
   printf("\nTong so nut la     = %d", tong_nut_la);
   getch();
}