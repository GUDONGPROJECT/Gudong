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
#include "./header/MAINUI.H"
#include "./header/headUtil.h"
#include "./header/map.h"
#include "./header/IoUtil.h"
#include "./header/things.h"
#include "./header/Find.h"
#include "./header/Circle.h"

/**********************************************************
Function��		Begin

Description��	��¼ע��������еķ���ֵ���������ã���Ϣ����

Input��			MOUSE *mouse 	  ������
				
Output��		������һ������

Return��		NONE
**********************************************************/
void Begin(MOUSE *mouse) {
    State state = UNDEFINED;
    PEOPLE people;
    while (1) {
        if (state == UNDEFINED) {
            state = Begin_menu(mouse, &people);
            if (state != UNDEFINED) {
                InitPeople(&people);
            }

            // �ϵ������
            char token1[22];
            char token2[22];
            strcpy(token1, people.name);
            strcpy(token2, people.key);
        }
        if (state == SPORTPAGE) {
			state = SportMain(mouse, &people);
        }
        if (state == BACK) {
            exit(0);
        }
        if (state == THINGS) {
            state = thingsPage(mouse, &people);
        }
        if (state == MINE) {
            state = MineMain(mouse, &people);
        }
        if (state == FIND) {
            state = findPage(mouse, &people);
        }
        if (state == CIRCLE) {
            state = circlePage(mouse, &people);
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
    //�����ϽǷ��ذ�ť
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    drawMap();
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

bool mouseDetector(int lx, int ly, int rx, int ry, int color, bool (*fun) (MOUSE *, PEOPLE *), MOUSE *mouse, PEOPLE *people) {
    bool isClicked = false;
    if (mouse->pos_x > lx && mouse->pos_y > ly && mouse->pos_x < rx && mouse->pos_y < ry) {
        mouse_recover(mouse);  //����ͷ�������
        SVGA_Rectangular(lx, ly, rx, ry, color);     //����Ӧλ�û�����
        mouse_reset(mouse);     //������ʾ��ͷ���
        while (true) {
            mouse_position(mouse);
            drawmouse(mouse);
            //�������������غ���
            if (mouse->button == 1) {
                delay(400);
                mouse_recover(mouse);
                isClicked = (bool) fun(mouse, people);
                mouse_reset(mouse);
                if (isClicked == true) {
//                    fun(mouse, people);
                    return true;
                };
                break;
            }
            if (mouse->pos_x < lx || mouse->pos_y < ly || mouse->pos_x > rx || mouse->pos_y > ry) {
                mouse_recover(mouse);  //����ͷ�������
                SVGA_Rectangular(lx, ly, rx, ry, DARK_GRAY);      //����Ӧλ�û��׿򸲸�����
                mouse_reset(mouse);     //������ʾ��ͷ���
                break;
            }
        }
    }
    return false;
}

/**********************************************************
Function��		Begin����menu

Description��	���ڴӿ�ʼ����ѡ����

Input��			MOUSE *mouse 	  ������
				
Output��		NONE

Return��		�������
**********************************************************/
State Begin_menu(MOUSE *mouse, PEOPLE *people) {
    Begin_draw();
    mouse_reset(mouse);//�������
    while (1) {
        mouse_position(mouse);//��ȡ���λ��
        drawmouse(mouse);//�������
        float size = 5.5;
        // �û�ע��
        if (mouseDetector(53*size-40,126*size-9, 53*size-40+16*5+4*4, 126*size-8+16, WHITE, Regist, mouse, people)) {
            return UNDEFINED;
        }
        // �û���¼
        if (mouseDetector(16*size-16*4,126*size-9, 16*size-16*4+16*3+4*2,126*size-8+16, WHITE, Login, mouse, people)) {
            return SPORTPAGE;
        }
        // ����
        if (mouseDetector(4*size, 8*size, 6*size, 12*size, WHITE, getTrue, mouse, people)) {
            return BACK;
        }
        // ΢�ŵ�¼
        if (mouseDetector(2 * size, 97 * size, 66 * size, 107 * size, WHITE, quickWechatLogin, mouse, people)) {
            return SPORTPAGE;
        }
        char * blankP = " ";
        headDisplay(2, 5, BLACK, DARK_GRAY);
		drawStatus(blankP, blankP, blankP, blankP, blankP);
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

/**
 * �����ϲ�
 *
 * @return
 */
bool getTrue(MOUSE *mouse, PEOPLE *people) {
    return true;
}

//bool quickLogin(MOUSE *mouse, PEOPLE *peopleP, char *loginWay) {
//    char path[35];
//    createLoginPath(loginWay, path);
//    inputPeople(path, PeopleP);
//    return true;
//}


bool quickWechatLogin(MOUSE *mouse, PEOPLE *peopleP) {
    char path[35];
    createLoginPath("wechat", path);
    inputPeople(path, peopleP);
    strcpy(peopleP->name, "17371266527");
    return true;
}

/**********************************************************
Function��		Regist

Description��	�û�ע�ắ��

Input��			MOUSE *mouse 	  ������
				
Output��		ע�ắ����ʹ��

Return��		NONE
				
**********************************************************/
bool Regist(MOUSE *mouse, PEOPLE *people) {
    // �������ڴ洢����
	char *name = (char *) malloc(15);
    // ���ڴ洢����
    char *key = (char *) malloc(15);
    // ���ڼ����û������Ƿ���ȷ
    char *key1 = (char *) malloc(15);
    //���ڴ洢�ļ���
    char *txtname = (char *) malloc(35);
    FILE *fp;
    int state = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    float size = 5.5;
    Regist_draw();
    mouse_reset(mouse);
    //���ذ���
    for (;;)
    {
        // ��ȡ���λ��
        mouse_position(mouse);
        // �������
        drawmouse(mouse);
        // ����û������������û����׿���
        if (mouse->pos_x > 6*size && mouse->pos_y > 40*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 40*size &&
            mouse->button == 1) {
            // ���Է�ֹ˫��
            delay(100);
            // xyΪ�û������Ͻǰ׿�
            // ע��ʧ�ܵ����
            if (Rname(mouse, name, &num1, 15*size, 40*size-36) == false) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
            // ��ֹ���ֻ��ȥ��һȦ��
            if (num1 != 0) {
                // �����ļ�·��
                Create_path(name, txtname);
                // �Ƿ��ڴ����ñ�����Ŀ
                fp = fopen(txtname, "r+");
                if (fp != NULL) {
                    fclose(fp);
                    //readbmp(182,128,"pic\\chongfu.bmp");//��ʾ�û������ظ�,���������û�ע�����
                    mouse_recover(mouse);
                    SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
                    SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
                    dis_24hz(19*size, 327, "�ֻ�����ע��", 0);
                    delay(1500);
                    Regist_draw();
                    mouse_reset(mouse);
                    num1 = 0;
                    num2 = 0;
                    num3 = 0;
                } else {
                    // �û������У��ɹ�
                    fclose(fp);
                }
            }
        } else if (mouse->pos_x > 6*size && mouse->pos_y > 65*size-36 && mouse->pos_x < 62*size&& mouse->pos_y < 65*size &&
                   mouse->button == 1) {
            // ���Է�ֹ˫��
            delay(100);
            // ¼���һ�ε�����
            if (Rkey(mouse, key, &num2, 20*size, 65*size-36) == -1) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
        } else if (mouse->pos_x > 6*size && mouse->pos_y > 90*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 90*size &&
                   mouse->button == 1) {
            // ���Է�ֹ˫��
            delay(100);
            // ¼��ڶ��ε�����
            if (Rkey(mouse, key1, &num3, 20*size, 90*size-36) == -1) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
            // �Ƿ����ñ���key1
        } else if (mouse->pos_x > 2*size && mouse->pos_y > 106*size-5*size && mouse->pos_x < 66*size && mouse->pos_y < 116*size &&
                   mouse->button == 1)
        {
            // ���ע�ᰴť
            // ���Է�ֹ˫��
            delay(100);
            mouse_recover(mouse);
            // ע��ɹ�����������������
            state = R_check(txtname, key, key1);
            mouse_reset(mouse);
            if (state == 1) {
                fp = fopen("txt\\username.txt", "a+");
                fprintf(fp, "%s\n", name);
                fclose(fp);
                // �ͷŶѿռ�
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
                return true;
            } else {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
        } else if (mouse->pos_x > 4*size && mouse->pos_y > 8*size && mouse->pos_x < 6*size && mouse->pos_y < 12*size &&
                   mouse->button == 1) {
            // �������ذ�ť�����˻ص���һ�����
            // ���Է�ֹ˫��
            delay(100);
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
//            Begin_menu(mouse);
            mouse_recover(mouse);
            return false;
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
    SVGA_Line(6*size,40*size,62*size,40*size,LIGHT_GRAY);
    //���������
    dis_24hz(34*size-24*4.5,50*size-12,"������Ҫ���õ�����",BLACK);
    SVGA_Line(6*size,65*size,62*size,65*size,LIGHT_GRAY);
    //���������
    dis_24hz(34*size-24*4.75,75*size-12,"�ٴ�������Ҫ���õ�����",BLACK);
    SVGA_Line(6*size,90*size,62*size,90*size,LIGHT_GRAY);
    //�Ѿ�ע�᣿
    dis_16hz(34*size-16*7.5,124*size-8,"�Ѿ�ע������ˣ�",LIGHT_GRAY);
    dis_16hz(34*size+16*2,124*size-8,"��˵�¼",GREEN);
}


/**********************************************************
Function��

Description��	�û���¼�����������û������û��ļ���

Input��			MOUSE *mouse 	  ������
				PEOPLE *people    �û��ṹ��
				
Output��		NONE

Return��		�������
				
**********************************************************/
bool Login(MOUSE *mouse, PEOPLE *people) {
    char *name = (char *) malloc(15);
    // �������ڴ洢����
    char *key = (char *) malloc(15);
    // ���ڴ洢����
    char *txtname = (char *) malloc(35);
    // ���ڴ洢�ļ���
    FILE *fp;
    int num1 = 0;
    int num2 = 0;
    int state = 0;
    float const size = 5.5;
    //readbmp(182,128,"pic\\Login.bmp");
    Login_draw();
    // �����½����
    mouse_reset(mouse);
    for (;;) {
        mouse_position(mouse);
        // ��ȡ���λ��
        drawmouse(mouse);
        // �������
        // �Ƶ������
        if (mouse->pos_x > 6*size && mouse->pos_y > 47*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 47*size &&
            mouse->button == 1)
        {
            delay(100);
            // ���Է�ֹ˫��
            if (Rname(mouse, name, &num1, 6*size, 41*size-10) == -1) {
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
                    SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
                    SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
                    dis_24hz(19*size, 327, "���ֻ��Ų�����", 0);
                    delay(1500);
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
        } else if (mouse->pos_x > 6*size && mouse->pos_y > 57*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 57*size &&
                   mouse->button == 1) {
            // �����¼��ť��¼
            // ���Է�ֹ˫��
            delay(100);
            if (Rkey(mouse, key, &num2, 6*size, 51*size-10) == -1) {
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
        } else if (mouse->pos_x > 2*size && mouse->pos_y > 65*size && mouse->pos_x < 66*size && mouse->pos_y < 75*size &&
                   mouse->button == 1) {
            // �����¼��ť
            // ���Է�ֹ˫��
            delay(100);
            mouse_recover(mouse);
            state = L_check(people, txtname, key);
            mouse_reset(mouse);
            if (state == 1) {
                mouse_recover(mouse);
                // ��¼�ɹ������ػ�
//                Begin_draw();
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
                return true;
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
                return false;
            } else {
                // �Ծ�ͣ���ڵ�¼����
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
        } else if (mouse->pos_x > 4*size && mouse->pos_y > 8*size && mouse->pos_x < 6*size && mouse->pos_y < 12*size &&
                   mouse->button == 1) {
            // ���Է�ֹ˫��
            delay(100);
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
            return false;
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
    // ���ڴ洢��ȷ������
    char *key = (char *) malloc(15);
    char ac;
    float size = 5.5;
    fp = fopen(txtname, "r+");
    if (fp == NULL) {
        //readbmp(182,128,"pic\\notexist.bmp");//��ʾ�û���������
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "���ֻ��Ų�����", 0);
        delay(1500);
        // ������ΪʲôҪ�ͷ�һ��
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
    fscanf(fp, "%s\n", key);
    if (strcmp(key, key1) == 0) {
        // ��������ȷ����������˵�����
        fclose(fp);
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
        // ����������д����
        if (fgetc(fp) == EOF) {
            fclose(fp);
            //readbmp(182,128,"pic\\black.bmp");//��ʾ�û��Ѿ���������������˳���������
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "���ں�������", 0);
            delay(1500);
            //Begin_menu(mouse);
            if (key != NULL) {
                free(key);
                key = NULL;
            }
            return 2;
        }
        fclose(fp);
        //readbmp(182,128,"pic\\erro.bmp");//�����벻���ڣ�����ʾ�������
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "���������������", 0);
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

Output��		��ʾ����Ա��¼״̬������������

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
Function��		Rkey

Description��	���ڶ�ȡ�û��ڵ�¼ע��ʱ���������

Input��			char *        �����洢������ַ���
				int x             �ı���ĺ�����
				int y			  �ı����������

Output��		�û�������ַ�

Return��		����״̬���к�

**********************************************************/
int Rkey(MOUSE *mouse, char *data, int *number, int x, int y) {
    // ���ڴ洢����ļ�ֵ����ʾ
    char ac;
    int num = *number;
    int pos = x + 2 + num * 20;
    float size = 5.5;
    // �������
    mouse_recover(mouse);
    dis_16hz(pos, y + 9, "������������λ������", 0);
    delay(500);
    // bioskey(1)��ѯ�Ƿ���һ�����������£��򷵻ط���ֵ
    while (bioskey(1))
    {
        getch();
    }
    SVGA_Bar(pos, y + 2, pos + 200, y + 30, -1);
    // ��ʾ���
    SVGA_Straight(pos + 2, y + 9, 16, 0);
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9')) || (ac >= 'a') && (ac <= 'z')) {
            // ��ס֮ǰ�Ĺ��
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num++] = ac;
            // ʹ��outtext����ַ���ԭ��
            SVGA_Ball(pos + 10, y + 15, 5, 0);
            // ���������20��Ϊ��һ���������
            pos = pos + 20;
            // ����һ�����
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        } else if (((ac == 127) || (ac == 8)) && (num > 0)) {
            // ����del����backspace����ɾ���ַ�
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num] = 0;
            num--;
            // �������ȥ20��Ϊ��һ���ַ�������
            pos = pos - 20;
            // ����ɫ�����ڸ�ס֮ǰ���ַ�
            SVGA_Bar(pos, y + 5, pos + 19, y + 30, -1);
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 8) {
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "����λ������", 0);
            //readbmp(182,128,"pic\\too.bmp");
            // ��ʾ����λ������
            delay(1500);
            return -1;
        }
    }
    // ��ס���еĹ��
    SVGA_Straight(pos + 2, y + 9, 16, -1);
    // �������
    mouse_reset(mouse);
    // ���һλ������ֹ��������fscan��ȡ
    data[num] = '\0';
    // ����������λ�����ص���������
    number[0] = num;
    if (num < 4) {
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "����λ������", 0);
        //readbmp(182,128,"pic\\too.bmp");
        // ��ʾ����λ������
        delay(500);
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
bool Rname(MOUSE *mouse, char *data, int *number, int x, int y) {
    // ���ڴ洢����ļ�ֵ����ʾ
    char ac;
    // ���ڴ洢�����ַ����Ҵ���ͼ��ģʽ���ı�����������ַ�����
    char str[2];
    // number��num1�ĵ�ַ,
    int num = *number;
    int pos = x + 2 + num * 20;
    float size = 5.5;
    str[1] = '\0';
    // �������
    mouse_recover(mouse);
    dis_16hz(pos, y + 9, "������11λ�ֻ���", 0);
    delay(500);
    // bioskey(1)��ѯ�Ƿ���һ�����������£��򷵻ط���ֵ
    while (bioskey(1)) {
        getch();
    }
    SVGA_Bar(pos, y + 9, pos + 200, y + 30, -1);
    // �����
    SVGA_Straight(pos + 2, y + 9, 16, 0);
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9'))) {
            // ��ס֮ǰ�Ĺ��
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            // num��dataָ���±�
            data[num++] = ac;
            str[0] = ac;
            // ʹ����ģ����ַ���ԭ��
            dis_16zf(pos, y + 9, str, 0);
            // ���������20��Ϊ��һ���������
            pos = pos + 20;
            SVGA_Straight(pos + 2, y + 9, 16, 0);//�����
        } else if (((ac == 127) || (ac == 8)) && (num > 0)) {
            // ����del����backspace����ɾ���ַ�
            // ��ס���Ĺ��
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num] = 0;
            num--;
            // �������ȥ20��Ϊ��һ���ַ�������
            pos = pos - 20;
            // ����ɫ�����ڸ�ס֮ǰ���ַ�
            SVGA_Bar(pos, y, pos + 20, y + 30, -1);
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 11) {
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "�ֻ���λ������", 0);
            //readbmp(182,128,"pic\\too.bmp");//��ʾ����λ������
            delay(1500);
            return false;
        }
    }
    SVGA_Straight(pos + 2, y + 9, 16, -1);
    //�������
    mouse_reset(mouse);
    //���һλ������ֹ��������fscan��ȡ
    data[num] = '\0';
    //����������λ�����ص���������
    number[0] = num;
    if (num < 4) {
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "�ֻ���λ������", 0);
        //readbmp(182,128,"pic\\too.bmp");//��ʾ����λ������
        delay(1500);
        return false;
    }
    return true;
}

/**********************************************************
Function��		InitPeople

Description��	���ڶ�ȡ���û�����Ϣ������people

Input��		    PEOPLE *people    �û��ṹ��

Output��		�õ��û���Ϣ��people

Return��		NULL

**********************************************************/
void InitPeople(PEOPLE* people){
    int flag=0;
    int temp;
    people->exeTimes=0;
    people->runLen=0;
    people->walkLen=0;
    people->rideLen=0;
    int year, mon, day, hour, min;
    char s[10];
    char key[2];
    char mT[3];
    char sT[3];
    char zS[3];
    char pS[3];
    char zV[3];
    char pV[3];
    FILE *fp = fopen(people->txtname, "r+");
    for(int i=0;i<11;i++) //�������룬ѭ��10�ε���ʼ��������ѭ��11��
        fscanf(fp, "%s", s);
    while (1) {
        if (GetData(fp, key, zS, pS, mT, sT, zV, pV, year, mon, day, hour, min)) {
            people->exeTimes++;
            if(key[0]=='#') {
                temp=atoi(zS) * 1000 + atoi(pS) * 10;
                people->runLen += temp;
                flag=1;
            }
            else if(key[0]=='*'){
                temp=atoi(zS) * 1000 + atoi(pS) * 10;
                people->walkLen += temp;
                flag=2;
            }
            else if(key[0]=='&'){
                temp=atoi(zS) * 1000 + atoi(pS) * 10;
                people->rideLen += temp;
                flag=3;
            }
        }
        else {
            break;
        }
    }
    fclose(fp);
    if(flag==1)
        people->runLen -= temp;
    else if(flag==2)
        people->walkLen -= temp;
    else if(flag==3)
        people->rideLen -= temp;
    people->exeTimes--;
}
