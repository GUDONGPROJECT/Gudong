#include "UserIO.h"

void DataIn(PEOPLE *people,char* key,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int year,int mon,int day,int hour,int min){
    FILE* fp=fopen(people->txtname, "a+");
    fprintf(fp,"%s %s %s %s %s %s %s %d %d %d %d %d\n",key,zS,pS,mT,sT,zV,pV,year,mon,day,hour,min);
    fclose(fp);
}

bool GetRecord(FILE* fp,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int& year,int& mon,int& day,int& hour,int& min){
    //检测文件
    if(feof(fp))
        return false;
    char key[2];
    fscanf(fp,"%s%s%s%s%s%s%s%d%d%d%d%d",key,zS,pS,mT,sT,zV,pV,&year,&mon,&day,&hour,&min);
    return true;
}

bool GetData(FILE* fp,char* key,char* zS,char* pS,char* mT,char* sT,char* zV,char* pV,int& year,int& mon,int& day,int& hour,int& min){
    //检测文件
    if(feof(fp))
        return false;
    fscanf(fp,"%s%s%s%s%s%s%s%d%d%d%d%d",key,zS,pS,mT,sT,zV,pV,&year,&mon,&day,&hour,&min);
    return true;
}


