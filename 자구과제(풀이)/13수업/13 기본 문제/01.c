#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_STACK 20
#define MAX_SIZE_QUEUE 10

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
    element *arr[MAX_SIZE_QUEUE];
} queue;

typedef struct stack
{
    int top;
    element *arr[MAX_SIZE_STACK];
} stack;

// file
FILE *readFile();

// node
int readData(FILE *file);
element *creatNode(int data);

// queue(정적)
void initQueue(queue *q);
element *popQueue(queue *q);
void pushQueue(queue *q, element *node);
void printQueue(queue q);

// stack(정적)
void initStack(stack *s);
element *popStack(stack *s);
void pushStack(stack *s, element *node);
void printStack(stack s);

// tree & out
element *createLevelOrderTree(FILE *file, element *head, queue *q);
void inorderSearch(element *head);
void printLevelOrder(element *head, queue *q);
void iterativeInorderSearch(element *head);

int main()
{
    FILE *file = readFile();

    queue q;
    initQueue(&q);
    element *head = NULL;
    head = createLevelOrderTree(file, head, &q);

    printLevelOrder(head, &q);

    printf("inorder : ");
    inorderSearch(head);
    printf("\n");
    
    iterativeInorderSearch(head);
}

void initStack(stack *s)
{
    s->top = 0;
    for (int i = 0; i < MAX_SIZE_STACK; i++)
    {
        s->arr[i] = NULL;
    }
}

element *popStack(stack *s)
{
    if (s->top <= 0)
    {
        printf("stack is empty\n");
        return NULL;
    }
    return s->arr[--s->top];
}

void pushStack(stack *s, element *node)
{
    if (s->top >= MAX_SIZE_STACK)
    {
        printf("stack is full\n");
        return;
    }
    s->arr[s->top++] = node;
}

void printStack(stack s)
{
    printf("stack : ");
    for (int i = 0; i < s.top; i++)
    {
        printf("%d ", s.arr[i]->data);
    }
    printf("\n");
}

void printLevelOrder(element *head, queue *q)
{
    initQueue(q);
    pushQueue(q, head);
    printf("level order : ");
    while (q->front != q->rear)
    {
        element *temp = popQueue(q);
        printf("%d ", temp->data);
        if (!(temp->left)) // 만들어 줄때 left 먼저 생성 하므로 left가 없으면 right도 없다고 판단
        {
            continue;
        }
        pushQueue(q, temp->left);
        pushQueue(q, temp->right);
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

// level로 tree 구성성
element *createLevelOrderTree(FILE *file, element *head, queue *q)
{
    int data;
    while (fscanf(file, "%d", &data) != EOF)
    {
        if (!head)
        {
            head = creatNode(data);
            pushQueue(q, head);
        }
        else
        {
            // printQueue(*q); // 디버깅
            element *temp = popQueue(q);
            if (!(temp->left))
            {
                element *leftNode = creatNode(data);
                temp->left = leftNode;
                pushQueue(q, leftNode);
            }
            if (!(temp->right))
            {
                fscanf(file, "%d", &data);
                element *rightNode = creatNode(data);
                temp->right = rightNode;
                pushQueue(q, rightNode);
            }
        }
    }
    // printQueue(*q); // 디버깅
    return head;
}

int readData(FILE *file)
{
    int data;
    fscanf(file, "%d", &data);
    return data;
}

// 재귀를 이용한 중위 순회회
void inorderSearch(element *head)
{
    if (!head)
    {
        return;
    }
    inorderSearch(head->left);
    printf("%d ", head->data);
    inorderSearch(head->right);
}

// inorder 출력 (반복적 중위 순회랑 그냥 중위 순회가 다르네)
void iterativeInorderSearch(element *head)
{
    stack s;
    initStack(&s);

    printf("iterative inorder : ");
    while (head != NULL || s.top > 0)
    {
        while (head != NULL)
        {
            pushStack(&s, head);
            head = head->left;
        }

        head = popStack(&s);
        if (head == NULL)
        {
            break;
        }

        printf("%d ", head->data);
        head = head->right;
    }
    printf("\n");
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