//
// Created by patrick on 10/19/18.
//

#include "./header/map.h"

// lx from 375 ly from 0
// rx to  1024 ry to 768
// middle x 324.5 middle y 384

bool drawMap() {
	// 米单位像素
    const float meter = 4;
	// 东操大背景
	const int bg = MOSS_GREEN;
	// 操场背景
	const int bgPlayground = BLACK;
	// 划线颜色
	const int fgLine = WHITE;
//    const int xx = 31.84 * 4 * 2;
//    const int yy = 100 * 4 + 31.84 * 4 * 2;
//    Pen mapPixel[xx][2] = {0};
	// 画笔辅助结构体
    Pen mPen = {699.5, 384};
	// 刷东操大背景
    SVGA_Bar(375, 0, 1024, 768, bg);
    // 背景色
    SVGA_Bar(699.5 - 12 * meter - 31.84 * meter, 384 - 77 * meter, 699.5 + 12 * meter + 31.84 * meter, 384 + 77 * meter, bgPlayground);
    SVGA_Bar(699.5 - 31.84 * meter, 384 - 90 * meter, 699.5 + 31.84 * meter, 384 + 90 * meter, bgPlayground);
    // 上半圆
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 2 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 4 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 6 * meter, fgLine);
//    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 8 * meter, fgLine);
    // 下半圆
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 2 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 4 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 6 * meter, fgLine);
//    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 8 * meter, fgLine);
    // 覆盖下半圆和上半圆
    SVGA_Bar(699.5 - 39.84 * meter, 384 - 50 * meter, 699.5 + 39.84 * meter, 384 + 50 * meter, bgPlayground);
    SVGA_Cricle(mPen.x, mPen.y, 5 * meter, fgLine);
    // 向左向右的球场中线
//    SVGA_Line(699.5, 384, 699.5 + 31.84 * meter, 384, fgLine);
    SVGA_Line(mPen.x, mPen.y, mPen.x - 31.84 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x + 31.84 * meter, mPen.y, fgLine);
    mPen.x -= 31.84 * meter;
	// 画笔走到球场左上角
    SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y - 50 * meter, fgLine);
    mPen.y -= 50 * meter;
	// 画左侧的跑道
	SVGA_Line(mPen.x, mPen.y, mPen.x - 6 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 2 * meter, mPen.y, mPen.x - 2 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 4 * meter, mPen.y, mPen.x - 4 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 6 * meter, mPen.y, mPen.x - 6 * meter, mPen.y + 100 * meter, fgLine);
	// 画笔走向球场右上角
    SVGA_Line(mPen.x, mPen.y, mPen.x + 31.84 * 2 * meter, mPen.y, fgLine);
    mPen.x += 31.84 * 2 * meter;
	SVGA_Line(mPen.x, mPen.y, mPen.x + 6 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 2 * meter, mPen.y, mPen.x + 2 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 4 * meter, mPen.y, mPen.x + 4 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 6 * meter, mPen.y, mPen.x + 6 * meter, mPen.y + 100 * meter, fgLine);
	// 画笔走向球场右下角
	mPen.y += 100 * meter;
	// 画球场底线
	SVGA_Line(mPen.x + 6 * meter, mPen.y, mPen.x - 31.84 * 2 * meter - 6 * meter, mPen.y, fgLine);
}