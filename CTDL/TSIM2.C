/* Kiem tra xem hai cay co dang cau nhau khong */
#include <stdio.h>
#include <alloc.h>

typedef int element_type;
typedef struct node {
  element_type element;
  struct node *left, *right;
} NODE;

NODE *root1, *root2;

void khoi_tao_cay(NODE **root)
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
    scanf("%d%*c", &e);
    if (e != -1)
      insert_node(e, root);
  } while (e != -1);
}

int kiemtra(NODE *root1, NODE *root2)
{
  if (root1 != NULL && root2 != NULL)
    if (kiemtra(root1->left, root2->right) &&
        kiemtra(root1->right, root2->left))
      return 1;
    else
     return 0;
  else
    if (root1 == NULL && root2 == NULL)
      return 1;
    else
      return 0;
}

void main()
{
   khoi_tao_cay(&root1);
   nhap_cay(&root1);
   khoi_tao_cay(&root2);
   nhap_cay(&root2);
   if (kiemtra(root1, root2))
     printf("\nHai cay da cho tuong tu cau truc");
   else
     printf("\nHai cay da cho khac cau truc");
   getch();
}