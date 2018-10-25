#include "./header/SVGA.h"
/**************************************
   SVGA的功能号ax说明
   0x4f00  读SVGA卡信息
   0x4f01  读显示模式信息
   0x4f02  设置显示模式
   0x4f03  读当前显示模式
   0x4f04  存储或恢复SVGA的视频状态
   0x4f05  控制内存页区域切换
   0x4f06  设置或读取逻辑扫描线宽度
   0x4f07  设置或读取视频内存与屏幕的初始对应位置
   0x4f08  设置或读取DAC各原色有效位数
   SVGA显示模式号bx：
		模式号		分辨率		颜色数		颜色位定义
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
Description：	用于显示图像

Function List：
	1.void Set_SVGA(void);
	设置显示模式
    2.void selectpage(register char page);
	用于控制内存页区域切换
    3.void (const int top,const int bottom,const int left,const int right,const int x,const int y,const char *path);
	用于显示图像内部分图像
    4.void (int x, int y,char*path);
	用于读取bmp文件
    5.void put_pixel(int x,int y,int color); 
    画点函数
    6.void SVGA_Horizon(const int x1,const int y1,const int length,const int color);
	画水平线函数
    7.void SVGA_Line( int x1, int x2, int y1, int y2, int color);
	暂未实现全部功能
    8.void SVGA_Rectangular(const int x1,const int x2,const int y1, const int y2,const int color );
	画方框函数
    9.void SVGA_Bar(const int x1,const int x2,const int y1, const int y2,const int color );
	画实心矩形函数
    10.void SVGA_Cricle(const int x1,const int y1,const int r,const int color);
	画空心圆函数
    11.void (const int x1,const int y1,const int r,const int color);
	画实心圆函数
    12.void get_image(const int x1,const int y1,const int x2,const y2,short far *buffer);
	取屏幕上部分图像的函数（不支持换页）
    13.void put_image(const int x1,const int y1,const int x2,const y2,short far *buffer);
	将部分图像还原到屏幕上的函数（不支持换页）
    14.void SVGA_Straight(const x,const y,const length,const color);
	画垂直线函数
	15.void enlarge(int x, int y,int n,char * path)
	放大图像为整数倍
	16.int Getcolor(const int x, const int y)
	获取某点的颜色
	17.void maskbmp(int x, int y,char*path)
	只画图像黑色的部分
**********************************************************/
//借用他人，不计入代码量
/**********************************************************
Function：		Line

Description：	画一般直线函数
				可以接收超出屏幕范围的数据，只画出在屏幕内部分
				因为没有防止整型变量溢出的判断，画超出屏幕的线时应防止输入特大数据

Calls：			Putpixel256
				
				abs

Called By：		LightSW
				LightNE
				LightNW
				LightSE

Input：			int x1					起始点横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y1					起始点纵坐标，从上到下增加，0为最小值（屏幕参考系）
				int x2					终止点横坐标（屏幕参考系）
				int y2					终止点纵坐标（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		屏幕上画出直线

Return：		None
Others：		None
**********************************************************/
void SVGA_Line(int x1, int y1, int x2, int y2, const int color) {
    int dx, dy;      /*直线x、y坐标差值*/
    int dx2, dy2;    /*加快运算速度的中间值*/
    int xinc, yinc;    /*判断想、y增加方向的符号值*/
    int d, dxy;      /*决策变量*/

/*计算坐标差值和中间变量*/
    dx = abs(x2 - x1);
    dx2 = dx << 1;
    dy = abs(y2 - y1);
    dy2 = dy << 1;

/*判断直线x坐标增加方向*/
    if (x2 > x1) {
        xinc = 1;
    }

/*如果是竖直线*/
    else if (x2 == x1) {
        /*y坐标排序*/
        if (y1 > y2) {
            dx = y1;
            y1 = y2;
            y2 = dx;
        }

        /*画竖直线*/
        for (dx = y1; dx <= y2; dx++) {
            put_pixel(x1, dx, color);
        }

        return;
    } else {
        xinc = -1;
    }

/*判断直线y坐标增加方向*/
    if (y2 > y1) {
        yinc = 1;
    }

/*如果是水平线*/
    else if (y2 == y1) {
        SVGA_Horizon(x1, y1, x2 - x1, color);
        return;
    } else {
        yinc = -1;
    }

/*******************************
以下运用Bresenham算法生成直线。
该算法是得到公认的成熟的快速算法。
具体细节略去。
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
**函数名：Set_SVGA
**参数：  Void
**功能：  设置显示模式为0x117
********************************/
void Set_SVGA(void)
//设置当前显示模式
{
    union REGS regs;
    regs.x.ax = 0x4f02;//设置当前显示模式
    regs.x.bx = 0x117;//设置显示模式分辨率为1024*768 颜色数4K 颜色盘5:6:5
    int86(0x10, &regs, &regs);//调用BIOS int86 10h 中断
    if (regs.x.ax != 0x004f)//如果设置出错，则终止程序
    {
        printf("Set SVGA mode wrong");
        exit(1);
    }
}

/********************************
**函数名：selectpage
**参数：  Void
**功能：  更换界面
********************************/
void selectpage(register char page)
//换页函数
{
    union REGS r;
    r.x.ax = 0x4f05;
    r.x.bx = 0;
    r.x.dx = page; /*选择页面*/
    int86(0x10, &r, &r);
}

/********************************
**函数名：PartBmp
**参数：     const int top       所取的部分在原图像的顶部坐标
			 const int bottom    所取的部分在原图像的底部坐标
			 const int left      所取的部分在原图像的左端坐标
			 const int right     所取的部分在原图像的右端坐标
			 const int x         所取的部分在屏幕上的横坐标
			 const int y         所取的部分在屏幕上的纵坐标
			 const char *path
**功能：  将图像的某一部分读取到屏幕上
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
    long int Width, Height;//图像宽高
    long int linebytes;//一行应该有的字节数
    unsigned long position;//每个像素点在屏幕上应该存在的位置
    register int i, j;//计数
    register char page_new = 0;//换页标识
    register char page_old;
    long int Resx, Resy;
    long int PartWidth, PartHeight;
    short *buffer = NULL;//设置显示屏一行显示1024个像素
    short
    far
    *
    const VideoBuffer = (short
    far
    *)0xA0000000L;//设定显存指针不变
    if ((fpbmp = fopen(path, "rb")) == NULL) {
        printf("Cannot open the picture");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 0L, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//若指定图像并不是bmp，则终止程序
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//读取图像宽、高
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
    linebytes = (Width * 2) % 4;//因为16位的bmp，每个像素两个字节，若宽度所占字节不能被4整除，则补全
    if (fseek(fpbmp, bottom * Width, SEEK_SET) == -1) {
        printf("Fail to analyse file !");
        fclose(fpbmp);
        return;
    }
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4 - linebytes;//补全成为可以被4整除的bmp图片内真实的一行的字节数
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL) {
        printf("no memory");
    }
    fseek(fpbmp, 70L + linebytes * (Height - bottom) + left * 2L, 0);
    for (j = PartHeight - 1; j > -1; j--) {
        fread(buffer, 2, PartWidth, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//整除52.1，观察一行是否都在一页内，如果不在一页则一页一页处理
            {
                for (i = 0; i < Resx; i++) {
                    position = 1024L * (y + j) + (x + i);//此处必须加上L否则会出现只显示一部分反复覆盖的情况，猜测是因为数据过大，把position冲爆了，然后页数一直没变化
                    page_new = position >> 15;  /*计算显示页，两个字节*2/65536*/
                    position &= 0x0000ffffl;    /*计算在一个页面上的偏移位置，整除65536的快速方案，保留低16位*/
                    if (page_new != page_old)   /*更换页面*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    VideoBuffer[position] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*更换页面*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {

                    VideoBuffer[position + i] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
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
**函数名：readbmp

**参数：     const int x         所取的部分在屏幕上的横坐标
			 const int y         所取的部分在屏幕上的纵坐标
			 const char *path
			 
**功能：  将指定bmp文件中的图像读取到屏幕上,超过屏幕的部分不予以显示

********************************/
void readbmp(int x, int y, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//图像宽度
    long int Height;//图像高度
    long int linebytes;//补全后一行字节数
    unsigned int sign;//bmp文件标识
    unsigned long position;//每个像素应该在屏幕上显示的坐标
    register int i, j;
    long int Resx, Resy;//最后显示的长度和宽度
    register char page_new = 0;//换页标识
    static char page_old = 0;
    short *buffer = NULL;//设置显示屏一行显1024个字节
    short
    far
    *
    const VideoBuffer = (short
    far
    *)0xA0000000L;//设定显存指针不变
    if ((fpbmp = fopen(path, "rb")) == NULL)//若无法打开指定图像，终止程??
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//若指定图像并不是bmp，则终止程序
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//读取图像宽、高
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + Width > 1024)//设置屏幕限制，超出屏幕大小不予以显示
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
    linebytes = (Width * 2) % 4;//因为16位的bmp，每个像素两个字节，若宽度所占字节不能被4整除，则补全
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//补全全称为可以被4整除的bmp图片内真实的一行的字节数
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//分配空间，用于存储每行图像的信息，之所以用int格式，是因为16位bmp每两个像素一位，这样方便定位
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim读图上下颠倒，所以同相反的方式将图像录入显存
    {
        fread(buffer, linebytes, 1, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//观察一行是否都在一页内，如果不在一页则一页一页处理
            {
                for (i = 0; i < Resx; i++) {
                    position = 1024L * (y + j) + (x + i);//此处必须加上L否则会出现只显示一部分反复覆盖的情况，猜测是因为数据过大，把position冲爆了，然后页数一直没变
                    page_new = position >> 15;  /*计算显示页，两个字节*2/65536*/
                    position &= 0x0000ffffl;    //计算在一个页面上的偏移位置，整除65536的快速方案，保留低十六位
                    if (page_new != page_old)   /*更换页面*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    VideoBuffer[position] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*更换页面*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {

                    VideoBuffer[position + i] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
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
**函数名：put_pixel
**参数：
**    const int x     目标点的横坐标
**    const int y     目标点的纵坐标
**    const int color 目标点的颜色
**功能：在屏幕(x,y)上画点
********************************/
void put_pixel(int x, int y, int color) {
/*显存指针常量，指向显存首地址，指针本身不允许修改*/
    unsigned int
    far
    *
    const video_buffer = (unsigned int
    far
    *)0xa0000000L;
/*要切换的页面号*/
    unsigned char new_page;
/*对应显存地址偏移量*/
    unsigned long int page;
    page = ((unsigned long int) y << 10) + x;
    new_page = page >> 15;  /*32k个点一换页，除以32k的替代算法*/
    selectpage(new_page);
    video_buffer[page] = color;
}

/********************************
**函数名：SVGA_Horizon
**参数：
**    const int x1     目标直线的起始点横坐标
**    const int y1     目标直线的起始点纵坐标
**    const int length  目标直线的宽度
**    const int color     画线的颜色
**功能：调用put_pixel画起始点（x1,y1）,长度为lenght的横线
********************************/
void SVGA_Horizon(const int x1, const int y1, const int length, const int color) {
    register char page_old = (x1 + y1 * 1024) >> 15;
    register char page_new;
    short
    far
    * Videobuffer = (short
    far
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
            if (page_new != page_old)   /*更换页面*/
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
            if (page_new != page_old)   /*更换页面*/
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
**函数名：SVGA_Rectangular
**参数：
**    const int x1     目标矩形的左端点横坐标
**    const int y1     目标矩形的左端点纵坐标
**    const int x2     目标矩形的右端点横坐标
**    const int y2     目标矩形的右端点纵坐标
**	  const int x3     目标矩形的右端点横坐标
**    const int y3     目标矩形的右端点纵坐标
**    const int color     画线的颜色
**功能：调用put_pixel(x1,y1),(x2,y2)画矩形
**只支持左侧起始点，右侧终止点的操作
********************************/
void SVGA_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, unsigned char color) {
    SVGA_Line(x1, y1, x2, y2, color);
    SVGA_Line(x1, y1, x3, y3, color);
    SVGA_Line(x2, y2, x3, y3, color);
}

/********************************
**函数名：SVGA_Rectangular
**参数：
**    const int x1     目标矩形的左端点横坐标
**    const int y1     目标矩形的左端点纵坐标
**    const int x2     目标矩形的右端点横坐标
**    const int y2     目标矩形的右端点纵坐标
**    const int color     画线的颜色
**功能：调用put_pixel(x1,y1),(x2,y2)画矩形
**只支持左侧起始点，右侧终止点的操作
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
**函数名：SVGA_Button
**参数：
**    const int x1     目标矩形的左端点横坐标
**    const int y1     目标矩形的左端点纵坐标
**    const int x2     目标矩形的右端点横坐标
**    const int y2     目标矩形的右端点纵坐标
**    const int color     画线的颜色
**功能：调用put_pixel(x1,y1),(x2,y2)画矩形
**只支持左侧起始点，右侧终止点的操作
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
**函数名：SVGA_Straight
**参数：
**    const int x1     目标直线的起始点横坐标
**    const int y1     目标直线的起始点纵坐标
**    const int length  目标直线的宽度
**    const int color     画线的颜色
**功能：调用put_pixel画起始点（x1,y1）,长度为lenght的竖线线
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
**函数名：SVGA_Bar
**参数：
**    const int x1     目标矩形的左端点横坐标
**    const int y1     目标矩形的左端点纵坐标
**    const int x2     目标矩形的右端点横坐标
**    const int y2     目标矩形的右端点纵坐标
**    const int color     画线的颜色
**功能：调用put_pixel(x1,y1)到(x2,y2)画实心矩形
**只支持左侧起始点，右侧终止点的操作
********************************/
void SVGA_Bar(const int x1, const int y1, const int x2, const int y2, const int color) {
    register char page_old = (x1 + y1 * 1024) >> 15;
    register char page_new = 0;
    short
    far
    * Videobuffer = (short
    far
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
            if (page_new != page_old)   /*更换页面*/
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
**函数名：SVGA_Cricle
**参数：
**    const int x1     目标圆的横坐标
**    const int y1     目标圆的纵坐标
**    const int r      目标圆的半径
**    const int color     画线的颜色
**功能：调用put_pixel画圆心为(x1,y1),半径为r的空心圆
********************************/
void SVGA_Cricle(const int x1, const int y1, const int r, const int color) {
    float i;
    for (i = 0; i < 2 * PI; i = i + PI / 180) {
        put_pixel(x1 + r * cos(i), y1 + r * sin(i), color);
    }
}

/********************************
**函数名：SVGA_Ball
**参数：
**    const int x1     目标圆的横坐标
**    const int y1     目标圆的纵坐标
**    const int r      目标圆的半径
**    const int color     画线的颜色
**功能：调用put_pixel画圆心为(x1,y1),半径为r的实心圆
********************************/
void SVGA_Ball(const int x1, const int y1, const int r, const int color) {
    int R;
    for (R = 0; R < r; R++) {
        SVGA_Cricle(x1, y1, R, color);
    }
}

/********************************
**函数名：get_image
**参数：
**    const int x1     目标点的横坐标
**    const int y1     目标点的纵坐标
**    const int x2     目标点的横坐标
**    const int y2     目标点的纵坐标
**功能：存储屏幕(x1,y1)到(x2,y2)的区域，将信息传递给buffer
**注意：只能存储不超过屏幕大小的东西
********************************/
void get_image(const int x1, const int y1, const int x2, const int y2, short far

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
        short
far
*)0xA0000000L;  //初始化指向屏幕点显存的指针，初始化位置（左上角）
oldpage = (y1 * (long) 1024 + x1) >> 15;    //初始化页码
newpage = oldpage;
selectpage(oldpage);
for (
i = 0;
i<n;
i++)
{
for (
j = 0;
j<m;
j++, k++)
{
position = (i + y1) * (long) 1024 + j + x1;
newpage = position >> 15;
if (newpage!=oldpage)            //调用换页函数
{
selectpage(newpage);
oldpage = newpage;
}
position&=0x0000ffffl;
save[k]=*(video_buffer+position);//i是会刷新覆盖的，不可以用i作为存储数值
}
}
}

/********************************
**函数名：put_image
**参数：
**    const int x1     目标点的横坐标
**    const int y1     目标点的纵坐标
**    const int x2     目标点的横坐标
**    const int y2     目标点的纵坐标
**    short * buffer    指向所存储的信息
**功能：将存储的信息重新输入到屏幕上
**注意：只能存储不超过屏幕大小的东西
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
        short
far
*)0xA0000000L;
if (x2>1024)
{
printf("the Blancket area is in the select part");//超出屏幕则不予以显示
return;
}
if (y2>768)
{
printf("the Blancket area is in the select part");
return;
}
position = x1 + y1 * 1024L;
page_old = position >> 15;
page_new = page_old;
selectpage(page_old);
for (
j = 0;
j<y2-
y1;
j++)
{
for (
i = 0;
i<x2-
x1;
i++, k++)
{
position = 1024L * (y1 + j) + x1 + i;
page_new = position >> 15;//65536个字节换一页
if (page_new != page_old)   /*更换页面*/
{
selectpage(page_new);
page_old = page_new;
}
position&=0x0000ffffl;//确定函数在新页面上的位置
*(Videobuffer+position)=buffer[k];//i是会刷新覆盖的，不可以用i作为存储数值
}
}
}

/**********************************************************
Function：		Getcolor

Description：	用于获取当前点颜色

Input：			int x       用户的用户名
				int y 	    用户名所对应的用户路径

Output：	    NONE

Return：		当前颜色

**********************************************************/
int Getcolor(const int x, const int y) {
    short
    far
    * Videobuffer = (short
    far
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
Function：		maskbmp

Description：   用于显示图像中黑色的部分

Input：
				int x       左上角坐标
				int y       左上角坐标
				int n       放大倍数
				char *path  图像对应路径

Output：	    图像为黑色的部分

Return：		NONE

**********************************************************/
void maskbmp(int x, int y, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//图像宽度
    long int Height;//图像高度
    long int linebytes;//补全后一行字节数
    unsigned int sign;//bmp文件标识
    unsigned long position;//每个像素应该在屏幕上显示的坐标
    register int i, j;
    long int Resx, Resy;//最后显示的长度和宽度
    register char page_new = 0;//换页标识
    static char page_old = 0;
    short *buffer = NULL;//设置显示屏一行显1024个字节
    short
    far
    *
    const VideoBuffer = (short
    far
    *)0xA0000000L;//设定显存指针不变
    if ((fpbmp = fopen(path, "rb")) == NULL)//若无法打开指定图像，终止程??
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//若指定图像并不是bmp，则终止程序
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//读取图像宽、高
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + Width > 1024)//设置屏幕限制，超出屏幕大小不予以显示
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
    linebytes = (Width * 2) % 4;//因为16位的bmp，每个像素两个字节，若宽度所占字节不能被4整除，则补全
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//补全全称为可以被4整除的bmp图片内真实的一行的字节数
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//分配空间，用于存储每行图像的信息，之所以用int格式，是因为16位bmp每两个像素一位，这样方便定位
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim读图上下颠倒，所以同相反的方式将图像录入显存
    {
        fread(buffer, linebytes, 1, fpbmp);
        if (j < Resy) {
            if ((j + y) * 5 % 256 > 251)//观察一行是否都在一页内，如果不在一页则一页一页处理
            {
                for (i = 0; i < Resx; i++) {
                    if (buffer[i] != -1) {
                        position = 1024L * (y + j) + (x + i);//此处必须加上L否则会出现只显示一部分反复覆盖的情况，猜测是因为数据过大，把position冲爆了，然后页数一直没变
                        page_new = position >> 15;  /*计算显示页，两个字节*2/65536*/
                        position &= 0x0000ffffl;    //计算在一个页面上的偏移位置，整除65536的快速方案，保留低十六位
                        if (page_new != page_old)   /*更换页面*/
                        {
                            selectpage(page_new);
                            page_old = page_new;
                        }
                        VideoBuffer[position] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
                    }
                }
            } else {
                position = (y + j) * 1024L + x;
                page_new = position >> 15;
                position &= 0x0000ffffl;
                if (page_new != page_old)   /*更换页面*/
                {
                    selectpage(page_new);
                    page_old = page_new;
                }
                for (i = 0; i < Resx; i++) {
                    if (buffer[i] != -1) {
                        VideoBuffer[position + i] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
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
Function：		enlarge

Description：	用于放大图像为整数倍

Input：
				int x       左上角坐标
				int y       左上角坐标
				int n       放大倍数
				char *path  图像对应路径

Output：	    放大后的图像

Return：		NONE

**********************************************************/
void enlarge(int x, int y, int n, char *path) {
    FILE *fpbmp = NULL;
    long int Width;//图像宽度
    long int Height;//图像高度
    long int linebytes;//补全后一行字节数
    unsigned int sign;//bmp文件标识
    unsigned long position;//每个像素应该在屏幕上显示的坐标
    register int i, j;
    register int k = 0, m = 0;//计算是否达到应有倍数
    long int Resx, Resy;//最后显示的长度和宽度
    register char page_new = 0;//换页标识
    static char page_old = 0;
    short *buffer = NULL;//设置显示屏一行显1024个字节
    short
    far
    *
    const VideoBuffer = (short
    far
    *)0xA0000000L;//设定显存指针不变
    if ((fpbmp = fopen(path, "rb")) == NULL)//若无法打开指定图像，终止程序
    {
        printf("Cannot open the picture");
        exit(1);
    }
    fseek(fpbmp, 0, 0);
    fread(&sign, 2, 1, fpbmp);
    if (sign != 0x4d42)//若指定图像并不是bmp，则终止程序
    {
        printf("the file is not a bmp");
        fclose(fpbmp);
        exit(1);
    }
    fseek(fpbmp, 18L, 0);
    fread(&Width, 4, 1, fpbmp);//读取图像宽、高
    fseek(fpbmp, 22L, 0);
    fread(&Height, 4, 1, fpbmp);
    if (x + n * Width > 1024)//设置屏幕限制，超出屏幕大小不予以显示
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
    linebytes = (Width * 2) % 4;//因为16位的bmp，每个像素两个字节，若宽度所占字节不能被4整除，则补全
    if (!linebytes) {
        linebytes = Width * 2;
    } else {
        linebytes = Width * 2 + 4L - linebytes;//补全全称为可以被4整除的bmp图片内真实的一行的字节数
    }
    if ((buffer = (short *) malloc(linebytes)) == NULL)//分配空间，用于存储每行图像的信息，之所以用int格式，是因为16位bmp每两个像素一位，这样方便定位
    {
        printf("no memory");
        exit(1);
    }
    fseek(fpbmp, 70L, 0);
    page_old = (Resy - 1 + y) * 1024L + Resx + x;
    selectpage(page_old);
    page_new = page_old;
    for (j = Height - 1; j > -1; j--)//dim读图上下颠倒，所以同相反的方式将图像录入显存
    {
        fread(buffer, linebytes, 1, fpbmp);
        for (k = 0; k < n; k++) {
            if (j * n + y < Resy) {
                if ((j * n + y + k) * 5 % 256 > 251)//观察一行是否都在一页内，如果不在一页则一页一页处理
                {
                    for (i = 0; (m + i * n < Resx); i++) {
                        for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {
                            position = 1024L * (y + j * n + k) +
                                       (x + m + i * n);//此处必须加上L否则会出现只显示一部分反复覆盖的情况，猜测是因为数据过大，把position冲爆了，然后页数一直没变
                            page_new = position >> 15;  /*计算显示页，两个字节*2/65536*/
                            position &= 0x0000ffffl;    //计算在一个页面上的偏移位置，整除65536的快速方案，保留低十六位
                            if (page_new != page_old)   /*更换页面*/
                            {
                                selectpage(page_new);
                                page_old = page_new;
                            }
                            VideoBuffer[position] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
                        }
                    }
                } else {
                    position = (y + j * n + k) * 1024L + x;
                    page_new = position >> 15;
                    position &= 0x0000ffffl;
                    if (page_new != page_old)   /*更换页面*/
                    {
                        selectpage(page_new);
                        page_old = page_new;
                    }
                    for (i = 0; (m + i * n < Resx); i++)
                        for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {

                            for (m = 0; ((m < n) && (m + i * n < Resx)); m++) {
                                VideoBuffer[position + i * n + m] = buffer[i];//因为最后是以两位相对，所以也不用乘以2
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
Function：		CircleBar

Description：	用于画出圆角实心矩形

Input：
				int x1       左圆心x坐标
				int y1       左圆心y坐标
				int x2       右圆心x坐标
				int y2       右圆心y坐标
				int radius   两圆的半径
				int color    填充的颜色

Output：	    圆角实心矩形

Return：		NONE

**********************************************************/
void CircleBar(const int x1, const int y1, const int x2, const int y2, const int radius, const int color) {
    SVGA_Ball(x1, y1, radius, color);
    SVGA_Ball(x2, y2, radius, color);
    SVGA_Bar(x1, y1 - radius, x2, y2 + radius, color);
}
/**********************************************************
Function：		Pieslice

Description：	用于画出扇形

Input：
				int x        圆弧的圆心x坐标
				int y        圆弧的圆心y坐标
				int stangle  起始角度
				int endangle 结束角度
				int radius   圆弧的半径
				int color    圆弧的颜色

Output：	    圆角实心矩形

Return：		NONE

**********************************************************/
void Arc(int x,int y,float stangle,float endangle,int radius,int color){
    float i;
    for (i = stangle; i <= endangle; i = i + PI / 180) {
        put_pixel(x + radius * cos(i), y - radius * sin(i), color);
    }
}
/**********************************************************
Function：		Pieslice

Description：	用于画出扇形

Input：
				int x        扇形的圆心x坐标
				int y        扇形的圆心y坐标
				int stangle  起始角度
				int endangle 结束角度
				int radius   扇形的半径
				int color    填充的颜色

Output：	    圆角实心矩形

Return：		NONE

**********************************************************/
void Pieslice(int x,int y,float stangle,float endangle,int radius, int color){
    int R;
    for (R = 0; R <= radius; R++) {
        Arc(x, y,stangle,endangle, R, color);
    }
}