//
// Created by patrick on 10/18/18.
//

#include "./header/headUtil.h"

bool headDisplay(float x, float y, int color, int bg) {
    int startX = x;
    time_t now;
    struct tm *tm_now;
    time(&now);
    tm_now = localtime(&now);
    char timeHead[100];
    char* temp;
    char token[10];
    itoa(tm_now -> tm_year + 1900, timeHead, 10);
//    char test[] = "100";
//    printf("now datetime: %d-%d-%d %d:%d:%d\n",
//           tm_now->tm_year+1900, tm_now->tm_mon+1, tm_now->tm_mday, tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec) ;

//    string timeInfo = to_string(m_now->tm_year+1900 + tm_now->tm_mon+1 + tm_now->tm_mday + tm_now->tm_hour + tm_now->tm_min + tm_now->tm_sec);
    dis_16zf(x, y, timeHead, color);
    dis_16hz(x += 64, y, "Äê", color);

    temp = tm_now -> tm_mon +1 > 9 ? NULL : "0";
    itoa(tm_now -> tm_mon + 1, token, 10);
    strcpy(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "ÔÂ", color);

    temp = tm_now -> tm_mday > 9 ? NULL : "0";
    itoa(tm_now -> tm_mday, token, 10);
    strcpy(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "ÈÕ", color);

    temp = tm_now -> tm_hour > 9 ? NULL : "0";
    itoa(tm_now -> tm_hour, token, 10);
    strcpy(temp, token);
    dis_16zf(x += 142, y, temp, color);

    put_pixel(x += 32, y + 8, color);
    put_pixel(x, y + 4, color);

    static int minFlag = tm_now -> tm_min;
    if (minFlag != tm_now -> tm_min) {
        SVGA_Bar(startX, y, startX + 372, y + 16, bg);
        minFlag = tm_now -> tm_min;
    }
    temp = tm_now -> tm_min > 9 ? NULL : "0";
    itoa(tm_now -> tm_min, token, 10);
    strcpy(temp, token);
    dis_16zf(x += 6 , y, temp, color);

}