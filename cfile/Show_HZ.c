/**********************************************************
Copyright (C) 2017 .
File name:		Show_HZ.c
Author:
Description：	用于显示汉字

Function List：
	1.void get_16hz(FILE *hzk_p,char incode[],char bytes[]);
		取得16X16汉字字模的函数
		
	2.void dis_16hz(int x,int y,char *s,int color);
		在屏幕上显示16X16汉字的函数
		
	3.void get_24hz(FILE *hzk_p,char incode[],char bytes[]);
		取得24X24汉字字模的函数
		
	4.void dis_24hz(int x,int y,char *s,int color);
		在屏幕上显示24X24汉字的函数
		
	5.void get_16zf(FILE *hzk_p,char *s,char bytes[]);
		取得16X16数字、大写英文字母、小写英文字母字模的函数
		
	6.void dis_16zf(int x0,int y0,char *s,int color);
		在屏幕上显示16X16数字、大写英文字母、小写英文字母的函数
		
	7.void get_24zf(FILE *hzk_p,char *s,char bytes[]);
		取得24X24数字、大写英文字母、小写英文字母字模的函数
		
	8.void dis_24zf(int x0,int y0,char *s,int color);
		在屏幕上显示24X24数字、大写英文字母、小写英文字母和金钱符号的函数（输入*代表金钱符号）
		
	9.void dis_16xh(int x0,int y0,int n,int color);
		在屏幕上显示序号，即1.等字符的函数
		
	10.void dis_16srf(int x,int y,int qw,int n,int page,int color);
		在屏幕上显示输入法待选区中的汉字
		
	11.void dis_16srfhz(int x,int y,int qw,int n,int page,int color);
		在评论区显示输出的单个汉字
		
	12.void dis_hz(int x,int y,int M,char *s,int color);
		以M倍放大24X24汉字（空心，速度快）
		
	13.void dis_hz_gai(int x,int y,int M,char *s,int color);
		以M倍放大24X24汉字（实心，速度慢）
	
	14.void dis_16hz_gai(int x0,int y0,char *s,int color,int n)
		在n处换行的16位汉字
	
	15.void dis_24hz_gai(int x0,int y0,char *s,int color,int n)
		在n处换行的24位汉字
	
**********************************************************/

#include<malloc.h>
#include<stdio.h>
#include<graphics.h>
#include<fcntl.h>
#include<io.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include"./header/SVGA.h"
#include"./header/Show_HZ.h"


/**********************************************************
Function：		get_16hz
				
Description：	获取单个汉字的字模

Input：			FILE *hzk_p   		指向汉字库的文件指针
				char incode[]		存储汉字的字符串
				char bytes[]		保存该汉字的字模

Output：		none

Return：		none
**********************************************************/
void get_16hz(FILE *hzk_p, char incode[], char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    qh = incode[0] - 0xa0;            //计算区号和位号
    wh = incode[1] - 0xa0;
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(bytes, 32, 1, hzk_p);        //将字模输入字符串bytes中
}

