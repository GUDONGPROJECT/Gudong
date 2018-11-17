//
// Created by patrick on 11/15/18.
//


#include "./header/Circle.h"
#include "./header/headUtil.h"

State circlePage(MOUSE *mouse, PEOPLE *people) {
    //获取鼠标位置
//    mouse_position(mouse);
    // 固定顺序,先drwa,再reset
    circleDraw(mouse, people);
    mouse_reset(mouse);
    while (true) {

        //当点击鼠标
        if (mouse->button == 1) {

            if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                //当点击运动圈
                if (mouse->pos_x > 14.5 * SIZE && mouse->pos_x < 27.5 * SIZE) {

                    return FIND;
                }
                //当点击发现
                if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE) {

                    return THINGS;
                }
                //当点击运动
                if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {

                    return SPORTPAGE;
                }
                //当点击我的
                if (mouse->pos_x > 53.5 * SIZE) {

                    return MINE;
                }
            }
        }
        mouse_position(mouse);
        drawmouse(mouse);
        // 展示顶部时间
        headDisplay(2, 5, BLACK, WHITE);
    }
}

void circleDraw(MOUSE *mouse, PEOPLE *people) {
    // 循环变量
    int i;
    // 画上下的绿白背景
    SVGA_Bar(0, 0, 68 * SIZE, 140 * SIZE, WHITE);
    // 三个tab下方的灰线
    SVGA_Line(0, 26 * SIZE + 1, 68 * SIZE, 26 * SIZE + 1, DARK_GRAY);
    // 五个选项上方的灰线
    SVGA_Line(0, 132 * SIZE, 68 * SIZE, 132 * SIZE, DARK_GRAY);

    // 三个tab下方的绿线
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 96, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 96, 26 * SIZE - 1, GREEN);
    // 画3个选项
    dis_16hz(5 * SIZE, 21 * SIZE, "参加的课程", GREEN);

    // 画天气显示
    SVGA_Bar(2 * SIZE, 5 * SIZE, 60 * SIZE, 15 * SIZE, LIGHT_GRAY);
    SVGA_Cricle(6 * SIZE, 10 * SIZE, 2 * SIZE, WHITE);
    SVGA_Line(6 * SIZE + 2 * SIZE * sin(45), 10 * SIZE + 2 * SIZE * sin(45),
              6 * SIZE + 3 * SIZE * sin(45), 10 * SIZE + 3 * SIZE * sin(45), WHITE);
    // 底部5个按钮
    dis_16hz(8 * SIZE - 8 * 3, 136 * SIZE - 8, "运动圈", GREEN);
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "运动", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "我的", LIGHT_GRAY);

    showClassMsg(0, 26 * SIZE, false, NULL);
}

void showClassMsg(float x, float y, bool hasAchieved, MsgP msgP) {
    int color = hasAchieved ? GREEN : DARK_GRAY;
//    SVGA_Ball(x, y, 2 * SIZE, color[0]);
    SVGA_Bar(x + 4 * SIZE, y + 4 * SIZE, 64 * SIZE, y + 4 * SIZE + 27 * SIZE, color);
    dis_24hz(x + 8 * SIZE, y + 6 * SIZE, "迎新跑", WHITE);
    dis_16hz(x + 8 * SIZE, y + 12 * SIZE, "零基础", WHITE);
    dis_16zf(x + 20 * SIZE, y + 12 * SIZE, "21", WHITE);
    dis_16hz(x + 28 * SIZE, y + 12 * SIZE, "分钟", WHITE);
    dis_16hz(x + 8 * SIZE, y + 25 * SIZE, "参加人数", WHITE);
    dis_16zf(x + 23 * SIZE, y + 25 * SIZE, "22342342", WHITE);
//    SVGA_Bar(x - 3 * SIZE, y + 4 * SIZE, x + 13 * SIZE, y + 20 * SIZE, color[1]);
//    dis_24hz(x + 16 * SIZE, y + 4 * SIZE, msgP->title, BLACK);
//    SVGA_Bar(x + 16 * SIZE, y + 16 * SIZE, x + 31 * SIZE, y + 20 * SIZE, LIGHT_CYAN);
//    dis_16hz(x + 16 * SIZE + 4, y + 16 * SIZE + 2, msgP->type, GREEN);
//    dis_16hz(x + 45 * SIZE, y + 16 * SIZE + 2, "阅读", DARK_GRAY);
//    dis_16zf(x + 53 * SIZE, y + 16 * SIZE + 2, msgP->readNum, DARK_GRAY);
}

