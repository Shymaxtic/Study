/* Bai tap 3_84 - Khao sat tinh lien thong cua mot do thi */
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

int sonut = 0;
typedef struct tagnode {
  int x, y; /* Vi tri tren man hinh */
} NODE;

NODE nut[MAX];
int  weight[MAX][MAX];
int  themduoc = 1;

void DFS();

void initialize()
{
  char s1[] = "Nhap nut phai chuot de them nut";
  char s2[] = "Nhap nut trai chuot va re de them duong noi";
  char s3[] = "Nhan phim Q de thoat - S de bat dau minh hoa giai thuat";
  int i, j;

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  outtextxy((getmaxx()-textwidth(s1))/2, 5, s1);
  outtextxy((getmaxx()-textwidth(s2))/2, 15, s2);
  outtextxy((getmaxx()-textwidth(s3))/2, 25, s3);
  line(0, 35, getmaxx(), 35);
  set_mouse_hlimits(5, getmaxx()-6);
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

void get_weight()
{
  int x, y, oldx, oldy, i, OK = 0, start, end;
  char s[5];
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
    if (abs(nut[i].x - xmouse) < 4 && abs(nut[i].y - ymouse) < 4)
    {
      end = i;
      OK = 1;
      break;
    }
  if (OK && end != start)
  {
    weight[start][end] = 100;
    weight[end][start] = 100;
    setcolor(GREEN);
    line(x, y, nut[end].x, nut[end].y);
  }
  setwritemode(COPY_PUT);
  show_mouse();
}

void main()
{
  int done = 0;
  char c, s[4];

  initialize();
  do {
    get_mouse();
    if (kbhit())
    {
      c = toupper(getch());
      switch(c)
      {
        case 'Q' : done = 1; break;
        case 'S' : DFS(); break;
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
      get_weight();
      clear_mouse();
    }
  } while (!done);
  closegraph();
}

void out(char *s)
{
  setcolor(BLUE);
  setfillstyle(SOLID_FILL, BLUE);
  bar(1, 36, getmaxx()-1, 46);
  setcolor(YELLOW);
  outtextxy(4, 38, s);
}

int visited[MAX];
int top, stack[MAX];
int visited[MAX];

void push(int value)
{
  stack[++top] = value;
  visited[value] = 1;
}

void pop(int *value)
{
  *value = stack[top--];
}

int get()
{
  if (!isempty())
    return stack[top];
  else
    return -1;
}

int isempty(void)
{
  return (top == -1);
}


void visit(int nutxet)
{
  int i, OK;
  char s[3];

  push(nutxet);
  visited[nutxet] = 1;
  for (i=0; i<sonut; i++)
    if (weight[nutxet][i] != -1 && visited[i] == 0)
      visit(i);
  pop(&nutxet);
}

void DFS()
{
  int size, i, OK = 0;
  void far *buf;
  char *s[] = {"Do thi lien thong", "Do thi khong lien thong."};

  size = imagesize(1, 36, getmaxx()-1, 46);
  buf = malloc(size);
  hide_mouse();
  getimage(1, 36, getmaxx()-1, 46, buf);
/* Bat dau giai thuat */
    for (i=0; i<sonut; i++)
      visited[i] = 0;
    visit(0);
    for (i=0; i<sonut; i++)
/* Neu co toi thieu mot nut khong the tham duoc thi do thi khong lien thong */
      if (visited[i] == 0)
      {
        OK = 1;
        break;
      }
/* Ket thuc giai thuat */
  out(s[OK]);
  getch();
  putimage(1, 36, buf, COPY_PUT);
  free(buf);
  clear_mouse();
  show_mouse();
}
