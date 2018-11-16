#include "./header/MainUI.h"
State SportMain(MOUSE *mouse,PEOPLE *people) {
    Sport state = RUN;
    float size = 5.5;
    mouse_reset(mouse);//�������
    while (1) {
        //��λ���ܲ�����ʱ
        if (state == RUN) {
            Draw_Sport_Run(people);
            mouse_position(mouse);  //��ȡ���λ��
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //������꽫��������
                mouse_show(mouse);      //�������
            //}
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ�������
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = WALK;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = RIDE;
                        break;
                    }
                    //�Ƿ���GO
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //��ת����ʼ�ܲ��Ľ���
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, RUN);
                                runningMan.Run();
                                break;
                            }
                            Update(people,RUN);
                        }
                    }
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
            }
        }
        //��λ�ڽ��߽���ʱ
        if (state == WALK) {
            Draw_Sport_Walk(people);
            mouse_position(mouse);//��ȡ���λ��
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //������꽫��������
                mouse_show(mouse);      //�������
            //}
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ����ܲ�
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RUN;
                        break;
                    }
                    //�Ƿ�������
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = RIDE;
                        break;
                    }
                    //�Ƿ���GO
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //��ת����ʼ�ܲ��Ľ���
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, WALK);
                                runningMan.Run();
                                break;
                            }
                            Update(people,WALK);
                        }
                    }
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
            }
        }
        //��λ�����н���ʱ
        if (state == RIDE) {
            Draw_Sport_Ride(people);
            mouse_position(mouse);//��ȡ���λ��
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //������꽫��������
                mouse_show(mouse);      //�������
            //}
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //������ܲ�ʱ
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RUN;
                        break;
                    }
                    //���������ʱ
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = WALK;
                        break;
                    }
