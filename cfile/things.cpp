//
// Created by patrick on 10/25/18.
//

#include "./header/things.h"
#include "./header/headUtil.h"
#include "./header/ioUtil.h"

/**
 * �ɻ����������溯��
 *
 * @param mouse ���
 * @param people �û�
 * @return ����State,���û�������·�ѡ����
 */
State thingsPage(MOUSE *mouse, PEOPLE *people) {
    MsgP msgP = (MsgP) malloc(3 * sizeof(Msg));
    Things state = RECOMMEND;
    mouse_reset(mouse);//�������
    while (1) {
        //��λ���Ƽ�����ʱ
        if (state == RECOMMEND) {
            recommendDraw(mouse, people, msgP);
            //��ȡ���λ��
            mouse_position(mouse);
            mouse_reset(mouse);
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ���ѵ��
                    if (mouse->pos_x > 10.5 * SIZE + 16 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 21 * SIZE + 32 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = TRAIN;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * SIZE + 32 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 31.5 * SIZE + 48 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = HELP;
                        break;
                    }
                    // �Ƿ����������
                    if (mouse->pos_x > 0 && mouse->pos_x < 22 * SIZE && mouse->pos_y > 26 * SIZE && mouse->pos_y < 49 * SIZE) {

                    }
                    // �Ƿ����˶��ɻ�
                    if (mouse->pos_x > 22 && mouse->pos_x < 44 * SIZE && mouse->pos_y > 26 * SIZE && mouse->pos_y < 49 * SIZE) {

                    }
                    // �Ƿ���װ������
                    if (mouse->pos_x > 44 && mouse->pos_x < 66 * SIZE && mouse->pos_y > 26 * SIZE && mouse->pos_y < 49 * SIZE) {

                    }
                    // �Ƿ�����һ����ǩ
                    if (mouse->pos_x > 0 && mouse->pos_x < 68 * SIZE && mouse->pos_y > 49 * SIZE && mouse->pos_y < 78 * SIZE) {
                        MsgP msgPToken = msgP + 0;
                        Jump jump = showMsg(msgPToken, mouse);
                        while (jump != NONE) {
                            if (jump == NEXT) {
                                jump = showMsg(msgPToken = msgPToken->next, mouse);
                            }
                            if (jump == LAST) {
                                jump = showMsg(msgPToken = msgPToken->last, mouse);
                            }
                        }
                    }
                    // �Ƿ����ڶ�����ǩ
                    if (mouse->pos_x > 0 && mouse->pos_x < 68 * SIZE && mouse->pos_y > 78 * SIZE && mouse->pos_y < 105 * SIZE) {
                        MsgP msgPToken = msgP + 1;
                        Jump jump = showMsg(msgPToken, mouse);
                        while (jump != NONE) {
                            if (jump == NEXT) {
                                jump = showMsg(msgPToken = msgPToken->next, mouse);
                            }
                            if (jump == LAST) {
                                jump = showMsg(msgPToken = msgPToken->last, mouse);
                            }
                        }
                    }
                    // �Ƿ�����������ǩ
                    if (mouse->pos_x > 0 && mouse->pos_x < 68 * SIZE && mouse->pos_y > 105 * SIZE && mouse->pos_y < 132 * SIZE) {
                        MsgP msgPToken = msgP + 2;
                        Jump jump = showMsg(msgPToken, mouse);
                        while (jump != NONE) {
                            if (jump == NEXT) {
                                jump = showMsg(msgPToken = msgPToken->next, mouse);
                            }
                            if (jump == LAST) {
                                jump = showMsg(msgPToken = msgPToken->last, mouse);
                            }
                        }
                    }
                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return CIRCLE;
                        }
                        //���������
                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return FIND;
                        }
                        //������˶�
                        if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return SPORTPAGE;
                        }
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * SIZE) {
                            freeHeapMalloc(msgP);
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
        //��λ��ѵ������ʱ
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
                    if (mouse->pos_y > 18 * SIZE && mouse->pos_x < 10.5 * SIZE + 16 && mouse->pos_y < 26 * SIZE) {
                        state = RECOMMEND;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * SIZE + 32 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 31.5 * SIZE + 48 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = HELP;
                        break;
                    }
                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return CIRCLE;
                        }
                        //���������

                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return FIND;
                        }
                        //������˶�
                        if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return SPORTPAGE;
                        }
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return MINE;
                        }
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
                    if (mouse->pos_y > 18 * SIZE && mouse->pos_x < 10.5 * SIZE + 16 && mouse->pos_y < 26 * SIZE) {
                        state = RECOMMEND;
                        break;
                    }
                    //�����ѵ��ʱ
                    if (mouse->pos_x > 10.5 * SIZE + 16 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 21 * SIZE + 32 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = TRAIN;
                        break;
                    }
                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * SIZE) {
                            return CIRCLE;
                        }
                        //���������
                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE) {
                            return FIND;
                        }
                        //������˶�
                        if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return SPORTPAGE;
                        }
                        //������ҵ�
                        if (mouse->pos_x > 53.5 * SIZE) {
                            freeHeapMalloc(msgP);
                            return MINE;
                        }
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

