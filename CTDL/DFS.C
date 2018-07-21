/* Bai tap 3_78 - Giai thuat DFS (Depth First Search)  */
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

int input_weight(int start, int end)
{
  int size, i;
  void far *buf;
  char c, s[]="Nhap trong so", s1[3]="";
  size = imagesize(getmaxx()/2 - 70, getmaxy()/2 - 20,getmaxx()/2 + 70, getmaxy()/2 + 10);
  buf = malloc(size);
  getimage(getmaxx()/2 - 70, getmaxy()/2 - 20,getmaxx()/2 + 70, getmaxy()/2 + 10, buf);
  setcolor(BLUE);
  setfillstyle(SOLID_FILL, BLUE);
  bar(getmaxx()/2 - 70, getmaxy()/2 - 20,getmaxx()/2 + 70, getmaxy()/2 + 10);
  setcolor(WHITE);
  rectangle(getmaxx()/2 - 70, getmaxy()/2 - 20,getmaxx()/2 + 70, getmaxy()/2 + 10);
  line(getmaxx()/2 - 70, getmaxy()/2 - 5,getmaxx()/2 + 70, getmaxy()/2 - 5);
  outtextxy((getmaxx()-textwidth(s))/2 - 4, getmaxy()/2 - 16, s);
  i = 0;
  do {
    do {
      c = getch();
    } while ((c < '0' || c > '9') && c != 13 && c != 27 && c != 8);
    if (c>='0' && c <= '9' && i<2)
    {
      s1[i] = c;
      s1[i+1] = 0;
      i++;
    }
    if (c == 8 && i>0)
    {
      i--;
      s1[i] = 0;
    }
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(getmaxx()/2 - 69, getmaxy()/2 - 3,getmaxx()/2 + 69, getmaxy()/2 + 9);
    setcolor(YELLOW);
    outtextxy((getmaxx()-textwidth(s))/2 - 4, getmaxy()/2 - 1, s1);
  } while(c != 13 && c != 27);
  putimage(getmaxx()/2 - 70, getmaxy()/2 - 20, buf, COPY_PUT);
  free(buf);
  if (c == 13)
  {
    i = atoi(s1);
    weight[start][end] = i;
    weight[end][start] = i;
    return i;
  }
  else
    return -1;
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
    if ((i = input_weight(start, end)) != -1)
    {
      setcolor(GREEN);
      line(x, y, nut[end].x, nut[end].y);
      itoa(i, s, 10);
      setcolor(RED);
      outtextxy(x + (nut[end].x - x) / 2 + 4, y + (nut[end].y - y) / 2 + 4, s);
    }
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

int xpos = 1;

void visit(int nutxet)
{
  int i, OK;
  char s[3];

  push(nutxet);
  setcolor(YELLOW); itoa(nutxet, s, 10); outtextxy(xpos++*20, 38, s);
  circle(nut[nutxet].x, nut[nutxet].y, 4); delay(1000);
  visited[nutxet] = 1;
  for (i=0; i<sonut; i++)
    if (weight[nutxet][i] != -1 && visited[i] == 0)
      visit(i);
  pop(&nutxet);
}

void DFS()
{
  int start=-1, size, nutxet, i, OK;
  void far *buf;
  char *s = {"Dung nut trai de chon nut dau."};

  size = imagesize(1, 36, getmaxx()-1, 46);
  buf = malloc(size);
  getimage(1, 36, getmaxx()-1, 46, buf);
  out(s);
  do {
    get_mouse();
    start = index(xmouse, ymouse, 1);
  } while (rbutton == 0 && start == -1);
  if (lbutton == 1)
  {
    clear_mouse();
    hide_mouse();
    setcolor(RED);
    circle(nut[start].x, nut[start].y, 4);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(1, 36, getmaxx()-1, 46);
/* Bat dau giai thuat */
    top = -1;
    for (i=0; i<sonut; i++)
      visited[i] = 0;
    visit(start);
/* Ket thuc giai thuat */
    show_mouse();
    getch();
  }
  putimage(1, 36, buf, COPY_PUT);
  free(buf);
  clear_mouse();
  hide_mouse();
  setcolor(WHITE);
  if (start != -1)
    circle(nut[start].x, nut[start].y, 4);
  show_mouse();
}
