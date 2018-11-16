#include<stdio.h>
#include<string.h>
#include<dos.h>
#include<bios.h>
#include<graphics.h>
#include "Run.h"
#include"./header/mouse.h"
#include"./header/SVGA.h"
#include"./header/head.h"
#include"./header/login.h"
#include"./header/mainUI.h"
#include "./header/map.h"

// TODO
// 文件名与文件夹名修改

void main() {
    MOUSE mouse;
    Set_SVGA();
    set_mouse();
    mouse.save_mouse = (short
    far *)malloc(320);    //给鼠标分配存储空间
    mouse.oldx = mouse.pos_x = 512;
    mouse.oldy = mouse.pos_y = 384;
    Begin(&mouse);

//    while(1) {
//        if (Begin_Run()) {
//            Character runningMan;
//            runningMan.Run();
////                            Draw_Sport_Run(people);
//        }
//        break;
//    }
//    getch();

//    readbmp(1,1,"C:\\Farm\\Farm\\pic\\people.bmp");
//    SportMain(&mouse);
//    short far *p;
//    get_image(1,1,300,300,p);
//    getch();
//    put_image(301,301,600,600,p);

//    char *key = (char *) malloc(50);
////    int x;
//    FILE* fp= fopen("C:\\Gudong\\txt\\13461421.TXT", "a+");
////    fread(key,1,1,fp);
////    fscanf(fp,"%s%d",key,&x);
////    printf("%s\n%d",key,x);
//    key="123456789";
//    fprintf(fp,"\n%s",key);
//    fclose(fp);
//    fp= fopen("C:\\Gudong\\txt\\13461421.TXT", "r+");
//    for(int i=0;i<12;i++) {//不含密码，循环10次到开始，含密码循环11次
//        fscanf(fp, "%s", key);
//        printf("%s\n", key);
//    }
//    fclose(fp);
//    if(Begin_Run()) {
//        Character runningMan;
//        runningMan.Run();
//    }
//    int year, mon, day, hour, min;
//    char s[10];
//    char key[2];
//    char mT[3];
//    char sT[3];
//    char zS[3];
//    char pS[3];
//    char zV[3];
//    char pV[3];
//    FILE *fp = fopen("C:\\Gudong\\txt\\13461421.TXT", "r+");
//    for(int i=0;i<11;i++) { //不含密码，循环10次到开始，含密码循环11次
//        fscanf(fp, "%s", s);
//        printf("%s",s);
//    }
//    printf("\n");
//    while (1) {
//        if (GetData(fp,key ,zS, pS, mT, sT, zV, pV, year, mon, day, hour, min)) {
//            printf("%s %s %s %s %s %s %s %d %d %d %d %d\n",key,zS,pS,mT,sT,zV,pV,year,mon,day,hour,min);
//        }
//        else {
//            break;
//        }
//    }
//    fclose(fp);
//    getch();

//    getch();
}

