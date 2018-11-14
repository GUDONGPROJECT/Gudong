//
// Created by patrick on 11/9/18.
//

#include "./header/IoUtil.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path;
    path = (char *) malloc(50 * sizeof(char));
    createMsgPath("1", path);
    inputMsg(path);
    return 1;
}