//                    //�Ƿ���GO��ť
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 11 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 28 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2))){
//                        //��ת����ʼ�ܲ��Ľ���
//                        if(Begin_Run()) {
//                            Character runningMan(people);
//                            runningMan.Run();
//                        }
                    //�Ƿ���GO��ť
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //��ת����ʼ�ܲ��Ľ���
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, RIDE);
                                runningMan.Run();
                                break;
                            }
                            Update(people,RIDE);
                        }
                    }
                    //�Ƿ�����������ť
                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
                        mouse->pos_x > 40 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
                        mouse->pos_y < 57 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
                    //���뿪ʼ���н���
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
            }
        }
        //��������
        /*if(mouse->button == 1) {
            //�����������Ϊ�·�5��
            if( mouse->pos_y > 130 * size && mouse->pos_y < 140 * size){
                //������˶�Ȧ
                if(mouse->pos_x<14.5*size)
                    return CIRCLE;
                //���������
                if(mouse->pos_x<27.5*size &&mouse->pos_x>14.5*size)
                    return FIND;
                //������ɻ�
                if(mouse->pos_x>40.5*size&&mouse->pos_x<53.5*size)
                    return THINGS;
                //������ҵ�
                if(mouse->pox_x>53.5*size)
                    return MINE;
            }*/
    }
}
/**********************************************************
Function��		Draw_Sport_Run

Description��	���ܲ���������

Input��			PEOPLE* people

Output��		�ܲ�������

Return��		NONE
**********************************************************/
void Draw_Sport_Run(PEOPLE* people) {
    float size = 5.5;
    int i;          //ѭ������
    int s=people->runLen;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
    //�����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //��������ʾ
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //��4��ѡ��
    dis_16hz(5 * size, 21 * size, "�ܲ�", GREEN);
    SVGA_Line(5*size,26*size,5*size+32,26*size,GREEN);
    SVGA_Line(5*size,26*size-1,5*size+32,26*size-1,GREEN);
    dis_16hz(16 * size, 21 * size, "����", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"����", LIGHT_GRAY );
    //�ܲ��ܹ���
    if(strlen(zS)==2) {
        dis_24zf(34 * size - 48, 35 * size, zS, BLACK);
    }
    else{
        dis_24zf(34 * size - 48, 35 * size, "0", BLACK);
        dis_24zf(34 * size - 24, 35 * size, zS, BLACK);
    }
    SVGA_Ball(34 * size ,35 * size+21,3, BLACK);
    if(strlen(pS)==2) {
        dis_24zf(34 * size , 35 * size, pS, BLACK);
    }
    else{
        dis_24zf(34 * size , 35 * size, "0", BLACK);
        dis_24zf(34 * size + 24, 35 * size, pS, BLACK);
    }
    dis_24hz(34 * size - 12 * 5, 50 * size, "�˶��ܹ���", BLACK);
    //GO��ť
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //�ײ�5����ť
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "�˶�", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "�ҵ�", LIGHT_GRAY);
}
/**********************************************************
Function��		Draw_Sport_Walk

Description��	�����ߵ�������

Input��			NONE

Output��		����������

Return��		NONE
**********************************************************/
void Draw_Sport_Walk(PEOPLE* people) {
    float size = 5.5;
    int i;          //ѭ������
    int s=people->walkLen;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
    //�����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //��������ʾ
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //��4��ѡ��
    dis_16hz(5 * size, 21 * size, "�ܲ�", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "����", GREEN);
    SVGA_Line(16 * size, 26 * size, 16 * size + 32, 26 * size, GREEN);
    SVGA_Line(16 * size, 26 * size - 1, 16 * size + 32, 26 * size - 1, GREEN);
    dis_16hz(27 * size, 21 * size,"����", LIGHT_GRAY );
    //�����ܹ���
    if(strlen(zS)==2) {
        dis_24zf(34 * size - 48, 35 * size, zS, BLACK);
    }
    else{
        dis_24zf(34 * size - 48, 35 * size, "0", BLACK);
        dis_24zf(34 * size - 24, 35 * size, zS, BLACK);
    }
    SVGA_Ball(34 * size ,35 * size+21,3, BLACK);
    if(strlen(pS)==2) {
        dis_24zf(34 * size , 35 * size, pS, BLACK);
    }
    else{
        dis_24zf(34 * size , 35 * size, "0", BLACK);
        dis_24zf(34 * size + 24, 35 * size, pS, BLACK);
    }
    dis_24hz(34 * size - 12 * 5, 50 * size, "�����ܹ���", BLACK);
    //GO��ť
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //�ײ�5����ť
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "�˶�", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "�ҵ�", LIGHT_GRAY);
}
/**********************************************************
Function��		Draw_Sport_Ride

Description��	�����е�������

Input��			NONE

Output��		����������

Return��		NONE
**********************************************************/
void Draw_Sport_Ride(PEOPLE* people) {
    float size = 5.5;
    int i;          //ѭ������
    int s=people->rideLen;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
    //�����µ��̰ױ���
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //��������ʾ
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //��4��ѡ��
    dis_16hz(5 * size, 21 * size, "�ܲ�", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "����", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"����", GREEN);
    SVGA_Line(27*size,26*size,27*size+32,26*size,GREEN);
    SVGA_Line(27*size,26*size-1,27*size+32,26*size-1,GREEN);
    //�����ܹ���
    if(strlen(zS)==2) {
        dis_24zf(34 * size - 48, 35 * size, zS, BLACK);
    }
    else{
        dis_24zf(34 * size - 48, 35 * size, "0", BLACK);
        dis_24zf(34 * size - 24, 35 * size, zS, BLACK);
    }
    SVGA_Ball(34 * size ,35 * size+21,3, BLACK);
    if(strlen(pS)==2) {
        dis_24zf(34 * size , 35 * size, pS, BLACK);
    }
    else{
        dis_24zf(34 * size , 35 * size, "0", BLACK);
        dis_24zf(34 * size + 24, 35 * size, pS, BLACK);
    }
    dis_24hz(34 * size - 12 * 5, 50 * size, "�����ܹ���", BLACK);
//    //GO��ť
//    CircleBar( 11 * size, 98 * size, 28 * size, 98 * size, 5*size, GREEN);
//    dis_24zf(19.5 * size - 24, 98 * size - 12, "GO", WHITE);
    //GO��ť
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
//    //��������ť dis_24zf(48.5 * size - 24*2, 98 * size - 12, , WHITE);
//    CircleBar( 40 * size, 98 * size, 57 * size, 98 * size, 5*size, GREEN);
//    dis_24zf(48.5*size-24*2,98*size-12,"������",WHITE);      //ERROR:���������ʾ��������
    //�ײ�5����ť
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "�˶�", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "�ҵ�", LIGHT_GRAY);
}
/**********************************************************
Function��		Update

Description��	�����˶����������

Input��			PEOPLE* people
               SPORT state

Output��		�˶�����

Return��		NONE
**********************************************************/
void Update(PEOPLE* people,Sport state) {
    float size=5.5;
    int s;
    if(state==RUN)
        s = people->runLen;
    else if(state==WALK)
        s = people->walkLen;
    else if(state==RIDE)
        s = people->rideLen;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
    itoa(s / 1000, zS, 10);
    itoa((s % 1000 - s % 10) / 10, pS, 10);
    SVGA_Bar(34 * size - 48,35 * size,34 * size + 72,35 * size+24,WHITE);
    if (strlen(zS) == 2) {
        dis_24zf(34 * size - 48, 35 * size, zS, BLACK);
    } else {
        dis_24zf(34 * size - 48, 35 * size, "0", BLACK);
        dis_24zf(34 * size - 24, 35 * size, zS, BLACK);
    }
    SVGA_Ball(34 * size, 35 * size + 21, 3, BLACK);
    if (strlen(pS) == 2) {
        dis_24zf(34 * size, 35 * size, pS, BLACK);
    } else {
        dis_24zf(34 * size, 35 * size, "0", BLACK);
        dis_24zf(34 * size + 24, 35 * size, pS, BLACK);
    }
}









































