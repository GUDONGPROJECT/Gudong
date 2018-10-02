#ifndef _head_h_
#define _head_h_

#include"./header/Show_HZ.h"
#include<conio.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./header/SVGA.h"

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
    int num[2];//人数预设
    int dnum;           //若预约了人数，为一，则可以进入有权限限制的界面
    char bbqtxt[35];//存储烧烤费用的路径
    int jilu[6];  //若游览了该景点，改数据为1
    int money[6];//钱数
    int pay;
} PEOPLE;


typedef struct {
    char syllable[10];
    int qw;
} pinyin;

typedef struct {

    int fish[4];

    int tool;

    int fishtool[6];
    int money;

} ANGLE;


#endif
