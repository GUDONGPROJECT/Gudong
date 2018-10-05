/**********************************************************
Copyright (C) 2017 .
File name:		regist.c
Author:
Description��	�����û��ĵ�¼ע��

Function List��
	1.void Begin(MOUSE * mouse)
	��¼ע��������еķ���ֵ���������ã���Ϣ����
	2.int Begin_menu(MOUSE*mouse,PEOPLE*people);
	��ʼ����Ĳ���
	3.void Begin_draw(void)
	��ʼ�����ͼ��
	4.void Regist(MOUSE *mouse,PEOPLE *people);
	ע������������
	5.void Regist_draw(void)
	��ע�����ͼ��
	6.int R_check(MOUSE *mouse,PEOPLE *people,char *txtname,char * key, char *key1);
	���ע��ʱ�û������Ƿ����Ҫ����ʾ�û�������һ������
	7.int Login(MOUSE *mouse,PEOPLE *people);
	��¼�����������
	8.void Login_draw(void)
	����¼����
	9.int L_check(MOUSE *mouse,PEOPLE *people,char *txtname, char *key1);
	��������Ƿ���ȷ���û��Ƿ���������
	10.int registLogin(MOUSE *mouse,PEOPLE *people);
	����Ա��¼�����������
	11.void registLogin_draw(void)
	������Ա��¼����
	12.int RL_check(MOUSE *mouse,PEOPLE *people,char *txtname, char *key1);
	����Ա������
	13.int Rname(MOUSE *mouse,PEOPLE *people,char *data,int *number,int x,int y);
	��¼�û���������Ļ����ʾ�����ó�����λ
	14.int Rkey(MOUSE *mouse,char *data,int *number,int x,int y);
	��¼�û����벢����Ļ����ʾ�����ó�����λ
	15.void Create_path (char *name,char *textname);
	�����ļ�·��
	16.void flash(void)
	��������
**********************************************************/
#include"./header/login.h"

/**********************************************************
Function��		Begin

Description��	��¼ע��������еķ���ֵ���������ã���Ϣ����

Input��			MOUSE *mouse 	  ������
				
Output��		������һ������

Return��		NONE
**********************************************************/
void Begin(MOUSE *mouse) {
    int state = 3;
    PEOPLE people;
    while (1) {
        state = Begin_menu(mouse, &people);
        if (state == 1) {
//			menu1(mouse,&people);
        }
        if (state == 2) {
//			menu2(mouse);
        }
        if (state == 0) {
            exit(0);
        }
    }
}

/**********************************************************
Function��		Begin_draw

Description��	����ʼ����

Input��			NONE
				
Output��		��ʼ����

Return��		NONE
**********************************************************/
void Begin_draw(void) {
//    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
//    SVGA_Bar(302, 263, 632, 308, 0x7FFF0E);     //����Ӧλ�û�����
//    SVGA_Bar(302, 339, 632, 382, 0x7FFF0E);       //����Ӧλ�û�����
//    SVGA_Bar(302, 413, 632, 458, 0x7FFF0E);
//    SVGA_Bar(600, 481, 710, 526, 0x7FFF0E);
////dis_hz_gai(369,178,2,"��ӭ��¼",0);
//    dis_24hz(417, 178, "��ӭ��¼", 0);
//    dis_24hz(419, 273, "�û���¼", 0);
//    dis_24hz(419, 348, "�û�ע��", 0);
//    dis_24hz(407, 423, "����Ա��¼", 0);
//    dis_24hz(631, 491, "�˳�", 0);
    float size=5.5;
    SVGA_Bar(0,0,68*size,140*size,DARK_GRAY);
    //setcolor(GREEN);
    //��΢����ɫ��ť
    CircleBar(7*size,102*size,61*size,102*size,5*size,GREEN);
    dis_16hz(34*size-16,102*size-8,"΢��",WHITE);
    //��΢����QQ��ɫ��ť
    CircleBar(7*size,115*size,61*size,115*size,5*size,LIGHT_GRAY);
    dis_16hz(34*size-16*7,115*size-8,"΢��",WHITE);
    SVGA_Line(34*size,112*size,34*size,118*size,WHITE);
    dis_16zf(34*size+16*5,115*size-8,"QQ",WHITE);
    //���ֻ���|�����¼
    dis_16hz(16*size-16*4,126*size-8,"�ֻ���",WHITE);
    SVGA_Line(16*size,126*size-8,16*size,126*size+8,WHITE);
    dis_16hz(16*size+8,126*size-8,"�����¼",WHITE);
    //���ֻ���ע��
    dis_16hz(53*size-40,126*size-8,"�ֻ���ע��",WHITE);
    //Э��
    dis_16hz(3*size,134*size-8,"ע����¼��ͬ��",WHITE);
}

