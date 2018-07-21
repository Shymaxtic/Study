/* Bai tap 3_81 - Tim chu trinh HAMILTON cua mot do thi */
#include <dos.h>
#include <graphics.h>
#include <alloc.h>
#include "mouse.inc"

#pragma warn -sus

/* Toi da 100 nut */
#define MAX 100

int gr_drive=DETECT, gr_mode;
unsigned char lbutton, rbutton;
int xmouse, ymouse;

int sonut = 0, socanh = 0;
typedef struct tagnode {
  int x, y; /* Vi tri tren man hinh */
} NODE;

NODE nut[MAX];
int  themduoc = 1;
int weight[MAX][MAX];

void initialize()
{
  char s1[] = "Nhap nut phai chuot de them nut";
  char s2[] = "Nhap nut trai chuot va re de them duong noi";
  char s3[] = "Nhan phim Q de thoat - S de bat dau tim chu trinh Hamilton";
  int i, j;
  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  outtextxy((getmaxx()-textwidth(s1))/2, 5, s1);
  outtextxy((getmaxx()-textwidth(s2))/2, 15, s2);
  outtextxy((getmaxx()-textwidth(s3))/2, 25, s3);
  line(0, 35, getmaxx(), 35);
  line(51, 35, 51, getmaxy()-1);
  set_mouse_hlimits(56, getmaxx()-6);
  set_mouse_vlimits(40, getmaxy()-6);
  for (i=0; i<MAX; i++)
    for (j=0; j<MAX; j++)
      weight[i][j] = -1;
  show_mouse();
}

int index(int x, int y, int heso)
{
  int i, OK = 0;
  for (i=0; i<sonut; i++)
    if (abs(nut[i].x - x) < 4*heso && abs(nut[i].y - y) < 4*heso)
    {
      OK = 1;
      break;
    }
  if (OK)
    return i;
  else
    return -1;
}

void get_mouse()
{
  do {
    get_mouse_button(&lbutton, &rbutton, &xmouse, &ymouse);
  } while (lbutton == 0 && rbutton == 0 && !kbhit());
}

void clear_mouse()
{
  do {
    get_mouse_button(&lbutton, &rbutton, &xmouse, &ymouse);
  } while (lbutton == 1 || rbutton == 1);
}

void get_line()
{
  int x, y, oldx, oldy, i, OK = 0, start, end;
  setwritemode(XOR_PUT);
  setcolor(GREEN);
  for (i=0; i<sonut; i++)
    if (abs(nut[i].x - xmouse) < 4 && abs(nut[i].y - ymouse) < 4)
    {
      start = i;
      oldx = x = nut[i].x;
      oldy = y = nut[i].y;
      OK = 1;
      break;
    }
  if (!OK)
    return;
  hide_mouse();
  line(x, y, oldx, oldy);
  clear_mouse();
  show_mouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &xmouse, &ymouse);
    if (oldx != xmouse || oldy != ymouse)
    {
      hide_mouse();
      line(x, y, oldx, oldy);
      oldx = xmouse;
      oldy = ymouse;
      line(x, y, oldx, oldy);
      show_mouse();
    }
  } while (lbutton == 0);
  OK = 0;
  hide_mouse();
  line(x, y, oldx, oldy);
  for (i=0; i<sonut; i++)
    if (abs(nut[i].x - xmouse) < 4 && abs(nut[i].y - ymouse) < 4 )
    {
      end = i;
      OK = 1;
      break;
    }
  if (OK && end != start)
  {
    setcolor(GREEN);
    line(x, y, nut[end].x, nut[end].y);
    weight[start][end] = 1;
    weight[end][start] = 1;
    socanh++;
  }
  setwritemode(COPY_PUT);
  show_mouse();
}

