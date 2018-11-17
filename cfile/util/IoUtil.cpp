//
// Created by patrick on 11/5/18.
//

#include "./header/IoUtil.h"
#include "./header/head.h"

/**********************************************************
Function��		Create_path

Description��	���������û����û����ļ�·��

Input��
				char *name       �û����û���
				char *textname   �û�������Ӧ���û�·��

Output��	    NONE

Return��		NONE

**********************************************************/
void Create_path(char *name, char *textname) {
    stpcpy(textname, "txt\\");
    strcat(textname, name);
    strcat(textname, ".txt");
}

/**********************************************************
Function��		R_check

Description��	���ڼ���û��û��������Ƿ���ϱ�׼

Input��			char *txtname     �����洢�û����ļ�����ַ
			    char *key         �û���һ�����������
				char *key1        �û��ڶ������������

Output��		��ʾ�û�ע��״̬�������û����ļ��������û��ļ�

Return��		ע��״̬���

**********************************************************/
int R_check(char *txtname, char *key, char *key1) {
    // �жϺ����Ƿ���Կ�¼�룬�Լ�¼�뺯��
    FILE *fp;
    float size = 5.5;
    if (strcmp(key, key1) != 0) {
        //readbmp(182,128,"pic\\notmatch.bmp");//��ʾǰ�����ε����벻��ͬ�������������
        SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
        SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
        dis_24hz(19 * size, 327, "ǰ���������벻һ��", 0);
        delay(1500);
        //Regist(mouse,people);
        return 0;
    } else {
        fp = fopen(txtname, "r+");
        if (fp != NULL) {
            fclose(fp);
            //readbmp(182,128,"pic\\chongfu.bmp");//��ʾ�û������ظ�,���������û���¼����
            SVGA_Bar(6 * size, 228, 62 * size, 451, DARK_GRAY);
            SVGA_Bar(6 * size + 2, 228 + 2, 62 * size - 2, 451 - 2, LIGHT_GRAY);
            dis_24hz(19 * size, 327, "���ֻ�����ע��", 0);
            // ����߼��϶��߲���,�Ҿ�Ƥһ��
            delay(100000);
            //Regist(mouse,people);//�����¼����
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
            dis_24hz(19 * size, 327, "���Ѿ�ע��ɹ�", 0);
            delay(1500);
            //Begin_menu(mouse);
            return 1;
        }
    }
}

/**
 * ������Ϣ·��
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
 * ������Ϣ·��
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
 * ��Ϣ¼��
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
        dis_24hz(19 * size, 327, "���ļ�ʧ��", 0);
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
 * �������ݵ���
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
        // �����˻��з� ??
        fgets(sz, length - 1, fp);
        printf("%s + 0000 \n", sz);
    }
    // ���һ��з�
    find = strchr(sz, '\n');
    // ���find��Ϊ��ָ��
    if(find)
        *find = '\0';
    // �����Ƿ�����һ��
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