/**
 * mouseDetector �����귶Χ
 *
 * @param lx ���ϽǺ�����
 * @param ly ���Ͻ�������
 * @param rx ���½Ǻ�����
 * @param ry ���½�������
 * @param color ��ɫ
 * @param fun ���뺯��
 * @param
 */
//
//void mouseDetector(int lx, int ly, int rx, int ry, int color, int (*fun) (MOUSE *, PEOPLE *), MOUSE *mouse, PEOPLE *people, int *state) {
//    if (mouse->pos_x > lx && mouse->pos_y > ly && mouse->pos_x < rx && mouse->pos_y < ry) {
//        mouse_recover(mouse);  //����ͷ�������
//        SVGA_Rectangular(302, 263, 632, 308, 255);     //����Ӧλ�û�����
//        mouse_reset(mouse);     //������ʾ��ͷ���
//        while (1) {
//            mouse_position(mouse);
//            drawmouse(mouse);
//            //�������������غ���
//            if (mouse->button == 1) {
//                delay(400);
//                mouse_recover(mouse);
//                state = Login(mouse, people);
//                mouse_reset(mouse);
//                if (state == 1) {
//                    fun(mouse, people);
//                    return 1;
//                };
//                break;
//            }
//            if (mouse->pos_x < lx || mouse->pos_y < ly || mouse->pos_x > rx || mouse->pos_y > ry) {
//                mouse_recover(mouse);  //����ͷ�������
//                SVGA_Rectangular(302, 263, 632, 308, -1);      //����Ӧλ�û��׿򸲸�����
//                mouse_reset(mouse);     //������ʾ��ͷ���
//                break;
//            }
//        }
//    }
//}

/**********************************************************
Function��		Begin����menu

Description��	���ڴӿ�ʼ����ѡ����

Input��			MOUSE *mouse 	  ������
				
Output��		NONE

Return��		�������
**********************************************************/
int Begin_menu(MOUSE *mouse, PEOPLE *people) {
    int state = 0;
    Begin_draw();
    mouse_reset(mouse);//�������
    while (1) {
        mouse_position(mouse);//��ȡ���λ��
        drawmouse(mouse);//�������

        // �û�ע��
//        mouseDetector(302, 263, 632, 308, 255, NULL, mouse, people, &state);
        //����Ա��¼
        if (mouse->pos_x > 302 && mouse->pos_y > 413 && mouse->pos_x < 632 && mouse->pos_y < 458) {
            mouse_recover(mouse);  //����ͷ�������
            SVGA_Rectangular(302, 413, 632, 458, 255);
            mouse_reset(mouse);      //������ʾ��ͷ���
            while (1) {
                mouse_position(mouse);
                drawmouse(mouse);
                if (mouse->button == 1) {              //�������������غ���
                    delay(100);
                    mouse_recover(mouse);
                    state = registLogin(mouse);
                    mouse_reset(mouse);
                    if (state == 1) {
                        //	menu2(mouse);
                        return 2;
                    }
                    break;
                }
                delay(100);//���Է�ֹ˫��
                if (mouse->pos_x < 302 || mouse->pos_x > 632 || mouse->pos_y < 413 || mouse->pos_y > 458) {
                    mouse_recover(mouse);  //����ͷ�������
                    SVGA_Rectangular(302, 413, 632, 458, -1);
                    mouse_reset(mouse);      //������ʾ��ͷ���
                    break;
                }
            }

        }
        /*���λ���Ƶ�ע��*/
        if (mouse->pos_x > 600 && mouse->pos_y > 481 && mouse->pos_x < 710 && mouse->pos_y < 526) {
            mouse_recover(mouse);  //����ͷ�������
            SVGA_Rectangular(600, 481, 710, 526, 255);
            mouse_reset(mouse);      //������ʾ��ͷ���
            while (1) {
                mouse_position(mouse);
                drawmouse(mouse);
                if (mouse->button == 1) {
                    delay(100);    //���������˳���������
                    return 0;
                }          //�˳�����
                if (mouse->pos_x < 600 || mouse->pos_x > 710 || mouse->pos_y < 481 || mouse->pos_y > 526) {
                    mouse_recover(mouse);  //����ͷ�������
                    SVGA_Rectangular(600, 481, 710, 526, -1);
                    mouse_reset(mouse);      //������ʾ��ͷ���
                    break;
                }
            }
        }
    }
}

