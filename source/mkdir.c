#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "main.h"


int makeDir(DirectoryTree* dirTree, char* dirName, char type) {

    // main.h�� ������ .c�� �����ؾ���
    // ���� �Ȱ��� ���丮 ���� �� �˸�
    if (dirExistence(dirTree, dirName, type) != NULL) {
        printf("Directory '%s' already exists.\n", dirName);
        return FAIL;
    }

    // ���ο� Node ���� ���⼭ type�� 'd'�� ������
    DirectoryNode* newNode = (DirectoryNode*)malloc(sizeof(DirectoryNode));

    // ���ο� Node�� �̸�, ID, ���� �ð� ��. �����߰�
    strcpy(newNode->name, dirName);
    newNode->type = type;
    newNode->SIZE = 0;
    newNode->id.UID = dirTree->current->id.UID;
    newNode->id.GID = dirTree->current->id.GID;
    newNode->permission.mode = 755;


    // main.h�� ������ .c�� �����ؾ���
    getToday(&(newNode->date));
    // main.h�� ������ .c�� �����ؾ���
    modeToPermission(newNode);

    //���� ��ġ�� Node�� �θ�� ����
    newNode->parent = dirTree->current;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;

    //���� ���� child ���� ���ٸ� firstchild ����
    if (dirTree->current->firstChild == NULL) {
        dirTree->current->firstChild = newNode;
    }
    // ���� child �ִٸ� ������ sibling���� �����
    else {
        DirectoryNode* sibling = dirTree->current->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = newNode;
    }

    printf("Directory '%s' created successfully.\n", dirName);
    return SUCCESS;
}

 
    //��Ƽ�������� ���� ������ ���� �� makeDirUsedThread �Լ��� �����
void* makeDirUsedThread(void* arg) {
    ThreadTree* args = (ThreadTree*)arg;
    makeDir(args->threadTree, args->command, 'd'); 
    pthread_exit(NULL);
}

    // mkdir a b c�� �ԷµǸ� cmd�� �����
int ft_mkdir(DirectoryTree* dirTree, char* cmd) {
    char* token;
    char* delim = " ";
    int threadCount = 0;
    pthread_t tid[MAX_THREAD];
    // �����ִ� ThreadTree�� main.h�� ���ǵǾ�����
    ThreadTree* args[MAX_THREAD];

    token = strtok(cmd, delim);  // ù ��° ��ū�� "mkdir" �̹Ƿ� skip
    token = strtok(NULL, delim); // �� ��° ��ū���� ���� ex) cmd a���� a�� �Ҵ��

    // ��ū�� NULL�̰ų� �������� ������ �ʹ� Ŀ���� ����
    while (token != NULL && threadCount < MAX_THREAD) {
        //ThreadTree�� ���� �Ҵ�
        args[threadCount] = (ThreadTree*)malloc(sizeof(ThreadTree));
        args[threadCount]->threadTree = dirTree;
        args[threadCount]->command = strdup(token); // ���丮 �̸�
        // ������ ���� �� �Ʊ� ������ makeDirUsedThread ����
        pthread_create(&tid[threadCount], NULL, makeDirUsedThread, (void*)args[threadCount]);
        threadCount++;

        token = strtok(NULL, delim);
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(tid[i], NULL);
        free(args[i]->command);
        free(args[i]);
    }

    return SUCCESS;
}

// ���� ���
// mkdir a b c�� ������ 
// ft_mkdir(DirectoryTree* dirTree, char* cmd) �� �Լ��� ���� �����
// while ������ ���� a, b, c�� ���� �����尡 ���������� �����ǰ� �� ������� makeDirUsedThread �Լ��� ���� makeDir�� ����
// �� ��� mkdir a �ϳ��� ��쿡�� �����尡 �ϳ� �����ǰ� makeDir ���� �� �����



