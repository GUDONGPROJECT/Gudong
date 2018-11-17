//
// Created by patrick on 11/5/18.
//

#ifndef GUDONG_IOUTIL_H
#define GUDONG_IOUTIL_H

#include <string.h>
#include<stdio.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"

void Create_path(char *name, char *textname);

int R_check(char *txtname, char *key, char *key1);

void inputMsg(char * path, MsgP msgP);

void createMsgPath(char *fileName, char *path);

int getNextLinePos(FILE *p);

void loadData(FILE * fp, int * offset, char * buffer);

int loadDataWithLine(FILE *fp, int length, char *sz);

void createLoginPath(char *fileName, char *path);

void inputPeople(char *path, PEOPLE *PeopleP);

void inputUsr(char *path, UsrP usrP);

void addUsr(PEOPLE *peopleP, char *classWhich);

#endif //GUDONG_IOUTIL_H
