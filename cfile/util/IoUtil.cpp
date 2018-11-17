//
// Created by patrick on 11/5/18.
//

#include "./header/IoUtil.h"
#include "./header/head.h"

/**********************************************************
Function：		Create_path

Description：	用于生成用户的用户名文件路径

Input：
				char *name       用户的用户名
				char *textname   用户名所对应的用户路径

Output：	    NONE

Return：		NONE

**********************************************************/
void Create_path(char *name, char *textname) {
    stpcpy(textname, "txt\\");
    strcat(textname, name);
    strcat(textname, ".txt");
}

/**********************************************************
Function：		R_check

Description：	用于检测用户用户名密码是否符合标准

Input：			char *txtname     用来存储用户的文件名地址
			    char *key         用户第一次输入的密码
				char *key1        用户第二次输入的密码

Output：		提示用户注册状态，保存用户名文件，生成用户文件

Return：		注册状态序号

**********************************************************/
int R_check(char *txtname, char *key, char *key1) {
    // 判断函数是否可以可录入，以及录入函数
    FILE *fp;
    float size = 5.5;
    if (strcmp(key, key1) != 0) {
        //readbmp(182,128,"pic\\notmatch.bmp");//提示前后两次的密码不相同，重新载入界面
        SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
        SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
        dis_24hz(19 * size, 327, "前后密码输入不一致", 0);
        delay(1500);
        //Regist(mouse,people);
        return 0;
    } else {
        fp = fopen(txtname, "r+");
        if (fp != NULL) {
            fclose(fp);
            //readbmp(182,128,"pic\\chongfu.bmp");//提示用户名有重复,重新载入用户登录界面
            SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
            SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
            dis_24hz(19 * size, 327, "该手机号已注册", 0);
            // 这个逻辑肯定走不到,我就皮一下
            delay(100000);
            //Regist(mouse,people);//载入登录界面
            return 0;
        } else {
            fclose(fp);
            fp = fopen(txtname, "w+");
            fprintf(fp, "%s\n", key);
            fprintf(fp, "%s\n", "0 0 0 0 0 0 0 0 0 0 ");
            fclose(fp);
            //readbmp(182,128,"pic\\okay.bmp");
            SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
            SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
            dis_24hz(19 * size, 327, "您已经注册成功", 0);
            delay(1500);
            //Begin_menu(mouse);
            return 1;
        }
    }
}

/**
 * 创建消息路径
 *
 * @param fileName
 * @param path
 */
void createMsgPath(char *fileName, char *path) {
    stpcpy(path, "txt\\things\\");
    strcat(path, fileName);
    strcat(path, ".txt");
}

/**
 * 创建消息路径
 *
 * @param fileName
 * @param path
 */
void createLoginPath(char *fileName, char *path) {
    stpcpy(path, "txt\\login\\");
    strcat(path, fileName);
    strcat(path, ".txt");
}

void inputPeople(char *path, PEOPLE *PeopleP) {
    FILE *fp = fopen(path, "r+");
    char token[35];
    loadDataWithLine(fp, 35, PeopleP->txtname);
    strcpy(token, PeopleP->txtname);
    fclose(fp);
}

/**
 * 消息录入
 *
 * @param path
 */
void inputMsg(char *path, MsgP msgP) {
    float size = 5.5;
    int i;

    FILE *fp = fopen(path, "r+");
    if (fp == NULL) {
        SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
        SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
        dis_24hz(19 * size, 327, "打开文件失败", 0);
    }

    int offset = 0;
    int flag = 1;

//    loadData(fp, &offset, msgP->author);
//    loadData(fp, &offset, msgP->title);
//    loadData(fp, &offset, msgP->type);
//    loadData(fp, &offset, msgP->readNum);

    loadDataWithLine(fp, 30, msgP->author);
    loadDataWithLine(fp, 30, msgP->title);
    loadDataWithLine(fp, 30, msgP->type);
    loadDataWithLine(fp, 20, msgP->readNum);

    for (i = 0; flag; i++) {
        flag = loadDataWithLine(fp, 100, msgP->text[i]);
    }

    printf("1 %s\n", msgP->author);
    printf("2 %s\n", msgP->title);
    printf("3 %s\n", msgP->type);
    printf("4 %s\n", msgP->readNum);
    fclose(fp);
}

/**
 * 具体数据导入
 *
 * @param fp
 * @param offset
 * @param buffer
 */
void loadData(FILE *fp, int *offset, char *buffer) {
    FILE *fpBak = fp;
    fseek(fp, *offset, SEEK_SET);
    fscanf(fp, "%s\n", buffer);
    int curpos = ftell(fp);
    fp--;
    printf("ftell : %d \n", curpos);
    printf("origin offset :%d\n", *offset);
//    *offset += getNextLinePos(fpBak);
//    fp+=1;
}

int loadDataWithLine(FILE *fp, int length, char *sz) {
    char * find;
    if (!feof(fp)) {
        memset(sz, '\0', length);
        // 包含了换行符 ??
        fgets(sz, length - 1, fp);
        printf("%s + 0000 \n", sz);
    }
    // 查找换行符
    find = strchr(sz, '\n');
    // 如果find不为空指针
    if(find)
        *find = '\0';
    // 返回是否有下一行
    return !feof(fp);
}

int getNextLinePos(FILE *p) {
    int ch;
    int curpos = 0;
    ch = getc(p);
    curpos = ftell(p);
    printf("\n ftell : %d \n", curpos);
    while (ch != EOF) {
        putchar(ch);
        ch = getc(p);
        if (ch == '\n') {
            break;
        }
    }
    return (ftell(p) - curpos + 1);
}



