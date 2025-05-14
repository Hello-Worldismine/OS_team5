#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// ������ ������� Ȯ��
boolean isEmpty(Stack* stack) {
    return stack->cnt == 0;
}

// ���� �ʱ�ȭ (�޸� �Ҵ� + �ʱⰪ ����)
Stack* initStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Failed to allocate memory for Stack\n");
        return NULL;
    }
    stack->topNode = NULL;
    stack->cnt = 0;
    return stack;
}

// ���丮 �̸��� ���ÿ� push
int pushStack(Stack* stack, char* dirName) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory for StackNode\n");
        return FAIL;
    }
    strcpy(newNode->name, dirName);
    newNode->nextNode = stack->topNode;
    stack->topNode = newNode;
    stack->cnt++;
    return SUCCESS;
}

// ���ÿ��� ���丮 �̸��� pop�ϰ� ��ȯ (����� ���ڿ� ��ȯ)
char* popStack(Stack* stack) {
    if (isEmpty(stack)) return NULL;

    StackNode* temp = stack->topNode;
    char* poppedName = strdup(temp->name);  // ���ڿ� ����
    stack->topNode = temp->nextNode;
    free(temp);
    stack->cnt--;

    return poppedName;
}
