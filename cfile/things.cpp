//
// Created by patrick on 10/25/18.
//

#include "./header/things.h"
#include "./header/headUtil.h"

/**
 * �ɻ����������溯��
 *
 * @param mouse ���
 * @param people �û�
 * @return ����State,���û�������·�ѡ����
 */
State thingsPage(MOUSE *mouse,PEOPLE *people) {
    Things state = RECOMMEND;
    float size = 5.5;
    mouse_reset(mouse);//�������
    while (1) {
        //��λ���Ƽ�����ʱ
        if (state == RECOMMEND) {
            recommendDraw(mouse, people);
            //��ȡ���λ��
            mouse_position(mouse);
            mouse_reset(mouse);
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ���ѵ��
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = TRAIN;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = HELP;
                        break;
                    }


//                    //�Ƿ���GO
//                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
//                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
//                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
//                    //��ת����ʼ�ܲ��Ľ���


                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //���������
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //������ɻ�
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
                // չʾ����ʱ��
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
        //��λ�ڽ��߽���ʱ
        if (state == TRAIN) {
            trainDraw(mouse, people);
            //��ȡ���λ��
            mouse_position(mouse);
            //�������
            mouse_reset(mouse);
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ����Ƽ�
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RECOMMEND;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = HELP;
                        break;
                    }


//                    //�Ƿ���GO
//                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
//                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
//                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
//                    //��ת����ʼ���ߵĽ���


                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //���������
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //������ɻ�
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
        //��λ�ڹ��Խ���ʱ
        if (state == HELP) {
            helpDraw(mouse, people);
            //��ȡ���λ��
            mouse_position(mouse);
            //�������
            mouse_reset(mouse);

            while (1) {
                //��������
                if (mouse->button == 1) {
                    //������Ƽ�ʱ
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RECOMMEND;
                        break;
                    }
                    //�����ѵ��ʱ
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = TRAIN;
                        break;
                    }


//                    //�Ƿ���GO��ť
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 11 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 28 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
//                    //���뿪ʼ���н���
//                    //�Ƿ�����������ť
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 40 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 57 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
//                    //���뿪ʼ���н���


                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //���������
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //������ɻ�
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
    }
}

/**
 * �Ƽ�����Ļ���
 *
 * @param mouse
 * @param people
 */

void recommendDraw(MOUSE *mouse, PEOPLE *people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(5*size,26*size,5*size+32,26*size,GREEN);
    SVGA_Line(5*size,26*size-1,5*size+32,26*size-1,GREEN);
    // ��3��ѡ��
    dis_16hz(5 * size, 21 * size, "�Ƽ�", GREEN);
    dis_16hz(16 * size, 21 * size, "ѵ��", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"����", LIGHT_GRAY );
}

void trainDraw(MOUSE *mouse, PEOPLE * people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(16*size,26*size,16*size+32,26*size,GREEN);
    SVGA_Line(16*size,26*size-1,16*size+32,26*size-1,GREEN);
    // ��3��ѡ��
    dis_16hz(5 * size, 21 * size, "�Ƽ�", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "ѵ��", GREEN);
    dis_16hz(27 * size, 21 * size,"����", LIGHT_GRAY );
}

void helpDraw(MOUSE *mouse, PEOPLE * people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(27*size,26*size,27*size+32,26*size,GREEN);
    SVGA_Line(27*size,26*size-1,27*size+32,26*size-1,GREEN);
    //��3��ѡ��
    dis_16hz(5 * size, 21 * size, "�Ƽ�", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "ѵ��", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"����", GREEN);
}

void thingsDraw(MOUSE *mouse,PEOPLE *people){
    float size = 5.5;
    // ѭ������
    int i;

    // �����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    // ����tab�·��Ļ���
    SVGA_Line(0, 26 * size + 1, 68 * size, 26 * size + 1, DARK_GRAY);
    // ���ѡ���Ϸ��Ļ���
    SVGA_Line(0, 130 * size, 68 * size, 130 * size, DARK_GRAY);

    // ��������ʾ
    SVGA_Bar(2* size, 5 * size, 60 * size, 15 * size, LIGHT_GRAY);
    SVGA_Cricle(6 * size, 10 * size, 2 * size, WHITE);
    SVGA_Line(6 * size + 2 * size * sin(45), 10 * size + 2 * size * sin(45),
            6 * size + 3 * size * sin(45), 10 * size + 3 * size * sin(45), WHITE);

//    // �ܲ��ܹ���
//    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
//    dis_24hz(34 * size - 12 * 5, 50 * size, "�˶��ܹ���", BLACK);

//    //GO��ť
//    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
//    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);

    // �ײ�5����ť
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "�˶�", LIGHT_GRAY);
    dis_16hz(47 * size - 16, 135 * size - 8, "�ɻ�", GREEN);
    dis_16hz(60 * size - 16, 135 * size - 8, "�ҵ�", LIGHT_GRAY);

}