//
// Created by patrick on 10/19/18.
//

#include "./header/map.h"
#include "./header/headUtil.h"

// lx from 375 ly from 0
// rx to  1024 ry to 768
// middle x 324.5 middle y 384

bool drawMap() {
	// �׵�λ����
    const float meter = 4;
	// ���ٴ󱳾�
	const int bg = LIGHT_GRAY;
    // �ٳ�����
	const int bgPlayground = PINK;
	// �򳡱���
//	const int bgSoccerGround = COBALT_GREEN;
//    const int bgSoccerGround = DARK_SEA_GREEN;
    const int bgSoccerGround = PALE_GREEN;
	// ������ɫ
	const int fgLine = WHITE;
//    const int xx = 31.84 * 4 * 2;
//    const int yy = 100 * 4 + 31.84 * 4 * 2;
//    Pen mapPixel[xx][2] = {0};
	// ���ʸ����ṹ��
    Pen mPen = {699.5, 384};
	// ˢ���ٴ󱳾�
    SVGA_Bar(375, 0, 1024, 768, bg);
    // ����ɫ
    SVGA_Bar(699.5 - 12 * meter - 31.84 * meter, 384 - 77 * meter, 699.5 + 12 * meter + 31.84 * meter, 384 + 77 * meter, bgPlayground);
    SVGA_Bar(699.5 - 31.84 * meter, 384 - 89 * meter, 699.5 + 31.84 * meter, 384 + 89 * meter, bgPlayground);
    // �ĸ����ϵĻ�
    SVGA_Ball(699.5 - 31.84 * meter, 384 - 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 + 31.84 * meter, 384 - 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 - 31.84 * meter, 384 + 77 * meter, 12 * meter, bgPlayground);
    SVGA_Ball(699.5 + 31.84 * meter, 384 + 77 * meter, 12 * meter, bgPlayground);
    // �ϰ�Բ
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 2 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 4 * meter, fgLine);
    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 6 * meter, fgLine);
//    SVGA_Cricle(699.5, 384 - 50 * meter, 31.84 * meter + 8 * meter, fgLine);
    // �°�Բ
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 2 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 4 * meter, fgLine);
    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 6 * meter, fgLine);
//    SVGA_Cricle(699.5, 384 + 50 * meter, 31.84 * meter + 8 * meter, fgLine);
    // �����°�Բ���ϰ�Բ
    SVGA_Bar(699.5 - 39.84 * meter, 384 - 50 * meter, 699.5 + 39.84 * meter, 384 + 50 * meter, bgPlayground);
    // �򳡱���
    SVGA_Bar(699.5 - 31.84 * meter, 384 - 50 * meter, 699.5 + 31.84 * meter, 384 + 50 * meter, bgSoccerGround);
    // ����Բ
    SVGA_Cricle(mPen.x, mPen.y, 5 * meter, fgLine);
    // �Ϸ�����
    SVGA_Cricle(mPen.x, mPen.y - 43 * meter, 6 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter, mPen.y - 50 * meter, mPen.x + 12 * meter, mPen.y - 40 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter + 1, mPen.y - 50 * meter + 1, mPen.x + 12 * meter - 1, mPen.y - 40 * meter - 1, bgSoccerGround);
    SVGA_Bar(mPen.x - 6 * meter, mPen.y - 50 * meter, mPen.x + 6 * meter, mPen.y - 45 * meter, fgLine);
    SVGA_Bar(mPen.x - 6 * meter + 1, mPen.y - 50 * meter + 1, mPen.x + 6 * meter - 1, mPen.y - 45 * meter - 1, bgSoccerGround);
    // �·�����
    SVGA_Cricle(mPen.x, mPen.y + 43 * meter, 6 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter, mPen.y + 40 * meter, mPen.x + 12 * meter, mPen.y + 50 * meter, fgLine);
    SVGA_Bar(mPen.x - 12 * meter + 1, mPen.y + 40 * meter + 1, mPen.x + 12 * meter - 1, mPen.y + 50 * meter - 1, bgSoccerGround);
    SVGA_Bar(mPen.x - 6 * meter, mPen.y + 45 * meter, mPen.x + 6 * meter, mPen.y + 50 * meter, fgLine);
    SVGA_Bar(mPen.x - 6 * meter + 1, mPen.y + 45 * meter + 1, mPen.x + 6 * meter - 1, mPen.y + 50 * meter - 1, bgSoccerGround);
    // �������ҵ�������
