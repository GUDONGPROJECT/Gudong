//
// Created by patrick on 10/25/18.
//

#include "./header/things.h"
#include "./header/headUtil.h"
#include "./header/ioUtil.h"

/**
 * 干货界面主界面函数
 *
 * @param mouse 鼠标
 * @param people 用户
 * @return 返回State,即用户点击的下方选择栏
 */
State thingsPage(MOUSE *mouse, PEOPLE *people) {
    Things state = RECOMMEND;
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
                    if (mouse->pos_x > 10.5 * SIZE + 16 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 21 * SIZE + 32 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = TRAIN;
                        break;
                    }
                    //是否点击攻略
                    if (mouse->pos_x > 21 * SIZE + 32 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 31.5 * SIZE + 48 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = HELP;
                        break;
                    }
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * SIZE)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * SIZE)
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
                    if (mouse->pos_y > 18 * SIZE && mouse->pos_x < 10.5 * SIZE + 16 && mouse->pos_y < 26 * SIZE) {
                        state = RECOMMEND;
                        break;
                    }
                    //是否点击攻略
                    if (mouse->pos_x > 21 * SIZE + 32 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 31.5 * SIZE + 48 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = HELP;
                        break;
                    }
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * SIZE)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * SIZE)
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
                    if (mouse->pos_y > 18 * SIZE && mouse->pos_x < 10.5 * SIZE + 16 && mouse->pos_y < 26 * SIZE) {
                        state = RECOMMEND;
                        break;
                    }
                    //当点击训练时
                    if (mouse->pos_x > 10.5 * SIZE + 16 && mouse->pos_y > 18 * SIZE && mouse->pos_x < 21 * SIZE + 32 &&
                        mouse->pos_y < 26 * SIZE) {
                        state = TRAIN;
                        break;
                    }
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * SIZE)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * SIZE && mouse->pos_x > 14.5 * SIZE)
                            return FIND;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE)
                            return THINGS;
                        //当点击我的
                        if (mouse->pos_x > 53.5 * SIZE)
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
    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 32, 26 * SIZE - 1, GREEN);
    // 画3个选项
    dis_16hz(5 * SIZE, 21 * SIZE, "推荐", GREEN);
    dis_16hz(16 * SIZE, 21 * SIZE, "训练", LIGHT_GRAY);
    dis_16hz(27 * SIZE, 21 * SIZE, "攻略", LIGHT_GRAY);

    drawRecommendDetail();
}

/**
 * 训练界面的绘制
 * 
 * @param mouse 鼠标
 * @param people 人
 */

void trainDraw(MOUSE *mouse, PEOPLE *people) {
    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(16 * SIZE, 26 * SIZE, 16 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(16 * SIZE, 26 * SIZE - 1, 16 * SIZE + 32, 26 * SIZE - 1, GREEN);
    // 画3个选项
    dis_16hz(5 * SIZE, 21 * SIZE, "推荐", LIGHT_GRAY);
    dis_16hz(16 * SIZE, 21 * SIZE, "训练", GREEN);
    dis_16hz(27 * SIZE, 21 * SIZE, "攻略", LIGHT_GRAY);
}

/**
 * 帮助功能的绘制
 * 
 * @param mouse 
 * @param people 
 */

void helpDraw(MOUSE *mouse, PEOPLE *people) {
    thingsDraw(mouse, people);
    // 三个tab下方的绿线
    SVGA_Line(27 * SIZE, 26 * SIZE, 27 * SIZE + 32, 26 * SIZE, GREEN);
    SVGA_Line(27 * SIZE, 26 * SIZE - 1, 27 * SIZE + 32, 26 * SIZE - 1, GREEN);
    //画3个选项
    dis_16hz(5 * SIZE, 21 * SIZE, "推荐", LIGHT_GRAY);
    dis_16hz(16 * SIZE, 21 * SIZE, "训练", LIGHT_GRAY);
    dis_16hz(27 * SIZE, 21 * SIZE, "攻略", GREEN);
}

/**
 * 干货界面的绘制
 * 
 * @param mouse 
 * @param people 
 */
void thingsDraw(MOUSE *mouse, PEOPLE *people) {
    // 循环变量
    int i;

    // 画上下的绿白背景
    SVGA_Bar(0, 0, 68 * SIZE, 140 * SIZE, WHITE);
    // 三个tab下方的灰线
    SVGA_Line(0, 26 * SIZE + 1, 68 * SIZE, 26 * SIZE + 1, DARK_GRAY);
    // 五个选项上方的灰线
    SVGA_Line(0, 132 * SIZE, 68 * SIZE, 132 * SIZE, DARK_GRAY);

    // 画天气显示
    SVGA_Bar(2 * SIZE, 5 * SIZE, 60 * SIZE, 15 * SIZE, LIGHT_GRAY);
    SVGA_Cricle(6 * SIZE, 10 * SIZE, 2 * SIZE, WHITE);
    SVGA_Line(6 * SIZE + 2 * SIZE * sin(45), 10 * SIZE + 2 * SIZE * sin(45),
              6 * SIZE + 3 * SIZE * sin(45), 10 * SIZE + 3 * SIZE * sin(45), WHITE);

    // 底部5个按钮
    dis_16hz(8 * SIZE - 8 * 3, 136 * SIZE - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "运动", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "干货", GREEN);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "我的", LIGHT_GRAY);
}

