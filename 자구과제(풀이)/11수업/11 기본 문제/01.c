#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

typedef struct element
{
    int data;
    struct element *next;
} element;

FILE *readFile(FILE *f);
void inputData(FILE *f, element **arr);
void printData(element **arr, int size);
element *createNode(int data);
void initMark(int *mark, int size);


int main()
{
    FILE *file = readFile(NULL);

    int size;
    fscanf(file, "%d", &size);
    printf("%d\n", size);

    int *mark = (int *)malloc(sizeof(int) * size);
    initMark(mark, size);
    element **equivalArr = (element **)malloc(sizeof(element *) * size);
    for (int i = 0; i < size; i++)
    {
        equivalArr[i] = NULL;
    }

    inputData(file, equivalArr);
    printData(equivalArr, size);
}

// 포인터 배열 출력
void printData(element **arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d : ", i);
        element *temp = arr[i];
        while (temp != NULL)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}


void initMark(int *mark, int size)
{
    for (int i = 0; i < size; i++)
        mark[i] = FALSE;
}


void printEquivalance(element **arr, int size, int *mark)
{
    for (int i = 0; i < size; i++)
    {
        mark[i] = TRUE;
        element *temp = arr[i];

        while (temp != NULL)
        {
            temp = temp->next;
        }
        printf("\n");
    }
}

// 포인터 배열에 값 연결
void inputData(FILE *f, element **arr)
{
    int x, y;
    while (1)
    {
        fscanf(f, "%d %d", &x, &y);
        if (x < 0 && y < 0)
            break;
        element *nextNodeX = createNode(x);
        element *nextNodeY = createNode(y);
        nextNodeX->next = arr[y];
        arr[y] = nextNodeX;
        nextNodeY->next = arr[x];
        arr[x] = nextNodeY;
    }
}

// node 생성
element *createNode(int data)
{
    element *nextNode = (element *)malloc(sizeof(element));
    nextNode->data = data;
    nextNode->next = NULL;
    return nextNode;
}

// 파일 읽기
FILE *readFile(FILE *f)
{
    f = fopen("in1.txt", "r");
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
    return f;
}