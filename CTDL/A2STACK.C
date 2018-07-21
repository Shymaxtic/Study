/* Bai tap 3_67 - Quan ly hai STACK chi dung 1 day */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX 100

int stack[2*MAX];
int top1, top2;

void initstack()
{
  top1 = -1;
  top2 = 2*MAX;
}

void push(int value, int _stack)
{
  if (_stack == 0)
  {
    if (top1<top2)
      stack[++top1] = value;
  }
  else
  {
    if (top1<top2)
      stack[--top2] = value;
  }
}

int isempty(int _stack)
{
  if (_stack == 0)
    return top1 == -1;
  else
    return top2 == 2*MAX;
}

int pop(int _stack)
{
  if (_stack == 0)
    if (!isempty(_stack))
      return(stack[top1--]);
  if (!isempty(_stack))
    return stack[top2++];
  else
    return -1;
}

void main()
{
  int i, value, _stack;

  initstack();
  randomize();
  for (i = 0; i<20; i++)
  {
    _stack = random(2);
    value  = random(10);
    printf("\nPUSH %d vao stack %d", value, _stack);
    push(value, _stack);
  }
  printf("\nLay nhung gia tri tu stack 0 : ");
  while (!isempty(0))
    printf("%3d", pop(0));
  printf("\nLay nhung gia tri tu stack 1 : ");
  while (!isempty(1))
    printf("%3d", pop(1));
  getch();
}