#ifndef _mouse_h_
#define _mouse_h_

#include"./header/head.h"

void set_mouse(void);

void mouse_copy(MOUSE *mouse);

void mouse_recover(MOUSE *mouse);

void mouse_show(MOUSE *mouse);

void drawmouse(MOUSE *mouse);

void mouse_reset(MOUSE *mouse);

void MouseShape(void *buff);

void mouse_read(int *mouse_x, int *mouse_y, int *mouse_butt);

void mouse_position(MOUSE *mouse);

#endif