//    SVGA_Line(699.5, 384, 699.5 + 31.84 * meter, 384, fgLine);
    SVGA_Line(mPen.x, mPen.y, mPen.x - 31.84 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x + 31.84 * meter, mPen.y, fgLine);
    mPen.x -= 31.84 * meter;
	// �����ߵ������Ͻ�
    SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y - 50 * meter, fgLine);
    mPen.y -= 50 * meter;
	// �������ܵ�
	SVGA_Line(mPen.x, mPen.y, mPen.x - 6 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 2 * meter, mPen.y, mPen.x - 2 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 4 * meter, mPen.y, mPen.x - 4 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x - 6 * meter, mPen.y, mPen.x - 6 * meter, mPen.y + 100 * meter, fgLine);
	// �������������Ͻ�
    SVGA_Line(mPen.x, mPen.y, mPen.x + 31.84 * 2 * meter, mPen.y, fgLine);
    mPen.x += 31.84 * 2 * meter;
	SVGA_Line(mPen.x, mPen.y, mPen.x + 6 * meter, mPen.y, fgLine);
	SVGA_Line(mPen.x, mPen.y, mPen.x, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 2 * meter, mPen.y, mPen.x + 2 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 4 * meter, mPen.y, mPen.x + 4 * meter, mPen.y + 100 * meter, fgLine);
	SVGA_Line(mPen.x + 6 * meter, mPen.y, mPen.x + 6 * meter, mPen.y + 100 * meter, fgLine);
	// �������������½�
	mPen.y += 100 * meter;
	// ���򳡵���
	SVGA_Line(mPen.x + 6 * meter, mPen.y, mPen.x - 31.84 * 2 * meter - 6 * meter, mPen.y, fgLine);

}

/**
 * ������ͼ����״̬��
 *
 * @param endurance ����ֵ
 * @param velocity ʵʱ�ٶ�
 * @param length �˶�����
 * @param totalTime �˶�ʱ��
 */

void drawStatus(char * endurance, char * velocity, char * length, char * totalTimeMin, char * totalTimeSecond) {
    float x = 375;
    float y = 0;
    dis_24hz(x += 5, y += 8,"�˶���ʼʱ��", DARK_GRAY);
    drawClock(x, y += 26, WHITE, LIGHT_GRAY);

    dis_24hz(x, y +=28,"�˶�����ʱ��", DARK_GRAY);
    drawClock(x, y += 26, WHITE, LIGHT_GRAY);

    dis_24hz(x, y += 28,"����ֵ", DARK_GRAY);
    dis_24zf(x, y += 28, endurance, WHITE);

    dis_24hz(x, y += 28,"ʵʱ�ٶ�", DARK_GRAY);
    dis_24zf(x, y += 28, velocity, WHITE);
    dis_16hz(x + 72 + 4, y + 4, "��ÿ��", WHITE);

    dis_24hz(x, y += 28,"�˶�����", DARK_GRAY);
    dis_24zf(x, y += 28, length, WHITE);
    dis_16hz(440+48/*x + 48 + 4*/, y + 4, "ǧ��", WHITE);

    dis_24hz(x, y += 28,"���˶�ʱ��", DARK_GRAY);
    dis_24zf(x, y += 28, totalTimeMin, WHITE);
    dis_16hz(x + 54 + 4, y + 4, "����", WHITE);
    dis_24zf(x, y += 28, totalTimeSecond, WHITE);
    dis_16hz(x + 72 + 4, y + 4, "��", WHITE);
}

/**
 *
 * �������ֵ
 *
 */

void cleanEndurance() {
    SVGA_Bar(380, 144, 380 + 3 * 24, 144 + 24, LIGHT_GRAY);
}

/**
 *
 * ����ٶ�
 *
 */
void cleanVelocity() {
    SVGA_Bar(380, 200, 380 + 3 * 24, 200 + 24, LIGHT_GRAY);
}

/**
 *
 * ����˶�����
 *
 */

void cleanLength() {
    SVGA_Bar(380, 256, 440+48, 256 + 24, LIGHT_GRAY);
}

/**
 *
 * ����˶�ʱ��ķ���
 *
 */

void cleanTotalTimeMin() {
    SVGA_Bar(380, 312, 380 + 2 * 24, 312 + 24, LIGHT_GRAY);
}

/**
 *
 * ����˶�ʱ�������
 *
 */

void cleanTotalTimeSecond() {
    SVGA_Bar(380, 340, 380 + 2 * 24, 340 + 24, LIGHT_GRAY);
}