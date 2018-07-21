/* Bai tap 3_87 - Dem so nut trung gian trong mot cay */
#include <stdio.h>
#include <alloc.h>

typedef int element_type;
typedef struct node {
  element_type element;
  struct node *left, *right;
} NODE;

NODE *root;

#define max(a,b) ((a) > (b)? (a) : (b))

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

int dem_nut_tg(NODE *parent, NODE *root)
{
  if (root == NULL)
    return 0;
  else
    if (root->left == NULL && root->right == NULL)
      return 0;
    else
    {
      if (parent != NULL)
        return dem_nut_tg(root, root->left) +
               dem_nut_tg(root, root->right) + 1;
      else
        return dem_nut_tg(root, root->left) +
               dem_nut_tg(root, root->right) ;
    }
}

void main()
{
   khoi_tao_cay(&root);
   nhap_cay(&root);
   printf("\nSo nut trung gian cua cay = %d", dem_nut_tg(NULL, root));
   getch();
}