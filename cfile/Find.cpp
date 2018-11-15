//
// Created by patrick on 11/15/18.
//


#include "./header/Find.h"
#include "./header/headUtil.h"

State findPage(MOUSE *mouse, PEOPLE *people) {
    mouse_reset(mouse);
    SVGA_Bar(0, 0, 68 * SIZE, 1024, WHITE);
    findDraw(mouse, people);
    while (1) {
        //��ȡ���λ��
        mouse_position(mouse);
        mouse_reset(mouse);
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
            headDisplay(2, 5, BLACK, WHITE);
        }
    }
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
