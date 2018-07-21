/* Bai tap 3_52 - In bieu thuc dang hau to cua mot bieu thuc trung to */
#include <stdio.h>
#include <conio.h>

#define MAX 100

#define PLUS     0 /* Dau cong */
#define MINUS    1 /* Dau tru */
#define MULTIPLE 2 /* Dau nhan */
#define DIVIDE   3 /* Dau chia */
#define LPAREN   4 /* Dau mo ngoac don */
#define RPAREN   5 /* Dau dong ngoac don */

int top;

struct {
  int toantu;
} stack[MAX];

void push (int tt)
{
  if (top < MAX-1)
    stack[++top].toantu = tt;
}

int isempty()
{
  return top == -1;
}

int pop (int *tt)
{
  if (!isempty())
  {
    *tt = stack[top--].toantu;
    return 1;
  }
  return 0;
}

int get (int *tt)
{
  if (!isempty())
  {
    *tt = stack[top].toantu;
    return 1;
  }
  return 0;
}

void xet(int tt)
{
  char chuoi[] = "+-*/";
  int uutien[] = {0,0,1,1,-1,-1};
  int toantu, done = 0, val;

  if (isempty())
    push(tt);
  else
  {
    do {
      if (get(&toantu))
      {
        if (uutien[tt] <= uutien[toantu])
        {
          pop(&toantu);
          printf("%c ", chuoi[toantu]);
        }
        else
        {
          push(tt);
          done = 1;
        }
      }
      else
      {
        done = 1;
        push(tt);
      }
    } while (!done);
  }
}

void in_hauto(char *expr)
{
  int len, i=0, ttu, done;
  char c, chuoi[]="+-*/";
  top = -1;
  len = strlen(expr);
  do {
    c = expr[i++];
    while (c == ' ' && i < len-1)
      c = expr[i++];
    switch (c)
    {
      case '0' :
      case '1' :
      case '2' :
      case '3' :
      case '4' :
      case '5' :
      case '6' :
      case '7' :
      case '8' :
      case '9' : printf("%c ", c); break;
      case '+' : xet(PLUS); break;
      case '-' : xet(MINUS); break;
      case '*' : xet(MULTIPLE); break;
      case '/' : xet(DIVIDE); break;
      case '(' : push(LPAREN); break;
      case ')' : done = 0;
                 do {
                   if (isempty())
                   {
                     done = 1;
                     printf("\n\nError\n");
                   }
                   else
                   {
                     pop(&ttu);
                     if (ttu != LPAREN)
                       printf("%c ", chuoi[ttu]);
                     else
                       done = 1;
                   }
                 } while (!done);
                 break;
    }
  } while (i < len);
  while (!isempty())
  {
    pop(&ttu);
    printf("%c ", chuoi[ttu]);
  }
}

void main()
{
  char expr[50];
  int done = 0;

  printf("\nChuong trinh in bieu thuc hau to tuong ung voi mot bieu thuc"
         "trung to hop le"
         "\nChu y :"
         "\nCac toan hang chi tu 0 den 9"
         "\nCac toan tu chi gom + - * / ( )\n");
  do {
    printf("\nNhap mot bieu thuc trung to hop le (trong de thoat): ");
    gets(expr);
    if (strlen(expr) > 0)
      in_hauto(expr);
    else
      done = 1;
  } while (!done);
}