void main()
{
  int done = 0;
  char c, s[4];
  void Hamilton();

  initialize();
  do {
    get_mouse();
    if (kbhit())
    {
      c = toupper(getch());
      switch(c)
      {
        case 'Q' : done = 1; break;
        case 'S' : Hamilton(); break;
      }
    }
    if (rbutton == 1 && index(xmouse, ymouse, 10) == -1)
    {
      hide_mouse();
      if (themduoc)
      {
        setcolor(WHITE);
        circle(xmouse, ymouse, 4);
        itoa(sonut, s, 10);
        setcolor(CYAN);
        outtextxy(xmouse+6, ymouse-6, s);
        nut[sonut].x = xmouse;
        nut[sonut].y = ymouse;
        sonut++;
        if (sonut>=MAX)
          themduoc = 0;
      }
      clear_mouse();
      show_mouse();
    }
    if (lbutton == 1)
    {
      get_line();
      clear_mouse();
    }
  } while (!done);
  closegraph();
}

int top;
int stack[MAX];

void push(int v)
{
  stack[++top] = v;
}

void pop(int *v)
{
  *v = stack[top--];
}

int isempty(void)
{
  return (top == -1);
}

int dinh[MAX];

void Hamilton()
{
  int size, visited = 0, v1 = 0, v2, i, j, iseuler = 0;
  int y, OK = 1, oldv, n;
  char s[10], *kq[2] = { "Do thi co chu trinh HAMILTON","Do thi khong co chu trinh HAMILTON"};

  hide_mouse();
  setcolor(BLUE);
  setfillstyle(SOLID_FILL, BLUE);
  bar(getmaxx()/2 - 150, 36, getmaxx()/2 + 150, 48);
  setcolor(YELLOW);
  for (n=0; n<sonut; n++)
  {
    setcolor(WHITE);
    for (i=0; i<sonut; i++)
      for (j=0; j<sonut; j++)
        if (weight[i][j] != -1)
          line(nut[i].x, nut[i].y, nut[j].x, nut[j].y);
    y = 40;
    top = -1;
    for (i=0; i<sonut; i++)
        dinh[i] = 0; // Dinh chua duoc tham
    v1 = n;
    setcolor(YELLOW);
    push(v1);
    dinh[v1] = 1;
    visited = 1;
    sprintf(s, "%d", v1);
    outtextxy(5, y, s);
    y+=10;
    do {
      oldv = v1;
      pop(&v1);
      if (dinh[v1] == 0 && weight[oldv][v1] != -1)
      {
        dinh[v1] = 1;
        visited++;
        sprintf(s, "%d", v1);
        outtextxy(5, y, s);
        line(nut[oldv].x, nut[oldv].y, nut[v1].x, nut[v1].y);
        y += 10;
      }
      for (i = 0; i<sonut; i++)
        if (dinh[i] == 0 && weight[v1][i] != -1)
          push(i);
    } while ((!isempty() || v1 != n) && visited != sonut);
    outtextxy(5, getmaxy()-40, "HAMIL");
    setcolor(RED);
    if (weight[n][v1] == -1)
      line(5, getmaxy()-36, 45, getmaxy()-36);
    else
    {
      setcolor(YELLOW);
      line(nut[n].x, nut[n].y, nut[v1].x, nut[v1].y);
      iseuler = 1;
      setcolor(BLUE);
      setfillstyle(SOLID_FILL, BLUE);
      bar(getmaxx()/2 - 150, 36, getmaxx()/2 + 150, 48);
      setcolor(YELLOW);
      outtextxy((getmaxx()-textwidth(kq[0]))/2, 38, kq[0]);
      getch();
      break;
    }
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    getch();
    bar(1, 36, 50, getmaxy()-1);
  }
  if (!iseuler)
  {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(getmaxx()/2 - 150, 36, getmaxx()/2 + 150, 48);
    setcolor(YELLOW);
    outtextxy((getmaxx()-textwidth(kq[1]))/2, 38, kq[1]);
  }
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(1, 36, 50, getmaxy()-1);
  show_mouse();
}