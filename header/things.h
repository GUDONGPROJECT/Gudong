//
// Created by patrick on 10/25/18.
//

#ifndef GUDONG_THINGS_H
#define GUDONG_THINGS_H
#define SIZE 5.5

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"

enum Things {
    RECOMMEND,
    TRAIN,
    HELP};

enum Jump {
	LAST,
	NEXT,
	NONE
};

void thingsDraw(MOUSE *mouse,PEOPLE *people);

void recommendDraw(MOUSE *mouse, PEOPLE *people, MsgP MsgP, int which);

void trainDraw(MOUSE *mouse, PEOPLE * people);

void helpDraw(MOUSE *mouse, PEOPLE * people, MsgP msgP);

State thingsPage(MOUSE *mouse,PEOPLE *people);

void drawRecommendDetail(MsgP MsgP, int whichTheme);

void drawTrainDetail();

void drawHelpDetail(MsgP msgP);

void loadAllData(FILE *fp);

void showRecommendMsg(float x, float y, int * color, MsgP msgP);

void showHelpMsg(float x, float y, MsgP msgP);

void showMsgDetail(MsgP msgP);

Jump showMsg(MsgP msgP, MOUSE *mouse);

void freeHeapMalloc(MsgP msgP);

void showAllMsg(float x, float y, bool hasAchieved, MsgP msgP);

//void showClassMsg(float x, float y, bool hasAchieved, MsgP msgP);

#endif //GUDONG_THINGS_H
