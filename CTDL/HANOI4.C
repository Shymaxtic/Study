/* Bai tap 3_51 - Trinh bay cac buoc chuyen n dia tu coc A sang coc D
   trong bai toan thap Hanoi dung bon dia */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

#define A 0
#define B 1
#define C 2
#define D 3

void hanoi(int from, int to, int dia)
{
  int tg1, tg2, dia2;
  if (dia <= 1)
    printf("\nChuyen 1 dia tu coc %c sang coc %c", 'A'+from, 'A'+to);
  else
  {
     if ((from == A && to == D) || (from == D && to == A))
     {
       tg1 = B;
       tg2 = C;
     }
     else if ((from == A && to == B) || (from == B && to == A))
     {
       tg1 = C;
       tg2 = D;
     }
     else if ((from == A && to == C) || (from == C && to == A))
     {
       tg1 = B;
       tg2 = D;
     }
     else if ((from == B && to == C) || (from == C && to == B))
     {
       tg1 = A;
       tg2 = D;
     }
     else if ((from == B && to == D) || (from == D && to == B))
     {
       tg1 = A;
       tg2 = C;
     }
     else if ((from == C && to == D) || (from == D && to == C))
     {
       tg1 = A;
       tg2 = B;
     }
     dia2 = dia / 2;
     if (dia % 2 == 1)
     {
       hanoi(from, tg1, dia2);
       hanoi(from, tg2, dia2);
       hanoi(from, to, 1);
       hanoi(tg2, to, dia2);
       hanoi(tg1, to, dia2);
     }
     else
     {
       hanoi(from, tg1, dia2);
       if (dia2 > 1)
       {
         hanoi(from, tg2, dia2-1);
         hanoi(from, to, 1);
         hanoi(tg2, to, dia2-1);
       }
       else
         hanoi(from, to, 1);
       hanoi(tg1, to, dia2);
     }
  }
}

void main()
{
  int n;

  printf("\nCho biet so dia ( 3 -> 6 ): ");
  do {
    scanf("%d", &n);
  } while (n < 3 || n > 6);
  hanoi(A, D, n);
  getch();
}