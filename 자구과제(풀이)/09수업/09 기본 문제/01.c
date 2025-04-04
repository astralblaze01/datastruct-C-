#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int data;
    struct element *next;
} element;

void checkFile(FILE *f);
element *execute(element *node, int val, int type);
element *program1(element *node, int val);
element *program2(element *node, int val);
void checkAllocation(element *node);
void printList(element *node, int type);
void freeList(element *node);

int main()
{
    // 파일일
    FILE *fReed = fopen("in.txt", "r");
    checkFile(fReed);

    // head 노드
    element *head1 = NULL;
    element *head2 = NULL;
    int val;

    while (fscanf(fReed, "%d", &val) != EOF)
    {
        head1 = execute(head1, val, 1);
        head2 = execute(head2, val, 2);
    }

    // 출력력
    printf("i want to go home 2022111603 hyun tae\n");
    printList(head1, 1);
    printList(head2, 2);

    // free()
    freeList(head1);
    freeList(head2);

    // 파일 닫기
    fclose(fReed);
}

void freeList(element *node)
{
    if (!node->next)
    {
        return;
    }
    freeList(node->next);
    free(node);
}

element *execute(element *node, int val, int type)
{
    switch (type)
    {
    case 1:
        node = program1(node, val);
        break;
    case 2:
        node = program2(node, val);
        break;
    }
    return node;
}

element *program1(element *node, int val)
{

    element *nextNode = (element *)malloc(sizeof(element));
    checkAllocation(nextNode);
    nextNode->data = val;
    nextNode->next = NULL;

    if (!node)
    {
        return nextNode;
    }
    else
    {
        element *temp = node;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = nextNode;
        return node;
    }
}

void checkAllocation(element *node)
{
    if (!node)
    {
        printf("melloc is fail");
        exit(1);
    }
}

element *program2(element *node, int val)
{
    element *nextNode = (element *)malloc(sizeof(element));
    checkAllocation(nextNode);
    nextNode->data = val;
    nextNode->next = node;

    return nextNode;
}

void printList(element *node, int type)
{
    switch (type)
    {
    case 1:
        printf("problem 1:\n");
        break;
    case 2:
        printf("problem 2:\n");
    }

    while (node != NULL)
    {
        printf("%d (%o)\n", node->data, node);
        node = node->next;
    }
    printf("\n");
}

void checkFile(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}