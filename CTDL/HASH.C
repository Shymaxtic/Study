/* Bai tap 3_88 - Cai dat HASH */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 100

typedef struct tagitem {
  int value;
  char s[5];
} ITEM;

ITEM danhsach[MAX];
int HASH[MAX];

int hash(ITEM item)
{
  long l;
  l = (long)item.s[0] << 24 +
      (long)item.s[1] << 16 +
      (long)item.s[2] << 8 +
      (long)item.s[3];

  return (int)(l%MAX);
}

void insert_hash(ITEM item, int index)
{
  int hfunc;

  hfunc = hash(item);
  while(HASH[hfunc] != -1)
  {
    hfunc += 26;
    if (hfunc > MAX)
      hfunc %= MAX;
  }
  HASH[hfunc] = index;
}

void initialize()
{
  int i, j;
  ITEM item;

  clrscr();
  randomize();
  for (i=0; i<MAX; i++)
    HASH[i] = -1;
  for (i=0; i<20; i++)
  {
    item.value = random(20);
    for (j=0; j<4; j++)
      item.s[j] = random(26) + 'a';
    item.s[4] = 0;
    danhsach[i] = item;
    insert_hash(item, i);
    printf("\n%s %d", item.s, item.value);
  }
}

void main()
{
  int done = 0, hfunc, oldhfunc, error;
  ITEM item;
  initialize();
  do {
    printf("\nNhap chuoi tim kiem (toi da 4 ky tu) : ");
    gets(item.s);
    if (strlen(item.s)>0)
    {
      oldhfunc = hfunc = hash(item);
      error = 0;
      while (strcmp(item.s, danhsach[hfunc].s) != 0)
      {
        hfunc += 26;
        hfunc %= MAX;
        if (oldhfunc == hfunc || HASH[hfunc] == -1)
        {
          printf("Khong tim thay");
          error = 1;
          break;
        }
      }
      if (!error)
      {
        printf("Tim thay tai %d : %s %d", HASH[hfunc], danhsach[HASH[hfunc]].s,
               danhsach[HASH[hfunc]].value);
      }
    }
    else
      done = 1;
  } while (!done);
}