void flash(void) {
    int i = 0;//�������м�
    for (i = 0; i < 10; i++) {
        PartBmp(0, 768, 0, 824 + 20 * i, 0, 0, "pic\\pic4.bmp");
    }
    delay(500);
    for (i = 0; i < 10; i++) {
        PartBmp(0, 768, 0, 412 + 12 * i, 0, 0, "pic\\pic1.bmp");
        PartBmp(0, 768, 612 - 12 * i, 1024, 612 - 12 * i, 0, "pic\\pic1.bmp");
    }
    delay(500);
//ǰ�����м�
    for (i = 0; i < 10; i++) {
        PartBmp(0, 284 + 12 * i, 0, 1024, 0, 0, "pic\\pic2.bmp");
        PartBmp(484 - 12 * i, 768, 0, 1024, 0, 484 - 12 * i, "pic\\pic2.bmp");
    }
    delay(500);
//��ѭ�����ڴ��м������ͼ
    for (i = 0; i <= 20; i++) {
        PartBmp(340 - 17 * i, 428 + 17 * i, 280 - 14 * i, 744 + 14 * i, 280 - 14 * i, 340 - 17 * i, "pic\\pic3.bmp");
    }
    delay(700);
}

/**********************************************************
Function��		Regist

Description��	�û�ע�ắ��

Input��			MOUSE *mouse 	  ������
				
Output��		ע�ắ����ʹ��

Return��		NONE
				
**********************************************************/
void Regist(MOUSE *mouse)//�жϰ�������ִ�к�������
{
    char *name = (char *) malloc(15);//�������ڴ洢����
    char *key = (char *) malloc(15);//���ڴ洢����
    char *key1 = (char *) malloc(15);//���ڼ����û������Ƿ���ȷ
    char *txtname = (char *) malloc(35);//���ڴ洢�ļ���
    FILE *fp;
    int state = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    Regist_draw();
    mouse_reset(mouse);
    for (;;)//���ذ���
    {
        mouse_position(mouse);//��ȡ���λ��
        drawmouse(mouse);//�������
        if (mouse->pos_x > 352 && mouse->pos_y > 236 && mouse->pos_x < 686 && mouse->pos_y < 272 &&
            mouse->button == 1)//����û������������û����׿���
        {
            delay(100);//���Է�ֹ˫��
            if (Rname(mouse, name, &num1, 352, 236) == -1)//xyΪ�û������Ͻǰ׿�
            {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
            if (num1 != 0)//��ֹ���ֻ��ȥ��һȦ��
            {
                Create_path(name, txtname);//�����ļ�·��
                //�Ƿ��ڴ����ñ�����Ŀ
                fp = fopen(txtname, "r+");
                if (fp != NULL) {
                    fclose(fp);
                    //readbmp(182,128,"pic\\chongfu.bmp");//��ʾ�û������ظ�,���������û�ע�����
                    mouse_recover(mouse);
                    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
                    dis_24hz(393, 327, "�û����Ѵ���", 0);
                    delay(500);
                    Regist_draw();
                    mouse_reset(mouse);
                    num1 = 0;
                    num2 = 0;
                    num3 = 0;
                } else {
                    fclose(fp);
                }
            }
        } else if (mouse->pos_x > 352 && mouse->pos_y > 307 && mouse->pos_x < 686 && mouse->pos_y < 344 &&
                   mouse->button == 1) {
            delay(100);//���Է�ֹ˫��
            if (Rkey(mouse, key, &num2, 352, 307) == -1)//¼���һ�ε�����
            {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
        } else if (mouse->pos_x > 352 && mouse->pos_y > 379 && mouse->pos_x < 686 && mouse->pos_y < 417 &&
                   mouse->button == 1) {
            delay(100);//���Է�ֹ˫��
            if (Rkey(mouse, key1, &num3, 352, 379) == -1) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }//¼��ڶ��ε�����
            //�Ƿ����ñ�����key1
        } else if (mouse->pos_x > 247 && mouse->pos_y > 452 && mouse->pos_x < 352 && mouse->pos_y < 497 &&
                   mouse->button == 1)//���ע�ᰴť
        {
            delay(100);//���Է�ֹ˫��
            mouse_recover(mouse);
            state = R_check(txtname, key, key1);//ע��ɹ�����������������
            mouse_reset(mouse);
            if (state == 1) {
                fp = fopen("txt\\username.txt", "a+");
                fprintf(fp, "%s\n", name);
                fclose(fp);
                if (name != NULL) {
                    free(name);
                    name = NULL;
                }
                if (key != NULL) {
                    free(key);
                    key = NULL;
                }
                if (key1 != NULL) {
                    free(key1);
                    key1 = NULL;
                }
                if (txtname != NULL) {
                    free(txtname);
                    txtname = NULL;
                }
                mouse_recover(mouse);
                Begin_draw();
                return;
            } else {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
        } else if (mouse->pos_x > 577 && mouse->pos_y > 453 && mouse->pos_x < 686 && mouse->pos_y < 497 &&
                   mouse->button == 1)//�������ذ�ť�����˻ص���һ�����
        {
            delay(100);//���Է�ֹ˫��
            if (name != NULL) {
                free(name);
                name = NULL;
            }
            if (key != NULL) {
                free(key);
                key = NULL;
            }
            if (key1 != NULL) {
                free(key1);
                key1 = NULL;
            }
            if (txtname != NULL) {
                free(txtname);
                txtname = NULL;
            }
            //Begin_menu(mouse);
            mouse_recover(mouse);
            Begin_draw();
            return;
        }
    }
}

/**********************************************************
Function��		Regist_draw

Description��	��ע�����

Input��			NONE
				
Output��		ע�����

Return��		NONE
				
**********************************************************/
void Regist_draw(void) {
////readbmp(182,128,"pic\\regist.bmp");//����ע�����
//    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
//    SVGA_Bar(352, 236, 686, 272, -1);
//    SVGA_Bar(352, 307, 686, 344, -1);
//    SVGA_Bar(352, 379, 686, 417, -1);
//    SVGA_Bar(247, 452, 352, 497, 0x7FFF0E);
//    SVGA_Bar(577, 453, 686, 497, 0x7FFF0E);
//    dis_24hz(441, 164, "ע��", 0);
//    dis_16hz(246, 240, "�û�����", 0);
//    dis_16hz(246, 314, "���룺", 0);
//    dis_16hz(246, 386, "ȷ�ϣ�", 0);
//    dis_16hz(276, 465, "ע��", 0);
//    dis_16hz(608, 463, "�˳�", 0);
    float size=5.5;
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //�����ϽǷ��ذ�ť
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    //��ע�ᰴť
    CircleBar(7*size,111*size,61*size,111*size,5*size,DARK_GRAY);
    dis_16hz(34*size-16*1,111*size-8,"ע��",WHITE);
    //�����ֻ��ſ�
    dis_24hz(34*size-24*3.5,25*size-12,"��������ֻ���",BLACK);
    SVGA_Line(6*size,47*size,62*size,47*size,LIGHT_GRAY);
    //���������
    dis_24hz(34*size-24*4.5,75*size-12,"������Ҫ���õ�����",BLACK);
    SVGA_Line(6*size,97*size,62*size,97*size,LIGHT_GRAY);
    //�Ѿ�ע�᣿
    dis_16hz(34*size-16*7.5,124*size-8,"�Ѿ�ע������ˣ�",LIGHT_GRAY);
    dis_16hz(34*size+16*2,124*size-8,"��˵�¼",GREEN);
}

/**********************************************************
Function��		R_check

Description��	���ڼ���û��û��������Ƿ���ϱ�׼

Input��			char *txtname     �����洢�û����ļ�����ַ
			    char *key         �û���һ�����������
				char *key1        �û��ڶ������������
				
Output��		��ʾ�û�ע��״̬�������û����ļ��������û��ļ�

Return��		ע��״̬���
				
**********************************************************/
int R_check(char *txtname, char *key, char *key1)//�жϺ����Ƿ���Կ�¼�룬�Լ�¼�뺯��
{
    FILE *fp;
    if (strcmp(key, key1) != 0) {
        //readbmp(182,128,"pic\\notmatch.bmp");//��ʾǰ�����ε����벻��ͬ�������������
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "ǰ�����벻һ��", 0);
        delay(700);
        //Regist(mouse,people);
        return 0;
    } else {
        fp = fopen(txtname, "r+");
        if (fp != NULL) {
            fclose(fp);
            //readbmp(182,128,"pic\\chongfu.bmp");//��ʾ�û������ظ�,���������û���¼����
            SVGA_Bar(182, 128, 749, 551, 0x000EFF);
            dis_24hz(393, 327, "�û������ظ�", 0);
            delay(700);
            //Regist(mouse,people);//�����¼����
            return 0;
        } else {
            fclose(fp);
            fp = fopen(txtname, "w+");
            fprintf(fp, "%s\n", key);
            fprintf(fp, "%s\n", "0 0 0 0 0 0 0 0 0 0 ");
            fclose(fp);
            //readbmp(182,128,"pic\\okay.bmp");
            SVGA_Bar(182, 128, 749, 551, 0x000EFF);
            dis_24hz(393, 327, "����ע��ɹ�", 0);
            delay(700);
            //Begin_menu(mouse);
            return 1;
        }
    }
}

/**********************************************************
Function��		Login

Description��	�û���¼�����������û������û��ļ���

Input��			MOUSE *mouse 	  ������
				PEOPLE *people    �û��ṹ��
				
Output��		NONE

Return��		�������
				
**********************************************************/
int Login(MOUSE *mouse, PEOPLE *people) {
    char *name = (char *) malloc(15);
//�������ڴ洢����
    char *key = (char *) malloc(15);
//���ڴ洢����
    char *txtname = (char *) malloc(35);
//���ڴ洢�ļ���
    FILE *fp;
    int num1 = 0;
    int num2 = 0;
    int state = 0;
//readbmp(182,128,"pic\\Login.bmp");
    Login_draw();
//�����½����
    mouse_reset(mouse);
    for (;;) {
        mouse_position(mouse);
        //��ȡ���λ��
        drawmouse(mouse);
        //�������
        if (mouse->pos_x > 352 && mouse->pos_y > 263 && mouse->pos_x < 686 && mouse->pos_y < 299 &&
            mouse->button == 1)//����û���
        {
            delay(100);
            //���Է�ֹ˫��
            if (Rname(mouse, name, &num1, 352, 263) == -1) {
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
            if (num1 != 0) {
                Create_path(name, txtname);
                fp = fopen(txtname, "r+");
                if (fp == NULL) {
                    //readbmp(182,128,"pic\\notexist.bmp");//��ʾ�û���������
                    mouse_recover(mouse);
                    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
                    dis_24hz(393, 327, "�û���������", 0);
                    delay(700);
                    fclose(fp);
                    //Login(mouse,people);
                    Login_draw();
                    num1 = 0;
                    num2 = 0;
                    mouse_reset(mouse);
                } else {
                    fclose(fp);
                }
            }
        } else if (mouse->pos_x > 352 && mouse->pos_y > 334 && mouse->pos_x < 686 && mouse->pos_y < 372 &&
                   mouse->button == 1)//�����¼��ť��¼
        {
            delay(100);//���Է�ֹ˫��
            if (Rkey(mouse, key, &num2, 352, 334) == -1) {
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
        } else if (mouse->pos_x > 245 && mouse->pos_y > 443 && mouse->pos_x < 352 && mouse->pos_y < 487 &&
                   mouse->button == 1)//�����¼��ť
        {
            delay(100);//���Է�ֹ˫��
            mouse_recover(mouse);
            state = L_check(people, txtname, key);
            mouse_reset(mouse);
            if (state == 1) {
                mouse_recover(mouse);
                Begin_draw();
                strcpy(people->name, name);
                if (name != NULL) {
                    free(name);
                    name = NULL;
                }
                if (key != NULL) {
                    free(key);
                    key = NULL;
                }
                if (txtname != NULL) {
                    free(txtname);
                    txtname = NULL;
                }
                return 1;
            } else if (state == 2) {
                mouse_recover(mouse);
                Begin_draw();
                if (name != NULL) {
                    free(name);
                    name = NULL;
                }
                if (key != NULL) {
                    free(key);
                    key = NULL;
                }
                if (txtname != NULL) {
                    free(txtname);
                    txtname = NULL;
                }
                return 0;
            } else {
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
        } else if (mouse->pos_x > 578 && mouse->pos_y > 443 && mouse->pos_x < 687 && mouse->pos_y < 487 &&
                   mouse->button == 1) {
            delay(100);//���Է�ֹ˫��
            if (name != NULL) {
                free(name);
                name = NULL;
            }
            if (key != NULL) {
                free(key);
                key = NULL;
            }
            if (txtname != NULL) {
                free(txtname);
                txtname = NULL;
            }
            //Begin_menu(mouse);
            mouse_recover(mouse);
            Begin_draw();
            return 0;
        }
    }
}

/**********************************************************
Function��		Login_draw

Description��	����¼����

Input��			NONE
				
Output��		��¼����

Return��		NONE
				
**********************************************************/
void Login_draw(void) {
//    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
//    SVGA_Bar(352, 263, 686, 299, -1);
//    SVGA_Bar(352, 334, 686, 372, -1);
//    SVGA_Bar(245, 443, 352, 487, 0x7FFF0E);
//    SVGA_Bar(578, 443, 687, 487, 0x7FFF0E);
//    dis_24hz(441, 191, "��¼", 0);
//    dis_16hz(246, 267, "�û�����", 0);
//    dis_16hz(278, 454, "��¼", 0);
//    dis_16hz(607, 452, "�˳�", 0);
//    dis_16hz(246, 336, "���룺", 0);

    float size = 5.5;
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Line(6 * size, 8 * size, 4 * size, 10 * size, BLACK);
    //�����ϽǷ��ذ�ť
    SVGA_Line(6 * size, 12 * size, 4 * size, 10 * size, BLACK);
    //�ֻ���¼
    dis_24hz(6 * size, 18 * size, "�ֻ���¼", BLACK);
    //�˺������
    SVGA_Line(6 * size, 47 * size, 62 * size, 47 * size, LIGHT_GRAY);
    dis_16hz(6 * size, 41 * size, "�ֻ���", LIGHT_GRAY);
    //���������
    SVGA_Line(6 * size, 57 * size, 62 * size, 57 * size, LIGHT_GRAY);
    dis_16hz(6 * size, 51 * size, "����", LIGHT_GRAY);
    //��¼��ť
    CircleBar(7 * size, 70 * size, 61 * size, 70 * size, 5 * size, DARK_GRAY);
    dis_16hz(34 * size - 16 * 1, 70 * size - 8, "��¼", WHITE);
}

/**********************************************************
Function��		L_check

Description��	���ڼ���û��û����Ƿ���ڣ������Ƿ���ȷ�ĺ�������ʾ��һ������

Input��			PEOPLE *people    �û��ṹ��
				char *txtname     �����洢�û����ļ�����ַ
				char *key1        �û��ڶ������������
				
Output��		��ʾ�û���¼״̬������������

Return��		�û���¼״̬���к�
				
**********************************************************/
int L_check(PEOPLE *people, char *txtname, char *key1) {
    FILE *fp;
    char *key = (char *) malloc(15);//���ڴ洢��ȷ������
    char ac;
    fp = fopen(txtname, "r+");
    if (fp == NULL) {
        //readbmp(182,128,"pic\\notexist.bmp");//��ʾ�û���������
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "�û���������", 0);
        delay(700);
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
    fscanf(fp, "%s\n", key);
    if (strcmp(key, key1) == 0) {
        fclose(fp);//��������ȷ����������˵�����
        strcpy(people->key, key);
        strcpy(people->txtname, txtname);
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 1;
        //menu1(mouse,people);
    } else {
        fseek(fp, 0, 0);
        if (fgetc(fp) == EOF)//����������д����
        {
            fclose(fp);
            //readbmp(182,128,"pic\\black.bmp");//��ʾ�û��Ѿ���������������˳���������
            SVGA_Bar(182, 128, 749, 551, 0x000EFF);
            dis_24hz(393, 327, "���ں�������", 0);
            delay(500);
            //Begin_menu(mouse);
            if (key != NULL) {
                free(key);
                key = NULL;
            }
            return 2;
        }
        fclose(fp);
        //readbmp(182,128,"pic\\erro.bmp");//�����벻���ڣ�����ʾ�������
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "�����������", 0);
        delay(700);
        //Login(mouse,people);//�ص���¼����
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
}

/**********************************************************
Function��		registLogin

Description��	����Ա��¼����

Input��			MOUSE *mouse 	  ������
				PEOPLE *people    �û��ṹ��
				
Output��		��¼����

Return��		NONE
				
**********************************************************/
void registLogin_draw(void) {
    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
    SVGA_Bar(245, 443, 352, 487, 0x7FFF0E);
    SVGA_Bar(578, 443, 687, 487, 0x7FFF0E);
    SVGA_Bar(352, 317, 686, 355, -1);
    dis_24hz(405, 191, "����Ա��¼", 0);
    dis_16hz(246, 318, "���룺", 0);
    dis_16hz(278, 454, "��¼", 0);
    dis_16hz(607, 452, "�˳�", 0);
}

int registLogin(MOUSE *mouse) {
    char *key1 = (char *) malloc(15);//���ڴ洢����
    int num = 0;
    int state = 0;
    FILE *fp;
// readbmp(182,128,"pic\\register.bmp");//�����½����
    registLogin_draw();
    mouse_reset(mouse);//�������
    for (;;) {
        mouse_position(mouse);//��ȡ���λ��
        drawmouse(mouse);//�������

        if (mouse->pos_x > 352 && mouse->pos_y > 317 && mouse->pos_x < 686 && mouse->pos_y < 383 &&
            mouse->button == 1)//�����¼��ť��¼
        {
            delay(100);//���Է�ֹ˫��
            if (Rkey(mouse, key1, &num, 352, 317) == -1) {
                mouse_recover(mouse);
                registLogin_draw();
                mouse_reset(mouse);
                num = 0;
            }
        } else if (mouse->pos_x > 245 && mouse->pos_y > 443 && mouse->pos_x < 352 && mouse->pos_y < 487 &&
                   mouse->button == 1)//�����¼��ť
        {
            delay(100);//���Է�ֹ˫��
            mouse_recover(mouse);
            state = RL_check("txt\\regist.txt", key1);
            mouse_reset(mouse);
            if (state == 1) {
                if (key1 != NULL) {
                    free(key1);
                    key1 = NULL;
                }
                mouse_recover(mouse);
                Begin_draw();
                return 1;
            } else {
                mouse_recover(mouse);
                registLogin_draw();
                num = 0;
                mouse_reset(mouse);
            }
        } else if (mouse->pos_x > 577 && mouse->pos_y > 443 && mouse->pos_x < 686 && mouse->pos_y < 489 &&
                   mouse->button == 1)//����˳�
        {
            delay(100);//���Է�ֹ˫��
            if (key1 != NULL) {
                free(key1);
                key1 = NULL;
            }
            //Begin_menu(mouse);
            mouse_recover(mouse);
            Begin_draw();
            return 0;
        }
    }
}

/**********************************************************
Function��		RL_check

Description��	���ڼ�����Ա�����Ƿ���ȷ�ĺ���

Input��			MOUSE *mouse 	  ������
				PEOPLE *people    �û��ṹ��
				char *txtname     �����洢�û����ļ�����ַ
				char *key         �û���һ�����������
				char *key1        �û��ڶ������������

Output��		��ʾ����Ա��¼״̬�������������

Return��		NONE

**********************************************************/
int RL_check(char *txtname, char *key1) {
//int be;
    FILE *fp;
    char *key = (char *) malloc(15);
//char ac;
    fp = fopen(txtname, "r+");
    if (fp == NULL) {
        printf("regist file can not open");
        fclose(fp);
        exit(1);
    }
    fscanf(fp, "%s\n", key);
    if (strcmp(key, key1) == 0) {
        fclose(fp);//��������ȷ����������˵�����
        // for(be=0;be<6;be++)
        //{
        //	people->tuijian[be]=0;
        //}
        //menu2(mouse);
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 1;
    } else {
        fclose(fp);
        //readbmp(182,128,"pic\\erro.bmp");//�����벻���ڣ�����ʾ�������
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "�����������", 0);
        delay(700);
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
}

/**********************************************************
Function��		Create_path

Description��	���������û����û����ļ�·��

Input��
				char *name       �û����û���
				char *textname   �û�������Ӧ���û�·��

Output��	    NONE

Return��		NONE

**********************************************************/
void Create_path(char *name, char *textname) {
    stpcpy(textname, "txt\\");
    strcat(textname, name);
    strcat(textname, ".txt");
}

/**********************************************************
Function��		Rkey

Description��	���ڶ�ȡ�û��ڵ�¼ע��ʱ���������

Input��			char *data        �����洢������ַ���
				int x             �ı���ĺ�����
				int y			  �ı����������

Output��		�û�������ַ�

Return��		����״̬���к�

**********************************************************/
int Rkey(MOUSE *mouse, char *data, int *number, int x, int y) {
    char ac;//���ڴ洢����ļ�ֵ����ʾ
    int num = *number;
    int pos = x + 2 + num * 20;
    mouse_recover(mouse);//�������
    dis_16hz(pos, y + 9, "������λ", 0);
    delay(500);
    while (bioskey(1))//bioskey(1)��ѯ�Ƿ���һ�����������£��򷵻ط���ֵ
    {
        getch();
    }
    SVGA_Bar(pos, y + 2, pos + 100, y + 30, -1);
    SVGA_Straight(pos + 2, y + 9, 16, 0);//��ʾ���
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9')) || (ac >= 'a') && (ac <= 'z')) {
            SVGA_Straight(pos + 2, y + 9, 16, -1);//��ס֮ǰ�Ĺ��
            data[num++] = ac;
            SVGA_Ball(pos + 10, y + 15, 5, 0);//ʹ��outtext����ַ���ԭ��
            pos = pos + 20;//���������20��Ϊ��һ���������
            SVGA_Straight(pos + 2, y + 9, 16, 0);//����һ�����
        } else if (((ac == 127) || (ac == 8)) && (num > 0))//����del����backspace����ɾ���ַ�
        {
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num] = 0;
            num--;
            pos = pos - 20;//�������ȥ20��Ϊ��һ���ַ�������
            SVGA_Bar(pos, y + 5, pos + 19, y + 30, -1);//����ɫ�����ڸ�ס֮ǰ���ַ�
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 8) {
            SVGA_Bar(182, 128, 749, 551, 0x000EFF);
            dis_24hz(393, 327, "����λ������", 0);
            //readbmp(182,128,"pic\\too.bmp");
            delay(500);//��ʾ����λ������
            return -1;
        }
    }
    SVGA_Straight(pos + 2, y + 9, 16, -1);//��ס���еĹ��
    mouse_reset(mouse);//�������
    data[num] = '\0';//���һλ������ֹ��������fscan��ȡ
    number[0] = num;//����������λ�����ص���������
    if (num < 4) {
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "����λ������", 0);
        //readbmp(182,128,"pic\\too.bmp");
        delay(500);//��ʾ����λ������
        return -1;
    }
    return 1;
}