/**
 * 画推荐界面的各种细节
 */
void drawRecommendDetail() {
    char *path;
    path = (char *) malloc(50 * sizeof(char));
    // 人物故事
    SVGA_Ball(11 * SIZE, 35 * SIZE, 5 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, 35 * SIZE, 2.5 * SIZE, WHITE);
    SVGA_Ball(11 * SIZE, 35 * SIZE, 0.5 * SIZE, ORANGE);
    SVGA_Ball((11 - 1.4) * SIZE, 35 * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball((11 + 1.4) * SIZE, 35 * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, (35 - 1.4) * SIZE, 0.8 * SIZE, ORANGE);
    SVGA_Ball(11 * SIZE, (35 + 1.4) * SIZE, 0.8 * SIZE, ORANGE);
    dis_16hz(4 * SIZE, 42 * SIZE, "人物故事", BLACK);

    // 运动干货
    SVGA_Ball(33 * SIZE, 35 * SIZE, 5 * SIZE, HORIZON_BLUE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 3.5 * SIZE, WHITE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 2.5 * SIZE, HORIZON_BLUE);
    SVGA_Ball(33 * SIZE, 35 * SIZE, 1 * SIZE, WHITE);
    dis_16hz(26 * SIZE, 42 * SIZE, "运动干货", BLACK);

    // 装备评测
    SVGA_Ball(55 * SIZE, 35 * SIZE, 5 * SIZE, AQUA_BLUE);
    SVGA_Ball(53 * SIZE, 33 * SIZE, 1 * SIZE, WHITE);
    SVGA_Bar((55 + 0.8) * SIZE, (35 - 0.8) * SIZE, 61 * SIZE, 37.5 * SIZE, WHITE);
    dis_16hz(48 * SIZE, 42 * SIZE, "装备评测", BLACK);

    // 三个圈下面的灰色档档
    SVGA_Bar(1 * SIZE, 49 * SIZE, 67 * SIZE, 51 * SIZE, LIGHT_GRAY);

    // 下方的标签分界线
    SVGA_Line(1 * SIZE, 78 * SIZE, 67 * SIZE, 78 * SIZE, LIGHT_GRAY);
    SVGA_Line(1 * SIZE, 105 * SIZE, 67 * SIZE, 105 * SIZE, LIGHT_GRAY);

    int color1[] = {MEDIUM_PURPLE, BABY_PINK};
    MsgP msgP1 = (MsgP) malloc(sizeof(Msg));
    createMsgPath("1", path);
    inputMsg(path, msgP1);
    msgP1->last = NULL;

    int color2[] = {SKY_BLUE, GAINSBORO};
    MsgP msgP2 = (MsgP) malloc(sizeof(Msg));
    createMsgPath("2", path);
    inputMsg(path, msgP2);
    msgP2->last = msgP1;
    msgP1->next = msgP2;

    int color3[] = {BABY_PINK, SEASHELL};
    MsgP msgP3 = (MsgP) malloc(sizeof(Msg));
    createMsgPath("3", path);
    inputMsg(path, msgP3);
    msgP3->last = msgP2;
    msgP2->next = msgP3;

    // 标签1
    showRecommendMsg(6 * SIZE, 56 * SIZE, color1, msgP1);

    // 标签2
    showRecommendMsg(6 * SIZE, 83 * SIZE, color2, msgP2);

    // 标签3
    showRecommendMsg(6 * SIZE, 110 * SIZE, color3, msgP3);
}

void showRecommendMsg(float x, float y, int * color, MsgP msgP) {
    SVGA_Ball(x, y, 2 * SIZE, color[0]);
    dis_16hz(x + 4 * SIZE, y - 1 * SIZE, msgP->author, BLACK);
    SVGA_Bar(x - 3 * SIZE, y + 4 * SIZE, x + 13 * SIZE, y + 20 * SIZE, color[1]);
    dis_24hz(x + 16 * SIZE, y + 4 * SIZE, msgP->title, BLACK);
    SVGA_Bar(x + 16 * SIZE, y + 16 * SIZE, x + 31 * SIZE, y + 20 * SIZE, LIGHT_CYAN);
    dis_16hz(x + 16 * SIZE + 4, y + 16 * SIZE + 2, msgP->type, GREEN);
    dis_16hz(x + 45 * SIZE, y + 16 * SIZE + 2, "阅读", DARK_GRAY);
    dis_16zf(x + 53 * SIZE, y + 16 * SIZE + 2, msgP->readNum, DARK_GRAY);
}

/**
 * 画训练界面的个各种细节
 */
void drawTrainDetail() {

}

/**
 * 画出攻略界面的各种细节
 */
void drawHelpDetail() {

}