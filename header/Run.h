//
// Created by HP on 2018/10/19.
//

#ifndef GUDONG_RUN_H
#define GUDONG_RUN_H

#include"head.h"
#include "SVGA.H"
#include "map.h"
#include "headUtil.h"
#include "UserIO.h"
#include "MAINUI.H"
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include<conio.h>
#include<dos.h>
#define Pi 3.1415926
#define Null 0

#define maxX 1001
#define minX 397
#define maxY 745
#define minY 23
#define maxV 6
#define midV 4
#define lowV 2
#define minV 0
#define maxA 2
#define minA -1
//enum VMode{KEEP,CHANGE};

enum Speed{HIGH,MID,LOW,ZERO};

class Character{
    int x;
    int y;
    float v;
    float a;
    char txtname[35];
    long delta;
    int bgX;
    int bgY;
    float angle;
    short far *bg;
    struct timeb lastTime;
    struct timeb lastTimex;
    struct timeb lastTimey;
    struct tm *startTime;
    struct tm *endTime;
    float len;
    Speed speed;
    float energy;
    int state;//用于存储在进行的运动种类
public:
    Character(char* txt,int state0);
    ~Character(void);
    void Show(void);
    void PutBg(void);
    void GetBg(void);
    bool UpdatePos(void);
    void UpdateShow(void);
    void inScale(void);
    int OnKbhit(char key);
    void Run(int& exeS/*PEOPLE *people*/);
    void StartTime(struct tm * sTime);
    void EndTime(struct tm * eTime);
    int Len(void);
    int TimeLen(void);
    void ShowResult(void);
};

void Draw_Pause(void);
char* ToString(int x,char* s);

#endif GUDONG_RUN_H
