#include"Mine.h"

State MineMain(MOUSE *mouse,PEOPLE *people) {
    Mine state = MAIN;
    float size = 5.5;
    mouse_reset(mouse);//重置鼠标
    while (1) {
        //当位于我的主界面时
        if (state == MAIN) {
            Draw_Mine(people);
            mouse_position(mouse);  //获取鼠标位置
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
            mouse_copy(mouse);      //保存鼠标将覆盖区域
            mouse_show(mouse);      //画出鼠标
            //}
            while (1) {
                //当点击鼠标
                if (mouse->button == 1) {
                    //是否点击运动记录
                    if (mouse->pos_x > 0 && mouse->pos_y > 60 * size && mouse->pos_x < 68 * size &&
                        mouse->pos_y < 77 * size) {
                        state = RECORDS;
                        break;
                    }
                    //是否点击退出
                    if (mouse->pos_x > 4 * size && mouse->pos_y > 84 * size - 12 * size &&
                        mouse->pos_x < 64 * size * size &&
                        mouse->pos_y < 84 * size + 12) {
                        return BACK;
                        //退出
                    }
                    //当鼠标点击区域为下方5栏
                    if (mouse->pos_y > 134 * size && mouse->pos_y < 140 * size) {
                        //当点击运动圈
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //当点击发现
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //当点击运动
                        if (mouse->pos_x < 40.5 * size && mouse->pos_x > 27.5 * size)
                            return SPORTPAGE;
                        //当点击干货
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
            }
        }
        //当位于运动记录界面时
        if (state == RECORDS) {
            Draw_Records();
            mouse_position(mouse);//获取鼠标位置
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
            mouse_copy(mouse);      //保存鼠标将覆盖区域
            mouse_show(mouse);      //画出鼠标
            //}
            Record *stP = (Record *) malloc(sizeof(Record));
            Record *topP = (Record *) malloc(sizeof(Record));
            stP->next = topP;
            topP->last = stP;
            int year, mon, day, hour, min;
            char key[10];
            FILE *fp = fopen(people->txtname, "r+");
            for(int i=0;i<11;i++) //不含密码，循环10次到开始，含密码循环11次
                fscanf(fp, "%s", key);
            while (1) {
                char *zS = (char *) malloc(3 * sizeof(char));
                char *pS = (char *) malloc(3 * sizeof(char));
                char *mT = (char *) malloc(3 * sizeof(char));
                char *sT = (char *) malloc(3 * sizeof(char));
                char *zV = (char *) malloc(3 * sizeof(char));
                char *pV = (char *) malloc(3 * sizeof(char));
                if (GetRecord(fp, zS, pS, mT, sT, zV, pV, year, mon, day, hour, min)) {
                    Record *p = (Record *) malloc(sizeof(Record));
                    p->Init(zS, pS, mT, sT, zV, pV, year, mon, day, hour, min);
                    topP->last->next = p;
                    p->last = topP->last;
                    p->next = topP;
                    topP->last = p;
                } else {
                    break;
                }
            }
            topP->last=topP->last->last;
            topP->last->next=topP;
            Record *p = (Record *) malloc(sizeof(Record));
            p=topP;
            bool flag=false;
            while (1) {
                //当点击鼠标
                for(int i=0;i<4;i++){
                    if(p->last!=stP) {
                        p = p->last;
                        p->Dis(BASEH+i*DELTA);
                    }
                    else
                        break;
                }
                for(int j=0;j<i;j++){
                        p = p->next;
                }
                while(1) {
                    if (mouse->button == 1&& mouse->pos_x <= 374) {
                        //如果点击第一个运动记录
                        if (mouse->pos_y >= BASEH && mouse->pos_y <= BASEH+DELTA-1) {
                            if(i>=1)
                                p->last->Show();
                        }
                        //如果点击第二个运动记录
                        else if (mouse->pos_y >= BASEH+DELTA && mouse->pos_y <= BASEH+2*DELTA-1) {
                            if(i>=2)
                                p->last->last->Show();
                        }
                        //如果点击第三个运动记录
                        else if (mouse->pos_y >= BASEH+2*DELTA && mouse->pos_y <= BASEH+3*DELTA-1) {
                            if(i>=3)
                                p->last->last->last->Show();
                        }
                        //如果点击第四个运动记录
                        else if (mouse->pos_y >= BASEH+3*DELTA && mouse->pos_y <= BASEH+4*DELTA-1) {
                            if(i==4)
                                p->last->last->last->last->Show();
                        }
                        //10*size,128*size+1,30*size,138*size    38*size,128*size+1,58*size,138*size
                        // SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
                        //    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
                        //如果点击上一页
                        else if(mouse->pos_y >= 128*size+1 && mouse->pos_y <= 138*size && mouse->pos_x >= 10*size && mouse->pos_x <= 30*size){
                            if(p!=topP){
                                for(int j=0;j<4;j++)
                                    p = p->next;
                                //清空原页面
                                SVGA_Bar(0,BASEH,68*5.5,BASEH+4*DELTA,WHITE);
                                mouse->button = 0;
                                break;
                            }
                        }
                        //如果点击下一页
                        else if(mouse->pos_y >= 128*size+1 && mouse->pos_y <= 138*size && mouse->pos_x >= 38*size && mouse->pos_x <= 58*size){
                            if(i==4&&p->last->last->last->last->last!=stP){
                                for(int j=0;j<4;j++){
                                    p = p->last;
                                }
                                //清空原页面
                                SVGA_Bar(0,BASEH,68*5.5,BASEH+4*DELTA,WHITE);
                                mouse->button = 0;
                                break;
                            }
                        }
                        //如果点击返回
                        else if(mouse->pos_y >= 8*size && mouse->pos_y <= 12*size && mouse->pos_x >= 4*size && mouse->pos_x <= 6*size){
                            state=MAIN;
                            flag=true;
                            break;
                        }
                    }
                    mouse_position(mouse);
                    drawmouse(mouse);
                }
                //当点击了退出时，释放空间,退出
                if(flag) {
                    for(p=stP;p!=topP;){
                        Record* temp=p->next;
                        free(p);
                        p=temp;
                    }
                    free(topP);
                    stP=NULL;
                    topP=NULL;
                    p=NULL;
                    break;
                }
            }
        }
    }
}

/**********************************************************
Function：		Draw_Mine

Description：	画我的的主界面

Input：			NONE

Output：		我的主界面

Return：		NONE
**********************************************************/
void Draw_Mine(PEOPLE* people){
    float size=5.5;
    char times[10];
    itoa(people->exeTimes,times,10);
    //处理运动距离
    int s=people->runLen+people->walkLen+people->rideLen;
    char pS[3]; //跑步总公里的小数部分
    char zS[3]; //跑步总公里的整数部分
    itoa(s/1000,zS,10);
    itoa((s%1000-s%10)/10,pS,10);
    if(strlen(zS)!=2) {
        zS[2]='\0';
        zS[1]=zS[0];
        zS[0]='0';
    }
    if(strlen(pS)!=2) {
        pS[2]='\0';
        pS[1]=pS[0];
        pS[0]='0';
    }
    //将len转换为浮点公里整数与小数部分
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //钱包按钮
    dis_16hz(2*size,8*size,"钱包",BLACK);
    //消息按钮
    dis_16hz(66*size-32,8*size,"消息",BLACK);
    //头像
    SVGA_Ball(34*size,26*size,6*size,DARK_GRAY);
    //用户名
    dis_24zf(34*size-12*strlen(people->name),35*size-12,people->name,BLACK);
    //分割线
    SVGA_Line(3*size,40*size,65*size,40*size,DARK_GRAY);
    //分割条
    SVGA_Bar(0,58*size,68*size,60*size,LIGHT_GRAY);
    //画运动记录按钮(0,60*size,68*size,70*size)
    dis_24zf(4*size,65*size,times,BLACK);
    dis_24hz(4*size+strlen(times)*24,65*size,"次运动",BLACK);
    dis_16hz(4*size,70*size,"最近运动",LIGHT_GRAY);
    dis_16zf(4*size+5*16,70*size,zS,LIGHT_GRAY);
    SVGA_Ball(4*size+(5+strlen(zS))*16+8,70*size+14,2,LIGHT_GRAY);
    dis_16zf(4*size+(6+strlen(zS))*16,70*size,pS,LIGHT_GRAY);
    dis_16hz(4*size+(6+strlen(zS)+strlen(pS))*16,70*size,"公里",LIGHT_GRAY);
    dis_16hz(50*size,68.5*size-8,"查看记录",LIGHT_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,67.5*size,DARK_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,69.5*size,DARK_GRAY);
    //分割条
    SVGA_Bar(0,77*size,68*size,130*size,LIGHT_GRAY);
    //画退出按钮(0,60*size,68*size,70*size)
    SVGA_Bar(4*size,84*size-12,64*size,84*size+12,WHITE);
    dis_16hz(34*size-32,84*size-8,"退出登录",RED);
//    SVGA_Line(66*size,84*size,65*size,83*size,DARK_GRAY);
//    SVGA_Line(66*size,84*size,65*size,85*size,DARK_GRAY);
    //分割条
    //SVGA_Bar(0,89*size,68*size,130*size,LIGHT_GRAY);
    //Simple setting(0,60*size,68*size,70*size,"设置");
    //底部5个按钮
    SVGA_Bar(0, 134 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "运动圈", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "发现", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "运动", LIGHT_GRAY);
    dis_16hz(47 * size - 16, 136 * size - 8, "干货", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "我的", GREEN);
//    dis_16hz(8 * size - 8 * 3, 137 * size - 8, "运动圈", LIGHT_GRAY);
//    dis_16hz(21 * size - 16, 137 * size - 8, "发现", LIGHT_GRAY);
//    dis_16hz(34 * size - 16, 137 * size - 8, "运动", LIGHT_GRAY);
//    dis_16hz(47 * size - 16, 137 * size - 8, "干货", LIGHT_GRAY);
//    dis_16hz(60 * size - 16, 137 * size - 8, "我的", GREEN);
}
/**********************************************************
Function：		Draw_Records

Description：	画我的的运动记录界面

Input：			PEOPLE* people

Output：		我的运动记录界面

Return：		NONE
**********************************************************/
void Draw_Records(void){
    float size=5.5;
    //画背景色
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //画返回按键
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    //画运动记录题头
    dis_24hz(34*size-48,10*size-12,"运动记录",BLACK);
    //画分割线
    SVGA_Bar(0,20*size,68*size,24*size,LIGHT_GRAY);
    //画上一页按钮
    SVGA_Bar(10*size,128*size+1,30*size,138*size,LIGHT_GRAY);
    SVGA_Line(20*size,131*size,17*size,134*size,WHITE);
    SVGA_Line(20*size,131*size,23*size,134*size,WHITE);
    //画下一页按钮
    SVGA_Bar(38*size,128*size+1,58*size,138*size,LIGHT_GRAY);
    SVGA_Line(48*size,135*size,45*size,132*size,WHITE);
    SVGA_Line(48*size,135*size,51*size,132*size,WHITE);
}

void Record::Init(char* zs,char* ps,char* mt,char* st,char* zv,char* pv,int y,int m,int d,int h,int mi){
    zS=zs;
    pS=ps;
    mT=mt;
    sT=st;
    zV=zv;
    pV=pv;
    year=y;
    mon=m;
    day=d;
    hour=h;
    min=mi;
    next=NULL;
    last=NULL;
}
void Record::Dis(int h){
    float size=5.5;
    char s[5];
    //画跟下一个记录的分割线
    SVGA_Line(0,h+25*size-1,68*size,h+25*size-1,LIGHT_GRAY);
    //画运动图像
    SVGA_Bar(3*size,h+3*size,21*size,h+21*size,DARK_GRAY);
    //显示运动时刻
    ToString(hour,s);
    if(strlen(s)!=2){
        s[2]='\0';
        s[1]=s[0];
        s[0]='0';
    }
    dis_16zf(25*size,h+3*size,s,LIGHT_GRAY);
    SVGA_Ball(25*size+33,h+3*size+3,2,LIGHT_GRAY);
    SVGA_Ball(25*size+33,h+3*size+13,2,LIGHT_GRAY);
    ToString(min,s);
    if(strlen(s)!=2){
        s[2]='\0';
        s[1]=s[0];
        s[0]='0';
    }
    dis_16zf(25*size+34,h+3*size,s,LIGHT_GRAY);
    //显示运动日期
    dis_16zf(40*size,h+3*size,ToString(year,s),LIGHT_GRAY);
    SVGA_Ball(40*size+65,h+3*size+13,3,LIGHT_GRAY);
    dis_16zf(40*size+66,h+3*size,ToString(mon,s),LIGHT_GRAY);
    SVGA_Ball(40*size+99,h+3*size+13,3,LIGHT_GRAY);
    dis_16zf(40*size+100,h+3*size,ToString(day,s),LIGHT_GRAY);
    //显示运动距离
    dis_24zf(25*size,h+12.5*size-12,zS,BLACK);
    SVGA_Ball(25*size+49,h+12.5*size+9,3,BLACK);
    dis_24zf(25*size+50,h+12.5*size-12,pS,BLACK);
    dis_16hz(25*size+100,h+12.5*size-4,"公里",LIGHT_GRAY);
    //显示运动时长
    SVGA_Cricle(25*size+8,h+22*size-8,8,LIGHT_GRAY);
    SVGA_Ball(25*size+8,h+22*size-8,2,LIGHT_GRAY);
    SVGA_Line(25*size+8,h+22*size-8,25*size+8,h+22*size-13,LIGHT_GRAY);
    SVGA_Line(25*size+8,h+22*size-8,25*size+8+0.707*5,h+22*size-8+0.707*5,LIGHT_GRAY);
    dis_16zf(30*size,h+22*size-16,mT,LIGHT_GRAY);
    SVGA_Ball(30*size+33,h+22*size-4,2,LIGHT_GRAY);
    SVGA_Ball(30*size+33,h+22*size-12,2,LIGHT_GRAY);
//    SVGA_Bar(30*size+33,h+22*size-29,30*size+34,h+22*size-13,LIGHT_GRAY);
    dis_16zf(30*size+35,h+22*size-16,sT,LIGHT_GRAY);
//    SVGA_Bar(30*size+36,h+22*size-29,30*size+37,h+22*size-13,LIGHT_GRAY);
//    SVGA_Bar(30*size+40,h+22*size-29,30*size+41,h+22*size-13,LIGHT_GRAY);
    //显示运动速度
    SVGA_Cricle(45*size+8,h+22*size-8,8,LIGHT_GRAY);
    SVGA_Ball(45*size+8,h+22*size-8,2,LIGHT_GRAY);
    SVGA_Line(45*size+8,h+22*size-8,45*size+8+0.707*5,h+22*size-8-0.707*5,LIGHT_GRAY);
    dis_16zf(50*size,h+22*size-16,zV,LIGHT_GRAY);
    SVGA_Ball(50*size+35,h+22*size-3,3,LIGHT_GRAY);
    dis_16zf(50*size+38,h+22*size-16,pV,LIGHT_GRAY);
    //画展示按钮
    SVGA_Line(66*size,h+12.5*size,66*size-10,h+12.5*size+10,LIGHT_GRAY);
    SVGA_Line(66*size,h+12.5*size,66*size-10,h+12.5*size-10,LIGHT_GRAY);
};
void Record::Show(){
    float size=5.5;
    char s[5];
    //画页面大背景色
    SVGA_Bar(375,0,1024,768,DARK_GRAY);
    //显示运动时刻
    ToString(hour,s);
    if(strlen(s)!=2){
        s[2]='\0';
        s[1]=s[0];
        s[0]='0';
    }
    dis_16zf(100*size,2*size,s,LIGHT_GRAY);
    SVGA_Ball(100*size+33,2*size+3,2,LIGHT_GRAY);
    SVGA_Ball(100*size+33,2*size+13,2,LIGHT_GRAY);
    ToString(min,s);
    if(strlen(s)!=2){
        s[2]='\0';
        s[1]=s[0];
        s[0]='0';
    }
    dis_16zf(100*size+34,2*size,s,LIGHT_GRAY);
    //显示运动日期
    dis_16zf(70*size,2*size,ToString(year,s),LIGHT_GRAY);
    SVGA_Ball(70*size+65,2*size+13,3,LIGHT_GRAY);
    dis_16zf(70*size+66,2*size,ToString(mon,s),LIGHT_GRAY);
    SVGA_Ball(70*size+99,2*size+13,3,LIGHT_GRAY);
    dis_16zf(70*size+100,2*size,ToString(day,s),LIGHT_GRAY);
    //显示运动距离
    dis_24zf(699 - 48, 65 * size-12, zS, WHITE);
    SVGA_Ball(699 ,65 * size-12+21,3, WHITE);
    dis_24zf(699 , 65 * size-12, pS, WHITE);
    dis_16hz(699 - 8 * 5, 65 * size+24, "运动总公里", LIGHT_GRAY);
    //显示时间
    dis_16zf(494 - 48, 90 * size, mT, WHITE);
    SVGA_Ball(500 ,90 * size+5,2, WHITE);
    SVGA_Ball(500 ,90 * size+11,2, WHITE);
    dis_16zf(494 + 16, 90 * size, sT, WHITE);
    dis_16hz(494 - 16, 96 * size, "分", LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+5,2, LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+11,2, LIGHT_GRAY);
    dis_16hz(494 + 16, 96 * size, "秒", LIGHT_GRAY);
    //显示平均速度
    dis_16zf(904 - 32, 90 * size, zV, WHITE);
    SVGA_Ball(907 ,90 * size+12,3, WHITE);
    dis_16zf(904,90*size,":",WHITE);
    dis_16zf(904 + 16, 90 * size, pV, WHITE);
    dis_16hz(904 - 24, 100 * size, "米每秒", LIGHT_GRAY);
}

