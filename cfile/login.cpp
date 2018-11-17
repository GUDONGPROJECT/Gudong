/**********************************************************
Copyright (C) 2017 .
File name:		regist.c
Author:
Description：	用于用户的登录注册

Function List：
	1.void Begin(MOUSE * mouse)
	登录注册界面所有的返回值，函数调用，信息整理
	2.int Begin_menu(MOUSE*mouse,PEOPLE*people);
	开始界面的操作
	3.void Begin_draw(void)
	开始界面的图像
	4.void Regist(MOUSE *mouse,PEOPLE *people);
	注册界面的鼠标操作
	5.void Regist_draw(void)
	画注册界面图像
	6.int R_check(MOUSE *mouse,PEOPLE *people,char *txtname,char * key, char *key1);
	检查注册时用户名等是否符合要求，提示用户进行下一步操作
	7.int Login(MOUSE *mouse,PEOPLE *people);
	登录界面的鼠标操作
	8.void Login_draw(void)
	画登录界面
	9.int L_check(MOUSE *mouse,PEOPLE *people,char *txtname, char *key1);
	检查密码是否正确，用户是否进入黑名单
	10.int registLogin(MOUSE *mouse,PEOPLE *people);
	管理员登录界面的鼠标操作
	11.void registLogin_draw(void)
	画管理员登录界面
	12.int RL_check(MOUSE *mouse,PEOPLE *people,char *txtname, char *key1);
	管理员密码检查
	13.int Rname(MOUSE *mouse,PEOPLE *people,char *data,int *number,int x,int y);
	记录用户名并在屏幕上显示，不得超过八位
	14.int Rkey(MOUSE *mouse,char *data,int *number,int x,int y);
	记录用户密码并在屏幕上显示，不得超过八位
	15.void Create_path (char *name,char *textname);
	生成文件路径
	16.void flash(void)
	开机动画
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
Function：		Begin

Description：	登录注册界面所有的返回值，函数调用，信息整理

Input：			MOUSE *mouse 	  鼠标变量
				
Output：		调用下一级函数

Return：		NONE
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

            // 断点调试用
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
Function：		Begin_draw

Description：	画开始界面

Input：			NONE
				
Output：		开始界面

Return：		NONE
**********************************************************/
void Begin_draw(void) {
    float size=5.5;
    SVGA_Bar(0,0,68*size,140*size,DARK_GRAY);
    //setcolor(GREEN);
    //画微信绿色按钮
    CircleBar(7*size,102*size,61*size,102*size,5*size,GREEN);
    dis_16hz(34*size-16,102*size-8,"微信",WHITE);
    //画微博、QQ灰色按钮
    CircleBar(7*size,115*size,61*size,115*size,5*size,LIGHT_GRAY);
    dis_16hz(34*size-16*7,115*size-8,"微博",WHITE);
    SVGA_Line(34*size,112*size,34*size,118*size,WHITE);
    dis_16zf(34*size+16*5,115*size-8,"QQ",WHITE);
    //画手机号|邮箱登录
    dis_16hz(16*size-16*4,126*size-8,"手机号",WHITE);
    SVGA_Line(16*size,126*size-8,16*size,126*size+8,WHITE);
    dis_16hz(16*size+8,126*size-8,"邮箱登录",WHITE);
    //画手机号注册
    dis_16hz(53*size-40,126*size-8,"手机号注册",WHITE);
    //协议
    dis_16hz(3*size,134*size-8,"注册或登录即同意",WHITE);
    //画左上角返回按钮
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    drawMap();
}

/**
 * mouseDetector 侦测鼠标范围
 *
 * @param lx 左上角横坐标
 * @param ly 左上角纵坐标
 * @param rx 右下角横坐标
 * @param ry 右下角纵坐标
 * @param color 颜色
 * @param fun 传入函数
 * @param
 */

