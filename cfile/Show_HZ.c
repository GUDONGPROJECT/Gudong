/**********************************************************
Copyright (C) 2017 .
File name:		Show_HZ.c
Author:
Description��	������ʾ����

Function List��
	1.void get_16hz(FILE *hzk_p,char incode[],char bytes[]);
		ȡ��16X16������ģ�ĺ���
		
	2.void dis_16hz(int x,int y,char *s,int color);
		����Ļ����ʾ16X16���ֵĺ���
		
	3.void get_24hz(FILE *hzk_p,char incode[],char bytes[]);
		ȡ��24X24������ģ�ĺ���
		
	4.void dis_24hz(int x,int y,char *s,int color);
		����Ļ����ʾ24X24���ֵĺ���
		
	5.void get_16zf(FILE *hzk_p,char *s,char bytes[]);
		ȡ��16X16���֡���дӢ����ĸ��СдӢ����ĸ��ģ�ĺ���
		
	6.void dis_16zf(int x0,int y0,char *s,int color);
		����Ļ����ʾ16X16���֡���дӢ����ĸ��СдӢ����ĸ�ĺ���
		
	7.void get_24zf(FILE *hzk_p,char *s,char bytes[]);
		ȡ��24X24���֡���дӢ����ĸ��СдӢ����ĸ��ģ�ĺ���
		
	8.void dis_24zf(int x0,int y0,char *s,int color);
		����Ļ����ʾ24X24���֡���дӢ����ĸ��СдӢ����ĸ�ͽ�Ǯ���ŵĺ���������*�����Ǯ���ţ�
		
	9.void dis_16xh(int x0,int y0,int n,int color);
		����Ļ����ʾ��ţ���1.���ַ��ĺ���
		
	10.void dis_16srf(int x,int y,int qw,int n,int page,int color);
		����Ļ����ʾ���뷨��ѡ���еĺ���
		
	11.void dis_16srfhz(int x,int y,int qw,int n,int page,int color);
		����������ʾ����ĵ�������
		
	12.void dis_hz(int x,int y,int M,char *s,int color);
		��M���Ŵ�24X24���֣����ģ��ٶȿ죩
		
	13.void dis_hz_gai(int x,int y,int M,char *s,int color);
		��M���Ŵ�24X24���֣�ʵ�ģ��ٶ�����
	
	14.void dis_16hz_gai(int x0,int y0,char *s,int color,int n)
		��n�����е�16λ����
	
	15.void dis_24hz_gai(int x0,int y0,char *s,int color,int n)
		��n�����е�24λ����
	
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
Function��		get_16hz
				
Description��	��ȡ�������ֵ���ģ

Input��			FILE *hzk_p   		ָ���ֿ���ļ�ָ��
				char incode[]		�洢���ֵ��ַ���
				char bytes[]		����ú��ֵ���ģ

Output��		none

Return��		none
**********************************************************/
void get_16hz(FILE *hzk_p, char incode[], char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    qh = incode[0] - 0xa0;            //�������ź�λ��
    wh = incode[1] - 0xa0;
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(bytes, 32, 1, hzk_p);        //����ģ�����ַ���bytes��
}

/**********************************************************
Function��		dis_16hz
				
Description��	����Ļ����ʾ16X16����

Input��			int x0   			��������Ļ�ϵĺ�����
				int y0				��������Ļ�ϵ�������
				char *s				�洢Ҫ��ʾ�ĺ��ֵ��ַ���
				int color			Ҫ��ʾ�ĺ��ֵ���ɫ

Output��		����16X16����

Return��		none
**********************************************************/
void dis_16hz(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1��־�����ڸ��е���ʾλ��
    y1 = y0;                //y1��־�����ڸ��е���ʾλ��
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //���洢���ֵ��ַ���Ϊ��ʱ��������
    {
        get_16hz(hzk_p, s, mat);
        y2 = y1;
        for (i = 0; i < 16; i++)        //��ѭ��������ʾ��������
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
        x1 += 20;            //��ʾ��һ�����ֺ���������һλ
        s += 2;            //ָ���һ������
    }
    fclose(hzk_p);
}

/**********************************************************
Function��		get_24hz
				
Description��	��ȡ����24X24���ֵ���ģ

Input��			FILE *hzk_p   		ָ���ֿ���ļ�ָ��
				char incode[]		�洢���ֵ��ַ���
				char bytes[]		����ú��ֵ���ģ

Output��		none

Return��		none
**********************************************************/
void get_24hz(FILE *hzk_p, char incode[], char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    qh = incode[0] - 0xa0;            //�������ź�λ��
    wh = incode[1] - 0xa0;
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(bytes, 72, 1, hzk_p);        //����ģ�����ַ���bytes��
}

