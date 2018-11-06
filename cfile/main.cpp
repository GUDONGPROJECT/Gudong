#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include "Run.h"
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/head.h"
#include"./header/login.h"
#include"./header/mainUI.h"
#include "./header/map.h"

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
//    readbmp(1,1,"C:\\Farm\\Farm\\pic\\people.bmp");
    drawMap();
    Character runningMan;
    runningMan.Run();

//    short far *p;
//    get_image(1,1,300,300,p);
//    getch();
//    put_image(301,301,600,600,p);

    getch();
}

