//
// Created by patrick on 10/19/18.
//

#include "./header/map.h"
#include "./header/headUtil.h"

// lx from 375 ly from 0
// rx to  1024 ry to 768
// middle x 324.5 middle y 384

bool drawMap() {
	// 米单位像素
    const float meter = 4;
	// 东操大背景
	const int bg = LIGHT_GRAY;
    // 操场背景
	const int bgPlayground = PINK;
	// 球场背景
//	const int bgSoccerGround = COBALT_GREEN;
//    const int bgSoccerGround = DARK_SEA_GREEN;
    const int bgSoccerGround = PALE_GREEN;
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
    SVGA_Bar(699.5 - 31.84 * meter, 384 - 89 * meter, 699.5 + 31.84 * meter, 384 + 89 * meter, bgPlayground);
    // 四个角上的弧
    SVGA_Ball(699.5 - 31.84 * meter, 384 - 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 + 31.84 * meter, 384 - 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 - 31.84 * meter, 384 + 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 + 31.84 * meter, 384 + 77 * meter, 12 * meter, bgPlayground);
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
    // 球场背景
    SVGA_Bar(699.5 - 31.84 * meter, 384 - 50 * meter, 699.5 + 31.84 * meter, 384 + 50 * meter, bgSoccerGround);
    // 球场中圆
    SVGA_Cricle(mPen.x, mPen.y, 5 * meter, fgLine);
    // 上方禁区
    SVGA_Cricle(mPen.x, mPen.y - 43 * meter, 6 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter, mPen.y - 50 * meter, mPen.x + 12 * meter, mPen.y - 40 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter + 1, mPen.y - 50 * meter + 1, mPen.x + 12 * meter - 1, mPen.y - 40 * meter - 1, bgSoccerGround);
    SVGA_Bar(mPen.x - 6 * meter, mPen.y - 50 * meter, mPen.x + 6 * meter, mPen.y - 45 * meter, fgLine);
    SVGA_Bar(mPen.x - 6 * meter + 1, mPen.y - 50 * meter + 1, mPen.x + 6 * meter - 1, mPen.y - 45 * meter - 1, bgSoccerGround);
    // 下方禁区
    SVGA_Cricle(mPen.x, mPen.y + 43 * meter, 6 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter, mPen.y + 40 * meter, mPen.x + 12 * meter, mPen.y + 50 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter + 1, mPen.y + 40 * meter + 1, mPen.x + 12 * meter - 1, mPen.y + 50 * meter - 1, bgSoccerGround);
    SVGA_Bar(mPen.x - 6 * meter, mPen.y + 45 * meter, mPen.x + 6 * meter, mPen.y + 50 * meter, fgLine);
    SVGA_Bar(mPen.x - 6 * meter + 1, mPen.y + 45 * meter + 1, mPen.x + 6 * meter - 1, mPen.y + 50 * meter - 1, bgSoccerGround);
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

/**
 * 画出地图左侧的状态栏
 *
 * @param endurance 耐力值
 * @param velocity 实时速度
 * @param length 运动距离
 * @param totalTime 运动时间
 */

void drawStatus(char * endurance, char * velocity, char * length, char * totalTimeMin, char * totalTimeSecond) {
    float x = 375;
    float y = 0;
    dis_24hz(x += 5, y += 8,"运动开始时间", DARK_GRAY);
    drawClock(x, y += 26, WHITE, LIGHT_GRAY);

    dis_24hz(x, y +=28,"运动结束时间", DARK_GRAY);
    drawClock(x, y += 26, WHITE, LIGHT_GRAY);

    dis_24hz(x, y += 28,"耐力值", DARK_GRAY);
    dis_24zf(x, y += 28, endurance, WHITE);

    dis_24hz(x, y += 28,"实时速度", DARK_GRAY);
    dis_24zf(x, y += 28, velocity, WHITE);
    dis_16hz(x + 72 + 4, y + 4, "米每分", WHITE);

    dis_24hz(x, y += 28,"运动距离", DARK_GRAY);
    dis_24zf(x, y += 28, length, WHITE);
    dis_16hz(440+48/*x + 48 + 4*/, y + 4, "千米", WHITE);

    dis_24hz(x, y += 28,"总运动时长", DARK_GRAY);
    dis_24zf(x, y += 28, totalTimeMin, WHITE);
    dis_16hz(x + 54 + 4, y + 4, "分钟", WHITE);
    dis_24zf(x, y += 28, totalTimeSecond, WHITE);
    dis_16hz(x + 72 + 4, y + 4, "秒", WHITE);
}

/**
 *
 * 清除耐力值
 *
 */

void cleanEndurance() {
    SVGA_Bar(380, 144, 380 + 3 * 24, 144 + 24, LIGHT_GRAY);
}

/**
 *
 * 清除速度
 *
 */
void cleanVelocity() {
    SVGA_Bar(380, 200, 380 + 3 * 24, 200 + 24, LIGHT_GRAY);
}

/**
 *
 * 清除运动距离
 *
 */

void cleanLength() {
    SVGA_Bar(380, 256, 440+48, 256 + 24, LIGHT_GRAY);
}

/**
 *
 * 清除运动时间的分钟
 *
 */

void cleanTotalTimeMin() {
    SVGA_Bar(380, 312, 380 + 2 * 24, 312 + 24, LIGHT_GRAY);
}

/**
 *
 * 清除运动时间的秒钟
 *
 */

void cleanTotalTimeSecond() {
    SVGA_Bar(380, 340, 380 + 2 * 24, 340 + 24, LIGHT_GRAY);
}