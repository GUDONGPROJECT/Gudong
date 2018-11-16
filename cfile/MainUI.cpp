#include "./header/MainUI.h"
State SportMain(MOUSE *mouse,PEOPLE *people) {
    Sport state = RUN;
    float size = 5.5;
    mouse_reset(mouse);//重置鼠标
    while (1) {
        //当位于跑步界面时
        if (state == RUN) {
            Draw_Sport_Run(people);
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
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //跳转至开始跑步的界面
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, RUN);
                                runningMan.Run();
                                break;
                            }
                            Update(people,RUN);
                        }
                    }
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
            Draw_Sport_Walk(people);
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
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //跳转至开始跑步的界面
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, WALK);
                                runningMan.Run();
                                break;
                            }
                            Update(people,WALK);
                        }
                    }
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
            Draw_Sport_Ride(people);
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
//                    //是否点击GO按钮
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 11 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 28 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2))){
//                        //跳转至开始跑步的界面
//                        if(Begin_Run()) {
//                            Character runningMan(people);
//                            runningMan.Run();
//                        }
                    //是否点击GO按钮
                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2))){
                        //跳转至开始跑步的界面
                        if(Begin_Run()) {
                            while(1) {
                                Character runningMan(people, RIDE);
                                runningMan.Run();
                                break;
                            }
                            Update(people,RIDE);
                        }
                    }
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

Input：			PEOPLE* people

Output：		跑步主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Run(PEOPLE* people) {
    float size = 5.5;
    int i;          //循环变量
    int s=people->runLen;
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
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
    dis_24hz(34 * size - 12 * 5, 50 * size, "运动总公里", BLACK);
    //GO按钮
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //底部5个按钮
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Draw_Sport_Walk

Description：	画健走的主界面

Input：			NONE

Output：		健走主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Walk(PEOPLE* people) {
    float size = 5.5;
    int i;          //循环变量
    int s=people->walkLen;
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
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
    dis_24hz(34 * size - 12 * 5, 50 * size, "健走总公里", BLACK);
    //GO按钮
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
    //底部5个按钮
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Draw_Sport_Ride

Description：	画骑行的主界面

Input：			NONE

Output：		骑行主界面

Return：		NONE
**********************************************************/
void Draw_Sport_Ride(PEOPLE* people) {
    float size = 5.5;
    int i;          //循环变量
    int s=people->rideLen;
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
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
    dis_24hz(34 * size - 12 * 5, 50 * size, "骑行总公里", BLACK);
//    //GO按钮
//    CircleBar( 11 * size, 98 * size, 28 * size, 98 * size, 5*size, GREEN);
//    dis_24zf(19.5 * size - 24, 98 * size - 12, "GO", WHITE);
    //GO按钮
    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);
//    //共享单车按钮 dis_24zf(48.5 * size - 24*2, 98 * size - 12, , WHITE);
//    CircleBar( 40 * size, 98 * size, 57 * size, 98 * size, 5*size, GREEN);
//    dis_24zf(48.5*size-24*2,98*size-12,"共享单车",WHITE);      //ERROR:编码错误显示董董董董
    //底部5个按钮
    SVGA_Bar(0, 132 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "运动", GREEN);
    dis_16hz(47 * size - 16, 136 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "我的", LIGHT_GRAY);
}
/**********************************************************
Function：		Update

Description：	更新运动距离的数据

Input：			PEOPLE* people
               SPORT state

Output：		运动距离

Return：		NONE
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
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
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









