/**********************************************************
Function：		dis_16hz
				
Description：	在屏幕上显示16X16汉字

Input：			int x0   			汉字在屏幕上的横坐标
				int y0				汉字在屏幕上的纵坐标
				char *s				存储要显示的汉字的字符串
				int color			要显示的汉字的颜色

Output：		单个16X16汉字

Return：		none
**********************************************************/
void dis_16hz(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1标志汉字在该行的显示位置
    y1 = y0;                //y1标志汉字在该列的显示位置
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //当存储汉字的字符串为空时结束程序
    {
        get_16hz(hzk_p, s, mat);
        y2 = y1;
        for (i = 0; i < 16; i++)        //该循环用于显示单个汉字
        {
            x2 = x1;
            pos = 2 * i;
            for (j = 0; j < 16; j++) {
                if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                    put_pixel(x2, y2, color);
                x2++;
            }
            y2++;
        }
        x1 += 20;            //显示完一个汉字后横坐标后移一位
        s += 2;            //指向后一个汉字
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		get_24hz
				
Description：	获取单个24X24汉字的字模

Input：			FILE *hzk_p   		指向汉字库的文件指针
				char incode[]		存储汉字的字符串
				char bytes[]		保存该汉字的字模

Output：		none

Return：		none
**********************************************************/
void get_24hz(FILE *hzk_p, char incode[], char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    qh = incode[0] - 0xa0;            //计算区号和位号
    wh = incode[1] - 0xa0;
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(bytes, 72, 1, hzk_p);        //将字模输入字符串bytes中
}

/**********************************************************
Function：		dis_24hz
				
Description：	在屏幕上显示24X24汉字

Input：			int x0   			汉字在屏幕上的横坐标
				int y0				汉字在屏幕上的纵坐标
				char *s				存储要显示的汉字的字符串
				int color			要显示的汉字的颜色

Output：		单个24X24汉字

Return：		none
**********************************************************/
void dis_24hz(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    int i, j, x1, k, y1;
    unsigned char mat[72] = {0};            //用于存储汉字字模
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    x1 = x0;
    y1 = y0;
    hzk_p = fopen("HZK\\HZK24s", "rb");
    if (!hzk_p) {
        printf("The file HZK24s not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //字符不为空时显示
    {
        get_24hz(hzk_p, s, mat);
        for (i = 0; i < 24; i++)            //该循环用于显示单个汉字
        {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 8; k++) {
                    if ((mask[k % 8] & mat[3 * i + j]) != NULL) {
                        put_pixel(x1 + j * 8 + k, y1 + i, color);
                    }
                }
            }
        }
        x1 += 24;                  //横坐标后移一位
        s += 2;                  //指针指向下一个汉字
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		get_16zf
				
Description：	获取单个16X16字符的字模

Input：			FILE *hzk_p   		指向汉字库的文件指针
				char incode[]		存储字符的字符串
				char bytes[]		保存该字符的字模

Output：		none

Return：		none
**********************************************************/
void get_16zf(FILE *hzk_p, char *s, char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    if ((*s >= '0') && (*s <= '9'))        //当指向数字时位号从0的位号开始依次递增
    {
        qh = 03;
        wh = 16 + *s - '0';
    } else if (*s >= 'A' && *s <= 'Z')        //当指向大写英文字母时位号从A的位号开始依次递增
    {
        qh = 03;
        wh = 33 + *s - 'A';
    } else if (*s >= 'a' && *s <= 'z')        //当指向小写英文字母时位号从a的位号开始依次递增
    {
        qh = 03;
        wh = 65 + *s - 'a';
    } else if (*s == '*') {
        qh = 03;
        wh = 04;
    } else                  //指向其他字符时
    {
        printf("wrong input\n");
    }
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(bytes, 32, 1, hzk_p);        //将字模输入字符串bytes中
}

/**********************************************************
Function：		dis_16zf
				
Description：	在屏幕上显示16X16字符

Input：			int x0   			字符在屏幕上的横坐标
				int y0				字符在屏幕上的纵坐标
				char *s				存储要显示的字符的字符串
				int color			要显示的字符的颜色

Output：		16X16字符串（数字、英文字符、金钱符号）

Return：		none
**********************************************************/
void dis_16zf(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1标志汉字在该行的显示位置
    y1 = y0;                //y1标志汉字在该列的显示位置
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //当存储汉字的字符串为空时结束程序
    {
        get_16zf(hzk_p, s, mat);
        y2 = y1;
        for (i = 0; i < 16; i++)        //显示单个字符的循环
        {
            x2 = x1;
            pos = 2 * i;
            for (j = 0; j < 16; j++) {
                if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                    put_pixel(x2, y2, color);
                x2++;
            }
            y2++;
        }
        x1 += 16;            //显示完一个字符后横坐标后移一位
        s += 1;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		get_24zf
				
Description：	获取单个24X24字符的字模

Input：			FILE *hzk_p   		指向汉字库的文件指针
				char incode[]		存储字符的字符串
				char bytes[]		保存该字符的字模

Output：		none

Return：		none
**********************************************************/
void get_24zf(FILE *hzk_p, char *s, char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    if ((*s >= '0') && (*s <= '9'))        //当指向数字时位号从0的位号开始依次递增
    {
        qh = 03;
        wh = 16 + *s - '0';
    } else if (*s >= 'A' && *s <= 'Z')        //当指向大写英文字母时位号从A的位号开始依次递增
    {
        qh = 03;
        wh = 33 + *s - 'A';
    } else if (*s >= 'a' && *s <= 'z')        //当指向小写英文字母时位号从a的位号开始依次递增
    {
        qh = 03;
        wh = 65 + *s - 'a';
    } else if (*s == '*') {
        qh = 03;
        wh = 04;
    } else                  //指向其他字符时
    {
        printf("wrong input\n");
    }
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(bytes, 72, 1, hzk_p);        //将字模输入字符串bytes中
}

/**********************************************************
Function：		dis_24zf
				
Description：	在屏幕上显示24X24字符

Input：			int x0   			字符在屏幕上的横坐标
				int y0				字符在屏幕上的纵坐标
				char *s				存储要显示的字符的字符串
				int color			要显示的字符的颜色

Output：		24X24字符串（数字、英文字符、金钱符号）

Return：		none
**********************************************************/
void dis_24zf(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, k, pos;
    unsigned char mat[72] = {0};            //用于存储汉字字模
    x1 = x0;
    hzk_p = fopen("HZK\\HZK24", "rb");
    if (!hzk_p) {
        printf("The file HZK24 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //当存储汉字的字符串为空时结束程序
    {
        get_24zf(hzk_p, s, mat);
        for (i = 0; i < 24; i++)            //显示单个字符的循环
        {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 8; k++) {
                    if ((mat[i * 3 + j] >> (7 - k) & 1) != NULL) {
                        put_pixel(x1 + j * 8 + k, y0 + i, color);
                    }
                }
            }
        }
        x1 += 24;                  //显示完一个字符后横坐标后移一位
        s += 1;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		dis_16xh
				
Description：	在屏幕上显示16X16序号

Input：			int x0   			字符在屏幕上的横坐标
				int y0				字符在屏幕上的纵坐标
				int n				要输出的序号
				int color			要显示的字符的颜色

Output：		单个16X16序号

Return：		none
**********************************************************/
void dis_16xh(int x0, int y0, int n, int color) {
    FILE *hzk_p;
    register int i, j, x, y, pos;
    unsigned char qh, wh;
    unsigned long offset;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    y = y0;
    qh = 02;                  //计算位号
    wh = 16 + n;
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(mat, 32, 1, hzk_p);          //将字模输入字符串bytes中
    for (i = 0; i < 16; i++)              //该循环用于显示单个汉字
    {
        x = x0;
        pos = 2 * i;
        for (j = 0; j < 16; j++) {
            if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                put_pixel(x, y, color);
            x++;
        }
        y++;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		dis_16srf
				
Description：	在输入法框内上显示n个待选字

Input：			int x   			输入法框左上角在屏幕上的横坐标
				int y				输入法框左上角在屏幕上的纵坐标
				int qw				第一个字的区位号
				int n				显示的字的个数
				int page			显示的字是输入法的第几页
				int color			要显示的字的颜色

Output：		若干个待选字

Return：		none
**********************************************************/
void dis_16srf(int x, int y, int qw, int n, int page, int color) {
    FILE *hzk_p;
    register i,j, k, x1, y1, x2, y2, m, pos;
    unsigned char qh, wh;
    unsigned long offset;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x + 4;
    y1 = y + 24 + 4;
    m = 1;
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    qh = qw / 100;            //计算区号和位号
    wh = qw - 100 * qh;
    y2 = y1;
    for (k = 0; k < n; k++, m++) {
        dis_16xh(x1, y1, m, LIGHTRED);
        x1 += 32;
        offset = (94 * (qh - 1) + (wh - 6 + m + page * 4)) * 32L;      //计算偏移位置
        fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
        fread(mat, 32, 1, hzk_p);        //将字模输入字符串bytes中
        y2 = y1;
        for (i = 0; i < 16; i++)        //显示单个字符的循环
        {
            x2 = x1;
            pos = 2 * i;
            for (j = 0; j < 16; j++) {
                if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                    put_pixel(x2, y2, color);
                x2++;
            }
            y2++;
        }
        x1 += 32;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		dis_16srfzf
				
Description：	在评论区显示打出的汉字

Input：			int x   			汉字在评论区的横坐标
				int y				汉字在评论区的纵坐标
				int qw				汉字的区位号
				int n				选择的是输入法显示的第几个汉字
				int page			选择的字在输入法的第几页
				int color			要显示的字的颜色

Output：		单个汉字

Return：		none
**********************************************************/
void dis_16srfhz(int x, int y, int qw, int n, int page, int color) {
    FILE *hzk_p;
    register i,j, k, x2, y2, pos;
    unsigned char qh, wh;
    unsigned long offset;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    qh = qw / 100;            //计算区号和位号
    wh = qw - 100 * qh;
    offset = (94 * (qh - 1) + (wh - 6 + n + page * 4)) * 32L;      //计算偏移位置
    fseek(hzk_p, offset, SEEK_SET);      //寻找汉字的字模
    fread(mat, 32, 1, hzk_p);        //将字模输入字符串bytes中
    y2 = y;
    for (i = 0; i < 16; i++)        //显示单个字符的循环
    {
        x2 = x;
        pos = 2 * i;
        for (j = 0; j < 16; j++) {
            if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                put_pixel(x2, y2, color);
            x2++;
        }
        y2++;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		dis_hz
				
Description：	任意倍数放大24X24汉字（空心，速度快）

Input：			int x   			汉字在评论区的横坐标
				int y				汉字在评论区的纵坐标
				int M				放大倍数
				char code[]			要显示的汉字串
				int color			要显示的字的颜色

Output：		放大的汉字

Return：		none
**********************************************************/
void dis_hz(int x, int y, int M, char *s, int color) {
    FILE *hzk_p;
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    int i, j, k, q, r;
    char mat[72];
    hzk_p = fopen("HZK\\HZK24", "rb");
    if (!hzk_p) {
        printf("The file HZK24 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while ((*s != NULL) && (x < (1024 - M * 24))) {
        get_24hz(hzk_p, s, mat);
        for (i = 0; i < 24 * M; i = i + M) {
            for (q = 0; q < M; q++) {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 8; k++) {
                        if ((mask[k % 8] & mat[3 * i / M + j]) != NULL) {
                            for (r = 0; r < M; r++) {
                                put_pixel(x + j * M * 8 + k * M + r, y + i + M, color);
                            }
                        }
                    }
                }
            }
        }
        x += M * 24;
        s += 2;
    }
}

/**********************************************************
Function：		dis_hz_gai
				
Description：	任意倍数放大24X24汉字（实心，速度慢）

Input：			int x   			汉字在评论区的横坐标
				int y				汉字在评论区的纵坐标
				int M				放大倍数
				char *s				要显示的汉字串
				int color			要显示的字的颜色

Output：		放大的汉字

Return：		none
**********************************************************/
void dis_hz_gai(int x, int y, int M, char *s, int color) {
    FILE *hzk_p;
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    int i, j, k, q, r, n = 0;
    char mat[72];
    hzk_p = fopen("HZK\\HZK24", "rb");
    if (!hzk_p) {
        printf("The file HZK24 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while ((*s != NULL) && (x < (1024 - M * 24))) {
        get_24hz(hzk_p, s, mat);
        for (i = 0; i < 24 * M; i++) {
            if (i % M == 0) {
                for (q = 0; q < M; q++) {
                    for (j = 0; j < 3; j++) {
                        for (k = 0; k < 8; k++) {
                            if ((mask[k % 8] & mat[3 * i / M + j]) != NULL) {
                                for (r = 0; r < M; r++) {
                                    put_pixel(x + j * M * 8 + k * M + r, y + i + M, color);
                                }
                            }
                        }
                    }
                }
            } else {
                n++;
                for (q = 0; q < M; q++) {
                    for (j = 0; j < 3; j++) {
                        for (k = 0; k < 8; k++) {
                            if ((mask[k % 8] & mat[3 * (i - n) / M + j]) != NULL) {
                                for (r = 0; r < M; r++) {
                                    put_pixel(x + j * M * 8 + k * M + r, y + i + M, color);
                                }
                            }
                        }
                    }
                }
                if (n == M - 1) {
                    n = 0;
                }
            }
        }
        x += M * 24;
        s += 2;
    }
}

/**********************************************************
Function：		dis_16hz_gai
				
Description：	显示汉字并换行显示

Input：			int x   			汉字在评论区的横坐标
				int y				汉字在评论区的纵坐标
				char *s				要显示的汉字串
				int color			要显示的字的颜色
				int n				换行处的坐标

Output：		放大的汉字

Return：		none
**********************************************************/
void dis_16hz_gai(int x0, int y0, char *s, int color, int n) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1标志汉字在该行的显示位置
    y1 = y0;                //y1标志汉字在该列的显示位置
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //当存储汉字的字符串为空时结束程序
    {
        while (x1 < n && (*s != NULL)) {
            get_16hz(hzk_p, s, mat);
            y2 = y1;
            for (i = 0; i < 16; i++)        //该循环用于显示单个汉字
            {
                x2 = x1;
                pos = 2 * i;
                for (j = 0; j < 16; j++) {
                    if ((mask[j % 8] & mat[pos + j / 8]) != NULL)
                        put_pixel(x2, y2, color);
                    x2++;
                }
                y2++;
            }
            x1 += 20;            //显示完一个汉字后横坐标后移一位
            s += 2;            //指向后一个汉字
        }
        x2 = x0;              //换行后从初始横坐标开始显示
        x1 = x0;
        y1 += 20;
    }
    fclose(hzk_p);
}

/**********************************************************
Function：		dis_24hz_gai
				
Description：	换行显示汉字

Input：			int x   			汉字在评论区的横坐标
				int y				汉字在评论区的纵坐标
				char *s				要显示的汉字串
				int color			要显示的字的颜色
				int n				换行的坐标

Output：		放大的汉字

Return：		none
**********************************************************/
void dis_24hz_gai(int x0, int y0, char *s, int color, int n) {
    FILE *hzk_p;
    int i, j, x1, k, y1;
    unsigned char mat[72] = {0};            //用于存储汉字字模
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    x1 = x0;
    y1 = y0;
    hzk_p = fopen("HZK\\HZK24s", "rb");
    if (!hzk_p) {
        printf("The file HZK24s not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //字符不为空时显示
    {
        while ((*s != NULL) && (x1 < n)) {
            get_24hz(hzk_p, s, mat);
            for (i = 0; i < 24; i++)            //该循环用于显示单个汉字
            {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 8; k++) {
                        if ((mask[k % 8] & mat[3 * i + j]) != NULL) {
                            put_pixel(x1 + j * 8 + k, y1 + i, color);
                        }
                    }
                }
            }
            x1 += 24;                  //横坐标后移一位
            s += 2;                  //指针指向下一个汉字
        }
        x1 = x0;                    //换行后从初始横坐标开始显示
        y1 += 24;
    }
    fclose(hzk_p);
}