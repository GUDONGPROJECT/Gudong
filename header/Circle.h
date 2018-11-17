//
// Created by patrick on 11/15/18.
//

#ifndef GUDONG_CIRCLE_H
#define GUDONG_CIRCLE_H

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

State circlePage(MOUSE *mouse, PEOPLE *people);

void circleDraw(MOUSE *mouse, PEOPLE *people);

void showClassMsg(float x, float y, bool hasAchieved, MsgP msgP);

void getSelectMsg(MsgP msgP, PEOPLE *peopleP);

#endif //GUDONG_CIRCLE_H