bool mouseDetector(int lx, int ly, int rx, int ry, int color, bool (*fun) (MOUSE *, PEOPLE *), MOUSE *mouse, PEOPLE *people) {
    bool isClicked = false;
    if (mouse->pos_x > lx && mouse->pos_y > ly && mouse->pos_x < rx && mouse->pos_y < ry) {
        mouse_recover(mouse);  //将箭头鼠标屏蔽
        SVGA_Rectangular(lx, ly, rx, ry, color);     //在相应位置画蓝框
        mouse_reset(mouse);     //重新显示箭头鼠标
        while (true) {
            mouse_position(mouse);
            drawmouse(mouse);
            //点击鼠标则进入相关函数
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
                mouse_recover(mouse);  //将箭头鼠标屏蔽
                SVGA_Rectangular(lx, ly, rx, ry, DARK_GRAY);      //在相应位置画白框覆盖蓝框
                mouse_reset(mouse);     //重新显示箭头鼠标
                break;
            }
        }
    }
    return false;
}

/**********************************************************
Function：		Begin——menu

Description：	用于从开始界面选择功能

Input：			MOUSE *mouse 	  鼠标变量
				
Output：		NONE

Return：		功能序号
**********************************************************/
State Begin_menu(MOUSE *mouse, PEOPLE *people) {
    Begin_draw();
    mouse_reset(mouse);//重置鼠标
    while (1) {
        mouse_position(mouse);//获取鼠标位置
        drawmouse(mouse);//绘制鼠标
        float size = 5.5;
        // 用户注册
        if (mouseDetector(53*size-40,126*size-9, 53*size-40+16*5+4*4, 126*size-8+16, WHITE, Regist, mouse, people)) {
            return UNDEFINED;
        }
        // 用户登录
        if (mouseDetector(16*size-16*4,126*size-9, 16*size-16*4+16*3+4*2,126*size-8+16, WHITE, Login, mouse, people)) {
            return SPORTPAGE;
        }
        // 返回
        if (mouseDetector(4*size, 8*size, 6*size, 12*size, WHITE, getTrue, mouse, people)) {
            return BACK;
        }
        // 微信登录
        if (mouseDetector(2 * size, 97 * size, 66 * size, 107 * size, WHITE, quickWechatLogin, mouse, people)) {
            return SPORTPAGE;
        }
        char * blankP = " ";
        headDisplay(2, 5, BLACK, DARK_GRAY);
		drawStatus(blankP, blankP, blankP, blankP, blankP);
    }
}

void flash(void) {
    int i = 0;//左右向中间
    for (i = 0; i < 10; i++) {
        PartBmp(0, 768, 0, 824 + 20 * i, 0, 0, "pic\\pic4.bmp");
    }
    delay(500);
    for (i = 0; i < 10; i++) {
        PartBmp(0, 768, 0, 412 + 12 * i, 0, 0, "pic\\pic1.bmp");
        PartBmp(0, 768, 612 - 12 * i, 1024, 612 - 12 * i, 0, "pic\\pic1.bmp");
    }
    delay(500);
//前后向中间
    for (i = 0; i < 10; i++) {
        PartBmp(0, 284 + 12 * i, 0, 1024, 0, 0, "pic\\pic2.bmp");
        PartBmp(484 - 12 * i, 768, 0, 1024, 0, 484 - 12 * i, "pic\\pic2.bmp");
    }
    delay(500);
//该循环用于从中间往外读图
    for (i = 0; i <= 20; i++) {
        PartBmp(340 - 17 * i, 428 + 17 * i, 280 - 14 * i, 744 + 14 * i, 280 - 14 * i, 340 - 17 * i, "pic\\pic3.bmp");
    }
    delay(700);
}

