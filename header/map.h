//
// Created by patrick on 10/19/18.
//

#ifndef GUDONG_MAP_H
#define GUDONG_MAP_H

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"

bool drawMap();

void drawStatus(char * endurance, char * velocity, char * length, char * totalTimeMin, char * totalTimeSecond);

void cleanEndurance();

void cleanVelocity();

void cleanLength();

void cleanTotalTimeMin();

void cleanTotalTimeSecond();

#endif //GUDONG_MAP_H
