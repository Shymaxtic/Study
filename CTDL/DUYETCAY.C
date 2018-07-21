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

void NLR(NODE *root)
{
  if (root != NULL)
  {
    printf("%d ", root->element);
    NLR(root->left);
    NLR(root->right);
  }
}

void NRL(NODE *root)
{
  if (root != NULL)
  {
    printf("%d ", root->element);
    NRL(root->right);
    NRL(root->left);
  }
}

void LNR(NODE *root)
{
  if (root != NULL)
  {
    LNR(root->left);
    printf("%d ", root->element);
    LNR(root->right);
  }
}

void LRN(NODE *root)
{
  if (root != NULL)
  {
    LRN(root->left);
    LRN(root->right);
    printf("%d ", root->element);
  }
}

void RNL(NODE *root)
{
  if (root != NULL)
  {
    RNL(root->right);
    printf("%d ", root->element);
    RNL(root->left);
  }
}

void RLN(NODE *root)
{
  if (root != NULL)
  {
    RLN(root->right);
    RLN(root->left);
    printf("%d ", root->element);
  }
}

void main()
{
   khoi_tao_cay(&root);
   nhap_cay(&root);
   printf("\nDuyet cay NLR : ");
   NLR(root);
   printf("\nDuyet cay NRL : ");
   NRL(root);
   printf("\nDuyet cay LNR : ");
   LNR(root);
   printf("\nDuyet cay LRN : ");
   LRN(root);
   printf("\nDuyet cay RNL : ");
   RNL(root);
   printf("\nDuyet cay RLN : ");
   RLN(root);
   getch();
}