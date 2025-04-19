#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    char data;
    struct element *right;
    struct element *left;
} element;

element *createNode(char data);
void connectL(element *parent, element *child);
void connectR(element *parent, element *child);
void program1();
void program2();
void printInorder(element *root);
void printOrder(element *root);

void main()
{
    program1();
    program2();
    return;
}

// tree 구성후 순회
void program1()
{
    char dataList[] = {'A', 'B', 'C', 'E', 'H'};
    element *root = createNode('A');
    element *nodeB = createNode('B');
    element *nodeC = createNode('C');
    element *nodeE = createNode('E');
    element *nodeH = createNode('H');
    connectL(root, nodeB);
    connectR(root, nodeC);
    connectR(nodeB, nodeE);
    connectR(nodeC, nodeH);
    printInorder(root);
    printf("\n");
}

void printInorder(element *root)
{
    if (!root)
    {
        return;
    }
    printInorder(root->left);
    printf("%c ", root->data);
    printInorder(root->right);
}

void connectR(element *parent, element *child)
{
    parent->right = child;
}

void connectL(element *parent, element *child)
{
    parent->left = child;
}

element *createNode(char data)
{
    element *root = (element *)malloc(sizeof(element));
    if (!root)
    {
        printf("memory allocation is fail");
        exit(1);
    }
    root->left = NULL;
    root->right = NULL;
    root->data = data;
    return root;
}

void program2()
{
    int level = 0;
    scanf("%d", &level);
    if (level <= 0)
    {
        printf("level is none");
        return;
    }

    char strData = 49;
    element *root = createNode(strData);
    element *remenberNode = root;
    for (int i = 2; i <= level; i++)
    {
        strData = i + 48;
        if (i % 2 == 0)
        {
            element *leftNode = createNode(strData);
            connectL(remenberNode, leftNode);
            remenberNode = leftNode;
            continue;
        }
        element *rightNode = createNode(strData);
        connectR(remenberNode, rightNode);
        remenberNode = rightNode;
    }

    printOrder(root);
}

void printOrder(element *root)
{
    while (root != NULL)
    {
        printf("%c : (%p)\n", root->data, root);

        if (root->right != NULL)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
}
