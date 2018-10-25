#ifndef _SVGA_h_
#define _SVGA_h_

#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <alloc.h>
#include "./header/color.h"

#define PI 3.1415926

void Set_SVGA(void);

void selectpage(register char page);

void PartBmp(const int top,
             const int bottom,
             const int left,
             const int right,
             const int x,
             const int y,
             const char *path);

void readbmp(int x, int y, char *path);

void put_pixel(int x, int y, int color);

void SVGA_Horizon(const int x1, const int y1, const int length, const int color);

void SVGA_Line(int x1, int y1, int x2, int y2, const int color);

void SVGA_Rectangular(const int x1, const int x2, const int y1, const int y2, const int color);

void SVGA_Bar(const int x1, const int x2, const int y1, const int y2, const int color);

void SVGA_Cricle(const int x1, const int y1, const int r, const int color);

void SVGA_Ball(const int x1, const int y1, const int r, const int color);

void get_image(const int x1, const int y1, const int x2, const y2, short far *buffer);

void put_image(const int x1, const int y1, const int x2, const y2, short far *buffer);

void SVGA_Straight(const x, const y, const length, const color);

int Getcolor(const int x, const int y);

void maskbmp(int x, int y, char *path);

void enlarge(int x, int y, int n, char *path);

void SVGA_Button(const int x1, const int y1, const int x2, const int y2, const int color);

void SVGA_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char color);

void CircleBar(const int x1,const int y1,const int x2,const int y2,const int radius,const int color);

void Arc(int x,int y, float stangle, float endangle,int radius,int color);

void Pieslice(int x,int y, float stangle, float endangle,int radius,int color);

#endif