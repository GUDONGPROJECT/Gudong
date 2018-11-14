#include"Run.h"

//构造函数，初始化Character
Character::Character(void/*int _x=500,int _y=500,float _angle=90*/){
    // 初始化各种参数
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
////更新Character的各种物理参数
bool Character::UpdatePos(void) {
    //当速度与加速度为0时，返回false，表示没有在运动
    if (v == 0&&a==0)
        return false;
    //速度或加速度不为0时，开始物理参数的更新
    int rate = 4;
    double deltaT, deltaTx, deltaTy, deltaLenx, deltaLeny;
    struct timeb now;
    //获取距离上次更新参数的时间
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
    //计算该次更新前进的x、y轴上的距离
    deltaLenx = v * rate * deltaTx;
    deltaLeny = v * rate * deltaTy;
    //当前进距离大于或等于1个像素时，更新距离，更新当前更新数据的时间
    if (abs(deltaLenx * cos(angle)) >= 1) {
        x += deltaLenx * cos(angle);
        lastTimex = now;
    }
    if (abs(deltaLeny * sin(angle)) >= 1) {
        y -= deltaLeny * sin(angle);
        lastTimey = now;
    }
    /***********************
     * speed与速度的关系调整*
     **********************/
     //当加速时
    if(a==maxA) {
        //当速度为高速且当前速度小于最高速时，加速
        if (speed == HIGH && v < maxV) {
                v += a * deltaT;
        }
        //当速度为中速且当前速度不等于最高中速时
        else if (speed == MID&&v!=midV) {
            //当前速度大于最高中速时，减速
            if (v > midV) {
                if (v - a * deltaT > midV)
                    v -= a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
            //当前速度小于最高中速时，加速
            else if (v < midV) {
                if (v + a * deltaT < midV)
                    v += a * deltaT;
                else {
                    v = midV;
                    a = 0;
                }
            }
        }
        //当速度为低速且当前速度不等于最高低速时
        else if (speed == LOW&&v!=lowV) {
            //当前速度大于最高低速时，减速
            if (v > lowV) {
                if(v-a*deltaT>lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
            //当前速度小于最高低速时，加速
            else if (v < lowV){
                if(v+a*deltaT<lowV)
                    v -= a * deltaT;
                else {
                    v = lowV;
                    a = 0;
                }
            }
        }
        //当速度状态为零速时，减速
        else if (speed == ZERO && v > minV) {
            v -= a * deltaT;
        }
    }
    //当为减速状态时，在速度为0前减速
    else if(a==minA&&v!=minV) {
        v += a * deltaT;
    }
    //检测个物理参数是否在给定范围内
    inScale();
    //更新体力消耗
    float temp = sqrt(pow(x - bgX, 2) + pow(y - bgY, 2)) / rate;
    len += temp;    //更新运动距离
    //当体力大于100时，将体力值置为100
    if (energy > 100) {
        energy = 100;
    }
    //当体力大于80小于100时的体力消耗速率
    else if (energy > 80) {
        energy -= 0.1 * temp;
        //当更新后体力小于80时，将速度模式置为中速
        if(energy<=80) {
            speed = MID;
//            dis_16zf(700,i,ToString(a,s),BLACK);
//            i+=16;
        //当加速度为0时，将加速度置为maxA模式
            if(a==0)
                a=maxA;
        }
    }
    //当体力大于50小于80时的体力消耗速率
    else if (energy > 50) {
        energy -= 3 * temp / 80;
        //当更新后体力小于50时，将速度模式置为低速
        if(energy<=50) {
            speed = LOW;
            //当加速度为0时，将加速度置为maxA模式
            if(a==0)
                a = maxA;
        }
    }
    //当体力大于10小于50时的体力消耗速率
    else if (energy > 10) {
        energy -= 0.04 * temp;
        //当更新后体力小于10时，将速度模式置为零速
        if(energy<=10) {
            speed = ZERO;
            //当加速度为0时，将加速度置为maxA模式
            if(a==0)
                a = maxA;
        }
    }
    //当体力小于0时，将体力置为0
    else if(energy<0){
        energy = 0;
    }
    return true;
}
////更新Character的显示
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

////检测Character的各种物理参数是否在指定范围内，若不，进行更正
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
////对键盘输入的响应
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
////开始执行运动循环
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
    //进入运动循环
    while(1) {
        //监听按键
        if (kbhit())
            p=getch();
            OnKbhit(p);
        //运动，更新位置时，刷新人物位置显示
        if(energy>10&&(UpdatePos()||p=='a'||p=='A'||p=='d'||p=='D'))
            UpdateShow();
        //没有在运动时，回复体力
        else {
            double deltaT;
            struct timeb now;
            struct tm *_now;
            struct tm *_lastTime;
            _lastTime=localtime(&lastTimex.time);
            //体力大于100时，体力值置为100
            if(energy>100)
                energy=100;
            //体力大于80时的体力回复
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
            //体力大于50小于80时的体力回复
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
            //体力大于10小于50时的体力回复
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
            //体力大于0小于10时的体力回复
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
            //当体力值小于0时，置为0
            else
                energy=0;
            //得到当前时间
            ftime(&lastTimex);
            ftime(&lastTimey);
            ftime(&lastTime);
        }
        //将p置为空
        p=' ';

//        float x = 375;
//        float y = 0;
        //当体力更新时，跟新体力显示
        if(energy0!=(int)energy) {
            cleanEndurance();
            dis_24zf(380, 144, ToString(energy, s), WHITE);
        }
        //当速度更新时，跟新速度显示
        if(v0!=(int)v) {
            cleanVelocity();
            dis_24zf(380, 200, ToString(v, s), WHITE);
        }
        //当运动服距离更新时，跟新运动距离显示
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
        //更新当前各数据的整型值
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
        //更新晕哦东结束时间
        drawClock(380, 88, WHITE, LIGHT_GRAY);
    }
    //获得运动结束时间
    time_t now;
    time(&now);
    endTime = localtime(&now);
}

////将整数转为字符串并返回该字符串
char* ToString(int x,char* s){
    itoa(x,s,10);
    return s;
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
