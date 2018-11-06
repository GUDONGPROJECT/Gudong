#include"Run.h"

//���캯������ʼ��Character
Character::Character(void/*int _x=500,int _y=500,float _angle=90*/){
    // ��ȡ��ʼ�˶���ʱ��
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
//����Character�ĸ����������
bool Character::UpdatePos(void) {
    if (v == 0&&a==0)
        return false;
    int rate = 4;
    double deltaT, deltaTx, deltaTy, deltaLenx, deltaLeny;
    struct timeb now;
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
    deltaLenx = v * rate * deltaTx;
    deltaLeny = v * rate * deltaTy;
    if (abs(deltaLenx * cos(angle)) >= 1) {
        x += deltaLenx * cos(angle);
        lastTimex = now;
    }
    if (abs(deltaLeny * sin(angle)) >= 1) {
        y -= deltaLeny * sin(angle);
        lastTimey = now;
    }
    /*
     * speed���ٶȵĹ�ϵ����
     */
    if(a==maxA) {
        if (speed == HIGH && v < maxV) {
                v += a * deltaT;
        }
        else if (speed == MID&&v!=midV) {
            if (v > midV) {
                if (v - a * deltaT > midV)
                    v -= a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
            else if (v < midV) {
                if (v + a * deltaT < midV)
                    v += a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
        }
        else if (speed == LOW&&v!=lowV) {
            if (v > lowV) {
                if(v-a*deltaT>lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
            else if (v < lowV){
                if(v+a*deltaT<lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
        }
        else if (speed == ZERO && v > minV) {
            v -= a * deltaT;
        }
    }
    else if(a==minV&&v!=minV) {
        v += a * deltaT;
    }
    inScale();
    float temp = sqrt(pow(x - bgX, 2) + pow(y - bgY, 2)) / rate;
    len += temp;
    if (energy > 100) {
        energy = 100;
    }
    else if (energy > 80) {
        energy -= 0.1 * temp;
        if(energy<=80) {
            speed = MID;
            if(a!=minA)
                a=maxA;
        }
    }
    else if (energy > 50) {
        energy -= 3 * temp / 80;
        if(energy<=50) {
            speed = LOW;
            if(a!=minA)
                a = maxA;
        }
    }
    else if (energy > 10) {
        energy -= 0.04 * temp;
        if(energy<=10) {
            speed = ZERO;
            if(a!=minA)
                a = maxA;
        }
    }
    else if(energy<0){
        energy = 0;
    }
    return true;
}
//����Character����ʾ
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

//���Character�ĸ�����������Ƿ���ָ����Χ�ڣ����������и���
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
//�Լ����������Ӧ
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
//��ʼִ���˶�ѭ��
void Character::Run(void/*PEOPLE *people*/){
    char p;
    UpdateShow();
    while(1) {
        if (kbhit())
            p=getch();
            OnKbhit(p);
        if(energy>10&&(UpdatePos()||p=='a'||p=='A'||p=='d'||p=='D'))
            UpdateShow();
        else {
            double deltaT;
            struct timeb now;
            struct tm *_now;
            struct tm *_lastTime;
            _lastTime=localtime(&lastTimex.time);
            if(energy>100)
                energy=100;
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
            else
                energy=0;
            ftime(&lastTimex);
            ftime(&lastTimey);
            ftime(&lastTime);
        }
        p=' ';
    }
    time_t now;
    time(&now);
    endTime = localtime(&now);
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
