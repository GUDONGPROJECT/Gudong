#include "./header/MainUI.h"
State SportMain(void){
    Sport state=Sport.RUN;
    mouse_reset(mouse);//重置鼠标
    while(1){
        if(state==Sport.RUN){
            Draw_Sport_Run();
            mouse_position(mouse);//获取鼠标位置
            drawmouse(mouse);//绘制鼠标
            if(mouse->pos_x > 10.5*size+16 && mouse->pos_y > 18*size && mouse->pos_x < 21*size+32 && mouse->pos_y < 26*size) {
                state = Sport.WALK;
            }
            if(mouse->pos_x > 21*size+32 && mouse->pos_y > 18*size && mouse->pos_x < 31.5*size+48 && mouse->pos_y < 26*size) {
                state = Sport.RIDE;
            }
        }
        if(state==Sport.WALK){
            Draw_Sport_Walk();
            mouse_position(mouse);//获取鼠标位置
            drawmouse(mouse);//绘制鼠标
            if(mouse->pos_y > 18*size && mouse->pos_x < 10.5*size+16 && mouse->pos_y < 26*size) {
                state = Sport.RUN;
            }
            if(mouse->pos_x > 21*size+32 && mouse->pos_y > 18*size && mouse->pos_x < 31.5*size+48 && mouse->pos_y < 26*size) {
                state = Sport.RIDE;
            }
        }
        if(state==Sport.RIDE){
            Draw_Sport_Ride();
            mouse_position(mouse);//获取鼠标位置
            drawmouse(mouse);//绘制鼠标
            if(mouse->pos_y > 18*size && mouse->pos_x < 10.5*size+16 && mouse->pos_y < 26*size) {
                state = Sport.RUN;
            }
            if(mouse->pos_x > 10.5*size+16 && mouse->pos_y > 18*size && mouse->pos_x < 21*size+32 && mouse->pos_y < 26*size) {
                state = Sport.WALK;
            }
        }
    }
}
 /**********************************************************
Function：		Draw_Sport_Run

Description：	画运动的主界面

Input：			NONE

Output：		运动主界面

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
     SVGA_Line(5*size+,26*size-1,5*size+32,26*size-1,GREEN);
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

Description：	画运动的主界面

Input：			NONE

Output：		运动主界面

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

Description：	画运动的主界面

Input：			NONE

Output：		运动主界面

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
    SVGA_Line(27*size,26*size,27*size+32,26*size-1,GREEN);
    SVGA_Line(27*size,26*size-1,27*size+32,26*size-1,GREEN);
    //骑行总公里
    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
    dis_24hz(34 * size - 12 * 5, 50 * size, "骑行总公里", BLACK);
    //GO按钮
    CircleBar( 11 * size, 98 * size, 28 * size, 98 * size, 5*size, GREEN);
    dis_24zf(19.5 * size - 24, 98 * size - 12, "GO", WHITE);
    //共享单车按钮
    CircleBar( 40 * size, 98 * size, 57 * size, 98 * size, 5*size, GREEN);
    dis_24zf(48.5 * size - 24*2, 98 * size - 12, "共享单车", WHITE);
    //底部5个按钮
    SVGA_Bar(0, 130 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);
}
