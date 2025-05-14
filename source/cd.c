#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// �����/������ �����Ͽ� ���� ��η� �̵� ó��
int changeCurrentDirectory(DirectoryTree* dirTree, char* dirPath) {

    //���纻 ����
    DirectoryNode* temp;
    char path[MAX_BUFFER];

    // path �纻 ����� (strtok�� ���ڿ��� �ı��ϴϱ�)
    strcpy(path, dirPath);

    // 1. cd /���  2. cd /home/user/osteam�� ��� 3. pwd=/home/user �� �� cd osteam�� �ϴ� ���

    if (strcmp(path, "/") == 0) { // dirpath=="/"�� root�� �̵�
        dirTree->current = dirTree->root;
        return SUCCESS;
    }
    else if (path[0] == '/') {
        // ������ �� ��Ʈ���� ����
        temp = dirTree->root;
        // strtok�� ����� �۵��Ϸ��� /�� �����ؾ� �� �� "/etc/test" �� "etc/test"
        memmove(path, path + 1, strlen(path)); // ������ �� ĭ �б�
    }
    else {
        // ����� �� ���� ��ġ���� ����
        temp = dirTree->current;
    }

    // path���� /������ ��� �ϳ� ���(ex /home/ro ���ٸ� token�� home)
    char* token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, "..") == 0) { // cd ..�̶�� �θ� ���� ����
            if (temp->parent != NULL)
                temp = temp->parent;
        }
        else {                                   // cd /bin �̾��ٸ� ���� dirTree�� root�̹Ƿ� ���� �ڽĵ� Ž��
            DirectoryNode* child = temp->firstChild;
            boolean found = FALSE;
            while (child != NULL) {
                if (strcmp(child->name, token) == 0 && child->type == 'd') {
                    temp = child;
                    found = TRUE;
                    break;
                }
                child = child->nextSibling;     // child ����� ���� Ž��
            }
            if (!found) {
                printf("cd: no such directory: %s\n", token);
                return FAIL;
            }
        }
        token = strtok(NULL, "/");
    }

    dirTree->current = temp;
    return SUCCESS;
}



// cd ��ɾ� �� ó�� ����
int ft_cd(DirectoryTree* dirTree, char* cmd) {
    char* token = strtok(cmd, " ");  // cd ���� 
    token = strtok(NULL, " ");       // �̵� ���(ex /home

    if (token == NULL) {
        char path[MAX_BUFFER] = "/home/";
        strcat(path,usrList->current->name);
        return changeCurrentDirectory(dirTree, path);
    }
    return changeCurrentDirectory(dirTree, token);
}
