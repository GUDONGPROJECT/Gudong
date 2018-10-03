#include "./header/SVGA.h"
/**************************************
   SVGA�Ĺ��ܺ�ax˵��
   0x4f00  ��SVGA����Ϣ
   0x4f01  ����ʾģʽ��Ϣ
   0x4f02  ������ʾģʽ
   0x4f03  ����ǰ��ʾģʽ
   0x4f04  �洢��ָ�SVGA����Ƶ״̬
   0x4f05  �����ڴ�ҳ�����л�
   0x4f06  ���û��ȡ�߼�ɨ���߿��
   0x4f07  ���û��ȡ��Ƶ�ڴ�����Ļ�ĳ�ʼ��Ӧλ��
   0x4f08  ���û��ȡDAC��ԭɫ��Чλ��
   SVGA��ʾģʽ��bx��
		ģʽ��		�ֱ���		��ɫ��		��ɫλ����
		0x101		640*480		256				-
		0x103		800*600		256				-
		0x104		1024*768	16				-
		0x105		1024*768	256				-
		0x110		640*480		32K			1:5:5:5
		0x111		640*480		64K			5:6:5
		0x112		640*480		16.8M		8:8:8
		0x113		800*600		32K			1:5:5:5
		0x114		800*600		64K			5:6:5
		0x115		800*600		16.8M		8:8:8
		0x116		1024*768	32K			1:5:5:5
		0x117		1024*768	64K			5:6:5
		0x118		1024*768	16.8M		8:8:8
**************************************************/
/**********************************************************
Copyright (C) 2017 .
File name:		SVGA.c
Author:
Description��	������ʾͼ��

Function List��
	1.void Set_SVGA(void);
	������ʾģʽ
    2.void selectpage(register char page);
	���ڿ����ڴ�ҳ�����л�
    3.void PartBmp(const int top,const int bottom,const int left,const int right,const int x,const int y,const char *path);
	������ʾͼ���ڲ���ͼ��
    4.void readbmp(int x, int y,char*path);
	���ڶ�ȡbmp�ļ�
    5.void put_pixel(int x,int y,int color); 
    ���㺯��
    6.void SVGA_Horizon(const int x1,const int y1,const int length,const int color);
	��ˮƽ�ߺ���
    7.void SVGA_Line( int x1, int x2, int y1, int y2, int color);
	��δʵ��ȫ������
    8.void SVGA_Rectangular(const int x1,const int x2,const int y1, const int y2,const int color );
	��������
    9.void SVGA_Bar(const int x1,const int x2,const int y1, const int y2,const int color );
	��ʵ�ľ��κ���
    10.void SVGA_Cricle(const int x1,const int y1,const int r,const int color);
	������Բ����
    11.void SVGA_Ball(const int x1,const int y1,const int r,const int color);
	��ʵ��Բ����
    12.void get_image(const int x1,const int y1,const int x2,const y2,short far *buffer);
	ȡ��Ļ�ϲ���ͼ��ĺ�������֧�ֻ�ҳ��
    13.void put_image(const int x1,const int y1,const int x2,const y2,short far *buffer);
	������ͼ��ԭ����Ļ�ϵĺ�������֧�ֻ�ҳ��
    14.void SVGA_Straight(const x,const y,const length,const color);
	����ֱ�ߺ���
	15.void enlarge(int x, int y,int n,char * path)
	�Ŵ�ͼ��Ϊ������
	16.int Getcolor(const int x, const int y)
	��ȡĳ�����ɫ
	17.void maskbmp(int x, int y,char*path)
	ֻ��ͼ���ɫ�Ĳ���
**********************************************************/
//�������ˣ������������
/**********************************************************
Function��		Line

Description��	��һ��ֱ�ߺ���
				���Խ��ճ�����Ļ��Χ�����ݣ�ֻ��������Ļ�ڲ���
				��Ϊû�з�ֹ���ͱ���������жϣ���������Ļ����ʱӦ��ֹ�����ش�����

Calls��			Putpixel256
				
				abs

Called By��		LightSW
				LightNE
				LightNW
				LightSE

Input��			int x1					��ʼ������꣬���������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int y1					��ʼ�������꣬���ϵ������ӣ�0Ϊ��Сֵ����Ļ�ο�ϵ��
				int x2					��ֹ������꣨��Ļ�ο�ϵ��
				int y2					��ֹ�������꣨��Ļ�ο�ϵ��
				unsigned char color		��ɫ��������256��

Output��		��Ļ�ϻ���ֱ��

Return��		None
Others��		None
**********************************************************/
void SVGA_Line(int x1, int y1, int x2, int y2, unsigned char color) {
    int dx, dy;      /*ֱ��x��y�����ֵ*/
    int dx2, dy2;    /*�ӿ������ٶȵ��м�ֵ*/
    int xinc, yinc;    /*�ж��롢y���ӷ���ķ���ֵ*/
    int d, dxy;      /*���߱���*/

/*���������ֵ���м����*/
    dx = abs(x2 - x1);
    dx2 = dx << 1;
    dy = abs(y2 - y1);
    dy2 = dy << 1;

/*�ж�ֱ��x�������ӷ���*/
    if (x2 > x1) {
        xinc = 1;
    }

/*�������ֱ��*/
    else if (x2 == x1) {
        /*y��������*/
        if (y1 > y2) {
            dx = y1;
            y1 = y2;
            y2 = dx;
        }

        /*����ֱ��*/
        for (dx = y1; dx <= y2; dx++) {
            put_pixel(x1, dx, color);
        }

        return;
    } else {
        xinc = -1;
    }

/*�ж�ֱ��y�������ӷ���*/
    if (y2 > y1) {
        yinc = 1;
    }

/*�����ˮƽ��*/
    else if (y2 == y1) {
        SVGA_Horizon(x1, y1, x2 - x1, color);
        return;
    } else {
        yinc = -1;
    }

/*******************************
��������Bresenham�㷨����ֱ�ߡ�
���㷨�ǵõ����ϵĳ���Ŀ����㷨��
����ϸ����ȥ��
*******************************/
    put_pixel(x1, y1, color);

    if (dx >= dy) {
        d = dy2 - dx;
        dxy = dy2 - dx2;

        while (dx--) {
            if (d <= 0) {
                d += dy2;
            } else {
                d += dxy;
                y1 += yinc;
            }

            x1 += xinc;
            put_pixel(x1, y1, color);
        }
    } else {
        d = dx2 - dy;
        dxy = dx2 - dy2;

        while (dy--) {
            if (d <= 0) {
                d += dx2;
            } else {
                d += dxy;
                x1 += xinc;
            }

            y1 += yinc;
            put_pixel(x1, y1, color);
        }
    }
}

