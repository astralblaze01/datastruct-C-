#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

typedef struct element
{
    int data;
    struct element *right;
    struct element *left;
} element;

typedef struct queue
{
    int front;
    int rear;
    element *arr[MAX_SIZE];
} queue;

// file
FILE *readFile();

// node
int readData(FILE *file);
void iterativeInorderSearch(element *head);
element *creatNode(int data);

// queue
void initQueue(queue *q);
void popQueue(queue *q);
void pushQueue(queue *q, element *node);
void printQueue(queue q);

//tree
element *createLevelOrderTree(FILE *file, element *head, queue *q);

int main()
{
    FILE *file = readFile();
    queue q;
    initQueue(&q);
    element *head = NULL;
}

// queue 초기화
void initQueue(queue *q)
{
    q->front = q->rear = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        q->arr[i] = NULL;
        q->arr[i] = (element *)malloc(sizeof(element));
    }
}

// queue 제거
void popQueue(queue *q)
{
    if (q->front == q->rear)
    {
        printf("queue is empty\n");
        return;
    }
    q->front++;
}

// queue 삽입
void pushQueue(queue *q, element *node)
{
    if (q->rear > MAX_SIZE)
    {
        printf("queue is full\n");
        return;
    }
    q->arr[q->rear] = node;
    q->rear++;
}

// queue 출력
void printQueue(queue q)
{
    printf("queue : ");
    for (int i = q.front; i < q.rear; i++)
    {
        printf("%d ", q.arr[i]->data);
    }
    printf("\n");
}

element *createLevelOrderTree(FILE *file, element *head, queue *q)
{
    if (!head)
    {
        int data;
        fscanf(file, "%d", &data);
        head = createNode(data);
        return head;
    }
    else
    {

    }
}

int readData(FILE *file)
{
    int data;
    fscanf(file, "%d", &data);
    return data;
}

// inorder 출력 (반복적 중위 순회랑 그냥 중위 순회가 다르네)
void iterativeInorderSearch(element *head)
{
    iterativeInorderSearch(head->left);
    printf("%d ", head->data);
    iterativeInorderSearch(head->right);
}

// 노드 생성
element *creatNode(int data)
{
    element *node = (element *)malloc(sizeof(element));
    if (!node)
    {
        printf("node mamory allocation is fail");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 파일 읽기
FILE *readFile()
{
    FILE *file = fopen("in.txt", "r");
    if (!file)
    {
        printf("file is not open");
        exit(1);
    }
    return file;
}