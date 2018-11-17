//
// Created by patrick on 11/15/18.
//


#include "./header/Circle.h"
#include "./header/headUtil.h"

State circlePage(MOUSE *mouse, PEOPLE *people) {
    //��ȡ���λ��
//    mouse_position(mouse);
    // �̶�˳��,��drwa,��reset
    circleDraw(mouse, people);
    mouse_reset(mouse);
    while (true) {

        //��������
        if (mouse->button == 1) {

            if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                //������˶�Ȧ
                if (mouse->pos_x > 14.5 * SIZE && mouse->pos_x < 27.5 * SIZE) {

                    return FIND;
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
        headDisplay(2, 5, BLACK, WHITE);
    }
}

void circleDraw(MOUSE *mouse, PEOPLE *people) {
    // ѭ������
    int i;
    // �����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * SIZE, 140 * SIZE, WHITE);
    // ����tab�·��Ļ���
    SVGA_Line(0, 26 * SIZE + 1, 68 * SIZE, 26 * SIZE + 1, DARK_GRAY);
    // ���ѡ���Ϸ��Ļ���
    SVGA_Line(0, 132 * SIZE, 68 * SIZE, 132 * SIZE, DARK_GRAY);

    // ����tab�·�������
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 96, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 96, 26 * SIZE - 1, GREEN);
    // ��3��ѡ��
    dis_16hz(5 * SIZE, 21 * SIZE, "�μӵĿγ�", GREEN);

    // ��������ʾ
    SVGA_Bar(2 * SIZE, 5 * SIZE, 60 * SIZE, 15 * SIZE, LIGHT_GRAY);
    SVGA_Cricle(6 * SIZE, 10 * SIZE, 2 * SIZE, WHITE);
    SVGA_Line(6 * SIZE + 2 * SIZE * sin(45), 10 * SIZE + 2 * SIZE * sin(45),
              6 * SIZE + 3 * SIZE * sin(45), 10 * SIZE + 3 * SIZE * sin(45), WHITE);
    // �ײ�5����ť
    dis_16hz(8 * SIZE - 8 * 3, 136 * SIZE - 8, "�˶�Ȧ", GREEN);
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "�˶�", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "�ҵ�", LIGHT_GRAY);

    showClassMsg(0, 26 * SIZE, false, NULL);
}

void showClassMsg(float x, float y, bool hasAchieved, MsgP msgP) {
    int color = hasAchieved ? GREEN : DARK_GRAY;
//    SVGA_Ball(x, y, 2 * SIZE, color[0]);
    SVGA_Bar(x + 4 * SIZE, y + 4 * SIZE, 64 * SIZE, y + 4 * SIZE + 27 * SIZE, color);
    dis_24hz(x + 8 * SIZE, y + 6 * SIZE, "ӭ����", WHITE);
    dis_16hz(x + 8 * SIZE, y + 12 * SIZE, "�����", WHITE);
    dis_16zf(x + 20 * SIZE, y + 12 * SIZE, "21", WHITE);
    dis_16hz(x + 28 * SIZE, y + 12 * SIZE, "����", WHITE);
    dis_16hz(x + 8 * SIZE, y + 25 * SIZE, "�μ�����", WHITE);
    dis_16zf(x + 23 * SIZE, y + 25 * SIZE, "22342342", WHITE);
//    SVGA_Bar(x - 3 * SIZE, y + 4 * SIZE, x + 13 * SIZE, y + 20 * SIZE, color[1]);
//    dis_24hz(x + 16 * SIZE, y + 4 * SIZE, msgP->title, BLACK);
//    SVGA_Bar(x + 16 * SIZE, y + 16 * SIZE, x + 31 * SIZE, y + 20 * SIZE, LIGHT_CYAN);
//    dis_16hz(x + 16 * SIZE + 4, y + 16 * SIZE + 2, msgP->type, GREEN);
//    dis_16hz(x + 45 * SIZE, y + 16 * SIZE + 2, "�Ķ�", DARK_GRAY);
//    dis_16zf(x + 53 * SIZE, y + 16 * SIZE + 2, msgP->readNum, DARK_GRAY);
}

