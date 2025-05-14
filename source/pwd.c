#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"  // ����ü, Stack �Լ�, DirectoryTree �� ���� ����

// ���� ��θ� ��� (��Ʈ���� ���� ���丮����)
int printPath(DirectoryTree* dirTree, Stack* dirStack) {
    DirectoryNode* current = dirTree->current;

    // ���� ����
    while (!isEmpty(dirStack)) {
        popStack(dirStack);
    }

    // ���� ���丮���� ��Ʈ���� ���ÿ� push
    while (current != NULL) {
        pushStack(dirStack, current->name);
        current = current->parent;
    }

    // ������ pop�ϸ鼭 ���������� ��� ���
    printf("/");
    StackNode* node = dirStack->topNode;
    while (node != NULL) {
        if (strcmp(node->name, "/") != 0) {
            printf("%s", node->name);
            if (node->nextNode != NULL) {
                printf("/");
            }
        }
        node = node->nextNode;
    }
    printf("\n");

    return SUCCESS;
}

// "pwd" ��ɾ� ó�� �Լ�
int ft_pwd(DirectoryTree* dirTree, Stack* dirStack, char* cmd) {
    // ��ɾ� ��ȿ�� Ȯ�� (�Ľ̵� �Ķ�� ���� ����)
    if (strcmp(cmd, "pwd") != 0) {
        fprintf(stderr, "Invalid command for pwd: %s\n", cmd);
        return FAIL;
    }

    return printPath(dirTree, dirStack);
}
