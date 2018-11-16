//
// Created by HP on 2018/11/14.
//

#ifndef GUDONG_MINE_H
#define GUDONG_MINE_H

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"
#include "Run.h"

#define BASEH 133
#define DELTA 137.5

class Record{
public:
    char* zS;
    char* pS;
    char* mT;
    char* sT;
    char* zV;
    char* pV;
    int year;
    int mon;
    int day;
    int hour;
    int min;
    Record* next;
    Record* last;
    void Init(char* zs,char* ps,char* mt,char* st,char* zv,char* pv,int y,int m,int d,int h,int mi);
    void Dis(int h);
    void Show();
};

State MineMain(MOUSE *mouse,PEOPLE *people);
void Draw_Mine(PEOPLE* people);
void Draw_Records(void);

enum Mine{MAIN,RECORDS};

#endif //GUDONG_MINE_H