/**
 * 返回上层
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
Function：		Regist

Description：	用户注册函数

Input：			MOUSE *mouse 	  鼠标变量
				
Output：		注册函数的使用

Return：		NONE
				
**********************************************************/
bool Regist(MOUSE *mouse, PEOPLE *people) {
    // 定义用于存储姓名
	char *name = (char *) malloc(15);
    // 用于存储密码
    char *key = (char *) malloc(15);
    // 用于检验用户密码是否正确
    char *key1 = (char *) malloc(15);
    //用于存储文件名
    char *txtname = (char *) malloc(35);
    FILE *fp;
    int state = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    float size = 5.5;
    Regist_draw();
    mouse_reset(mouse);
    //来回按键
    for (;;)
    {
        // 获取鼠标位置
        mouse_position(mouse);
        // 绘制鼠标
        drawmouse(mouse);
        // 如果用户将鼠标放置在用户名白框内
        if (mouse->pos_x > 6*size && mouse->pos_y > 40*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 40*size &&
            mouse->button == 1) {
            // 可以防止双击
            delay(100);
            // xy为用户名左上角白框
            // 注册失败的情况
            if (Rname(mouse, name, &num1, 15*size, 40*size-36) == false) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
            // 防止鼠标只是去晃一圈的
            if (num1 != 0) {
                // 生成文件路径
                Create_path(name, txtname);
                // 是否在此设置报错项目
                fp = fopen(txtname, "r+");
                if (fp != NULL) {
                    fclose(fp);
                    //readbmp(182,128,"pic\\chongfu.bmp");//提示用户名有重复,重新载入用户注册界面
                    mouse_recover(mouse);
                    SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
                    SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
                    dis_24hz(19*size, 327, "手机号已注册", 0);
                    delay(1500);
                    Regist_draw();
                    mouse_reset(mouse);
                    num1 = 0;
                    num2 = 0;
                    num3 = 0;
                } else {
                    // 用户名检测校验成功
                    fclose(fp);
                }
            }
        } else if (mouse->pos_x > 6*size && mouse->pos_y > 65*size-36 && mouse->pos_x < 62*size&& mouse->pos_y < 65*size &&
                   mouse->button == 1) {
            // 可以防止双击
            delay(100);
            // 录入第一次的密码
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
            // 可以防止双击
            delay(100);
            // 录入第二次的密码
            if (Rkey(mouse, key1, &num3, 20*size, 90*size-36) == -1) {
                mouse_recover(mouse);
                Regist_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
                num3 = 0;
            }
            // 是否设置报错，key1
        } else if (mouse->pos_x > 2*size && mouse->pos_y > 106*size-5*size && mouse->pos_x < 66*size && mouse->pos_y < 116*size &&
                   mouse->button == 1)
        {
            // 点击注册按钮
            // 可以防止双击
            delay(100);
            mouse_recover(mouse);
            // 注册成功，则函数返回主界面
            state = R_check(txtname, key, key1);
            mouse_reset(mouse);
            if (state == 1) {
                fp = fopen("txt\\username.txt", "a+");
                fprintf(fp, "%s\n", name);
                fclose(fp);
                // 释放堆空间
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
            // 按到返回按钮，则退回到上一层界面
            // 可以防止双击
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
Function：		Regist_draw

Description：	画注册界面

Input：			NONE
				
Output：		注册界面

Return：		NONE
				
**********************************************************/
void Regist_draw(void) {
    float size=5.5;
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //画左上角返回按钮
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    //画注册按钮
    CircleBar(7*size,111*size,61*size,111*size,5*size,DARK_GRAY);
    dis_16hz(34*size-16*1,111*size-8,"注册",WHITE);
    //输入手机号框
    dis_24hz(34*size-24*3.5,25*size-12,"输入你的手机号",BLACK);
    SVGA_Line(6*size,40*size,62*size,40*size,LIGHT_GRAY);
    //输入密码框
    dis_24hz(34*size-24*4.5,50*size-12,"输入你要设置的密码",BLACK);
    SVGA_Line(6*size,65*size,62*size,65*size,LIGHT_GRAY);
    //输入密码框
    dis_24hz(34*size-24*4.75,75*size-12,"再次输入你要设置的密码",BLACK);
    SVGA_Line(6*size,90*size,62*size,90*size,LIGHT_GRAY);
    //已经注册？
    dis_16hz(34*size-16*7.5,124*size-8,"已经注册过咕咚？",LIGHT_GRAY);
    dis_16hz(34*size+16*2,124*size-8,"点此登录",GREEN);
}


/**********************************************************
Function：

Description：	用户登录函数，保存用户名，用户文件名

Input：			MOUSE *mouse 	  鼠标变量
				PEOPLE *people    用户结构体
				
Output：		NONE

Return：		功能序号
				
**********************************************************/
bool Login(MOUSE *mouse, PEOPLE *people) {
    char *name = (char *) malloc(15);
    // 定义用于存储姓名
    char *key = (char *) malloc(15);
    // 用于存储密码
    char *txtname = (char *) malloc(35);
    // 用于存储文件名
    FILE *fp;
    int num1 = 0;
    int num2 = 0;
    int state = 0;
    float const size = 5.5;
    //readbmp(182,128,"pic\\Login.bmp");
    Login_draw();
    // 载入登陆界面
    mouse_reset(mouse);
    for (;;) {
        mouse_position(mouse);
        // 获取鼠标位置
        drawmouse(mouse);
        // 绘制鼠标
        // 移到鼠标区
        if (mouse->pos_x > 6*size && mouse->pos_y > 47*size-36 && mouse->pos_x < 62*size && mouse->pos_y < 47*size &&
            mouse->button == 1)
        {
            delay(100);
            // 可以防止双击
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
                    //readbmp(182,128,"pic\\notexist.bmp");//提示用户名不存在
                    mouse_recover(mouse);
                    SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
                    SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
                    dis_24hz(19*size, 327, "该手机号不存在", 0);
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
            // 点击登录按钮登录
            // 可以防止双击
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
            // 点击登录按钮
            // 可以防止双击
            delay(100);
            mouse_recover(mouse);
            state = L_check(people, txtname, key);
            mouse_reset(mouse);
            if (state == 1) {
                mouse_recover(mouse);
                // 登录成功无需重绘
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
                // 仍旧停留在登录界面
                mouse_recover(mouse);
                Login_draw();
                mouse_reset(mouse);
                num1 = 0;
                num2 = 0;
            }
        } else if (mouse->pos_x > 4*size && mouse->pos_y > 8*size && mouse->pos_x < 6*size && mouse->pos_y < 12*size &&
                   mouse->button == 1) {
            // 可以防止双击
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
Function：		Login_draw

Description：	画登录界面

Input：			NONE
				
Output：		登录界面

Return：		NONE
				
**********************************************************/
void Login_draw(void) {
    float size = 5.5;
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Line(6 * size, 8 * size, 4 * size, 10 * size, BLACK);
    //画左上角返回按钮
    SVGA_Line(6 * size, 12 * size, 4 * size, 10 * size, BLACK);
    //手机登录
    dis_24hz(6 * size, 18 * size, "手机登录", BLACK);
    //账号输入框
    SVGA_Line(6 * size, 47 * size, 62 * size, 47 * size, LIGHT_GRAY);
    dis_16hz(6 * size, 41 * size, "手机号", LIGHT_GRAY);
    //密码输入框
    SVGA_Line(6 * size, 57 * size, 62 * size, 57 * size, LIGHT_GRAY);
    dis_16hz(6 * size, 51 * size, "密码", LIGHT_GRAY);
    //登录按钮
    CircleBar(7 * size, 70 * size, 61 * size, 70 * size, 5 * size, DARK_GRAY);
    dis_16hz(34 * size - 16 * 1, 70 * size - 8, "登录", WHITE);
}

/**********************************************************
Function：		L_check

Description：	用于检测用户用户名是否存在，密码是否正确的函数，提示下一步操作

Input：			PEOPLE *people    用户结构体
				char *txtname     用来存储用户的文件名地址
				char *key1        用户第二次输入的密码
				
Output：		提示用户登录状态，进入主界面

Return：		用户登录状态序列号
				
**********************************************************/
int L_check(PEOPLE *people, char *txtname, char *key1) {
    FILE *fp;
    // 用于存储正确的密码
    char *key = (char *) malloc(15);
    char ac;
    float size = 5.5;
    fp = fopen(txtname, "r+");
    if (fp == NULL) {
        //readbmp(182,128,"pic\\notexist.bmp");//提示用户名不存在
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "该手机号不存在", 0);
        delay(1500);
        // 不明白为什么要释放一次
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
    fscanf(fp, "%s\n", key);
    if (strcmp(key, key1) == 0) {
        // 若密码正确，则进入主菜单界面
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
        // 黑名单可以写在这
        if (fgetc(fp) == EOF) {
            fclose(fp);
            //readbmp(182,128,"pic\\black.bmp");//提示用户已经被加入黑名单，退出到主界面
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "您在黑名单上", 0);
            delay(1500);
            //Begin_menu(mouse);
            if (key != NULL) {
                free(key);
                key = NULL;
            }
            return 2;
        }
        fclose(fp);
        //readbmp(182,128,"pic\\erro.bmp");//若密码不存在，则提示密码错误
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "您输入的密码有误", 0);
        delay(700);
        //Login(mouse,people);//回到登录函数
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
}

/**********************************************************
Function：		registLogin

Description：	管理员登录函数

Input：			MOUSE *mouse 	  鼠标变量
				PEOPLE *people    用户结构体
				
Output：		登录界面

Return：		NONE
				
**********************************************************/

void registLogin_draw(void) {
    SVGA_Bar(182, 128, 749, 551, 0x000EFF);
    SVGA_Bar(245, 443, 352, 487, 0x7FFF0E);
    SVGA_Bar(578, 443, 687, 487, 0x7FFF0E);
    SVGA_Bar(352, 317, 686, 355, -1);
    dis_24hz(405, 191, "管理员登录", 0);
    dis_16hz(246, 318, "密码：", 0);
    dis_16hz(278, 454, "登录", 0);
    dis_16hz(607, 452, "退出", 0);
}

int registLogin(MOUSE *mouse) {
    char *key1 = (char *) malloc(15);//用于存储密码
    int num = 0;
    int state = 0;
    FILE *fp;
// readbmp(182,128,"pic\\register.bmp");//载入登陆界面
    registLogin_draw();
    mouse_reset(mouse);//重置鼠标
    for (;;) {
        mouse_position(mouse);//获取鼠标位置
        drawmouse(mouse);//绘制鼠标

        if (mouse->pos_x > 352 && mouse->pos_y > 317 && mouse->pos_x < 686 && mouse->pos_y < 383 &&
            mouse->button == 1)//点击登录按钮登录
        {
            delay(100);//可以防止双击
            if (Rkey(mouse, key1, &num, 352, 317) == -1) {
                mouse_recover(mouse);
                registLogin_draw();
                mouse_reset(mouse);
                num = 0;
            }
        } else if (mouse->pos_x > 245 && mouse->pos_y > 443 && mouse->pos_x < 352 && mouse->pos_y < 487 &&
                   mouse->button == 1)//点击登录按钮
        {
            delay(100);//可以防止双击
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
                   mouse->button == 1)//点击退出
        {
            delay(100);//可以防止双击
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
Function：		RL_check

Description：	用于检测管理员密码是否正确的函数

Input：			MOUSE *mouse 	  鼠标变量
				PEOPLE *people    用户结构体
				char *txtname     用来存储用户的文件名地址
				char *key         用户第一次输入的密码
				char *key1        用户第二次输入的密码

Output：		提示管理员登录状态，进入管理界面

Return：		NONE

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
        fclose(fp);//若密码正确，则进入主菜单界面
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
        //readbmp(182,128,"pic\\erro.bmp");//若密码不存在，则提示密码错误
        SVGA_Bar(182, 128, 749, 551, 0x000EFF);
        dis_24hz(393, 327, "您的密码错误", 0);
        delay(700);
        if (key != NULL) {
            free(key);
            key = NULL;
        }
        return 0;
    }
}

/**********************************************************
Function：		Rkey

Description：	用于读取用户在登录注册时输入的密码

Input：			char *        用来存储输入的字符串
				int x             文本框的横坐标
				int y			  文本框的纵坐标

Output：		用户输入的字符

Return：		输入状态序列号

**********************************************************/
int Rkey(MOUSE *mouse, char *data, int *number, int x, int y) {
    // 用于存储输入的键值并显示
    char ac;
    int num = *number;
    int pos = x + 2 + num * 20;
    float size = 5.5;
    // 屏蔽鼠标
    mouse_recover(mouse);
    dis_16hz(pos, y + 9, "请输入四至八位的密码", 0);
    delay(500);
    // bioskey(1)查询是否按下一个键，若按下，则返回非零值
    while (bioskey(1))
    {
        getch();
    }
    SVGA_Bar(pos, y + 2, pos + 200, y + 30, -1);
    // 显示光标
    SVGA_Straight(pos + 2, y + 9, 16, 0);
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9')) || (ac >= 'a') && (ac <= 'z')) {
            // 遮住之前的光标
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num++] = ac;
            // 使用outtext输出字符到原点
            SVGA_Ball(pos + 10, y + 15, 5, 0);
            // 横坐标加上20作为下一个点的坐标
            pos = pos + 20;
            // 画下一个光标
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        } else if (((ac == 127) || (ac == 8)) && (num > 0)) {
            // 按下del键，backspace，则删除字符
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num] = 0;
            num--;
            // 横坐标减去20作为下一个字符的坐标
            pos = pos - 20;
            // 画白色矩形掩盖住之前的字符
            SVGA_Bar(pos, y + 5, pos + 19, y + 30, -1);
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 8) {
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "密码位数过多", 0);
            //readbmp(182,128,"pic\\too.bmp");
            // 提示密码位数过多
            delay(1500);
            return -1;
        }
    }
    // 遮住所有的光标
    SVGA_Straight(pos + 2, y + 9, 16, -1);
    // 重置鼠标
    mouse_reset(mouse);
    // 最后一位放上终止符，方便fscan读取
    data[num] = '\0';
    // 将最后的密码位数传回到主函数中
    number[0] = num;
    if (num < 4) {
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "密码位数过多", 0);
        //readbmp(182,128,"pic\\too.bmp");
        // 提示密码位数过多
        delay(500);
        return -1;
    }
    return 1;
}

/**********************************************************
Function：		Rname

Description：	用于读取并显示用户在登录注册时输入的用户名

Input：			MOUSE *mouse 	  鼠标变量
				PEOPLE *people    用户结构体
				char *data        用来存储输入的字符串
				int x             文本框的横坐标
				int y			  文本框的纵坐标

Output：		用户输入的用户名

Return：		输入状态序列号

**********************************************************/
bool Rname(MOUSE *mouse, char *data, int *number, int x, int y) {
    // 用于存储输入的键值并显示
    char ac;
    // 用于存储输入字符并且传给图形模式下文本输出函数（字符串）
    char str[2];
    // number是num1的地址,
    int num = *number;
    int pos = x + 2 + num * 20;
    float size = 5.5;
    str[1] = '\0';
    // 屏蔽鼠标
    mouse_recover(mouse);
    dis_16hz(pos, y + 9, "请输入11位手机号", 0);
    delay(500);
    // bioskey(1)查询是否按下一个键，若按下，则返回非零值
    while (bioskey(1)) {
        getch();
    }
    SVGA_Bar(pos, y + 9, pos + 200, y + 30, -1);
    // 画光标
    SVGA_Straight(pos + 2, y + 9, 16, 0);
    while ((ac = getch()) != 13) {
        if (((ac >= '0') && (ac <= '9'))) {
            // 遮住之前的光标
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            // num是data指的下标
            data[num++] = ac;
            str[0] = ac;
            // 使用字模输出字符到原点
            dis_16zf(pos, y + 9, str, 0);
            // 横坐标加上20作为下一个点的坐标
            pos = pos + 20;
            SVGA_Straight(pos + 2, y + 9, 16, 0);//画光标
        } else if (((ac == 127) || (ac == 8)) && (num > 0)) {
            // 按下del键，backspace，则删除字符
            // 遮住画的光标
            SVGA_Straight(pos + 2, y + 9, 16, -1);
            data[num] = 0;
            num--;
            // 横坐标减去20作为下一个字符的坐标
            pos = pos - 20;
            // 画白色矩形掩盖住之前的字符
            SVGA_Bar(pos, y, pos + 20, y + 30, -1);
            SVGA_Straight(pos + 2, y + 9, 16, 0);
        }
        if (num > 11) {
            SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
            SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
            dis_24hz(19*size, 327, "手机号位数过多", 0);
            //readbmp(182,128,"pic\\too.bmp");//提示密码位数过多
            delay(1500);
            return false;
        }
    }
    SVGA_Straight(pos + 2, y + 9, 16, -1);
    //重置鼠标
    mouse_reset(mouse);
    //最后一位放上终止符，方便fscan读取
    data[num] = '\0';
    //将最后的密码位数传回到主函数中
    number[0] = num;
    if (num < 4) {
        SVGA_Bar(6*size, 228, 62*size, 451, DARK_GRAY);
        SVGA_Bar(6*size+2, 228+2, 62*size-2, 451-2, LIGHT_GRAY);
        dis_24hz(19*size, 327, "手机号位数过少", 0);
        //readbmp(182,128,"pic\\too.bmp");//提示密码位数过多
        delay(1500);
        return false;
    }
    return true;
}

/**********************************************************
Function：		InitPeople

Description：	用于读取并用户的信息并存入people

Input：		    PEOPLE *people    用户结构体

Output：		得到用户信息的people

Return：		NULL

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
    for(int i=0;i<11;i++) //不含密码，循环10次到开始，含密码循环11次
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
