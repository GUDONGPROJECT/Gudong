//
// Created by patrick on 11/15/18.
//

#ifndef GUDONG_FIND_H
#define GUDONG_FIND_H

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

State findPage(MOUSE *mouse, PEOPLE *people);

void findDraw(MOUSE *mouse, PEOPLE *people);

void drawSignal(int i);

void showClassMsg(float x, float y, UsrP usrP);

void getAllUsr(UsrP usrP);

#endif //GUDONG_FIND_H
