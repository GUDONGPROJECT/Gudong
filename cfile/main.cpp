#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/head.h"
#include"./header/login.h"
#include"./header/mainUI.h"

void main() {

    MOUSE mouse;

    Set_SVGA();
    set_mouse();
    mouse.save_mouse = (short
    far *)malloc(320);    //给鼠标分配存储空间
    mouse.oldx = mouse.pos_x = 512;
    mouse.oldy = mouse.pos_y = 384;
    //State state=SPORT;
    //SportMain(&mouse);
    //Begin(&mouse);
    /********************************
**函数名：PartBmp
**参数：     const int top       所取的部分在原图像的顶部坐标
			 const int bottom    所取的部分在原图像的底部坐标
			 const int left      所取的部分在原图像的左端坐标
			 const int right     所取的部分在原图像的右端坐标
			 const int x         所取的部分在屏幕上的横坐标
			 const int y         所取的部分在屏幕上的纵坐标
			 const char *path
**功能：  将图像的某一部分读取到屏幕上
********************************/
    //PartBmp(1, 1000,1,1000,1,1,"C:\\Gudong\\image\\sh.bmp");
    readbmp(1,1,"C:\\Gudong\\image\\lufei.bmp");
    getch();
}

