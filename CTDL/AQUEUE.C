#include <stdio.h>

#define MAX 100

int queue[MAX + 1];
int front, rear, queue_size;

void khoi_tao_queue()
{
  front = rear = 0;
  queue_size = 0;
}

int is_empty()
{
  return (queue_size == 0);
}

int is_full()
{
  return (queue_size == MAX);
}

int push(int value)
{
  if (queue_size < MAX)
  {
    queue_size++;
    queue[rear++] = value;
    if (rear == MAX)
      rear = 0;
  }
  return rear;
}

int pop(int *value)
{
  if (queue_size > 0)
  {
    *value = queue[front++];
    if (front > MAX)
      front = 0;
    queue_size--;
  }
  return front;
}

void main()
{
  int k;

  khoi_tao_queue();
  printf("\nNhap cac phan tu vao queue (-1 de ket thuc) : ");
  do {
    scanf("%d", &k);
    if (k != -1)
      push(k);
  } while (k != -1 && !is_full());
  printf("\n\nLay cac phan tu tu queue ra : ");
  while (!is_empty())
  {
    pop(&k);
    printf("%d ", k);
  }
  getch();
}