void recommendDraw(MOUSE *mouse, PEOPLE *people, MsgP msgP) {
    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 32, 26 * SIZE - 1, GREEN);
    // ��3��ѡ��
    dis_16hz(5 * SIZE, 21 * SIZE, "�Ƽ�", GREEN);
    dis_16hz(16 * SIZE, 21 * SIZE, "ѵ��", LIGHT_GRAY);
    dis_16hz(27 * SIZE, 21 * SIZE, "����", LIGHT_GRAY);

    drawRecommendDetail(msgP);
}

/**
 * ѵ������Ļ���
 * 
 * @param mouse ���
 * @param people ��
 */

void trainDraw(MOUSE *mouse, PEOPLE *people) {
    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(16 * SIZE, 26 * SIZE, 16 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(16 * SIZE, 26 * SIZE - 1, 16 * SIZE + 32, 26 * SIZE - 1, GREEN);
    // ��3��ѡ��
    dis_16hz(5 * SIZE, 21 * SIZE, "�Ƽ�", LIGHT_GRAY);
    dis_16hz(16 * SIZE, 21 * SIZE, "ѵ��", GREEN);
    dis_16hz(27 * SIZE, 21 * SIZE, "����", LIGHT_GRAY);
}

/**
 * �������ܵĻ���
 * 
 * @param mouse 
 * @param people 
 */

void helpDraw(MOUSE *mouse, PEOPLE *people) {
    thingsDraw(mouse, people);
    // ����tab�·�������
    SVGA_Line(27 * SIZE, 26 * SIZE, 27 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(27 * SIZE, 26 * SIZE - 1, 27 * SIZE + 32, 26 * SIZE - 1, GREEN);
    //��3��ѡ��
    dis_16hz(5 * SIZE, 21 * SIZE, "�Ƽ�", LIGHT_GRAY);
    dis_16hz(16 * SIZE, 21 * SIZE, "ѵ��", LIGHT_GRAY);
    dis_16hz(27 * SIZE, 21 * SIZE, "����", GREEN);
}

/**
 * �ɻ�����Ļ���
 * 
 * @param mouse 
 * @param people 
 */
void thingsDraw(MOUSE *mouse, PEOPLE *people) {
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
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "�˶�", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "�ɻ�", GREEN);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "�ҵ�", LIGHT_GRAY);
}

/**
 * ���Ƽ�����ĸ���ϸ��
 */
