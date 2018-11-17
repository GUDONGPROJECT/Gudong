//
// Created by patrick on 11/15/18.
//


#include "./header/Find.h"
#include "./header/headUtil.h"

State findPage(MOUSE *mouse, PEOPLE *people) {
    findDraw(mouse, people);
    mouse_reset(mouse);
    int i = 0;
    while (1) {
        //��������
        if (mouse->button == 1) {

            if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                //������˶�Ȧ
                if (mouse->pos_x < 14.5 * SIZE) {

                    return CIRCLE;
                }
                //���������
                if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE) {

                    return THINGS;
                }
                //������˶�
                if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {

                    return SPORTPAGE;
                }
                //������ҵ�
                if (mouse->pos_x > 53.5 * SIZE) {

                    return MINE;
                }
            }
        }
        mouse_position(mouse);
        drawmouse(mouse);
        // չʾ����ʱ��
    }
}

void drawSignal(int i) {
    const float Y = 768 / 2;
    const float X = 34 * SIZE;
    SVGA_Ball(X, Y, 12 * SIZE, LIGHT_GRAY);
//    void Arc(int x,int y,float stangle,float endangle,int radius,int color)
    Arc(X, Y, 60, -60, 20 * SIZE, LIGHT_GRAY);
}

void findDraw(MOUSE *mouse, PEOPLE *people) {
    // ѭ������
    int i;
    // �����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * SIZE, 140 * SIZE, WHITE);
    // ����tab�·��Ļ���
    SVGA_Line(0, 26 * SIZE + 1, 68 * SIZE, 26 * SIZE + 1, DARK_GRAY);
    // ���ѡ���Ϸ��Ļ���
    SVGA_Line(0, 132 * SIZE, 68 * SIZE, 132 * SIZE, DARK_GRAY);

    // ��3��ѡ��
    dis_16hz(5 * SIZE, 21 * SIZE, "�������û�", GREEN);
    // ����tab�·�������
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 96, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 96, 26 * SIZE - 1, GREEN);

    // ��������ʾ
    SVGA_Bar(2 * SIZE, 5 * SIZE, 60 * SIZE, 15 * SIZE, LIGHT_GRAY);
    SVGA_Cricle(6 * SIZE, 10 * SIZE, 2 * SIZE, WHITE);
    SVGA_Line(6 * SIZE + 2 * SIZE * sin(45), 10 * SIZE + 2 * SIZE * sin(45),
              6 * SIZE + 3 * SIZE * sin(45), 10 * SIZE + 3 * SIZE * sin(45), WHITE);
    // �ײ�5����ť
    dis_16hz(8 * SIZE - 8 * 3, 136 * SIZE - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "����", GREEN);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "�˶�", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "�ҵ�", LIGHT_GRAY);
}
