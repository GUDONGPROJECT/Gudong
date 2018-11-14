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

void thingsDraw(MOUSE *mouse,PEOPLE *people);

void recommendDraw(MOUSE *mouse, PEOPLE *people);

void trainDraw(MOUSE *mouse, PEOPLE * people);

void helpDraw(MOUSE *mouse, PEOPLE * people);

State thingsPage(MOUSE *mouse,PEOPLE *people);

void drawRecommendDetail();

void drawTrainDetail();

void drawHelpDetail();
void loadAllData(FILE *fp);

void showRecommendMsg(float x, float y, int * color, MsgP msgP);

enum Things {
    RECOMMEND,
    TRAIN,
    HELP};

#endif //GUDONG_THINGS_H
