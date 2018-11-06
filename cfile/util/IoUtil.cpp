//
// Created by patrick on 11/5/18.
//

#include <string.h>
#include "./header/IoUtil.h"

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