/**********************************************************
Function��		Rname

Description��	���ڶ�ȡ����ʾ�û��ڵ�¼ע��ʱ������û���

Input��			MOUSE *mouse 	  ������
				PEOPLE *people    �û��ṹ��
				char *data        �����洢������ַ���
				int x             �ı���ĺ�����
				int y			  �ı����������

Output��		�û�������û���

Return��		����״̬���к�

**********************************************************/
int Rname(MOUSE *mouse, char *data, int *number, int x, int y) {
    char ac;//���ڴ洢����ļ�ֵ����ʾ
    char str[2];//���ڴ洢�����ַ����Ҵ���ͼ��ģʽ���ı�����������ַ�����
    int num = *number;
    int pos = x + 2 + num * 20;
    str[1] = '\0';
    mouse_recover(mouse);//�������
    dis_16hz(pos, y + 9, "������λ", 0);
    delay(500);
    while (bioskey(1))//bioskey(1)��ѯ�Ƿ���һ�����������£��򷵻ط���ֵ
    {
        getch();
    }
    SVGA_Bar(pos, y + 9, pos + 100, y + 30, -1);
    SVGA_Straight(pos + 2, y + 9, 16, 0);//�����
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9')) || (ac >= 'a') && (ac <= 'z')) {
            SVGA_Straight(pos + 2, y + 9, 16, -1);//��ס֮ǰ�Ĺ��
            data[num++] = ac;
            str[0] = ac;
            dis_16zf(pos, y + 9, str, 0);//ʹ����ģ����ַ���ԭ��
            pos = pos + 20;//���������20��Ϊ��һ���������
            SVGA_Straight(pos + 2, y + 9, 16, 0);//�����
        } else if (((ac == 127) || (ac == 8)) && (num > 0))//����del����backspace����ɾ���ַ�
        {
            SVGA_Straight(pos + 2, y + 9, 16, -1);//��ס�����
            data[num] = 0;
            num--;
            pos = pos - 20;//�������ȥ20��Ϊ��һ���ַ�������
            SVGA_Bar(pos, y, pos + 20, y + 30, -1);//����ɫ�����ڸ�ס֮ǰ���ַ�
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 8) {
            SVGA_Bar(182, 128, 749, 551, 0x000EFF);
            dis_24hz(393, 327, "�û���λ������", 0);
            //readbmp(182,128,"pic\\too.bmp");//��ʾ����λ������
            delay(500);
            return -1;
        }
    }
    SVGA_Straight(pos + 2, y + 9, 16, -1);
    mouse_reset(mouse);//�������
    data[num] = '\0';//���һλ������ֹ��������fscan��ȡ
    number[0] = num;//����������λ�����ص���������
    if (num < 4) {
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "�û���λ������", 0);
        //readbmp(182,128,"pic\\too.bmp");//��ʾ����λ������
        delay(500);
        return -1;
    }
    return 1;
}
/**********void Change_key(PEOPLE *people)
{
	FILE *fp;
	fp=
}      *********/