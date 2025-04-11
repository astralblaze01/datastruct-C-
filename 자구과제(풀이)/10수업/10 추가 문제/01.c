#include <stdlib.h>
#include <stdio.h>
#define COMPARE(x, y) ((x) > (y) ? 1 : ((x) < (y) ? -1 : 0))

typedef struct polynomial
{
    int data;
    struct polynomial *next;
} polynomial;

polynomial *inputPoly(FILE *f, polynomial **node, polynomial *rear);
polynomial *creatPolyNode();
polynomial *appendPolyNode(polynomial **node, polynomial *rear, int data);
void printPoly(polynomial *node, char type);
void checkFile(FILE *f);
void intersection(polynomial *a, polynomial *rearA, polynomial *b, polynomial *rearB, polynomial **c, polynomial *rearC);

int main()
{
    FILE *fileA = fopen("in1.txt", "r");
    checkFile(fileA);
    FILE *fileB = fopen("in2.txt", "r");
    checkFile(fileB);

    polynomial *a = creatPolyNode();
    polynomial *rearA;
    polynomial *b = creatPolyNode();
    polynomial *rearB;
    polynomial *c = creatPolyNode();
    polynomial *rearC;

    a = NULL, b = NULL, c = NULL;
    rearA = inputPoly(fileA, &a, rearA);
    rearB = inputPoly(fileB, &b, rearB);

    printPoly(a, 'A');
    printPoly(b, 'B');

    intersection(a, rearA, b, rearB, &c, rearC);
    printPoly(c, 'C');
}

// 교집합합
void intersection(polynomial *a, polynomial *rearA, polynomial *b, polynomial *rearB, polynomial **c, polynomial *rearC)
{
    for(polynomial * i = a; i != rearA->next; i = i->next)
    {
        for(polynomial * k = b; k != rearB->next; k = k->next)
        {
            if(i->data == k->data)
            {
                rearC = appendPolyNode(c, rearC, i->data);
            }
        }
    }
}

polynomial *inputPoly(FILE *f, polynomial **node, polynomial *rear)
{
    int data;

    while (fscanf(f, "%d", &data) != EOF)
    {
        rear = appendPolyNode(node, rear, data);
    }

    return rear;
}

// 출력력
void printPoly(polynomial *node, char type)
{
    printf("%c : ", type);
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

polynomial *appendPolyNode(polynomial **node, polynomial *rear, int data)
{
    polynomial *nextNode = creatPolyNode();
    nextNode->data = data;

    if (!(*node))
    {
        *node = nextNode;
    }
    else
    {
        rear->next = nextNode;
    }
    return nextNode;
}

// node 생성성
polynomial *creatPolyNode()
{
    polynomial *node = (polynomial *)malloc(sizeof(polynomial));

    if (!node)
    {
        printf("malloc is false");
        exit(1);
    }

    node->data = 0;
    node->next = NULL;

    return node;
}

void checkFile(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}