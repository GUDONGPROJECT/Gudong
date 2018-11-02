//
// Created by patrick on 10/18/18.
//

#ifndef GUDONG_HEADUTIL_H
#define GUDONG_HEADUTIL_H
#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"
#include <time.h>

bool headDisplay(float x, float y, int color, int bg);
void drawClock(float x, float y, int color, int bg);
void drawClockOnce(float x, float y, int color);
#endif //GUDONG_HEADUTIL_H
