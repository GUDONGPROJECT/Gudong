//
// Created by patrick on 11/15/18.
//


#include "./header/Find.h"
#include "./header/headUtil.h"
#include "./header/IoUtil.h"

State findPage(MOUSE *mouse, PEOPLE *people) {
    int i = 0;
    UsrP usrP = (UsrP) malloc(sizeof(Usr));
    UsrP freeP = usrP;
    UsrP headP = usrP;
    UsrP page1P = usrP;
    getAllUsr(usrP);

    findDraw(mouse, people);

//    showClassMsg(0, (i + 26) * SIZE, usrP);
//    usrP = usrP->next;
//
//    i++;
//    showClassMsg(0, (i + 26) * SIZE, usrP);


    for (i = 0; usrP->name[0] != 'n' && i < 6; i++) {
        showClassMsg(0, (i * 17 + 26) * SIZE, usrP);
        usrP = usrP->next;
    }

    mouse_reset(mouse);
    while (1) {
        //当点击鼠标
        if (mouse->button == 1) {

            /*
             上翻页按钮范围：x:(37*size,21*size) y:(43*size,24*size)
             下翻页按钮范围：x:(52*size,21*size) y:(58*size,24*size)
             */
            if (mouse->pos_x > 37 * SIZE && mouse->pos_x < 43 * SIZE && mouse->pos_y > 21 * SIZE && mouse->pos_y < 24 * SIZE) {
                if (headP->last == NULL) {
                    mouse->button = 0;
                    delay(100);
                    continue;
                }
                SVGA_Bar(0, 26 * SIZE + 3, 68 * SIZE, (6 * 17 + 26) * SIZE + 4, WHITE);
//                for (int j = 0; j < 6; j++)
//                    headP = headP->last;
                headP = page1P;
                usrP = headP;
                delay(100);
                for (i = 0; usrP->next != NULL && i < 6; i++) {
                    showClassMsg(0, (i * 17 + 26) * SIZE, usrP);
                    usrP = usrP->next;
                }
                headP = usrP;
            }

            if (mouse->pos_x > 52 * SIZE && mouse->pos_x < 58 * SIZE && mouse->pos_y > 21 * SIZE && mouse->pos_y < 24 * SIZE) {
                if (usrP->next == NULL) {
                    mouse->button = 0;
                    delay(100);
                    continue;
                }
                headP = usrP;
                SVGA_Bar(0, 26 * SIZE + 3, 68 * SIZE, (6 * 17 + 26) * SIZE + 4, WHITE);
                delay(100);
                for (i = 0; usrP->next != NULL && i < 6; i++) {
                    showClassMsg(0, (i * 17 + 26) * SIZE, usrP);
                    usrP = usrP->next;
                }
                if (i == 6) {
                    headP = usrP;
                }
            }

            if (mouse->pos_y > 130 * SIZE && mouse->pos_y < 140 * SIZE) {
                //当点击运动圈
                if (mouse->pos_x < 14.5 * SIZE) {
                    freeAll(freeP);
                    return CIRCLE;
                }
                //当点击发现
                if (mouse->pos_x > 40.5 * SIZE && mouse->pos_x < 53.5 * SIZE) {
                    freeAll(freeP);
                    return THINGS;
                }
                //当点击运动
                if (mouse->pos_x > 27.5 * SIZE && mouse->pos_x < 40.5 * SIZE) {
                    freeAll(freeP);
                    return SPORTPAGE;
                }
                //当点击我的
                if (mouse->pos_x > 53.5 * SIZE) {
                    freeAll(freeP);
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

void drawSignal(int i) {
    const float Y = 768 / 2;
    const float X = 34 * SIZE;
    SVGA_Ball(X, Y, 12 * SIZE, LIGHT_GRAY);
//    void Arc(int x,int y,float stangle,float endangle,int radius,int color)
    Arc(X, Y, 60, -60, 20 * SIZE, LIGHT_GRAY);
}

void getAllUsr(UsrP usrP) {
    char * path = "txt\\USERNAME.txt";
    inputUsr( path, usrP);
}

void findDraw(MOUSE *mouse, PEOPLE *people) {
    // 循环变量
    int i;

    // 画上下的绿白背景
    SVGA_Bar(0, 0, 68 * SIZE, 140 * SIZE, WHITE);
    // 三个tab下方的灰线
    SVGA_Line(0, 26 * SIZE + 1, 68 * SIZE, 26 * SIZE + 1, DARK_GRAY);
    // 五个选项上方的灰线
    SVGA_Line(0, 132 * SIZE, 68 * SIZE, 132 * SIZE, DARK_GRAY);

    // 画3个选项
    dis_16hz(5 * SIZE, 21 * SIZE, "附近的用户", GREEN);
    // 三个tab下方的绿线
    SVGA_Line(5 * SIZE, 26 * SIZE, 5 * SIZE + 96, 26 * SIZE, GREEN);
    SVGA_Line(5 * SIZE, 26 * SIZE - 1, 5 * SIZE + 96, 26 * SIZE - 1, GREEN);

    // 画天气显示
    SVGA_Bar(2 * SIZE, 5 * SIZE, 60 * SIZE, 15 * SIZE, LIGHT_GRAY);
    SVGA_Cricle(6 * SIZE, 10 * SIZE, 2 * SIZE, WHITE);
    SVGA_Line(6 * SIZE + 2 * SIZE * sin(45), 10 * SIZE + 2 * SIZE * sin(45),
              6 * SIZE + 3 * SIZE * sin(45), 10 * SIZE + 3 * SIZE * sin(45), WHITE);
    // 底部5个按钮
    dis_16hz(8 * SIZE - 8 * 3, 136 * SIZE - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * SIZE - 16, 136 * SIZE - 8, "发现", GREEN);
    dis_16hz(34 * SIZE - 16, 136 * SIZE - 8, "运动", LIGHT_GRAY);
    dis_16hz(47 * SIZE - 16, 136 * SIZE - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * SIZE - 16, 136 * SIZE - 8, "我的", LIGHT_GRAY);

    Find_PageController();
}

void showClassMsg(float x, float y, UsrP usrP) {

    SVGA_Bar(x + 4 * SIZE, y + 4 * SIZE, 64 * SIZE, y + 4 * SIZE + 13.5 * SIZE, DARK_GRAY);
    dis_24hz(x + 8 * SIZE, y + 6 * SIZE, "用户：", WHITE);
    dis_16zf(x + 18 * SIZE, y + 12 * SIZE, usrP->name, WHITE);

}

void freeAll(UsrP usrP) {
    if (usrP != NULL) {
        free(usrP);
        usrP = usrP->next;
    }
}


