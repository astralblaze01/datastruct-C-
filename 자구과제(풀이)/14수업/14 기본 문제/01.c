#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_QUEUE 10

typedef struct element
{
    int data;
    struct element *left;
    struct element *right;
} element;

typedef struct queue
{
    int front;
    int rear;
    element *arr[MAX_SIZE_QUEUE];
} queue;

// file
FILE *openFile(const char *fileName);

// node
element *createNode(int data);
element *constructBST(FILE *file, element *head);
void connectLeft(element *parent, element *child);
void connectRight(element *parent, element *child);

// queue(정적)
void initQueue(queue *q);
element *popQueue(queue *q);
void pushQueue(queue *q, element *node);
void printQueue(queue q);

// 출력
void printLevelOrder(element *head, queue *q);
int levelOfData(FILE *file, element *head);

int main()
{
    // 파일 입력
    FILE *file = openFile("in2.txt");
    FILE *searchFile = openFile("search.txt");

    // queue
    queue q;
    initQueue(&q);

    // node
    element *head = NULL;
    head = constructBST(file, head);

    // out
    printLevelOrder(head, &q);
}

// binary search tree 탐색
int levelOfData(FILE *file, element *head)
{
    
}

// binary search tree 구성
element *constructBST(FILE *file, element *head)
{
    int data;

    while (fscanf(file, "%d", &data) != EOF)
    {
        if (!head)
        {
            head = createNode(data);
        }
        else
        {
            element *temp = head;
            int mark = 0;

            while (mark != 1)
            {
                // data가 parent data보다 클 경우
                if (data > temp->data)
                {
                    if (temp->right == NULL)
                    {
                        element *rightNode = createNode(data);
                        connectRight(temp, rightNode);
                        mark = 1;
                        continue;
                    }
                    temp = temp->right;
                }

                // data가 parent data보다 작을 경우
                if (data < temp->data)
                {
                    if (temp->left == NULL)
                    {
                        element *leftNode = createNode(data);
                        connectLeft(temp, leftNode);
                        mark = 1;
                        continue;
                    }
                    temp = temp->left;
                }
            }
        }
    }
    return head;
}

// 오른쪽 연결
void connectRight(element *parent, element *child)
{
    parent->right = child;
}

// 왼쪽 연결
void connectLeft(element *parent, element *child)
{
    parent->left = child;
}

// node 생성
element *createNode(int data)
{
    element *node = (element *)malloc(sizeof(element));
    if (!node)
    {
        printf("memory allocation is fail");
        exit(1);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// level 순회
void printLevelOrder(element *head, queue *q)
{
    initQueue(q);
    pushQueue(q, head);
    printf("level order : ");
    while (q->front != q->rear)
    {
        element *temp = popQueue(q);
        printf("%d ", temp->data);
        if (temp->left)
        {
            pushQueue(q, temp->left);
        }
        if (temp->right)
        {
            pushQueue(q, temp->right);
        }
    }
    printf("\n");
}

// queue 초기화
void initQueue(queue *q)
{
    q->front = q->rear = 0;
    for (int i = 0; i < MAX_SIZE_QUEUE; i++)
    {
        q->arr[i] = NULL;
    }
}

// queue 제거
element *popQueue(queue *q)
{
    if (q->front == q->rear)
    {
        printf("queue is empty\n");
        // exit(1);
    }

    return q->arr[q->front++];
}

// queue 삽입
void pushQueue(queue *q, element *node)
{
    if (q->rear >= MAX_SIZE_QUEUE)
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

FILE *openFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        printf("file is not open");
        exit(1);
    }
    return file;
}
