/* Bai tap 3_94 - Bai toan tron tim */
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <ctype.h>

#define RADIUS 3
#define DELAY  10

int gr_drive=DETECT, gr_mode;
int xvat, yvat, xnguoi, ynguoi;
int dx, dy, left, right, top, bottom;

void initialize()
{
  char s1[] = "Nhan phim bat ky de bat dau";
  char s2[] = "Nhan phim ESCAPE de ket thuc";

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  outtextxy((getmaxx()-textwidth(s1))/2, 4, s1);
  line(0, 16, getmaxx(), 16);
  getch();
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(1, 1, getmaxx(), 15);
  setcolor(YELLOW);
  outtextxy((getmaxx()-textwidth(s1))/2, 4, s2);
  setviewport(1, 17, getmaxx()-1, getmaxy()-1, 1);
  left = top = 0;
  right = getmaxx() - 2;
  bottom = getmaxy() - 18;
  randomize();
  xvat = random(getmaxx()/2);
  xnguoi = random(getmaxx()/2)+getmaxx()/2;
  yvat = random(getmaxy()/2);
  ynguoi = random(getmaxy()/2)+getmaxy()/2;
}

void drawvat(int color)
{
  setcolor(color);
  circle(xvat, yvat, RADIUS);
}

void drawnguoi(int color)
{
  setcolor(color);
  rectangle(xnguoi-3, ynguoi-2, xnguoi+3, ynguoi+2);
}

void tinhvat()
{
  if (xnguoi >= xvat)
    xvat += 2;
  if (xnguoi < xvat)
    xvat -= 2;
/*
  if (xvat < 2)
    xvat += 2;
  if (xvat > right-2)
    xvat = right-2;
*/
  if (ynguoi >= yvat)
    yvat += 2;
  if (ynguoi < yvat)
    yvat -= 2;
/*
  if (yvat < 2)
    yvat += 2;
  if (yvat >bottom - 2)
    yvat = bottom - 2;
*/
}

void tinhnguoi()
{
  xnguoi += dx;
  ynguoi += dy;
  if (xnguoi < left)
    xnguoi = left;
  if (xnguoi > right)
    xnguoi = right;
  if (ynguoi < top)
    ynguoi = top;
  if (ynguoi > bottom)
    ynguoi = bottom;
}

void main()
{
  char c, s[] = "Oh! Ban da thua roi";
  initialize();
  drawvat(YELLOW);
  drawnguoi(WHITE);
  dx = dy = 0;
  do {
    if (kbhit())
    {
      c = toupper(getch());
      if (c == 0)
        c = getch();
      switch(c)
      {
        case 'A' : dx = 0; break;
        case 'S' : dy = 0; break;
        case 75 : dx = -2; break;
        case 77 : dx = 2; break;
        case 72 : dy = -2; break;
        case 80 : dy = 2; break;
      }
    }
    delay(DELAY);
    drawvat(BLACK);
    drawnguoi(BLACK);
    tinhnguoi();
    tinhvat();
    drawvat(YELLOW);
    drawnguoi(WHITE);
    if (abs(xnguoi-xvat) < 4 && abs(ynguoi-yvat) < 4)
    {
      setviewport(0, 0, getmaxx(), getmaxy(), 1);
      setcolor(BLACK);
      setfillstyle(SOLID_FILL, BLACK);
      bar(1, 1, getmaxx(), 15);
      setcolor(YELLOW);
      outtextxy((getmaxx()-textwidth(s))/2, 4, s);
      getch();
      c = 27;
    }
  } while (c != 27);
  closegraph();
}
