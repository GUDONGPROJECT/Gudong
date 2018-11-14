//
// Created by HP on 2018/10/19.
//

#ifndef GUDONG_RUN_H
#define GUDONG_RUN_H

#include"head.h"
#include "SVGA.H"
#include "map.h"
#include "headUtil.h"
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
//    float w;
    int bgX;
    int bgY;
    float angle;
    short far *bg;
    struct timeb lastTime;
    struct timeb lastTimex;
    struct timeb lastTimey;
    struct tm *startTime;
    struct tm *endTime;
//    time_t st;
    float len;
    Speed speed;
    float energy;
public:
    Character(void/*int _x=500,int _y=500,float _angle=90*/);
    void Show(void);
    void PutBg(void);
    void GetBg(void);
    bool UpdatePos(void);
    void UpdateShow(void);
    void inScale(void);
    void OnKbhit(char key);
    void Run(void/*PEOPLE *people*/);
    void StartTime(struct tm * sTime);
    void EndTime(struct tm * eTime);
    int Len(void);
    int TimeLen(void);

};

char* ToString(int x,char* s);

#endif GUDONG_RUN_H
