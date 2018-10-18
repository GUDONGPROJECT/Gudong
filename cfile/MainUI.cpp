#include "./header/MainUI.h"
State SportMain(MOUSE *mouse,PEOPLE *people) {
    Sport state = RUN;
    float size = 5.5;
    mouse_reset(mouse);//重置鼠标
    while (1) {
        //当位于跑步界面时
        if (state == RUN) {
            Draw_Sport_Run();
            mouse_position(mouse);  //获取鼠标位置
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //保存鼠标将覆盖区域
                mouse_show(mouse);      //画出鼠标
            //}
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //是否点击健走
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = WALK;
                        break;
                    }
                    //是否点击骑行
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = RIDE;
                        break;
                    }
                    //是否点击GO
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
                    //跳转至开始跑步的界面
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
            }
        }
        //当位于健走界面时
        if (state == WALK) {
            Draw_Sport_Walk();
            mouse_position(mouse);//获取鼠标位置
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //保存鼠标将覆盖区域
                mouse_show(mouse);      //画出鼠标
            //}
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //是否点击跑步
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RUN;
                        break;
                    }
                    //是否点击骑行
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = RIDE;
                        break;
                    }
                    //是否点击GO
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
                    //跳转至开始健走的界面
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
            }
        }
        //当位于骑行界面时
        if (state == RIDE) {
            Draw_Sport_Ride();
            mouse_position(mouse);//获取鼠标位置
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
                mouse_copy(mouse);      //保存鼠标将覆盖区域
                mouse_show(mouse);      //画出鼠标
            //}
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //当点击跑步时
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RUN;
                        break;
                    }
                    //当点击健走时
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = WALK;
                        break;
                    }
                    //是否点击GO按钮
                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
                        mouse->pos_x > 11 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
                        mouse->pos_y < 28 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
                    //进入开始骑行界面
                    //是否点击共享单车按钮
                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
                        mouse->pos_x > 40 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
                        mouse->pos_y < 57 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
                    //进入开始骑行界面
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * size && mouse->pos_y < 140 * size) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * size)
                            return MINE;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
            }
        }
        //当点击鼠标
        /*if(mouse->button == 1) {
            //当鼠标点击区域为下方5栏
            if( mouse->pos_y > 130 * size && mouse->pos_y < 140 * size){
                //当点击运动圈
                if(mouse->pos_x<14.5*size)
                    return CIRCLE;
                //当点击发现
                if(mouse->pos_x<27.5*size &&mouse->pos_x>14.5*size)
                    return FIND;
                //当点击干货
                if(mouse->pos_x>40.5*size&&mouse->pos_x<53.5*size)
                    return THINGS;
                //当点击我的
                if(mouse->pox_x>53.5*size)
                    return MINE;
            }*/
    }
}
/**********************************************************
Function：		Draw_Sport_Run

Description：	画跑步的主界面

Input：			NONE

Output：		跑步主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Run(void) {
    float size = 5.5;
    int i;          //循环变量
    char *s = "0.02"; //跑步总公里
    //画上下的绿白背景
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //画天气显示
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //画4个选项
    dis_16hz(5 * size, 21 * size, "跑步", GREEN);
    SVGA_Line(5*size,26*size,5*size+32,26*size,GREEN);
    SVGA_Line(5*size,26*size-1,5*size+32,26*size-1,GREEN);
    dis_16hz(16 * size, 21 * size, "健走", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"骑行", LIGHT_GRAY );
    //跑步总公里
    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
    dis_24hz(34 * size - 12 * 5, 50 * size, "运动总公里", BLACK);
    //GO按钮
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //底部5个按钮
    SVGA_Bar(0, 130 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Draw_Sport_Walk

Description：	画健走的主界面

Input：			NONE

Output：		健走主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Walk(void) {
    float size = 5.5;
    int i;          //循环变量
    char *s = "0.02"; //跑步总公里
    //画上下的绿白背景
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //画天气显示
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //画4个选项
    dis_16hz(5 * size, 21 * size, "跑步", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "健走", GREEN);
    SVGA_Line(16 * size, 26 * size, 16 * size + 32, 26 * size, GREEN);
    SVGA_Line(16 * size, 26 * size - 1, 16 * size + 32, 26 * size - 1, GREEN);
    dis_16hz(27 * size, 21 * size,"骑行", LIGHT_GRAY );
    //健走总公里
    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
    dis_24hz(34 * size - 12 * 5, 50 * size, "健走总公里", BLACK);
    //GO按钮
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //底部5个按钮
    SVGA_Bar(0, 130 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Draw_Sport_Walk

Description：	画骑行的主界面

Input：			NONE

Output：		骑行主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Ride(void) {
    float size = 5.5;
    int i;          //循环变量
    char *s = "0.02"; //跑步总公里
    //画上下的绿白背景
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    SVGA_Bar(0, 0, 68 * size, 18 * size, GREEN);
    //画天气显示
    SVGA_Cricle(6 * size, 11 * size, 1 * size, WHITE);
    for (i = 1; i <= 8; i++) {
        double t = 2 * PI * i / 8;
        SVGA_Line(6 * size + 2 * size * cos(t), 11 * size - 2 * size * sin(t), 6 * size + 3 * size * cos(t),
                  11 * size - 3 * size * sin(t), WHITE);
    }
    //画4个选项
    dis_16hz(5 * size, 21 * size, "跑步", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "健走", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"骑行", GREEN);
    SVGA_Line(27*size,26*size,27*size+32,26*size,GREEN);
    SVGA_Line(27*size,26*size-1,27*size+32,26*size-1,GREEN);
    //骑行总公里
    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
    dis_24hz(34 * size - 12 * 5, 50 * size, "骑行总公里", BLACK);
    //GO按钮
    CircleBar( 11 * size, 98 * size, 28 * size, 98 * size, 5*size, GREEN);
    dis_24zf(19.5 * size - 24, 98 * size - 12, "GO", WHITE);
    //共享单车按钮 dis_24zf(48.5 * size - 24*2, 98 * size - 12, , WHITE);
    CircleBar( 40 * size, 98 * size, 57 * size, 98 * size, 5*size, GREEN);
    dis_24zf(48.5*size-24*2,98*size-12,"共享单车",WHITE);      //ERROR:编码错误显示董董董董
    //底部5个按钮
    SVGA_Bar(0, 130 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Draw_Mine

Description：	画我的的主界面

Input：			NONE

Output：		我的主界面

Return：		NONE
**********************************************************/
void Draw_Mine(PEOPLE &people){
    float size=5.5;
    char times[10],len[15];
    itoa(people.exeTimes,times,10);
    itoa(people.exeLen,len,10);
    //将len转换为浮点公里整数与小数部分
    char xiao[3];
    for(int i=0;i<2;i++)
        xiao[i]=len[strlen(len)-3+i];
    xiao[2]='\0';
    len[strlen(len)-3]='\0';
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //钱包按钮
    dis_16hz(2*size,8*size,"钱包",BLACK);
    //消息按钮
    dis_16hz(66*size-32,8*size,"消息",BLACK);
    //头像
    SVGA_Ball(34*size,26*size,6*size,DARK_GRAY);
    //用户名
    dis_24zf(34*size-12*strlen(people.name),35*size-12,people.name,BLACK);
    //分割线
    SVGA_Line(3*size,40*size,65*size,40*size,DARK_GRAY);
    //分割条
    SVGA_Bar(0,58*size,68*size,60*size,LIGHT_GRAY);
    //画运动记录按钮(0,60*size,68*size,70*size)
    dis_24zf(4*size,65*size,times,BLACK);
    dis_24hz(4*size+strlen(times)*24,65*size,"次运动",BLACK);
    dis_16hz(4*size,70*size,"最近运动",LIGHT_GRAY);
    dis_16zf(4*size+5*16,70*size,len,LIGHT_GRAY);
    SVGA_Ball(4*size+(5+strlen(len))*16+8,70*size+14,2,LIGHT_GRAY);
    dis_16zf(4*size+(6+strlen(len))*16,70*size,xiao,LIGHT_GRAY);
    dis_16hz(4*size+(6+strlen(len)+strlen(xiao))*16,70*size,"公里",LIGHT_GRAY);
    dis_16hz(50*size,68.5*size-8,"查看记录",LIGHT_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,67.5*size,DARK_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,69.5*size,DARK_GRAY);
    //分割条
    SVGA_Bar(0,77*size,68*size,79*size,LIGHT_GRAY);
    //画设置按钮(0,60*size,68*size,70*size)
    dis_16hz(4*size,84*size-8,"设置",BLACK);
    SVGA_Line(66*size,84*size,65*size,83*size,DARK_GRAY);
    SVGA_Line(66*size,84*size,65*size,85*size,DARK_GRAY);
    //分割条
    SVGA_Bar(0,89*size,68*size,130*size,LIGHT_GRAY);
    //Simple setting(0,60*size,68*size,70*size,"设置");
    //底部5个按钮
    SVGA_Bar(0, 130 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);
}








































