#ifndef _head_h_
#define _head_h_

#include"./header/Show_HZ.h"
#include<conio.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./header/SVGA.h"
#define Null 0

typedef enum {
    false, true
} bool;

typedef struct        //鼠标结构
{
    short far * save_mouse;          //保存鼠标指针覆盖区域
    int pos_x, pos_y;
    int oldx, oldy;
    int button;
} MOUSE;

typedef struct {           //用户结构
    char name[10];       //用户名
    char key[10];           //密码
    char txtname[35];  //用于存储生成的txt的路径
    int exeTimes;   //运动次数
    int runLen;     //单位为米
    int walkLen;     //单位为米
    int rideLen;     //单位为米
} PEOPLE;

typedef struct Node{
    char author[30];
    char title[30];
    char level[15];
    char time [5];
    char joinedNum[12];
    char type[30];
    char readNum[20];
    int color;
    int image;
    int icon;
    Node * next;
    Node * last;
    char text[20][100];
}Msg, * MsgP;

typedef struct User{
    char name[20];
    int color;
    int icon;
    User * next;
    User * last;
}Usr, * UsrP;



typedef struct {
    float x;
    float y;
} Pen;

enum State {
    MAINLOG,
    SPORT,
    FIND,
    CIRCLE,
    THINGS,
    MINE,
    UNDEFINED,
    BACK,
    REGIST,
    SPORTPAGE
};

#endif
