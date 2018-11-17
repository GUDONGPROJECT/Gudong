#ifndef _mainUI_h_
#define _mainUI_h_

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"Run.h"
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"
void Draw_Sport_Run(PEOPLE *people);
void Draw_Sport_Walk(PEOPLE *people);
void Draw_Sport_Ride(PEOPLE *people);
State SportMain(MOUSE *mouse,PEOPLE *people);
enum Sport{RUN,WALK,RIDE};
void Update(PEOPLE* people,Sport state);
void Begin_Run(void);

//void Run(/*PEOPLE* people,*/Sport state);

#endif