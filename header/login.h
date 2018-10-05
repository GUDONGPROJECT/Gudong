#ifndef _regist_h_
#define _regist_h_

#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"

//#include"./header/fishing.h"
void Begin(MOUSE *mouse);

int Begin_menu(MOUSE *mouse, PEOPLE *people);

void Begin_draw(void);

void Regist(MOUSE *mouse);

void Regist_draw(void);

int R_check(char *txtname, char *key, char *key1);

int Login(MOUSE *mouse, PEOPLE *people);

void Login_draw(void);

int L_check(PEOPLE *people, char *txtname, char *key1);

int registLogin(MOUSE *mouse);

int RL_check(char *txtname, char *key1);

void flash(void);

int Rkey(MOUSE *mouse, char *data, int *number, int x, int y);

int Rname(MOUSE *mouse, char *data, int *number, int x, int y);

void Create_path(char *name, char *textname);

#endif