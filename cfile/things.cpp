//
// Created by patrick on 10/25/18.
//

#include "./header/things.h"
#include "./header/headUtil.h"

/**
 * 干货界面主界面函数
 *
 * @param mouse 鼠标
 * @param people 用户
 * @return 返回State,即用户点击的下方选择栏
 */
State thingsPage(MOUSE *mouse,PEOPLE *people) {
    Things state = RECOMMEND;
    float size = 5.5;
    mouse_reset(mouse);//重置鼠标
    while (1) {
        //当位于推荐界面时
        if (state == RECOMMEND) {
            recommendDraw(mouse, people);
            //获取鼠标位置
            mouse_position(mouse);
            mouse_reset(mouse);
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //是否点击训练
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = TRAIN;
                        break;
                    }
                    //是否点击攻略
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = HELP;
                        break;
                    }


//                    //是否点击GO
//                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
//                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
//                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
//                    //跳转至开始跑步的界面


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
                // 展示顶部时间
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
        //当位于健走界面时
        if (state == TRAIN) {
            trainDraw(mouse, people);
            //获取鼠标位置
            mouse_position(mouse);
            //画出鼠标
            mouse_reset(mouse);
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //是否点击推荐
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RECOMMEND;
                        break;
                    }
                    //是否点击攻略
                    if (mouse->pos_x > 21 * size + 32 && mouse->pos_y > 18 * size && mouse->pos_x < 31.5 * size + 48 &&
                        mouse->pos_y < 26 * size) {
                        state = HELP;
                        break;
                    }


//                    //是否点击GO
//                    if (mouse->pos_x > 24 * size && mouse->pos_x < 44 * size &&
//                        mouse->pos_y > 95 * size - sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)) &&
//                        mouse->pos_y < 95 * size + sqrt(pow(10 * size, 2) - pow((mouse->pos_x - 34 * size), 2)));
//                    //跳转至开始健走的界面


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
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
        //当位于攻略界面时
        if (state == HELP) {
            helpDraw(mouse, people);
            //获取鼠标位置
            mouse_position(mouse);
            //画出鼠标
            mouse_reset(mouse);

            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //当点击推荐时
                    if (mouse->pos_y > 18 * size && mouse->pos_x < 10.5 * size + 16 && mouse->pos_y < 26 * size) {
                        state = RECOMMEND;
                        break;
                    }
                    //当点击训练时
                    if (mouse->pos_x > 10.5 * size + 16 && mouse->pos_y > 18 * size && mouse->pos_x < 21 * size + 32 &&
                        mouse->pos_y < 26 * size) {
                        state = TRAIN;
                        break;
                    }


//                    //是否点击GO按钮
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 11 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 28 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
//                    //进入开始骑行界面
//                    //是否点击共享单车按钮
//                    if (mouse->pos_y > 93 * size && mouse->pos_y < 103 * size &&
//                        mouse->pos_x > 40 * size - sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)) &&
//                        mouse->pos_y < 57 * size + sqrt(pow(5 * size, 2) - pow((mouse->pos_y - 98 * size), 2)));
//                    //进入开始骑行界面


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
                headDisplay(2, 5, BLACK, WHITE);
            }
        }
    }
}

/**
 * 推荐界面的绘制
 *
 * @param mouse
 * @param people
 */

void recommendDraw(MOUSE *mouse, PEOPLE *people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(5*size,26*size,5*size+32,26*size,GREEN);
    SVGA_Line(5*size,26*size-1,5*size+32,26*size-1,GREEN);
    // 画3个选项
    dis_16hz(5 * size, 21 * size, "推荐", GREEN);
    dis_16hz(16 * size, 21 * size, "训练", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"攻略", LIGHT_GRAY );
}

void trainDraw(MOUSE *mouse, PEOPLE * people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(16*size,26*size,16*size+32,26*size,GREEN);
    SVGA_Line(16*size,26*size-1,16*size+32,26*size-1,GREEN);
    // 画3个选项
    dis_16hz(5 * size, 21 * size, "推荐", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "训练", GREEN);
    dis_16hz(27 * size, 21 * size,"攻略", LIGHT_GRAY );
}

void helpDraw(MOUSE *mouse, PEOPLE * people) {
    float size = 5.5;

    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(27*size,26*size,27*size+32,26*size,GREEN);
    SVGA_Line(27*size,26*size-1,27*size+32,26*size-1,GREEN);
    //画3个选项
    dis_16hz(5 * size, 21 * size, "推荐", LIGHT_GRAY);
    dis_16hz(16 * size, 21 * size, "训练", LIGHT_GRAY);
    dis_16hz(27 * size, 21 * size,"攻略", GREEN);
}

void thingsDraw(MOUSE *mouse,PEOPLE *people){
    float size = 5.5;
    // 循环变量
    int i;

    // 画上下的绿白背景
    SVGA_Bar(0, 0, 68 * size, 140 * size, WHITE);
    // 三个tab下方的灰线
    SVGA_Line(0, 26 * size + 1, 68 * size, 26 * size + 1, DARK_GRAY);
    // 五个选项上方的灰线
    SVGA_Line(0, 130 * size, 68 * size, 130 * size, DARK_GRAY);

    // 画天气显示
    SVGA_Bar(2* size, 5 * size, 60 * size, 15 * size, LIGHT_GRAY);
    SVGA_Cricle(6 * size, 10 * size, 2 * size, WHITE);
    SVGA_Line(6 * size + 2 * size * sin(45), 10 * size + 2 * size * sin(45),
            6 * size + 3 * size * sin(45), 10 * size + 3 * size * sin(45), WHITE);

//    // 跑步总公里
//    dis_24zf(34 * size - strlen(s) * 12, 35 * size, s, BLACK);
//    dis_24hz(34 * size - 12 * 5, 50 * size, "运动总公里", BLACK);

//    //GO按钮
//    SVGA_Ball(34 * size, 95 * size, 10 * size, GREEN);
//    dis_24zf(34 * size - 24, 95 * size - 12, "GO", WHITE);

    // 底部5个按钮
    dis_16hz(8 * size - 8 * 3, 135 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 135 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 135 * size - 8, "运动", LIGHT_GRAY);
    dis_16hz(47 * size - 16, 135 * size - 8, "干货", GREEN);
    dis_16hz(60 * size - 16, 135 * size - 8, "我的", LIGHT_GRAY);

}