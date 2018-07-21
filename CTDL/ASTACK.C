#include <stdio.h>

#define MAX 100

int stack[MAX + 1];
int top;

void khoi_tao_stack()
{
  top = -1;
}

int is_empty()
{
  return (top == -1);
}

int is_full()
{
  return (top == MAX);
}

int push(int value)
{
  if (top < MAX)
    stack[++top] = value;
  return top;
}

int pop(int *value)
{
  *value = stack[top--];
  return top;
}

void main()
{
  int k;

  khoi_tao_stack();
  printf("\nNhap cac phan tu vao stack (-1 de ket thuc) : ");
  do {
    scanf("%d", &k);
    if (k != -1)
      push(k);
  } while (k != -1 && !is_full());
  printf("\n\nLay cac phan tu tu stack ra : ");
  while (!is_empty())
  {
    pop(&k);
    printf("%d ", k);
  }
  getch();
}