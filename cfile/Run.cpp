#include"Run.h"

////��ʼ�����˶�
int Begin_Run(void){
    short far *bg;
    char p;
    drawMap();
    get_image(639, 324,759, 444, bg);
    Draw_Start();
    while(1){
        if (kbhit()) {
            p = getch();
            if (p == ' ') {
                put_image(639, 324, 759, 444, bg);
                dis_24zf(687,372,"3",WHITE);
                delay(1000);
                put_image(639, 324, 759, 444, bg);
                dis_24zf(687,372,"2",WHITE);
                delay(1000);
                put_image(639, 324, 759, 444, bg);
                dis_24zf(687,372,"1",WHITE);
                delay(1000);
                put_image(639, 324, 759, 444, bg);
                dis_16zf(683,378,"GO",WHITE);
                delay(1000);
                put_image(639, 324, 759, 444, bg);
                return 1;
            }
        }
    }
}

void Draw_Start(void){
    SVGA_Ball(699,384,60,GREEN);
    SVGA_Bar(689,369,719,399,WHITE);
    Pieslice(720,384,Pi/2,5*Pi/6,31, GREEN);
    Pieslice(720,384,-5*Pi/6,-Pi/2,31, GREEN);
}

void Draw_Pause(void){
    SVGA_Ball(634,384,60,GREEN);
    SVGA_Bar(624,369,654,399,WHITE);
    Pieslice(655,384,Pi/2,5*Pi/6,31, GREEN);
    Pieslice(655,384,-5*Pi/6,-Pi/2,31, GREEN);
//    SVGA_Ball(699,384,60,GREEN);
//    SVGA_Bar(684,369,689,399,WHITE);
//    SVGA_Bar(709,369,714,399,WHITE);
    SVGA_Ball(764,384,60,GREEN);
    SVGA_Bar(749,369,779,399,WHITE);
}

////���캯������ʼ��Character
Character::Character(PEOPLE *people0,int state0){
    // ��ʼ�����ֲ���
    state=state0;
    people=people0;
    x=500;
    y=500;
    angle=Pi*90/180;
    v=0;
    a=0;
    len=0;
    speed=HIGH;
    energy=100;
    time_t now;
    time(&now);
    startTime = localtime(&now);
//    w=0;
}

