#include"Run.h"

//构造函数，初始化Character
Character::Character(void/*int _x=500,int _y=500,float _angle=90*/){
    // 获取开始运动的时间
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
//显示Character
void Character::Show(void){
    float size=5.5;
    Pieslice(x+4*size*cos(angle),y-4*size*sin(angle),angle-7*Pi/6,angle-5*Pi/6,2*1.732*size, BLUE);
    SVGA_Ball(x,y,2*size,WHITE);
    SVGA_Ball(x,y,1.5*size,BLUE);
}
//放置原来位置的get到的image
void Character::PutBg(void){
    float size=5.5;
    put_image(bgX-4*size, bgY-4*size, bgX+4*size, bgY+4*size, bg);
}
//获取将要移动到的位置的image
void Character::GetBg(void){
    float size=5.5;
    bgX=x;
    bgY=y;
    get_image(x-4*size, y-4*size,x+4*size, y+4*size, bg);
}
//更新Character的各种物理参数
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
     * speed与速度的关系调整
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
//更新Character的显示
void Character::UpdateShow(void) {
    PutBg();    //Error:多出三点
    GetBg();
    Show();
}

//bool Character::IsMove(void){
//    if(v!=0)
//        return true;
//    return false;
//}

//检测Character的各种物理参数是否在指定范围内，若不，进行更正
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
//对键盘输入的响应
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
//    else if(key=='0')   //按#退出运动
//        break;
}
//开始执行运动循环
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
////获得开始运动的时刻
//void Character::StartTime(struct tm * sTime){
//    sTime=startTime;
//}
////获得结束运动的时刻
//void Character::EndTime(struct tm * eTime){
//    eTime=endTime;
//}
////获得此次运动的路程长度
//int Character::Len(void){
//    return len;
//}
////获得此次运动的时长
//int Character::TimeLen(void){
//    return (startTime->tm_hour-endTime->tm_hour)*3600+(startTime->tm_min-endTime->tm_min)*60+(startTime->tm_sec-endTime->tm_sec);
//}
////    if(a>maxA)
////        a =maxA;
////    else if(a<minA)
////        a=minA;
