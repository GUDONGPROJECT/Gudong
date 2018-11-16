//
// Created by HP on 2018/11/15.
//

#ifndef GUDONG_USERIO_H
#define GUDONG_USERIO_H

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"

void DataIn(PEOPLE *people,char* key,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int year,int mon,int day,int hour,int min);
bool GetRecord(FILE* fp,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int& year,int& mon,int& day,int& hour,int& min);
bool GetData(FILE* fp,char* key,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int& year,int& mon,int& day,int& hour,int& min);

#endif //GUDONG_USERIO_H
