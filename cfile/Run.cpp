#include"Run.h"

////开始进入运动
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

////构造函数，初始化Character
Character::Character(PEOPLE *people0,int state0){
    // 初始化各种参数
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

////析构函数
Character::~Character(void){
    float size=5.5;
    char mT[3];
    char sT[3];
    SVGA_Bar(375,0,1024,768,DARK_GRAY);
    char zV[3];
    char pV[3];
    //显示运动距离
    int s=len;
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
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
    dis_16hz(699 - 8 * 5, 65 * size+24, "运动总公里", LIGHT_GRAY);
    //显示时间
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
    dis_16hz(494 - 16, 96 * size, "分", LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+5,2, LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+11,2, LIGHT_GRAY);
    dis_16hz(494 + 16, 96 * size, "秒", LIGHT_GRAY);
    //显示平均速度
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
    dis_16hz(904 - 24, 100 * size, "米每秒", LIGHT_GRAY);
    //将数据写入文件与people
    char key[2];
    if(state==RUN) {
        key[0]='#';//代表为跑步
        key[1]='\0';
        DataIn(people, key,zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->runLen+=s;
    }
    else if(state==WALK){
        key[0]='*';//代表为跑步
        key[1]='\0';
        DataIn(people,key, zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->walkLen+=s;
    }
    else if(state==RIDE){
        key[0]='&';//代表为跑步
        key[1]='\0';
        DataIn(people,key, zS, pS, mT, sT, zV, pV, startTime->tm_year + 1900, startTime->tm_mon + 1, startTime->tm_mday,
               startTime->tm_hour, startTime->tm_min);
        people->rideLen+=s;
    }
    people->exeTimes++;
}

////显示Character
void Character::Show(void){
    float size=5.5;
    Pieslice(x+4*size*cos(angle),y-4*size*sin(angle),angle-7*Pi/6,angle-5*Pi/6,2*1.732*size, BLUE);
    SVGA_Ball(x,y,2*size,WHITE);
    SVGA_Ball(x,y,1.5*size,BLUE);
}
////放置原来位置的get到的image
void Character::PutBg(void){
    float size=5.5;
    put_image(bgX-4*size, bgY-4*size, bgX+4*size, bgY+4*size, bg);
}
////获取将要移动到的位置的image
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
    else if(key==' '){   //按空格暂停运动
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
////开始执行运动循环
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
    //进入运动循环
    while(1) {
        //监听按键
        if (kbhit())
            p=getch();
        if(ifPause=OnKbhit(p)) {
            if(ifPause==1)
                break;
        }
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
        p='#';

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
        //更新运动结束时间
        drawClock(380, 88, WHITE, LIGHT_GRAY);
    }
}

////将整数转为字符串并返回该字符串
char* ToString(int x,char* s){
    itoa(x,s,10);
    return s;
}

void Character::ShowResult(void){
    ;
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
