#include <stdlib.h>
#include <stdio.h>

typedef struct polynomial
{
    int coef;  // 숫자
    int expon; // 지수
    struct polynomial *next;
} polynomial;

polynomial *inputPoly(FILE *f, polynomial **node, polynomial *rear);
polynomial *creatPolyNode();
polynomial *appendPolyNode(polynomial **node, polynomial *rear, int coef, int expon);
void printPoly(polynomial *node, char type);
void checkFile(FILE *f);
void addPoly(polynomial *a, polynomial *rearA, polynomial *b, polynomial *rearB, polynomial **c, polynomial *rearC, int *cnt);

int main()
{
    FILE *fileA = fopen("a.txt", "r");
    checkFile(fileA);
    FILE *fileB = fopen("b.txt", "r");
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
    printPoly(b, 'C');

    int cnt = 0;
    addPoly(a, rearA, b, rearB, &c, rearC, &cnt);
    printf("아니 아직도 전역을 안했다고? 2022111603 황현태\n");
    printf("%d ", cnt);
    printPoly(c, 'C');
}

// a + b
void addPoly(polynomial *a, polynomial *rearA, polynomial *b, polynomial *rearB, polynomial **c, polynomial *rearC, int *cnt)
{
    while (a != rearA && b != rearB)
    {
        if (a->expon == b->expon)
        {
            if (!(a->coef + b->coef))
            {
                a = a->next;
                b = b->next;
            }
            else
            {
                rearC = appendPolyNode(c, rearC, a->coef, a->expon);
                a = a->next;
                b = b->next;
                (*cnt)++;
            }
        }
        else if (a->expon > b->expon)
        {
            rearC = appendPolyNode(c, rearC, a->coef, a->expon);
            a = a->next;
            (*cnt)++;
        }
        else
        {
            rearC = appendPolyNode(c, rearC, b->coef, b->expon);
            b = b->next;
            (*cnt)++;
        }
    }

    while (a != rearA)
    {
        rearC = appendPolyNode(c, rearC, a->coef, a->expon);
        a = a->next;
        (*cnt)++;
    }

    while (b != rearB)
    {
        rearC = appendPolyNode(c, rearC, b->coef, b->expon);
        b = b->next;
        (*cnt)++;
    }
}

polynomial *inputPoly(FILE *f, polynomial **node, polynomial *rear)
{
    int coef, expon;
    int n;

    fscanf(f, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d %d", &coef, &expon);
        rear = appendPolyNode(node, rear, coef, expon);
    }

    return rear;
}

// 출력력
void printPoly(polynomial *node, char type)
{
    printf("%c : ", type);
    while (node != NULL)
    {
        printf("%d %d ", node->coef, node->expon);
        node = node->next;
    }
    printf("\n");
}

// 마지막값 기억하고 node연결결
polynomial *appendPolyNode(polynomial **node, polynomial *rear, int coef, int expon)
{
    polynomial *nextNode = creatPolyNode();
    nextNode->coef = coef;
    nextNode->expon = expon;

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

    node->coef = 0;
    node->expon = 0;
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