/********************************
**��������Set_SVGA
**������  Void
**���ܣ�  ������ʾģʽΪ0x117
********************************/
void Set_SVGA(void)
//���õ�ǰ��ʾģʽ
{
    union REGS regs;
    regs.x.ax = 0x4f02;//���õ�ǰ��ʾģʽ
    regs.x.bx = 0x117;//������ʾģʽ�ֱ���Ϊ1024*768 ��ɫ��4K ��ɫ��5:6:5
    int86(0x10, &regs, &regs);//����BIOS int86 10h �ж�
    if (regs.x.ax != 0x004f)//������ó�������ֹ����
    {
        printf("Set SVGA mode wrong");
        exit(1);
    }
}

/********************************
**��������selectpage
**������  Void
**���ܣ�  ��������
********************************/
void selectpage(register char page)
//��ҳ����
{
    union REGS r;
    r.x.ax = 0x4f05;
    r.x.bx = 0;
    r.x.dx = page; /*ѡ��ҳ��*/
    int86(0x10, &r, &r);
}

/********************************
**��������PartBmp
**������     const int top       ��ȡ�Ĳ�����ԭͼ��Ķ�������
			 const int bottom    ��ȡ�Ĳ�����ԭͼ��ĵײ�����
			 const int left      ��ȡ�Ĳ�����ԭͼ����������
			 const int right     ��ȡ�Ĳ�����ԭͼ����Ҷ�����
			 const int x         ��ȡ�Ĳ�������Ļ�ϵĺ�����
			 const int y         ��ȡ�Ĳ�������Ļ�ϵ�������
			 const char *path
**���ܣ�  ��ͼ���ĳһ���ֶ�ȡ����Ļ��
********************************/
void PartBmp(const int top,
             const int bottom,
             const int left,
             const int right,
             const int x,
             const int y,
             const char *path) {
    FILE *fpbmp = NULL;
    int sign = 0;
    long int Width, Height;//ͼ����
    long int linebytes;//һ��Ӧ���е��ֽ���
    unsigned long position;//ÿ�����ص�����Ļ��Ӧ�ô��ڵ�λ��
    register int i, j;//����
    register char page_new = 0;//��ҳ��ʶ
    register char page_old;
    long int Resx, Resy;
    long int PartWidth, PartHeight;
    short *buffer = NULL;//������ʾ��һ����ʾ1024������
    short far
    *
    const VideoBuffer = (short far
    *)0xA0000000L;//�趨�Դ�ָ�벻��
    if ((fpbmp = fopen(path, "rb")) == NULL) {
        printf("Cannot open the picture");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 0L, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//��ָ��ͼ�񲢲���bmp������ֹ����
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//��ȡͼ�����
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (right > Width) {
        PartWidth = Width - left;
    } else {
        PartWidth = right - left;
    }
    if (bottom > Height) {
        PartHeight = Height - top;
    } else {
        PartHeight = bottom - top;
    }
    if (PartWidth + x > 1024) {
        Resx = 1024 - x;
    } else {
        Resx = PartWidth;
    }
    if ((PartHeight + y) > 768) {
        Resy = 768 - y;
    } else {
        Resy = PartHeight;
    }
    linebytes = (Width * 2) % 4;//��Ϊ16λ��bmp��ÿ�����������ֽڣ��������ռ�ֽڲ��ܱ�4��������ȫ
    if (fseek(fpbmp, bottom * Width, SEEK_SET) == -1) {
        printf("Fail to analyse file !");
        fclose(fpbmp);
        return;
    }
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4 - linebytes;//��ȫ��Ϊ���Ա�4������bmpͼƬ����ʵ��һ�е��ֽ���
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL) {
        printf("no memory");
    }
    fseek(fpbmp, 70L + linebytes * (Height - bottom) + left * 2L, 0);
    for (j = PartHeight - 1; j > -1; j--) {
        fread(buffer, 2, PartWidth, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//����52.1���۲�һ���Ƿ���һҳ�ڣ��������һҳ��һҳһҳ����
            {
                for (i = 0; i < Resx; i++) {
                    position = 1024L * (y + j) + (x + i);//�˴��������L��������ֻ��ʾһ���ַ������ǵ�������²�����Ϊ���ݹ��󣬰�position�屬�ˣ�Ȼ��ҳ��һֱû�仯
                    page_new = position >> 15;  /*������ʾҳ�������ֽ�*2/65536*/
                    position &= 0x0000ffffl;    /*������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ�����������16λ*/
                    if (page_new != page_old)   /*����ҳ��*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    VideoBuffer[position] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*����ҳ��*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {

                    VideoBuffer[position + i] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                }
            }
        }
        fseek(fpbmp, linebytes - PartWidth * 2l, SEEK_CUR);
    }
    fclose(fpbmp);
    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}

/********************************
**��������readbmp

**������     const int x         ��ȡ�Ĳ�������Ļ�ϵĺ�����
			 const int y         ��ȡ�Ĳ�������Ļ�ϵ�������
			 const char *path
			 
**���ܣ�  ��ָ��bmp�ļ��е�ͼ���ȡ����Ļ��,������Ļ�Ĳ��ֲ�������ʾ

********************************/
void readbmp(int x, int y, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//ͼ����
    long int Height;//ͼ��߶�
    long int linebytes;//��ȫ��һ���ֽ���
    unsigned int sign;//bmp�ļ���ʶ
    unsigned long position;//ÿ������Ӧ������Ļ����ʾ������
    register int i, j;
    long int Resx, Resy;//�����ʾ�ĳ��ȺͿ��
    register char page_new = 0;//��ҳ��ʶ
    static char page_old = 0;
    short *buffer = NULL;//������ʾ��һ����1024���ֽ�
    short far
    *
    const VideoBuffer = (short far
    *)0xA0000000L;//�趨�Դ�ָ�벻��
    if ((fpbmp = fopen(path, "rb")) == NULL)//���޷���ָ��ͼ����ֹ��??
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//��ָ��ͼ�񲢲���bmp������ֹ����
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//��ȡͼ�����
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + Width > 1024)//������Ļ���ƣ�������Ļ��С��������ʾ
    {
        Resx = 1024 - x;
    } else {
        Resx = Width;
    }
    if (y + Height > 768) {
        Resy = 768 - y;
    } else {
        Resy = Height;
    }
    linebytes = (Width * 2) % 4;//��Ϊ16λ��bmp��ÿ�����������ֽڣ��������ռ�ֽڲ��ܱ�4��������ȫ
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//��ȫȫ��Ϊ���Ա�4������bmpͼƬ����ʵ��һ�е��ֽ���
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//����ռ䣬���ڴ洢ÿ��ͼ�����Ϣ��֮������int��ʽ������Ϊ16λbmpÿ��������һλ���������㶨λ
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim��ͼ���µߵ�������ͬ�෴�ķ�ʽ��ͼ��¼���Դ�
    {
        fread(buffer, linebytes, 1, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//�۲�һ���Ƿ���һҳ�ڣ��������һҳ��һҳһҳ����
            {
                for (i = 0; i < Resx; i++) {
                    position = 1024L * (y + j) + (x + i);//�˴��������L��������ֻ��ʾһ���ַ������ǵ�������²�����Ϊ���ݹ��󣬰�position�屬�ˣ�Ȼ��ҳ��һֱû��
                    page_new = position >> 15;  /*������ʾҳ�������ֽ�*2/65536*/
                    position &= 0x0000ffffl;    //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ�����������ʮ��λ
                    if (page_new != page_old)   /*����ҳ��*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    VideoBuffer[position] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*����ҳ��*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {

                    VideoBuffer[position + i] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                }
            }
        }
    }
    fclose(fpbmp);
    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}

/********************************
**��������put_pixel
**������
**    const int x     Ŀ���ĺ�����
**    const int y     Ŀ����������
**    const int color Ŀ������ɫ
**���ܣ�����Ļ(x,y)�ϻ���
********************************/
void put_pixel(int x, int y, int color) {
/*�Դ�ָ�볣����ָ���Դ��׵�ַ��ָ�뱾�������޸�*/
    unsigned int far
    *
    const video_buffer = (unsigned int far
    *)0xa0000000L;
/*Ҫ�л���ҳ���*/
    unsigned char new_page;
/*��Ӧ�Դ��ַƫ����*/
    unsigned long int page;
    page = ((unsigned long int) y << 10) + x;
    new_page = page >> 15;  /*32k����һ��ҳ������32k������㷨*/
    selectpage(new_page);
    video_buffer[page] = color;
}

/********************************
**��������SVGA_Horizon
**������
**    const int x1     Ŀ��ֱ�ߵ���ʼ�������
**    const int y1     Ŀ��ֱ�ߵ���ʼ��������
**    const int length  Ŀ��ֱ�ߵĿ��
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel����ʼ�㣨x1,y1��,����Ϊlenght�ĺ���
********************************/
void SVGA_Horizon(const int x1, const int y1, const int length, const int color) {
    register char page_old = (x1 + y1 * 1024) >> 15;
    register char page_new;
    short far
    *Videobuffer =(short far
    *)0xA0000000L;
    long int position = 0;
    int x = 0;//move for x
    if (length > 0) {
        if (y1 * 5 % 256 > 251) {
            for (x = x1; x <= x1 + length; x++) {
                put_pixel(x, y1, color);
            }
        } else {
            page_new = (x1 + 1024L * y1) >> 15;
            if (page_new != page_old)   /*����ҳ��*/
            {
                selectpage(page_new);
                page_old = page_new;
            }
            selectpage(page_new);
            for (x = x1; x <= x1 + length; x++) {
                position = (y1 * 1024L + x);
                position &= 0x0000ffffl;
                Videobuffer[position] = color;
            }
        }
    } else {
        if (y1 * 5 % 256 > 251) {
            for (x = x1; x >= x1 + length; x--) {
                put_pixel(x, y1, color);
            }
        } else {
            page_new = (x1 + 1024L * y1) >> 15;
            if (page_new != page_old)   /*����ҳ��*/
            {
                selectpage(page_new);
                page_old = page_new;
            }
            selectpage(page_new);
            for (x = x1; x >= x1 + length; x--) {
                position = (y1 * 1024L + x);
                position &= 0x0000ffffl;
                Videobuffer[position] = color;
            }
        }
    }
}

/********************************
**��������SVGA_Rectangular
**������
**    const int x1     Ŀ����ε���˵������
**    const int y1     Ŀ����ε���˵�������
**    const int x2     Ŀ����ε��Ҷ˵������
**    const int y2     Ŀ����ε��Ҷ˵�������
**	  const int x3     Ŀ����ε��Ҷ˵������
**    const int y3     Ŀ����ε��Ҷ˵�������
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel(x1,y1),(x2,y2)������
**ֻ֧�������ʼ�㣬�Ҳ���ֹ��Ĳ���
********************************/
void SVGA_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char color) {
    SVGA_Line(x1, y1, x2, y2, color);
    SVGA_Line(x1, y1, x3, y3, color);
    SVGA_Line(x2, y2, x3, y3, color);
}

/********************************
**��������SVGA_Rectangular
**������
**    const int x1     Ŀ����ε���˵������
**    const int y1     Ŀ����ε���˵�������
**    const int x2     Ŀ����ε��Ҷ˵������
**    const int y2     Ŀ����ε��Ҷ˵�������
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel(x1,y1),(x2,y2)������
**ֻ֧�������ʼ�㣬�Ҳ���ֹ��Ĳ���
********************************/
void SVGA_Rectangular(const int x1, const int y1, const int x2, const int y2, const int color) {
    int x, y;
    for (y = y1; y < y2; y++) {
        put_pixel(x1, y, color);
        put_pixel(x2, y, color);
    }
    SVGA_Horizon(x1, y1, x2 - x1, color);
    SVGA_Horizon(x1, y2, x2 - x1, color);
}

/********************************
**��������SVGA_Button
**������
**    const int x1     Ŀ����ε���˵������
**    const int y1     Ŀ����ε���˵�������
**    const int x2     Ŀ����ε��Ҷ˵������
**    const int y2     Ŀ����ε��Ҷ˵�������
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel(x1,y1),(x2,y2)������
**ֻ֧�������ʼ�㣬�Ҳ���ֹ��Ĳ���
********************************/
void SVGA_Button(const int x1, const int y1, const int x2, const int y2, const int color) {
    int i;
    for (i = 0; i < 3; i++) {
        SVGA_Straight(x1 + i, y1, y2 - y1, color);
        SVGA_Straight(x2 - i, y1, y2 - y1, color);
        SVGA_Horizon(x1, y1 + i, x2 - x1, color);
        SVGA_Horizon(x1, y2 - i, x2 - x1, color);
    }
}

/********************************
**��������SVGA_Straight
**������
**    const int x1     Ŀ��ֱ�ߵ���ʼ�������
**    const int y1     Ŀ��ֱ�ߵ���ʼ��������
**    const int length  Ŀ��ֱ�ߵĿ��
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel����ʼ�㣨x1,y1��,����Ϊlenght��������
********************************/
void SVGA_Straight(const x, const y, const length, const color) {
    int y1;
    if (length > 0) {
        for (y1 = y; y1 < y + length; y1++) {
            put_pixel(x, y1, color);
        }
    } else {
        for (y1 = y; y1 > y + length; y1--) {
            put_pixel(x, y1, color);
        }
    }
}

/********************************
**��������SVGA_Bar
**������
**    const int x1     Ŀ����ε���˵������
**    const int y1     Ŀ����ε���˵�������
**    const int x2     Ŀ����ε��Ҷ˵������
**    const int y2     Ŀ����ε��Ҷ˵�������
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel(x1,y1)��(x2,y2)��ʵ�ľ���
**ֻ֧�������ʼ�㣬�Ҳ���ֹ��Ĳ���
********************************/
void SVGA_Bar(const int x1, const int y1, const int x2, const int y2, const int color) {
    register char page_old = (x1 + y1 * 1024) >> 15;
    register char page_new = 0;
    short far
    *Videobuffer =(short far
    *)0xA0000000L;
    long int position = 0;
    int x = 0, y = 0;
    for (y = y1; y < y2; y++) {
        if (y1 * 5 % 256 > 251) {
            for (x = x1; x <= x2; x++) {
                put_pixel(x, y, color);
            }
        } else {
            page_new = (x1 + 1024L * y) >> 15;
            if (page_new != page_old)   /*����ҳ��*/
            {
                selectpage(page_new);
                page_old = page_new;
            }
            selectpage(page_new);
            for (x = x1; x <= x2; x++) {
                position = (y * 1024L + x);
                position &= 0x0000ffffl;
                Videobuffer[position] = color;
            }
        }
    }
}

/********************************
**��������SVGA_Cricle
**������
**    const int x1     Ŀ��Բ�ĺ�����
**    const int y1     Ŀ��Բ��������
**    const int r      Ŀ��Բ�İ뾶
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel��Բ��Ϊ(x1,y1),�뾶Ϊr�Ŀ���Բ
********************************/
void SVGA_Cricle(const int x1, const int y1, const int r, const int color) {
    float i;
    for (i = 0; i < 2 * PI; i = i + PI / 180) {
        put_pixel(x1 + r * cos(i), y1 + r * sin(i), color);
    }
}

/********************************
**��������SVGA_Ball
**������
**    const int x1     Ŀ��Բ�ĺ�����
**    const int y1     Ŀ��Բ��������
**    const int r      Ŀ��Բ�İ뾶
**    const int color     ���ߵ���ɫ
**���ܣ�����put_pixel��Բ��Ϊ(x1,y1),�뾶Ϊr��ʵ��Բ
********************************/
void SVGA_Ball(const int x1, const int y1, const int r, const int color) {
    int R;
    for (R = 0; R < r; R++) {
        SVGA_Cricle(x1, y1, R, color);
    }
}

/********************************
**��������get_image
**������
**    const int x1     Ŀ���ĺ�����
**    const int y1     Ŀ����������
**    const int x2     Ŀ���ĺ�����
**    const int y2     Ŀ����������
**���ܣ��洢��Ļ(x1,y1)��(x2,y2)�����򣬽���Ϣ���ݸ�buffer
**ע�⣺ֻ�ܴ洢��������Ļ��С�Ķ���
********************************/
void get_image(int x1, int y1, int x2, int y2, short far

*save)
{
int i, j, k = 0;
int m = x2 - x1, n = y2 - y1;
char oldpage, newpage;
unsigned long position;
short far
*
video_buffer =
(
short far
*)0xA0000000L;  //��ʼ��ָ����Ļ���Դ��ָ�룬��ʼ��λ�ã����Ͻǣ�
oldpage = (y1 * (long) 1024 + x1) >> 15;    //��ʼ��ҳ��
newpage = oldpage;
selectpage(oldpage);
for(
i = 0;
i<n;
i++)
{
for(
j = 0;
j<m;
j++,k++)
{
position = (i + y1) * (long) 1024 + j + x1;
newpage = position >> 15;
if(newpage!=oldpage)            //���û�ҳ����
{
selectpage(newpage);
oldpage = newpage;
}
position&=0x0000ffffl;
save[k]=*(video_buffer+position);//i�ǻ�ˢ�¸��ǵģ���������i��Ϊ�洢��ֵ
}
}
}

/********************************
**��������put_image
**������
**    const int x1     Ŀ���ĺ�����
**    const int y1     Ŀ����������
**    const int x2     Ŀ���ĺ�����
**    const int y2     Ŀ����������
**    short * buffer    ָ�����洢����Ϣ
**���ܣ����洢����Ϣ�������뵽��Ļ��
**ע�⣺ֻ�ܴ洢��������Ļ��С�Ķ���
********************************/
void put_image(const int x1, const int y1, const int x2, const int y2, short far

*buffer)
{
register int i;
register int j;
register int k = 0;
register char page_old;
register char page_new;
long int position;
short far
*
Videobuffer =
(
short far
*)0xA0000000L;
if(x2>1024)
{
printf("the Blancket area is in the select part");//������Ļ��������ʾ
return;
}
if(y2>768)
{
printf("the Blancket area is in the select part");
return;
}
position = x1 + y1 * 1024L;
page_old = position >> 15;
page_new = page_old;
selectpage(page_old);
for(
j = 0;
j<y2-
y1;
j++)
{
for(
i = 0;
i<x2-
x1;
i++,k++)
{
position = 1024L * (y1 + j) + x1 + i;
page_new = position >> 15;//65536���ֽڻ�һҳ
if (page_new != page_old)   /*����ҳ��*/
{
selectpage(page_new);
page_old = page_new;
}
position&=0x0000ffffl;//ȷ����������ҳ���ϵ�λ��
*(Videobuffer+position)=buffer[k];//i�ǻ�ˢ�¸��ǵģ���������i��Ϊ�洢��ֵ
}
}
}

/**********************************************************
Function��		Getcolor

Description��	���ڻ�ȡ��ǰ����ɫ

Input��			int x       �û����û���
				int y 	    �û�������Ӧ���û�·��

Output��	    NONE

Return��		��ǰ��ɫ

**********************************************************/
int Getcolor(const int x, const int y) {
    short far
    *Videobuffer =(short far
    *)0xA0000000L;
    int color;
    long int position;
    register page;
    position = x + y * 1024L;
    page = position >> 15;
    selectpage(page);
    position &= 0x0000ffffl;
    color = Videobuffer[position];
    return color;
}

/**********************************************************
Function��		maskbmp

Description��   ������ʾͼ���к�ɫ�Ĳ���

Input��
				int x       ���Ͻ�����
				int y       ���Ͻ�����
				int n       �Ŵ���
				char *path  ͼ���Ӧ·��

Output��	    ͼ��Ϊ��ɫ�Ĳ���

Return��		NONE

**********************************************************/
void maskbmp(int x, int y, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//ͼ����
    long int Height;//ͼ��߶�
    long int linebytes;//��ȫ��һ���ֽ���
    unsigned int sign;//bmp�ļ���ʶ
    unsigned long position;//ÿ������Ӧ������Ļ����ʾ������
    register int i, j;
    long int Resx, Resy;//�����ʾ�ĳ��ȺͿ��
    register char page_new = 0;//��ҳ��ʶ
    static char page_old = 0;
    short *buffer = NULL;//������ʾ��һ����1024���ֽ�
    short far
    *
    const VideoBuffer = (short far
    *)0xA0000000L;//�趨�Դ�ָ�벻��
    if ((fpbmp = fopen(path, "rb")) == NULL)//���޷���ָ��ͼ����ֹ��??
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//��ָ��ͼ�񲢲���bmp������ֹ����
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//��ȡͼ�����
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + Width > 1024)//������Ļ���ƣ�������Ļ��С��������ʾ
    {
        Resx = 1024 - x;
    } else {
        Resx = Width;
    }
    if (y + Height > 768) {
        Resy = 768 - y;
    } else {
        Resy = Height;
    }
    linebytes = (Width * 2) % 4;//��Ϊ16λ��bmp��ÿ�����������ֽڣ��������ռ�ֽڲ��ܱ�4��������ȫ
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//��ȫȫ��Ϊ���Ա�4������bmpͼƬ����ʵ��һ�е��ֽ���
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//����ռ䣬���ڴ洢ÿ��ͼ�����Ϣ��֮������int��ʽ������Ϊ16λbmpÿ��������һλ���������㶨λ
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim��ͼ���µߵ�������ͬ�෴�ķ�ʽ��ͼ��¼���Դ�
    {
        fread(buffer, linebytes, 1, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//�۲�һ���Ƿ���һҳ�ڣ��������һҳ��һҳһҳ����
            {
                for (i = 0; i < Resx; i++) {
                    if (buffer[i] != -1) {
                        position = 1024L * (y + j) + (x + i);//�˴��������L��������ֻ��ʾһ���ַ������ǵ�������²�����Ϊ���ݹ��󣬰�position�屬�ˣ�Ȼ��ҳ��һֱû��
                        page_new = position >> 15;  /*������ʾҳ�������ֽ�*2/65536*/
                        position &= 0x0000ffffl;    //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ�����������ʮ��λ
                        if (page_new != page_old)   /*����ҳ��*/
                        {
                            selectpage(page_new);
                            page_old = page_new;
                        }
                        VideoBuffer[position] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                    }
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*����ҳ��*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {
                    if (buffer[i] != -1) {
                        VideoBuffer[position + i] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                    }
                }
            }
        }
    }
    fclose(fpbmp);
    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}

/**********************************************************
Function��		enlarge

Description��	���ڷŴ�ͼ��Ϊ������

Input��
				int x       ���Ͻ�����
				int y       ���Ͻ�����
				int n       �Ŵ���
				char *path  ͼ���Ӧ·��

Output��	    �Ŵ���ͼ��

Return��		NONE

**********************************************************/
void enlarge(int x, int y, int n, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//ͼ����
    long int Height;//ͼ��߶�
    long int linebytes;//��ȫ��һ���ֽ���
    unsigned int sign;//bmp�ļ���ʶ
    unsigned long position;//ÿ������Ӧ������Ļ����ʾ������
    register int i, j;
    register int k = 0, m = 0;//�����Ƿ�ﵽӦ�б���
    long int Resx, Resy;//�����ʾ�ĳ��ȺͿ��
    register char page_new = 0;//��ҳ��ʶ
    static char page_old = 0;
    short *buffer = NULL;//������ʾ��һ����1024���ֽ�
    short far
    *
    const VideoBuffer = (short far
    *)0xA0000000L;//�趨�Դ�ָ�벻��
    if ((fpbmp = fopen(path, "rb")) == NULL)//���޷���ָ��ͼ����ֹ����
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//��ָ��ͼ�񲢲���bmp������ֹ����
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//��ȡͼ�����
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + n * Width > 1024)//������Ļ���ƣ�������Ļ��С��������ʾ
    {
        Resx = 1024 - x;
    } else {
        Resx = n * Width;
    }
    if (y + n * Height > 768) {
        Resy = 768 - y;
    } else {
        Resy = n * Height;
    }
    linebytes = (Width * 2) % 4;//��Ϊ16λ��bmp��ÿ�����������ֽڣ��������ռ�ֽڲ��ܱ�4��������ȫ
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//��ȫȫ��Ϊ���Ա�4������bmpͼƬ����ʵ��һ�е��ֽ���
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//����ռ䣬���ڴ洢ÿ��ͼ�����Ϣ��֮������int��ʽ������Ϊ16λbmpÿ��������һλ���������㶨λ
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim��ͼ���µߵ�������ͬ�෴�ķ�ʽ��ͼ��¼���Դ�
    {
        fread(buffer, linebytes, 1, fpbmp);
        for (k = 0; k < n; k++) {
            if (j * n + y < Resy) {
                if ((j * n + y + k) * 5 % 256 > 251)//�۲�һ���Ƿ���һҳ�ڣ��������һҳ��һҳһҳ����
                {
                    for (i = 0; (m + i * n < Resx); i++) {
                        for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {
                            position = 1024L * (y + j * n + k) +
                                       (x + m + i * n);//�˴��������L��������ֻ��ʾһ���ַ������ǵ�������²�����Ϊ���ݹ��󣬰�position�屬�ˣ�Ȼ��ҳ��һֱû��
                            page_new = position >> 15;  /*������ʾҳ�������ֽ�*2/65536*/
                            position &= 0x0000ffffl;    //������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ�����������ʮ��λ
                            if (page_new != page_old)   /*����ҳ��*/
                            {
                                selectpage(page_new);
                                page_old = page_new;
                            }
                            VideoBuffer[position] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                        }
                    }
                } else {
                    position = (y + j * n + k) * 1024L + x;
                    page_new = position >> 15;
                    position &= 0x0000ffffl;
                    if (page_new != page_old)   /*����ҳ��*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    for (i = 0; (m + i * n < Resx); i++)
                        for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {

                            for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {
                                VideoBuffer[position + i * n + m] = buffer[i];//��Ϊ���������λ��ԣ�����Ҳ���ó���2
                            }
                        }
                }
            }
        }
    }
    fclose(fpbmp);
    if (buffer != NULL) {
        free(buffer);
        buffer = NULL;
    }
}
/**********************************************************
Function��		CircleBar

Description��	���ڻ���Բ��ʵ�ľ���

Input��
				int x1       ��Բ��x����
				int y1       ��Բ��y����
				int x2       ��Բ��x����
				int y2       ��Բ��y����
				int radius   ��Բ�İ뾶
				int color    ������ɫ

Output��	    Բ��ʵ�ľ���

Return��		NONE

**********************************************************/
void CircleBar(const int x1,const int y1,const int x2,const int y2,const int radius,const int color) {
    SVGA_Ball(x1,y1,radius,color);
    SVGA_Ball(x2,y2,radius,color);
    SVGA_Bar(x1, y1-radius, x2, y2+radius, color);
}