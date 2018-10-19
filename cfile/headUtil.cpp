//
// Created by patrick on 10/18/18.
//

#include "./header/headUtil.h"
/**
 * ����״̬����ʾ
 *
 * @param x ���Ͻ�x����
 * @param y ���Ͻ�y����
 * @param color ʱ����ʾǰ��ɫ
 * @param bg ʱ����ʾ����ɫ
 * @return
 */

bool headDisplay(float x, float y, int color, int bg) {
    // �����ʼ��lx,�Ա������б���ɫ����
    int startX = x;
    // ��ȡϵͳʱ��
    time_t now;
    // ϵͳ�Դ�ʱ��ṹ��
    struct tm *tm_now;
    // ��ȡ������
    time(&now);
    // ��������ת��Ϊ�ṹ������
    tm_now = localtime(&now);
    // ��ʱָ������ָ����ʾ������
    char* temp;
    // ����װ��0�������,��Ϊ�����������ƴ��,���Գ�����Ҫ�㹻
    char zeroPart[10] = "0";
    // ����װ�ؽṹ���ڵ�ʱ��,���ܻ�����С��10�����,��ʱ�жϺ���temp(0)ƴ��
    char token[10];

    itoa(tm_now -> tm_year + 1900, temp, 10);
    dis_16zf(x, y, temp, color);
    dis_16hz(x += 64, y, "��", color);

    temp = tm_now -> tm_mon +1 > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_mon + 1, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "��", color);
    // �����ϴ�ƴ�ӵĲ���Ӱ��
    zeroPart[1] = '\0';

    temp = tm_now -> tm_mday > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_mday, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 16, y, temp, color);
    dis_16hz(x += 32, y, "��", color);
    zeroPart[1] = '\0';

    temp = tm_now -> tm_hour > 9 ? NULL : zeroPart;
    itoa(tm_now -> tm_hour, token, 10);
    if (temp == NULL)
        temp = token;
    else
        strcat(temp, token);
    dis_16zf(x += 142, y, temp, color);
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

    // ������ɵ�����һ����,���ñ���ɫˢ�¸ý���
    static int minFlag = tm_now -> tm_min;
    if (minFlag != tm_now -> tm_min) {
        SVGA_Bar(startX, y, startX + 372, y + 16, bg);
        // ˢ�º���¶�Ӧ��flag
        minFlag = tm_now -> tm_min;
    }
}