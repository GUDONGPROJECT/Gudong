//
// Created by patrick on 10/18/18.
//

#include "./header/headUtil.h"
/**
 * 顶部状态栏显示
 *
 * @param x 左上角x坐标
 * @param y 左上角y坐标
 * @param color 时间显示前景色
 * @param bg 时间显示背景色
 * @return
 */

bool headDisplay(float x, float y, int color, int bg) {
    // 定义初始的lx,以便后面进行背景色覆盖
    int startX = x;

    // 获取系统时间
    time_t now;
    // 系统自带时间结构体
    struct tm *tm_now;
    // 获取毫秒数
    time(&now);
    // 将毫秒数转化为结构体数据
    tm_now = localtime(&now);
    // 临时指针用来指向显示的数字
    char* temp;
    // 用来装载0这个数字,因为后面会用它来拼接,所以长度需要足够
    char zeroPart[10] = "0";
    // 用来装载结构体内的时间,可能会遇见小于10的情况,此时判断后与temp(0)拼接
    char token[10];

    itoa(tm_now -> tm_year + 1900, temp, 10);
    dis_16zf(x, y, temp, color);
    dis_16hz(x += 64, y, "年", color);

    temp = tm_now -> tm_mon +1 > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_mon + 1, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "月", color);
    // 避免上次拼接的残余影响
    zeroPart[1] = '\0';

    temp = tm_now -> tm_mday > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_mday, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "日", color);
    zeroPart[1] = '\0';

    drawClock(x += 142, y, color, bg);
}

void drawClock(float x, float y, int color, int bg){
    float startX = x;
    // 获取系统时间
    time_t now;
    // 系统自带时间结构体
    struct tm *tm_now;
    // 获取毫秒数
    time(&now);
    // 将毫秒数转化为结构体数据
    tm_now = localtime(&now);
    // 用来装载0这个数字,因为后面会用它来拼接,所以长度需要足够
    char zeroPart[10] = "0";
    // 用来装载结构体内的时间,可能会遇见小于10的情况,此时判断后与temp(0)拼接
    char token[10];
    // 临时指针用来指向显示的数字
    char* temp;

    temp = tm_now -> tm_hour > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_hour, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x, y, temp, color);
    zeroPart[1] = '\0';

    put_pixel(x += 32, y + 8, color);
    put_pixel(x, y + 4, color);

    temp = tm_now -> tm_min > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_min, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 6 , y, temp, color);
    zeroPart[1] = '\0';

    // 如果过渡到了下一分钟,利用背景色刷新该界面
    static int minFlag = tm_now -> tm_min;
    // 因为两个地方同时在使用,用count计数更新状况
    static int count = 2;
    if (minFlag != tm_now -> tm_min) {
        SVGA_Bar(startX, y, startX + 70, y + 16, bg);
        // 成功更新一次以后count变为1,第二次该更新的时候count变为0
        if (--count == 0) {
            // 刷新后更新对应的flag
            minFlag = tm_now->tm_min;
            count = 2;
        }

    }
}

void drawClockOnce(float x, float y, int color) {
    // 获取系统时间
    time_t now;
    // 获取毫秒数
    time(&now);
    // 将毫秒数转化为结构体数据
    struct tm * tm_now = localtime(&now);
    // 如果过渡到了下一分钟,直接返回
    static int minFlag = tm_now -> tm_min;
    if (minFlag != tm_now -> tm_min) {
        return ;
    }
    // 用来装载0这个数字,因为后面会用它来拼接,所以长度需要足够
    char zeroPart[10] = "0";
    // 用来装载结构体内的时间,可能会遇见小于10的情况,此时判断后与temp(0)拼接
    char token[10];
    // 临时指针用来指向显示的数字
    char* temp;

    temp = tm_now -> tm_hour > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_hour, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x, y, temp, color);
    zeroPart[1] = '\0';

    put_pixel(x += 32, y + 8, color);
    put_pixel(x, y + 4, color);

    temp = tm_now -> tm_min > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_min, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 6 , y, temp, color);
    zeroPart[1] = '\0';
}