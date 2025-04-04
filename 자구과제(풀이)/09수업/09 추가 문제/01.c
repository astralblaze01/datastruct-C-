#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int data;
    struct element *next;
} element;

void checkFile(FILE *f);
void checkAllocation(element *node);
void insertList(element **node, int val);
void deleteList(element **node, int delVal);
void printList(element *node);
void freeList(element *node);

int main()
{
    // 파일
    FILE *fReed = fopen("in.txt", "r");
    checkFile(fReed);

    // 입력
    element *head = NULL;
    int val;
    while (fscanf(fReed, "%d", &val) != EOF)
    {
        insertList(&head, val);
    }

    // 메인 동작작
    int delVal = 10;
    printf("i want to go home!! 2022111603 hyuntae\n");
    while (1)
    {
        printList(head);

        scanf("%d", &delVal);
        if (delVal <= 0)
        {
            break;
        }
        
        deleteList(&head, delVal);
    }

    // free
    freeList(head);

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

void checkAllocation(element *node)
{
    if (!node)
    {
        printf("melloc is fail");
        exit(1);
    }
}

void insertList(element **node, int val)
{
    element *nextNode = (element *)malloc(sizeof(element));
    checkAllocation(nextNode);
    nextNode->data = val;
    nextNode->next = NULL;

    if (!(*node))
    {
        *node = nextNode;
    }
    else
    {
        element *temp = *node;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = nextNode;
    }
}

void deleteList(element **node, int delVal)
{
    element *temp = *node;
    element *delNode;
    int cnt = 0;

    // head 값값
    if ((*node)->data == delVal)
    {
        cnt++;
        delNode = *node;
        (*node) = (*node)->next;
        free(delNode);
    }
    else
    {
        // 중간값 & 마지막 값
        while (temp->next != NULL)
        {
            if ((temp->next)->data == delVal)
            {
                cnt++;
                delNode = temp->next;
                temp->next = (temp->next)->next;
                free(delNode);
                break;
            }
            temp = temp->next;
        }
    }

    if (cnt == 0)
    {
        printf("Not exist\n");
    }
}

void printList(element *node)
{
    printf("L : ");
    while (node != NULL)
    {
        printf("%d ", node->data);
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