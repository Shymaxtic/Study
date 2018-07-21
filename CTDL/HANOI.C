/* Bai tap 3_50 - Trinh bay cac buoc chuyen n dia tu coc A sang coc C
   trong bai toan thap Hanoi dung ba dia */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

#define A 0
#define B 1
#define C 2

void hanoi(int from, int to, int dia)
{
  int trunggian;
  if (dia == 1)
    printf("\nChuyen 1 dia tu coc %c sang coc %c", 'A'+from, 'A'+to);
  else
  {
     if ((from == A && to == C) || (from == C && to == A))
       trunggian = B;
     else if ((from == A && to == B) || (from == B && to == A))
       trunggian = C;
     else if ((from == C && to == B) || (from == B && to == C))
       trunggian = A;
     hanoi(from, trunggian, dia-1);
     hanoi(from, to, 1);
     hanoi(trunggian, to, dia-1);
  }
}

void main()
{
  int n;

  printf("\nCho biet so dia ( 3 -> 6 ): ");
  do {
    scanf("%d", &n);
  } while (n < 3 || n > 6);
  hanoi(A, C, n);
  getch();
}