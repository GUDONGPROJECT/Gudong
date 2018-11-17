//
// Created by patrick on 11/15/18.
//


#include "./header/Circle.h"
#include "./header/headUtil.h"
#include "./header/things.h"
#include "./header/IoUtil.h"

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
    MsgP msgP = (MsgP) malloc(3 * sizeof(Msg));
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

    getSelectMsg(msgP, people);
}

void showClassMsg(float x, float y, bool hasAchieved, MsgP msgP) {
    int color = hasAchieved ? GREEN : DARK_GRAY;
//    SVGA_Ball(x, y, 2 * SIZE, color[0]);
    SVGA_Bar(x + 4 * SIZE, y + 4 * SIZE, 64 * SIZE, y + 4 * SIZE + 27 * SIZE, msgP->color);
    dis_24hz(x + 8 * SIZE, y + 6 * SIZE, msgP->author, WHITE);
    dis_16hz(x + 8 * SIZE, y + 12 * SIZE, msgP->title, WHITE);
    dis_16zf(x + 20 * SIZE, y + 12 * SIZE, msgP->type, WHITE);
    dis_16hz(x + 28 * SIZE, y + 12 * SIZE, "分钟", WHITE);
    dis_16hz(x + 8 * SIZE, y + 25 * SIZE, "参加人数", WHITE);
    dis_16zf(x + 23 * SIZE, y + 25 * SIZE, msgP->readNum, WHITE);
//    SVGA_Bar(x - 3 * SIZE, y + 4 * SIZE, x + 13 * SIZE, y + 20 * SIZE, color[1]);
//    dis_24hz(x + 16 * SIZE, y + 4 * SIZE, msgP->title, BLACK);
//    SVGA_Bar(x + 16 * SIZE, y + 16 * SIZE, x + 31 * SIZE, y + 20 * SIZE, LIGHT_CYAN);
//    dis_16hz(x + 16 * SIZE + 4, y + 16 * SIZE + 2, msgP->type, GREEN);
//    dis_16hz(x + 45 * SIZE, y + 16 * SIZE + 2, "阅读", DARK_GRAY);
//    dis_16zf(x + 53 * SIZE, y + 16 * SIZE + 2, msgP->readNum, DARK_GRAY);
}

void getSelectMsg(MsgP msgP, PEOPLE *peopleP) {
    char *path;
    bool flag;
    float height = 26 * SIZE;
    path = (char *) malloc(50 * sizeof(char));

    MsgP msgP1 = msgP + 0;

    createMsgPath("class1", path);


    inputMsg(path, msgP1);

    flag = !checkIfSelect(msgP1, peopleP);
    if (flag) {
        msgP1->color = GREEN;
    }
    else {
        msgP1->color = DARK_GRAY;
    }

    msgP1->last = NULL;

    int color2[] = {SKY_BLUE, GAINSBORO};
    MsgP msgP2 = msgP + 1;

    createMsgPath("class2", path);


    inputMsg(path, msgP2);
    flag = !checkIfSelect(msgP2, peopleP);
    if (flag) {
        msgP2->color = GREEN;
    }
    else {
        msgP2->color = DARK_GRAY;
    }
    msgP2->last = msgP1;
    msgP1->next = msgP2;

    int color3[] = {BABY_PINK, SEASHELL};
    MsgP msgP3 = msgP + 2;

    createMsgPath("class3", path);

    inputMsg(path, msgP3);

    flag = !checkIfSelect(msgP3, peopleP);
    if (flag) {
        msgP3->color = GREEN;
    }
    else {
        msgP3->color = DARK_GRAY;
    }

    msgP3->last = msgP2;
    msgP2->next = msgP3;
    // 形成循环链表
    msgP1->last = msgP3;
    msgP3->next = msgP1;

    if (msgP1->color == GREEN) {
        // 标签1
        showAllMsg(0, height, msgP1);
        height += 35 * SIZE;
    }

    if (msgP2->color == GREEN) {
        // 标签1
        showAllMsg(0, height, msgP2);
        height += 35 * SIZE;
    }

    if (msgP3->color == GREEN) {
        // 标签1
        showAllMsg(0, height, msgP3);
        height += 35 * SIZE;
    }
}