////��������
Character::~Character(void){
    float size=5.5;
    char mT[3];
    char sT[3];
    SVGA_Bar(375,0,1024,768,DARK_GRAY);
    char zV[3];
    char pV[3];
    //��ʾ�˶�����
    int s=len;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
    if(strlen(zS)==2) {
        dis_24zf(699 - 48, 65 * size-12, zS, WHITE);
    }
    else{
        zS[2]='\0';
        zS[1]=zS[0];
        zS[0]='0';
//        dis_24zf(699 - 48, 65 * size-12, "0", WHITE);
        dis_24zf(699 - 48, 65 * size-12, zS, WHITE);
    }
    SVGA_Ball(699 ,65 * size-12+21,3, WHITE);
    if(strlen(pS)==2) {
        dis_24zf(699 , 65 * size-12, pS, WHITE);
    }
    else{
        pS[2]='\0';
        pS[1]=pS[0];
        pS[0]='0';
//        dis_24zf(699 , 65 * size-12, "0", WHITE);
        dis_24zf(699 , 65 * size-12, pS, WHITE);
    }
    dis_16hz(699 - 8 * 5, 65 * size+24, "�˶��ܹ���", LIGHT_GRAY);
    //��ʾʱ��
    itoa(delta/60,mT,10);
    itoa(delta%60,sT,10);
    if(strlen(mT)==2) {
        dis_16zf(494 - 48, 90 * size, mT, WHITE);
    }
    else{
        mT[2]='\0';
        mT[1]=mT[0];
        mT[0]='0';
//        dis_16zf(494 - 48, 90 * size, "0", WHITE);
        dis_16zf(494 - 48, 90 * size, mT, WHITE);
    }
    SVGA_Ball(500 ,90 * size+5,2, WHITE);
    SVGA_Ball(500 ,90 * size+11,2, WHITE);
//    SVGA_Ball(34 * size ,35 * size+21,3, WHITE);
//    SVGA_Ball(34 * size ,35 * size+21,3, WHITE);
    if(strlen(sT)==2) {
        dis_16zf(494+16 , 90 * size, sT, WHITE);
    }
    else{
        sT[2]='\0';
        sT[1]=sT[0];
        sT[0]='0';
//        dis_16zf(494 + 16 , 90 * size, "0", WHITE);
        dis_16zf(494 + 16, 90 * size, sT, WHITE);
    }
    dis_16hz(494 - 16, 96 * size, "��", LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+5,2, LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+11,2, LIGHT_GRAY);
    dis_16hz(494 + 16, 96 * size, "��", LIGHT_GRAY);
    //��ʾƽ���ٶ�
    itoa((int)(len/delta),zV,10);
    itoa((int)(100*(len/delta-(int)(len/delta))),pV,10);
    if(strlen(zV)==2) {
        dis_16zf(904 - 48, 90 * size, zV, WHITE);
    }
    else{
        zV[2]='\0';
        zV[1]=zV[0];
        zV[0]='0';
//        dis_16zf(904 - 48, 90 * size, "0", WHITE);
        dis_16zf(904 - 32, 90 * size, zV, WHITE);
    }
    SVGA_Ball(907 ,90 * size+12,3, WHITE);
    dis_16zf(904,90*size,":",WHITE);
//    SVGA_Ball(34 * size ,35 * size+21,3, WHITE);
//    SVGA_Ball(34 * size ,35 * size+21,3, WHITE);
    if(strlen(pV)==2) {
        dis_16zf(904+16 , 90 * size, pV, WHITE);
    }
    else{
        pV[2]='\0';
        pV[1]=pV[0];
        pV[0]='0';
//        dis_16zf(904 + 16 , 90 * size, "0", WHITE);
        dis_16zf(904 + 16, 90 * size, pV, WHITE);
    }
    dis_16hz(904 - 24, 100 * size, "��ÿ��", LIGHT_GRAY);
    //������д���ļ���people
    char key[2];
    if(state==RUN) {
        key[0]='#';//����Ϊ�ܲ�
        key[1]='\0';
        DataIn(people, key,zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->runLen+=s;
    }
    else if(state==WALK){
        key[0]='*';//����Ϊ�ܲ�
        key[1]='\0';
        DataIn(people,key, zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->walkLen+=s;
    }
    else if(state==RIDE){
        key[0]='&';//����Ϊ�ܲ�
        key[1]='\0';
        DataIn(people,key, zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->rideLen+=s;
    }
    people->exeTimes++;
}

////��ʾCharacter
void Character::Show(void){
    float size=5.5;
    Pieslice(x+4*size*cos(angle),y-4*size*sin(angle),angle-7*Pi/6,angle-5*Pi/6,2*1.732*size, BLUE);
    SVGA_Ball(x,y,2*size,WHITE);
    SVGA_Ball(x,y,1.5*size,BLUE);
}
////����ԭ��λ�õ�get����image
void Character::PutBg(void){
    float size=5.5;
    put_image(bgX-4*size, bgY-4*size, bgX+4*size, bgY+4*size, bg);
}
////��ȡ��Ҫ�ƶ�����λ�õ�image
void Character::GetBg(void){
    float size=5.5;
    bgX=x;
    bgY=y;
    get_image(x-4*size, y-4*size,x+4*size, y+4*size, bg);
}
////����Character�ĸ����������
bool Character::UpdatePos(void) {
    //���ٶ�����ٶ�Ϊ0ʱ������false����ʾû�����˶�
    if (v == 0&&a==0)
        return false;
    //�ٶȻ���ٶȲ�Ϊ0ʱ����ʼ��������ĸ���
    int rate = 4;
    double deltaT, deltaTx, deltaTy, deltaLenx, deltaLeny;
    struct timeb now;
    //��ȡ�����ϴθ��²�����ʱ��
    ftime(&now);
    deltaTx = ((double) (now.millitm - lastTimex.millitm)) / 1000;
    deltaTy = ((double) (now.millitm - lastTimey.millitm)) / 1000;
    deltaT = ((double) (now.millitm - lastTime.millitm)) / 1000;
    if (deltaTx < 0) {
        deltaTx += 1;
    }
    if (deltaTy < 0) {
        deltaTy += 1;
    }
    if (deltaT < 0) {
        deltaT += 1;
    }
    //����ôθ���ǰ����x��y���ϵľ���
    deltaLenx = v * rate * deltaTx;
    deltaLeny = v * rate * deltaTy;
    //��ǰ��������ڻ����1������ʱ�����¾��룬���µ�ǰ�������ݵ�ʱ��
    if (abs(deltaLenx * cos(angle)) >= 1) {
        x += deltaLenx * cos(angle);
        lastTimex = now;
    }
    if (abs(deltaLeny * sin(angle)) >= 1) {
        y -= deltaLeny * sin(angle);
        lastTimey = now;
    }
    /***********************
     * speed���ٶȵĹ�ϵ����*
     **********************/
    //������ʱ
    if(a==maxA) {
        //���ٶ�Ϊ�����ҵ�ǰ�ٶ�С�������ʱ������
        if (speed == HIGH && v < maxV) {
            v += a * deltaT;
        }
            //���ٶ�Ϊ�����ҵ�ǰ�ٶȲ������������ʱ
        else if (speed == MID&&v!=midV) {
            //��ǰ�ٶȴ����������ʱ������
            if (v > midV) {
                if (v - a * deltaT > midV)
                    v -= a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
                //��ǰ�ٶ�С���������ʱ������
            else if (v < midV) {
                if (v + a * deltaT < midV)
                    v += a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
        }
            //���ٶ�Ϊ�����ҵ�ǰ�ٶȲ�������ߵ���ʱ
        else if (speed == LOW&&v!=lowV) {
            //��ǰ�ٶȴ�����ߵ���ʱ������
            if (v > lowV) {
                if(v-a*deltaT>lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
                //��ǰ�ٶ�С����ߵ���ʱ������
            else if (v < lowV){
                if(v+a*deltaT<lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
        }
            //���ٶ�״̬Ϊ����ʱ������
        else if (speed == ZERO && v > minV) {
            v -= a * deltaT;
        }
    }
        //��Ϊ����״̬ʱ�����ٶ�Ϊ0ǰ����
    else if(a==minA&&v!=minV) {
        v += a * deltaT;
    }
    //������������Ƿ��ڸ�����Χ��
    inScale();
    //������������
    float temp = sqrt(pow(x - bgX, 2) + pow(y - bgY, 2)) / rate;
    len += temp;    //�����˶�����
    //����������100ʱ��������ֵ��Ϊ100
    if (energy > 100) {
        energy = 100;
    }
        //����������80С��100ʱ��������������
    else if (energy > 80) {
        energy -= 0.1 * temp;
        //�����º�����С��80ʱ�����ٶ�ģʽ��Ϊ����
        if(energy<=80) {
            speed = MID;
//            dis_16zf(700,i,ToString(a,s),BLACK);
//            i+=16;
            //�����ٶ�Ϊ0ʱ�������ٶ���ΪmaxAģʽ
            if(a==0)
                a=maxA;
        }
    }
        //����������50С��80ʱ��������������
    else if (energy > 50) {
        energy -= 3 * temp / 80;
        //�����º�����С��50ʱ�����ٶ�ģʽ��Ϊ����
        if(energy<=50) {
            speed = LOW;
            //�����ٶ�Ϊ0ʱ�������ٶ���ΪmaxAģʽ
            if(a==0)
                a = maxA;
        }
    }
        //����������10С��50ʱ��������������
    else if (energy > 10) {
        energy -= 0.04 * temp;
        //�����º�����С��10ʱ�����ٶ�ģʽ��Ϊ����
        if(energy<=10) {
            speed = ZERO;
            //�����ٶ�Ϊ0ʱ�������ٶ���ΪmaxAģʽ
            if(a==0)
                a = maxA;
        }
    }
        //������С��0ʱ����������Ϊ0
    else if(energy<0){
        energy = 0;
    }
    return true;
}
////����Character����ʾ
void Character::UpdateShow(void) {
    PutBg();    //Error:�������
    GetBg();
    Show();
}

//bool Character::IsMove(void){
//    if(v!=0)
//        return true;
//    return false;
//}

////���Character�ĸ�����������Ƿ���ָ����Χ�ڣ����������и���
void Character::inScale(void) {
    if (x > maxX)
        x = maxX;
    else if (x < minX)
        x = minX;
    if (y > maxY)
        y = maxY;
    else if (y < minY)
        y = minY;
    if (v > maxV) {
        v = maxV;
        a = 0;
    }
    else if (v < minV) {
        v = minV;
        a = 0;
    }
}
////�Լ����������Ӧ
int Character::OnKbhit(char key) {
//    if(key=='w'||key=='W')
//        a=maxA;
//    else if(key=='s'||key=='S')
//        a=minA;
//    if(key=='w'||key=='W'){
//        x+=5*cos(angle);
//        y-=5*sin(angle);
//    }
    if(key=='w'||key=='W') {
        if (v==0&&a==0)
            a = maxA;
        return 0;
    }
    else if(key=='s'||key=='S') {
        if (v != 0)
            a = minA;
        return 0;
    }
//    else if(key=='s'||key=='S')
//        a=minA;
    else if(key=='a'||key=='A') {
        angle += 5 * Pi / 180;
        return 0;
    }
    else if(key=='d'||key=='D') {
        angle -= 5 * Pi / 180;
        return 0;
    }
    else if(key==' '){   //���ո���ͣ�˶�
        short far *bg0;
        char p;
        get_image(574, 324,824, 444, bg0);
        Draw_Pause();
        while(1){
            if (kbhit()) {
                p = getch();
                if (p == ' ') {
                    put_image(574, 324,824, 444, bg0);
                    dis_24zf(687,372,"3",WHITE);
                    delay(1000);
                    put_image(574, 324,824, 444, bg0);
                    dis_24zf(687,372,"2",WHITE);
                    delay(1000);
                    put_image(574, 324,824, 444, bg0);
                    dis_24zf(687,372,"1",WHITE);
                    delay(1000);
                    put_image(574, 324,824, 444, bg0);
                    dis_16zf(683,378,"GO",WHITE);
                    delay(1000);
                    put_image(574, 324,824, 444, bg0);
                    ftime(&lastTimex);
                    ftime(&lastTimey);
                    ftime(&lastTime);
                    return 2;
                }
                else if(p==0x1b){
                    return 1;
                }
            }
        }
    }
    else
        return 0;
}
////��ʼִ���˶�ѭ��
void Character::Run(void){
    int ifPause=0;
    char p='#';
    char s[10];
    int v0=v,energy0=energy,len0=len,zlen=0,plen=0,min=0,sec=0;
    time_t now;
    time_t st;
    time(&now);
    time(&st);
    ftime(&lastTimex);
    ftime(&lastTimey);
    GetBg();
//    time(&now);
    delta=0;
//    drawMap();
    UpdateShow();
    drawStatus("100", "0", "0", "0","0");
    cleanLength();
    dis_24zf(408, 256,"0", WHITE);
    SVGA_Ball(438,279,2, WHITE);
    dis_24zf(440, 256, "0", WHITE);
    dis_24zf(468, 256, "0", WHITE);
    //�����˶�ѭ��
    while(1) {
        //��������
        if (kbhit())
            p=getch();
        if(ifPause=OnKbhit(p)) {
            if(ifPause==1)
                break;
        }
        //�˶�������λ��ʱ��ˢ������λ����ʾ
        if(energy>10&&(UpdatePos()||p=='a'||p=='A'||p=='d'||p=='D'))
            UpdateShow();
            //û�����˶�ʱ���ظ�����
        else {
            double deltaT;
            struct timeb now;
            struct tm *_now;
            struct tm *_lastTime;
            _lastTime=localtime(&lastTimex.time);
            //��������100ʱ������ֵ��Ϊ100
            if(energy>100)
                energy=100;
                //��������80ʱ�������ظ�
            else if(energy>80) {
                ftime(&now);
                _now=localtime(&now.time);
                deltaT=((double)(now.millitm-lastTimex.millitm))/1000;
                if(deltaT<0) {
                    deltaT += 1;
                }
                energy += 0.1*deltaT;
                speed = HIGH;
            }
                //��������50С��80ʱ�������ظ�
            else if(energy>50) {
                ftime(&now);
                _now=localtime(&now.time);
                deltaT=((double)(now.millitm-lastTimex.millitm))/1000;
                if(deltaT<0) {
                    deltaT += 1;
                }
                energy += 0.5*deltaT;
                speed = MID;
            }
                //��������10С��50ʱ�������ظ�
            else if(energy>10) {
                ftime(&now);
                _now=localtime(&now.time);
                deltaT=((double)(now.millitm-lastTimex.millitm))/1000;
                if(deltaT<0) {
                    deltaT += 1;
                }
                energy += 1 * deltaT;
                speed = LOW;
            }
                //��������0С��10ʱ�������ظ�
            else if(energy>0) {
                ftime(&now);
                _now=localtime(&now.time);
                deltaT=((double)(now.millitm-lastTimex.millitm))/1000;
                if(deltaT<0) {
                    deltaT += 1;
                }
                energy += 2*deltaT;
                speed = ZERO;
            }
                //������ֵС��0ʱ����Ϊ0
            else
                energy=0;
            //�õ���ǰʱ��
            ftime(&lastTimex);
            ftime(&lastTimey);
            ftime(&lastTime);
        }
        //��p��Ϊ��
        p='#';

//        float x = 375;
//        float y = 0;
        //����������ʱ������������ʾ
        if(energy0!=(int)energy) {
            cleanEndurance();
            dis_24zf(380, 144, ToString(energy, s), WHITE);
        }
        //���ٶȸ���ʱ�������ٶ���ʾ
        if(v0!=(int)v) {
            cleanVelocity();
            dis_24zf(380, 200, ToString(v, s), WHITE);
        }
        //���˶����������ʱ�������˶�������ʾ
        if(((int)len%1000-(int)len%10)/10-plen>=1) {
            len0=len;
            zlen=len0/1000;
            plen=(len0%1000-len0%10)/10;
            cleanLength();
            if(zlen/10!=0) {
                dis_24zf(380, 256, ToString(zlen, s), WHITE);
            }
            else{
                dis_24zf(408, 256, ToString(zlen, s), WHITE);
            }
            SVGA_Ball(438,279,2, WHITE);
            if(plen/10!=0) {
                dis_24zf(440, 256, ToString(plen, s), WHITE);
            }
            else{
                dis_24zf(440, 256, "0", WHITE);
                dis_24zf(468, 256, ToString(plen, s), WHITE);
            }
        }
        //���µ�ǰ�����ݵ�����ֵ
        v0=v;
        energy0=energy;
        len0=len;
///////////////////////////////////////////
        time(&now);
        if(ifPause==2)
            st+=now-st-delta;
        if(delta/60!=(now-st)/60) {
            delta=now-st;
            cleanTotalTimeMin();
            dis_24zf(380, 312, ToString(delta/60,s), WHITE);
            cleanTotalTimeSecond();
            dis_24zf(380, 340,"0" , WHITE);
        }
        if(delta!=now-st) {
            delta=now-st;
            cleanTotalTimeSecond();
            dis_24zf(380, 340,ToString(delta%60,s) , WHITE);
        }
//        else{
//            cleanTotalTimeSecond();
//            dis_24zf(380, 340,ToString(0,s) , WHITE);
//        }
///////////////////////////////////////////
        //�����˶�����ʱ��
        drawClock(380, 88, WHITE, LIGHT_GRAY);
    }
}

////������תΪ�ַ��������ظ��ַ���
char* ToString(int x,char* s){
    itoa(x,s,10);
    return s;
}

void Character::ShowResult(void){
    ;
}

////��ÿ�ʼ�˶���ʱ��
//void Character::StartTime(struct tm * sTime){
//    sTime=startTime;
//}
////��ý����˶���ʱ��
//void Character::EndTime(struct tm * eTime){
//    eTime=endTime;
//}
////��ô˴��˶���·�̳���
//int Character::Len(void){
//    return len;
//}
////��ô˴��˶���ʱ��
//int Character::TimeLen(void){
//    return (startTime->tm_hour-endTime->tm_hour)*3600+(startTime->tm_min-endTime->tm_min)*60+(startTime->tm_sec-endTime->tm_sec);
//}
////    if(a>maxA)
////        a =maxA;
////    else if(a<minA)
////        a=minA;