/**********************************************************
Function��		dis_24hz
				
Description��	����Ļ����ʾ24X24����

Input��			int x0   			��������Ļ�ϵĺ�����
				int y0				��������Ļ�ϵ�������
				char *s				�洢Ҫ��ʾ�ĺ��ֵ��ַ���
				int color			Ҫ��ʾ�ĺ��ֵ���ɫ

Output��		����24X24����

Return��		none
**********************************************************/
void dis_24hz(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    int i, j, x1, k, y1;
    unsigned char mat[72] = {0};            //���ڴ洢������ģ
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    x1 = x0;
    y1 = y0;
    hzk_p = fopen("HZK\\HZK24s", "rb");
    if (!hzk_p) {
        printf("The file HZK24s not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //�ַ���Ϊ��ʱ��ʾ
    {
        get_24hz(hzk_p, s, mat);
        for (i = 0; i < 24; i++)            //��ѭ��������ʾ��������
        {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 8; k++) {
                    if ((mask[k % 8] & mat[3 * i + j]) != NULL) {
                        put_pixel(x1 + j * 8 + k, y1 + i, color);
                    }
                }
            }
        }
        x1 += 24;                  //���������һλ
        s += 2;                  //ָ��ָ����һ������
    }
    fclose(hzk_p);
}

/**********************************************************
Function��		get_16zf
				
Description��	��ȡ����16X16�ַ�����ģ

Input��			FILE *hzk_p   		ָ���ֿ���ļ�ָ��
				char incode[]		�洢�ַ����ַ���
				char bytes[]		������ַ�����ģ

Output��		none

Return��		none
**********************************************************/
void get_16zf(FILE *hzk_p, char *s, char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    if ((*s >= '0') && (*s <= '9'))        //��ָ������ʱλ�Ŵ�0��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 16 + *s - '0';
    } else if (*s >= 'A' && *s <= 'Z')        //��ָ���дӢ����ĸʱλ�Ŵ�A��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 33 + *s - 'A';
    } else if (*s >= 'a' && *s <= 'z')        //��ָ��СдӢ����ĸʱλ�Ŵ�a��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 65 + *s - 'a';
    } else if (*s == '*') {
        qh = 03;
        wh = 04;
    } else                  //ָ�������ַ�ʱ
    {
        printf("wrong input\n");
    }
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(bytes, 32, 1, hzk_p);        //����ģ�����ַ���bytes��
}

/**********************************************************
Function��		dis_16zf
				
Description��	����Ļ����ʾ16X16�ַ�

Input��			int x0   			�ַ�����Ļ�ϵĺ�����
				int y0				�ַ�����Ļ�ϵ�������
				char *s				�洢Ҫ��ʾ���ַ����ַ���
				int color			Ҫ��ʾ���ַ�����ɫ

Output��		16X16�ַ��������֡�Ӣ���ַ�����Ǯ���ţ�

Return��		none
**********************************************************/
void dis_16zf(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1��־�����ڸ��е���ʾλ��
    y1 = y0;                //y1��־�����ڸ��е���ʾλ��
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //���洢���ֵ��ַ���Ϊ��ʱ��������
    {
        get_16zf(hzk_p, s, mat);
        y2 = y1;
        for (i = 0; i < 16; i++)        //��ʾ�����ַ���ѭ��
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
        x1 += 16;            //��ʾ��һ���ַ�����������һλ
        s += 1;
    }
    fclose(hzk_p);
}

/**********************************************************
Function��		get_24zf
				
Description��	��ȡ����24X24�ַ�����ģ

Input��			FILE *hzk_p   		ָ���ֿ���ļ�ָ��
				char incode[]		�洢�ַ����ַ���
				char bytes[]		������ַ�����ģ

Output��		none

Return��		none
**********************************************************/
void get_24zf(FILE *hzk_p, char *s, char bytes[]) {
    unsigned char qh, wh;
    unsigned long offset;
    if ((*s >= '0') && (*s <= '9'))        //��ָ������ʱλ�Ŵ�0��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 16 + *s - '0';
    } else if (*s >= 'A' && *s <= 'Z')        //��ָ���дӢ����ĸʱλ�Ŵ�A��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 33 + *s - 'A';
    } else if (*s >= 'a' && *s <= 'z')        //��ָ��СдӢ����ĸʱλ�Ŵ�a��λ�ſ�ʼ���ε���
    {
        qh = 03;
        wh = 65 + *s - 'a';
    } else if (*s == '*') {
        qh = 03;
        wh = 04;
    } else                  //ָ�������ַ�ʱ
    {
        printf("wrong input\n");
    }
    offset = (94 * (qh - 1) + (wh - 1)) * 72L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(bytes, 72, 1, hzk_p);        //����ģ�����ַ���bytes��
}

