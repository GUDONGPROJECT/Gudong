#include"Run.h"

//���캯������ʼ��Character
Character::Character(void/*int _x=500,int _y=500,float _angle=90*/){
    // ��ʼ�����ֲ���
    time_t now;
    time(&now);
    startTime = localtime(&now);
    ftime(&lastTimex);
    ftime(&lastTimey);
    x=500;
    y=500;
    angle=Pi*90/180;
    v=0;
    a=0;
    len=0;
    speed=HIGH;
    energy=100;
    GetBg();
//    w=0;
}
//��ʾCharacter
void Character::Show(void){
    float size=5.5;
    Pieslice(x+4*size*cos(angle),y-4*size*sin(angle),angle-7*Pi/6,angle-5*Pi/6,2*1.732*size, BLUE);
    SVGA_Ball(x,y,2*size,WHITE);
    SVGA_Ball(x,y,1.5*size,BLUE);
}
//����ԭ��λ�õ�get����image
void Character::PutBg(void){
    float size=5.5;
    put_image(bgX-4*size, bgY-4*size, bgX+4*size, bgY+4*size, bg);
}
//��ȡ��Ҫ�ƶ�����λ�õ�image
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
void Character::OnKbhit(char key) {
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
    }
    else if(key=='s'||key=='S') {
        if (v != 0)
            a = minA;
    }
//    else if(key=='s'||key=='S')
//        a=minA;
    else if(key=='a'||key=='A')
        angle+=5*Pi/180;
    else if(key=='d'||key=='D')
        angle-=5*Pi/180;
//    else if(key=='0')   //��#�˳��˶�
//        break;
}
////��ʼִ���˶�ѭ��
void Character::Run(void/*PEOPLE *people*/){
    char p;
    char s[10];
    int v0=v,energy0=energy,len0=len,zlen=0,plen=0,min=0,sec=0;
//    time(&now);
//    long delta=now-st;
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
            OnKbhit(p);
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
        p=' ';

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
//        time(&now);
//        if(delta/60!=(now-st)/60) {
//            delta=now-st;
//            cleanTotalTimeMin();
//            dis_24zf(380, 312, ToString(delta/60,s), WHITE);
//        }
//        if(delta!=now-st) {
//            delta=now-st;
//            cleanTotalTimeSecond();
//            dis_24zf(380, 340,ToString(delta%60,s) , WHITE);
//        }
        //������Ŷ������ʱ��
        drawClock(380, 88, WHITE, LIGHT_GRAY);
    }
    //����˶�����ʱ��
    time_t now;
    time(&now);
    endTime = localtime(&now);
}

////������תΪ�ַ��������ظ��ַ���
char* ToString(int x,char* s){
    itoa(x,s,10);
    return s;
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
