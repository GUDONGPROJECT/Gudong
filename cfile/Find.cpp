//
// Created by patrick on 11/15/18.
//


#include "./header/Find.h"
#include "./header/headUtil.h"
#include "./header/IoUtil.h"

State findPage(MOUSE *mouse, PEOPLE *people) {
    int i = 0;
    UsrP usrP = (UsrP) malloc(sizeof(Usr));

    getAllUsr(usrP);

    findDraw(mouse, people);

//    showClassMsg(0, (i + 26) * SIZE, usrP);
//    usrP = usrP->next;
//
//    i++;
//    showClassMsg(0, (i + 26) * SIZE, usrP);


    for (i = 0; usrP->name[0] != 'n' && i < 6; i++) {
        showClassMsg(0, (i * 17 + 26) * SIZE, usrP);
        usrP = usrP->next;
    }

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

void drawSignal(int i) {
    const float Y = 768 / 2;
    const float X = 34 * SIZE;
    SVGA_Ball(X, Y, 12 * SIZE, LIGHT_GRAY);
//    void Arc(int x,int y,float stangle,float endangle,int radius,int color)
    Arc(X, Y, 60, -60, 20 * SIZE, LIGHT_GRAY);
}

void getAllUsr(UsrP usrP) {
    char * path = "txt\\USERNAME.txt";
    inputUsr( path, usrP);
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

void showClassMsg(float x, float y, UsrP usrP) {

    SVGA_Bar(x + 4 * SIZE, y + 4 * SIZE, 64 * SIZE, y + 4 * SIZE + 13.5 * SIZE, DARK_GRAY);
    dis_24hz(x + 8 * SIZE, y + 6 * SIZE, "�û���", WHITE);
    dis_16zf(x + 18 * SIZE, y + 12 * SIZE, usrP->name, WHITE);

}