/**********************************************************
Function��		dis_24zf
				
Description��	����Ļ����ʾ24X24�ַ�

Input��			int x0   			�ַ�����Ļ�ϵĺ�����
				int y0				�ַ�����Ļ�ϵ�������
				char *s				�洢Ҫ��ʾ���ַ����ַ���
				int color			Ҫ��ʾ���ַ�����ɫ

Output��		24X24�ַ��������֡�Ӣ���ַ�����Ǯ���ţ�

Return��		none
**********************************************************/
void dis_24zf(int x0, int y0, char *s, int color) {
    FILE *hzk_p;
    register int i, j, x1, k, pos;
    unsigned char mat[72] = {0};            //���ڴ洢������ģ
    x1 = x0;
    hzk_p = fopen("HZK\\HZK24", "rb");
    if (!hzk_p) {
        printf("The file HZK24 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //���洢���ֵ��ַ���Ϊ��ʱ��������
    {
        get_24zf(hzk_p, s, mat);
        for (i = 0; i < 24; i++)            //��ʾ�����ַ���ѭ��
        {
            for (j = 0; j < 3; j++) {
                for (k = 0; k < 8; k++) {
                    if ((mat[i * 3 + j] >> (7 - k) & 1) != NULL) {
                        put_pixel(x1 + j * 8 + k, y0 + i, color);
                    }
                }
            }
        }
        x1 += 24;                  //��ʾ��һ���ַ�����������һλ
        s += 1;
    }
    fclose(hzk_p);
}

/**********************************************************
Function��		dis_16xh
				
Description��	����Ļ����ʾ16X16���

Input��			int x0   			�ַ�����Ļ�ϵĺ�����
				int y0				�ַ�����Ļ�ϵ�������
				int n				Ҫ��������
				int color			Ҫ��ʾ���ַ�����ɫ

Output��		����16X16���

Return��		none
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
    qh = 02;                  //����λ��
    wh = 16 + n;
    offset = (94 * (qh - 1) + (wh - 1)) * 32L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(mat, 32, 1, hzk_p);          //����ģ�����ַ���bytes��
    for (i = 0; i < 16; i++)              //��ѭ��������ʾ��������
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
Function��		dis_16srf
				
Description��	�����뷨��������ʾn����ѡ��

Input��			int x   			���뷨�����Ͻ�����Ļ�ϵĺ�����
				int y				���뷨�����Ͻ�����Ļ�ϵ�������
				int qw				��һ���ֵ���λ��
				int n				��ʾ���ֵĸ���
				int page			��ʾ���������뷨�ĵڼ�ҳ
				int color			Ҫ��ʾ���ֵ���ɫ

Output��		���ɸ���ѡ��

Return��		none
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
    qh = qw / 100;            //�������ź�λ��
    wh = qw - 100 * qh;
    y2 = y1;
    for (k = 0; k < n; k++, m++) {
        dis_16xh(x1, y1, m, LIGHTRED);
        x1 += 32;
        offset = (94 * (qh - 1) + (wh - 6 + m + page * 4)) * 32L;      //����ƫ��λ��
        fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
        fread(mat, 32, 1, hzk_p);        //����ģ�����ַ���bytes��
        y2 = y1;
        for (i = 0; i < 16; i++)        //��ʾ�����ַ���ѭ��
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
Function��		dis_16srfzf
				
Description��	����������ʾ����ĺ���

Input��			int x   			�������������ĺ�����
				int y				��������������������
				int qw				���ֵ���λ��
				int n				ѡ��������뷨��ʾ�ĵڼ�������
				int page			ѡ����������뷨�ĵڼ�ҳ
				int color			Ҫ��ʾ���ֵ���ɫ

Output��		��������

Return��		none
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
    qh = qw / 100;            //�������ź�λ��
    wh = qw - 100 * qh;
    offset = (94 * (qh - 1) + (wh - 6 + n + page * 4)) * 32L;      //����ƫ��λ��
    fseek(hzk_p, offset, SEEK_SET);      //Ѱ�Һ��ֵ���ģ
    fread(mat, 32, 1, hzk_p);        //����ģ�����ַ���bytes��
    y2 = y;
    for (i = 0; i < 16; i++)        //��ʾ�����ַ���ѭ��
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
Function��		dis_hz
				
Description��	���ⱶ���Ŵ�24X24���֣����ģ��ٶȿ죩

Input��			int x   			�������������ĺ�����
				int y				��������������������
				int M				�Ŵ���
				char code[]			Ҫ��ʾ�ĺ��ִ�
				int color			Ҫ��ʾ���ֵ���ɫ

Output��		�Ŵ�ĺ���

Return��		none
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
Function��		dis_hz_gai
				
Description��	���ⱶ���Ŵ�24X24���֣�ʵ�ģ��ٶ�����

Input��			int x   			�������������ĺ�����
				int y				��������������������
				int M				�Ŵ���
				char *s				Ҫ��ʾ�ĺ��ִ�
				int color			Ҫ��ʾ���ֵ���ɫ

Output��		�Ŵ�ĺ���

Return��		none
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
Function��		dis_16hz_gai
				
Description��	��ʾ���ֲ�������ʾ

Input��			int x   			�������������ĺ�����
				int y				��������������������
				char *s				Ҫ��ʾ�ĺ��ִ�
				int color			Ҫ��ʾ���ֵ���ɫ
				int n				���д�������

Output��		�Ŵ�ĺ���

Return��		none
**********************************************************/
void dis_16hz_gai(int x0, int y0, char *s, int color, int n) {
    FILE *hzk_p;
    register int i, j, x1, y1, x2, y2, pos;
    unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    unsigned char mat[32] = {0};
    x1 = x0;                //x1��־�����ڸ��е���ʾλ��
    y1 = y0;                //y1��־�����ڸ��е���ʾλ��
    hzk_p = fopen("HZK\\HZK16", "rb");
    if (!hzk_p) {
        printf("The file HZK16 not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)            //���洢���ֵ��ַ���Ϊ��ʱ��������
    {
        while (x1 < n && (*s != NULL)) {
            get_16hz(hzk_p, s, mat);
            y2 = y1;
            for (i = 0; i < 16; i++)        //��ѭ��������ʾ��������
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
            x1 += 20;            //��ʾ��һ�����ֺ���������һλ
            s += 2;            //ָ���һ������
        }
        x2 = x0;              //���к�ӳ�ʼ�����꿪ʼ��ʾ
        x1 = x0;
        y1 += 20;
    }
    fclose(hzk_p);
}

/**********************************************************
Function��		dis_24hz_gai
				
Description��	������ʾ����

Input��			int x   			�������������ĺ�����
				int y				��������������������
				char *s				Ҫ��ʾ�ĺ��ִ�
				int color			Ҫ��ʾ���ֵ���ɫ
				int n				���е�����

Output��		�Ŵ�ĺ���

Return��		none
**********************************************************/
void dis_24hz_gai(int x0, int y0, char *s, int color, int n) {
    FILE *hzk_p;
    int i, j, x1, k, y1;
    unsigned char mat[72] = {0};            //���ڴ洢������ģ
    unsigned mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    x1 = x0;
    y1 = y0;
    hzk_p = fopen("HZK\\HZK24s", "rb");
    if (!hzk_p) {
        printf("The file HZK24s not exist!ENTER to system\n");
        getch();
        exit(1);
    }
    while (*s != NULL)                  //�ַ���Ϊ��ʱ��ʾ
    {
        while ((*s != NULL) && (x1 < n)) {
            get_24hz(hzk_p, s, mat);
            for (i = 0; i < 24; i++)            //��ѭ��������ʾ��������
            {
                for (j = 0; j < 3; j++) {
                    for (k = 0; k < 8; k++) {
                        if ((mask[k % 8] & mat[3 * i + j]) != NULL) {
                            put_pixel(x1 + j * 8 + k, y1 + i, color);
                        }
                    }
                }
            }
            x1 += 24;                  //���������һλ
            s += 2;                  //ָ��ָ����һ������
        }
        x1 = x0;                    //���к�ӳ�ʼ�����꿪ʼ��ʾ
        y1 += 24;
    }
    fclose(hzk_p);
}