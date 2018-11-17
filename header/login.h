#ifndef _regist_h_
#define _regist_h_

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include "Mine.h"
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"

//#include"./header/fishing.h"
void Begin(MOUSE *mouse);

State Begin_menu(MOUSE *mouse, PEOPLE *people);

void Begin_draw(void);

bool Regist(MOUSE *mouse, PEOPLE *people);

void Regist_draw(void);

int R_check(char *txtname, char *key, char *key1);

bool Login(MOUSE *mouse, PEOPLE *people);

void Login_draw(void);

int L_check(PEOPLE *people, char *txtname, char *key1);

int registLogin(MOUSE *mouse);

bool mouseDetector(int lx, int ly, int rx, int ry, int color, bool (*fun) (MOUSE *, PEOPLE *), MOUSE *mouse, PEOPLE *people);

int RL_check(char *txtname, char *key1);

void flash(void);

int Rkey(MOUSE *mouse, char *data, int *number, int x, int y);

bool Rname(MOUSE *mouse, char *data, int *number, int x, int y);

void Create_path(char *name, char *textname);

bool getTrue(MOUSE *mouse, PEOPLE *people);

void InitPeople(PEOPLE* people);

bool quickLogin(MOUSE *mouse, PEOPLE *peopleP, char *loginWay);

bool quickWechatLogin(MOUSE *mouse, PEOPLE *peopleP);
#endif