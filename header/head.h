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
    int num[2];//人数预设
    int dnum;           //若预约了人数，为一，则可以进入有权限限制的界面
    char bbqtxt[35];//存储烧烤费用的路径
    int jilu[6];  //若游览了该景点，改数据为1
    int money[6];//钱数
    int pay;
    int exeTimes;   //运动次数
    int runLen;     //单位为米
    int walkLen;     //单位为米
    int rideLen;     //单位为米
} PEOPLE;

typedef struct Node{
    char author[30];
    char title[30];
    char type[30];
    char readNum[20];
    Node * next;
    Node * last;
    char text[100][100];
}Msg, * MsgP;


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

typedef struct {
    float x;
    float y;
} Pen;

//class Button {
//    char *fun;      //按钮被点击后触发的事件接口
//    char *name;     //按钮的名字
//    int x1;         //左上角横坐标
//    int y1;         //左上角纵坐标
//    int x2;         //右下角横坐标
//    int y2;
//public:
//    Button(int xx1,int yy1,int xx2,int yy2,char *Fun=Null, char *n=Null);
//    bool IsClick(MOUSE *mouse);
//    virtual void Show(void);
//    virtual void OnClick(void);
//};
//
//class Simple::Button{
//    static int i=0;
//public:
//    Simple(int xx1,int yy1,int xx2,int yy2,char *Fun=Null, char *n=Null);
//    void Show(void);
//    void Onclick(void);
//};
//
//class Tweet::public Button{
//    char *picture;     //图片路径
//    char *title;    //文章标题
//    char *essay;    //文章内容
//    char *author;   //作者
//    char *tag;      //标签
//public:
//    Tweet(chao *p,char *t,char *e);
//    virtual void Show(void);
//};

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
