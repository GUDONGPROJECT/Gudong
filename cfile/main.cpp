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
#include "./header/IoUtil.h"
#include "./header/Find.h"

#include "./things.h"
#include "./header/map.h"

// TODO
// 文件名与文件夹名修改

void main() {

    MOUSE mouse;

    Set_SVGA();
    set_mouse();
    mouse.save_mouse = (short
    far *)malloc(320);    //给鼠标分配存储空间
    mouse.oldx = mouse.pos_x = 512;
    mouse.oldy = mouse.pos_y = 384;
//    PEOPLE people;
//    strcat(people.txtname,"C:\\Gudong\\txt\\13461421.TXT");
//
////    dis_24zf(500,250,"hhh",RED);
////    drawMap();
//    Run(RUN);
//    strcat(people.txtname,"C:\\Gudong\\txt\\13461421.TXT");
//    if(Begin_Run()) {
//    drawMap();
//        dis_24zf(500,250,"hhh",RED);
//        while(1) {
//            getch();dis_24zf(500,400,"hhh",RED);
//            Character runningMan(/*&people,*/RUN);
//    dis_24zf(500,350,"hhh",RED);
//    getch();dis_24zf(500,300,"hhh",RED);
//            runningMan.Run();
//
//
//            getch();
//            break;
//        }
//        dis_24zf(500,250,"hhh",RED);
//        Update(&people,WALK);
//    }

    // 愣头青的调试
//    State state=SPORT;
//    SportMain(&mouse);

    Begin(&mouse);
    // 调试things界面
//    thingsPage(&mouse, NULL);
    // 调试Find界面
//    findPage(&mouse, NULL);

//    char *path;
//    path = (char *) malloc(50 * sizeof(char));
//    MsgP msgP = (MsgP) malloc (sizeof(Msg));
//    createMsgPath("1", path);
//    inputMsg(path, msgP);
//    getchar();
}

