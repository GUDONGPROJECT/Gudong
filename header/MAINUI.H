#ifndef _mainUI_h_
#define _mainUI_h_

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"
#include"./header/head.h"
void Draw_Sport_Run(void);
void Draw_Sport_Walk(void);
void Draw_Sport_Ride(void);
enum Sport{RUN,WALK,RIDE};

#endif