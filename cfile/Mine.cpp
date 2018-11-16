#include"Mine.h"

State MineMain(MOUSE *mouse,PEOPLE *people) {
    Mine state = MAIN;
    float size = 5.5;
    mouse_reset(mouse);//�������
    while (1) {
        //��λ���ҵ�������ʱ
        if (state == MAIN) {
            Draw_Mine(people);
            mouse_position(mouse);  //��ȡ���λ��
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
            mouse_copy(mouse);      //������꽫��������
            mouse_show(mouse);      //�������
            //}
            while (1) {
                //��������
                if (mouse->button == 1) {
                    //�Ƿ����˶���¼
                    if (mouse->pos_x > 0 && mouse->pos_y > 60 * size && mouse->pos_x < 68 * size &&
                        mouse->pos_y < 77 * size) {
                        state = RECORDS;
                        break;
                    }
                    //�Ƿ����˳�
                    if (mouse->pos_x > 4 * size && mouse->pos_y > 84 * size - 12 * size &&
                        mouse->pos_x < 64 * size * size &&
                        mouse->pos_y < 84 * size + 12) {
                        return BACK;
                        //�˳�
                    }
                    //�����������Ϊ�·�5��
                    if (mouse->pos_y > 134 * size && mouse->pos_y < 140 * size) {
                        //������˶�Ȧ
                        if (mouse->pos_x < 14.5 * size)
                            return CIRCLE;
                        //���������
                        if (mouse->pos_x < 27.5 * size && mouse->pos_x > 14.5 * size)
                            return FIND;
                        //������˶�
                        if (mouse->pos_x < 40.5 * size && mouse->pos_x > 27.5 * size)
                            return SPORTPAGE;
                        //������ɻ�
                        if (mouse->pos_x > 40.5 * size && mouse->pos_x < 53.5 * size)
                            return THINGS;
                    }
                }
                mouse_position(mouse);
                drawmouse(mouse);
            }
        }
        //��λ���˶���¼����ʱ
        if (state == RECORDS) {
            Draw_Records();
            mouse_position(mouse);//��ȡ���λ��
            //if (mouse->pos_x != mouse->oldx || mouse->pos_y != mouse->oldy) {
            mouse_copy(mouse);      //������꽫��������
            mouse_show(mouse);      //�������
            //}
            Record *stP = (Record *) malloc(sizeof(Record));
            Record *topP = (Record *) malloc(sizeof(Record));
            stP->next = topP;
            topP->last = stP;
            int year, mon, day, hour, min;
            char key[10];
            FILE *fp = fopen(people->txtname, "r+");
            for(int i=0;i<11;i++) //�������룬ѭ��10�ε���ʼ��������ѭ��11��
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
                //��������
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
                        //��������һ���˶���¼
                        if (mouse->pos_y >= BASEH && mouse->pos_y <= BASEH+DELTA-1) {
                            if(i>=1)
                                p->last->Show();
                        }
                        //�������ڶ����˶���¼
                        else if (mouse->pos_y >= BASEH+DELTA && mouse->pos_y <= BASEH+2*DELTA-1) {
                            if(i>=2)
                                p->last->last->Show();
                        }
                        //�������������˶���¼
                        else if (mouse->pos_y >= BASEH+2*DELTA && mouse->pos_y <= BASEH+3*DELTA-1) {
                            if(i>=3)
                                p->last->last->last->Show();
                        }
                        //���������ĸ��˶���¼
                        else if (mouse->pos_y >= BASEH+3*DELTA && mouse->pos_y <= BASEH+4*DELTA-1) {
                            if(i==4)
                                p->last->last->last->last->Show();
                        }
                        //10*size,128*size+1,30*size,138*size    38*size,128*size+1,58*size,138*size
                        // SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
                        //    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
                        //��������һҳ
                        else if(mouse->pos_y >= 128*size+1 && mouse->pos_y <= 138*size && mouse->pos_x >= 10*size && mouse->pos_x <= 30*size){
                            if(p!=topP){
                                for(int j=0;j<4;j++)
                                    p = p->next;
                                //���ԭҳ��
                                SVGA_Bar(0,BASEH,68*5.5,BASEH+4*DELTA,WHITE);
                                mouse->button = 0;
                                break;
                            }
                        }
                        //��������һҳ
                        else if(mouse->pos_y >= 128*size+1 && mouse->pos_y <= 138*size && mouse->pos_x >= 38*size && mouse->pos_x <= 58*size){
                            if(i==4&&p->last->last->last->last->last!=stP){
                                for(int j=0;j<4;j++){
                                    p = p->last;
                                }
                                //���ԭҳ��
                                SVGA_Bar(0,BASEH,68*5.5,BASEH+4*DELTA,WHITE);
                                mouse->button = 0;
                                break;
                            }
                        }
                        //����������
                        else if(mouse->pos_y >= 8*size && mouse->pos_y <= 12*size && mouse->pos_x >= 4*size && mouse->pos_x <= 6*size){
                            state=MAIN;
                            flag=true;
                            break;
                        }
                    }
                    mouse_position(mouse);
                    drawmouse(mouse);
                }
                //��������˳�ʱ���ͷſռ�,�˳�
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
Function��		Draw_Mine

Description��	���ҵĵ�������

Input��			NONE

Output��		�ҵ�������

Return��		NONE
**********************************************************/
void Draw_Mine(PEOPLE* people){
    float size=5.5;
    char times[10];
    itoa(people->exeTimes,times,10);
    //�����˶�����
    int s=people->runLen+people->walkLen+people->rideLen;
    char pS[3]; //�ܲ��ܹ����С������
    char zS[3]; //�ܲ��ܹ������������
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
    //��lenת��Ϊ���㹫��������С������
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //Ǯ����ť
    dis_16hz(2*size,8*size,"Ǯ��",BLACK);
    //��Ϣ��ť
    dis_16hz(66*size-32,8*size,"��Ϣ",BLACK);
    //ͷ��
    SVGA_Ball(34*size,26*size,6*size,DARK_GRAY);
    //�û���
    dis_24zf(34*size-12*strlen(people->name),35*size-12,people->name,BLACK);
    //�ָ���
    SVGA_Line(3*size,40*size,65*size,40*size,DARK_GRAY);
    //�ָ���
    SVGA_Bar(0,58*size,68*size,60*size,LIGHT_GRAY);
    //���˶���¼��ť(0,60*size,68*size,70*size)
    dis_24zf(4*size,65*size,times,BLACK);
    dis_24hz(4*size+strlen(times)*24,65*size,"���˶�",BLACK);
    dis_16hz(4*size,70*size,"����˶�",LIGHT_GRAY);
    dis_16zf(4*size+5*16,70*size,zS,LIGHT_GRAY);
    SVGA_Ball(4*size+(5+strlen(zS))*16+8,70*size+14,2,LIGHT_GRAY);
    dis_16zf(4*size+(6+strlen(zS))*16,70*size,pS,LIGHT_GRAY);
    dis_16hz(4*size+(6+strlen(zS)+strlen(pS))*16,70*size,"����",LIGHT_GRAY);
    dis_16hz(50*size,68.5*size-8,"�鿴��¼",LIGHT_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,67.5*size,DARK_GRAY);
    SVGA_Line(66*size,68.5*size,65*size,69.5*size,DARK_GRAY);
    //�ָ���
    SVGA_Bar(0,77*size,68*size,130*size,LIGHT_GRAY);
    //���˳���ť(0,60*size,68*size,70*size)
    SVGA_Bar(4*size,84*size-12,64*size,84*size+12,WHITE);
    dis_16hz(34*size-32,84*size-8,"�˳���¼",RED);
//    SVGA_Line(66*size,84*size,65*size,83*size,DARK_GRAY);
//    SVGA_Line(66*size,84*size,65*size,85*size,DARK_GRAY);
    //�ָ���
    //SVGA_Bar(0,89*size,68*size,130*size,LIGHT_GRAY);
    //Simple setting(0,60*size,68*size,70*size,"����");
    //�ײ�5����ť
    SVGA_Bar(0, 134 * size, 68 * size, 140 * size, WHITE);
    dis_16hz(8 * size - 8 * 3, 136 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
    dis_16hz(21 * size - 16, 136 * size - 8, "����", LIGHT_GRAY);
    dis_16hz(34 * size - 16, 136 * size - 8, "�˶�", LIGHT_GRAY);
    dis_16hz(47 * size - 16, 136 * size - 8, "�ɻ�", LIGHT_GRAY);
    dis_16hz(60 * size - 16, 136 * size - 8, "�ҵ�", GREEN);
//    dis_16hz(8 * size - 8 * 3, 137 * size - 8, "�˶�Ȧ", LIGHT_GRAY);
//    dis_16hz(21 * size - 16, 137 * size - 8, "����", LIGHT_GRAY);
//    dis_16hz(34 * size - 16, 137 * size - 8, "�˶�", LIGHT_GRAY);
//    dis_16hz(47 * size - 16, 137 * size - 8, "�ɻ�", LIGHT_GRAY);
//    dis_16hz(60 * size - 16, 137 * size - 8, "�ҵ�", GREEN);
}
/**********************************************************
Function��		Draw_Records

Description��	���ҵĵ��˶���¼����

Input��			PEOPLE* people

Output��		�ҵ��˶���¼����

Return��		NONE
**********************************************************/
void Draw_Records(void){
    float size=5.5;
    //������ɫ
    SVGA_Bar(0,0,68*size,140*size,WHITE);
    //�����ذ���
    SVGA_Line(6*size,8*size,4*size,10*size,BLACK);
    SVGA_Line(6*size,12*size,4*size,10*size,BLACK);
    //���˶���¼��ͷ
    dis_24hz(34*size-48,10*size-12,"�˶���¼",BLACK);
    //���ָ���
    SVGA_Bar(0,20*size,68*size,24*size,LIGHT_GRAY);
    //����һҳ��ť
    SVGA_Bar(10*size,128*size+1,30*size,138*size,LIGHT_GRAY);
    SVGA_Line(20*size,131*size,17*size,134*size,WHITE);
    SVGA_Line(20*size,131*size,23*size,134*size,WHITE);
    //����һҳ��ť
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
    //������һ����¼�ķָ���
    SVGA_Line(0,h+25*size-1,68*size,h+25*size-1,LIGHT_GRAY);
    //���˶�ͼ��
    SVGA_Bar(3*size,h+3*size,21*size,h+21*size,DARK_GRAY);
    //��ʾ�˶�ʱ��
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
    //��ʾ�˶�����
    dis_16zf(40*size,h+3*size,ToString(year,s),LIGHT_GRAY);
    SVGA_Ball(40*size+65,h+3*size+13,3,LIGHT_GRAY);
    dis_16zf(40*size+66,h+3*size,ToString(mon,s),LIGHT_GRAY);
    SVGA_Ball(40*size+99,h+3*size+13,3,LIGHT_GRAY);
    dis_16zf(40*size+100,h+3*size,ToString(day,s),LIGHT_GRAY);
    //��ʾ�˶�����
    dis_24zf(25*size,h+12.5*size-12,zS,BLACK);
    SVGA_Ball(25*size+49,h+12.5*size+9,3,BLACK);
    dis_24zf(25*size+50,h+12.5*size-12,pS,BLACK);
    dis_16hz(25*size+100,h+12.5*size-4,"����",LIGHT_GRAY);
    //��ʾ�˶�ʱ��
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
    //��ʾ�˶��ٶ�
    SVGA_Cricle(45*size+8,h+22*size-8,8,LIGHT_GRAY);
    SVGA_Ball(45*size+8,h+22*size-8,2,LIGHT_GRAY);
    SVGA_Line(45*size+8,h+22*size-8,45*size+8+0.707*5,h+22*size-8-0.707*5,LIGHT_GRAY);
    dis_16zf(50*size,h+22*size-16,zV,LIGHT_GRAY);
    SVGA_Ball(50*size+35,h+22*size-3,3,LIGHT_GRAY);
    dis_16zf(50*size+38,h+22*size-16,pV,LIGHT_GRAY);
    //��չʾ��ť
    SVGA_Line(66*size,h+12.5*size,66*size-10,h+12.5*size+10,LIGHT_GRAY);
    SVGA_Line(66*size,h+12.5*size,66*size-10,h+12.5*size-10,LIGHT_GRAY);
};
void Record::Show(){
    float size=5.5;
    char s[5];
    //��ҳ��󱳾�ɫ
    SVGA_Bar(375,0,1024,768,DARK_GRAY);
    //��ʾ�˶�ʱ��
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
    //��ʾ�˶�����
    dis_16zf(70*size,2*size,ToString(year,s),LIGHT_GRAY);
    SVGA_Ball(70*size+65,2*size+13,3,LIGHT_GRAY);
    dis_16zf(70*size+66,2*size,ToString(mon,s),LIGHT_GRAY);
    SVGA_Ball(70*size+99,2*size+13,3,LIGHT_GRAY);
    dis_16zf(70*size+100,2*size,ToString(day,s),LIGHT_GRAY);
    //��ʾ�˶�����
    dis_24zf(699 - 48, 65 * size-12, zS, WHITE);
    SVGA_Ball(699 ,65 * size-12+21,3, WHITE);
    dis_24zf(699 , 65 * size-12, pS, WHITE);
    dis_16hz(699 - 8 * 5, 65 * size+24, "�˶��ܹ���", LIGHT_GRAY);
    //��ʾʱ��
    dis_16zf(494 - 48, 90 * size, mT, WHITE);
    SVGA_Ball(500 ,90 * size+5,2, WHITE);
    SVGA_Ball(500 ,90 * size+11,2, WHITE);
    dis_16zf(494 + 16, 90 * size, sT, WHITE);
    dis_16hz(494 - 16, 96 * size, "��", LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+5,2, LIGHT_GRAY);
    SVGA_Ball(500 ,96 * size+11,2, LIGHT_GRAY);
    dis_16hz(494 + 16, 96 * size, "��", LIGHT_GRAY);
    //��ʾƽ���ٶ�
    dis_16zf(904 - 32, 90 * size, zV, WHITE);
    SVGA_Ball(907 ,90 * size+12,3, WHITE);
    dis_16zf(904,90*size,":",WHITE);
    dis_16zf(904 + 16, 90 * size, pV, WHITE);
    dis_16hz(904 - 24, 100 * size, "��ÿ��", LIGHT_GRAY);
}

