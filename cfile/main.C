#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/head.h"
#include"./header/regist.h"

void main() {

    MOUSE mouse;

    Set_SVGA();
    set_mouse();
    mouse.save_mouse = (short
    far *)malloc(320);    //给鼠标分配存储空间
    mouse.oldx = mouse.pos_x = 512;
    mouse.oldy = mouse.pos_y = 384;

    Begin(&mouse);
}