void drawRecommendDetail(MsgP msgP) {
    char *path;
    path = (char *) malloc(50 * sizeof(char));
    // �������
    SVGA_Ball(11 * SIZE, 35 * SIZE, 5 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, 35 * SIZE, 2.5 * SIZE, WHITE);
    SVGA_Ball(11 * SIZE, 35 * SIZE, 0.5 * SIZE, ORANGE);
    SVGA_Ball((11 - 1.4) * SIZE, 35 * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball((11 + 1.4) * SIZE, 35 * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, (35 - 1.4) * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, (35 + 1.4) * SIZE, 0.8 * SIZE, ORANGE);
    dis_16hz(4 * SIZE, 42 * SIZE, "�������", BLACK);

    // �˶��ɻ�
    SVGA_Ball(33 * SIZE, 35 * SIZE, 5 * SIZE, HORIZON_BLUE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 3.5 * SIZE, WHITE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 2.5 * SIZE, HORIZON_BLUE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 1 * SIZE, WHITE);
    dis_16hz(26 * SIZE, 42 * SIZE, "�˶��ɻ�", BLACK);

    // װ������
    SVGA_Ball(55 * SIZE, 35 * SIZE, 5 * SIZE, AQUA_BLUE);
    SVGA_Ball(53 * SIZE, 33 * SIZE, 1 * SIZE, WHITE);
    SVGA_Bar((55 + 0.8) * SIZE, (35 - 0.8) * SIZE, 61 * SIZE, 37.5 * SIZE, WHITE);
    dis_16hz(48 * SIZE, 42 * SIZE, "װ������", BLACK);

    // ����Ȧ����Ļ�ɫ����
    SVGA_Bar(1 * SIZE, 49 * SIZE, 67 * SIZE, 51 * SIZE, LIGHT_GRAY);

    // �·��ı�ǩ�ֽ���
    SVGA_Line(1 * SIZE, 78 * SIZE, 67 * SIZE, 78 * SIZE, LIGHT_GRAY);
    SVGA_Line(1 * SIZE, 105 * SIZE, 67 * SIZE, 105 * SIZE, LIGHT_GRAY);

    int color1[] = {MEDIUM_PURPLE, BABY_PINK};
//    // ת��ָ��ָ��Ϊָ��
//    MsgP msgP = *msgPP;
//    // ��ȡ�ѿռ��ַ
//    msgP = (MsgP) malloc(3 * sizeof(Msg));

    MsgP msgP1 = msgP + 0;
    createMsgPath("1", path);
    inputMsg(path, msgP1);
    msgP1->last = NULL;

    int color2[] = {SKY_BLUE, GAINSBORO};
    MsgP msgP2 = msgP + 1;
    createMsgPath("2", path);
    inputMsg(path, msgP2);
    msgP2->last = msgP1;
    msgP1->next = msgP2;

    int color3[] = {BABY_PINK, SEASHELL};
    MsgP msgP3 = msgP + 2;
    createMsgPath("3", path);
    inputMsg(path, msgP3);
    msgP3->last = msgP2;
    msgP2->next = msgP3;
    // �γ�ѭ������
    msgP1->last = msgP3;
    msgP3->next = msgP1;

    // ��ǩ1
    showRecommendMsg(6 * SIZE, 56 * SIZE, color1, msgP1);

    // ��ǩ2
    showRecommendMsg(6 * SIZE, 83 * SIZE, color2, msgP2);

    // ��ǩ3
    showRecommendMsg(6 * SIZE, 110 * SIZE, color3, msgP3);
}

void showRecommendMsg(float x, float y, int *color, MsgP msgP) {
    SVGA_Ball(x, y, 2 * SIZE, color[0]);
    dis_16hz(x + 4 * SIZE, y - 1 * SIZE, msgP->author, BLACK);
    SVGA_Bar(x - 3 * SIZE, y + 4 * SIZE, x + 13 * SIZE, y + 20 * SIZE, color[1]);
    dis_24hz(x + 16 * SIZE, y + 4 * SIZE, msgP->title, BLACK);
    SVGA_Bar(x + 16 * SIZE, y + 16 * SIZE, x + 31 * SIZE, y + 20 * SIZE, LIGHT_CYAN);
    dis_16hz(x + 16 * SIZE + 4, y + 16 * SIZE + 2, msgP->type, GREEN);
    dis_16hz(x + 45 * SIZE, y + 16 * SIZE + 2, "�Ķ�", DARK_GRAY);
    dis_16zf(x + 53 * SIZE, y + 16 * SIZE + 2, msgP->readNum, DARK_GRAY);
}

/**
 * ��ѵ������ĸ�����ϸ��
 */
void drawTrainDetail() {

}

/**
 * �������Խ���ĸ���ϸ��
 */
void drawHelpDetail() {

}

Jump showMsg(MsgP msgP, MOUSE *mouse) {
    // �������
    mouse_recover(mouse);

    showMsgDetail(msgP);
    // �������
    mouse_reset(mouse);
    while(1){
        // ��ȡ���λ��
        mouse_position(mouse);
        // �������
        drawmouse(mouse);
        if (mouse->button == 1) {
            // �����ϲ�
            if (mouse->pos_x > 1024 - 8 * SIZE && mouse->pos_x < 1024 && mouse->pos_y > 0 && mouse->pos_y < 8 * SIZE) {
                // �������
                mouse_recover(mouse);
                SVGA_Bar(68 * SIZE + 2, 0, 1024, 768, WHITE);
                // �������
                mouse_reset(mouse);
                return NONE;
            }
            // ��һƪ
            if (mouse->pos_x > 86 * SIZE && mouse->pos_x < 108 * SIZE && mouse->pos_y > 768 - 16 * SIZE && mouse->pos_y < 768 - 8 * SIZE) {
                SVGA_Bar(68 * SIZE + 2, 0, 1024, 768, WHITE);
                return LAST;
            }
            // ��һƪ
            if (mouse->pos_x > 1024 - 40 * SIZE && mouse->pos_x < 1024 - 18 * SIZE && mouse->pos_y > 768 - 16 * SIZE && mouse->pos_y < 768 - 8 * SIZE) {
                SVGA_Bar(68 * SIZE + 2, 0, 1024, 768, WHITE);
                return NEXT;
            }
        }
    }
    return NONE;
}

void showMsgDetail(MsgP msgP) {
    SVGA_Bar(68 * SIZE + 2, 0, 1024, 768, WHITE);
    SVGA_Bar(1024 - 8 * SIZE, 0, 1024, 8 * SIZE, DARK_GRAY);
    SVGA_Bar(1024 - 8 * SIZE + 2, 2, 1024 - 2, 8 * SIZE - 2, WHITE);
    SVGA_Line(1024 - 8 * SIZE, 0, 1024, 8 * SIZE, DARK_GRAY);
    SVGA_Line(1024, 0, 1024 - 8 * SIZE, 8 * SIZE, DARK_GRAY);
    dis_24hz(72 * SIZE, 16 * SIZE, msgP->title, BLACK);
    dis_16hz(74 * SIZE, 24 * SIZE, msgP->author, BLACK);

    for (int i = 0; msgP->text[i][0] != '\0'; ++i) {
        dis_16hz(74 * SIZE, 32 * SIZE + i * 6 * SIZE, msgP->text[i], BLACK);
    }

    // ǳ��ɫ����
    SVGA_Bar(68 * SIZE + 18 * SIZE, 768 - 16 * SIZE, 108 * SIZE, 768 - 8 * SIZE, LIGHT_CYAN);
    SVGA_Bar(1024 - 40 * SIZE, 768 - 16 * SIZE, 1024 - 18 * SIZE, 768 - 8 * SIZE, LIGHT_CYAN);

    // �����һƪ����
    SVGA_Line(97 * SIZE, 768 - 14 * SIZE, 100 * SIZE, 768 - 10 * SIZE, GREEN);
    SVGA_Line(97 * SIZE, 768 - 14 * SIZE, 94 * SIZE, 768 - 10 * SIZE, GREEN);
    SVGA_Line(100 * SIZE, 768 - 10 * SIZE, 94 * SIZE, 768 - 10 * SIZE, GREEN);

    // �ұ���һƪ����
    SVGA_Line(1024 - 29 * SIZE, 768 - 10 * SIZE, 1024 - 32 * SIZE, 768 - 14 * SIZE, GREEN);
    SVGA_Line(1024 - 29 * SIZE, 768 - 10 * SIZE, 1024 - 26 * SIZE, 768 - 14 * SIZE, GREEN);
    SVGA_Line(1024 - 32 * SIZE, 768 - 14 * SIZE, 1024 - 26 * SIZE, 768 - 14 * SIZE, GREEN);

}

void freeHeapMalloc(MsgP msgP) {
    free(msgP);
    free(msgP + 1);
    free(msgP + 2);
}