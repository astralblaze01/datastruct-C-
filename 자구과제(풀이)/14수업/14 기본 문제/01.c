#include <stdio.h>
#include <stdlib.h>

typedef struct _tree
{
    int value;
    struct _tree *right;
    struct _tree *left;
} treeNode;

treeNode *makeTreeNode(int val);
treeNode *makeBST(FILE *file, treeNode *head);
void findLevelAndValue(FILE *file, treeNode *head);

int main(void)
{
    // 파일 입력
    FILE *file = fopen("in1-3.txt", "r");
    if (!file)
    {
        printf("file is not open!");
        exit(1);
    }
    FILE *searchFile = fopen("search1-3.txt", "r");
    if (!searchFile)
    {
        printf("searchFile is not open!");
        exit(1);
    }

    // head node 생성
    treeNode *head = NULL;

    head = makeBST(file, head);

    findLevelAndValue(searchFile, head);
}

void findLevelAndValue(FILE *file, treeNode *head)
{
    treeNode *temp;
    int level, cnt, key;
    
    while (fscanf(file, "%d", &key) != EOF)
    {
        temp = head;
        level = 1, cnt = 0;
        while (temp != NULL)
        {
            if (temp->value == key)
            {
                printf("%d ", level);
                cnt++;
                break;
            }
            else if (temp->value < key)
            {
                temp = temp->right;
            }
            else if (temp->value > key)
            {
                temp = temp->left;
            }
            level++;
        }
        // 값이 없을때
        if (cnt == 0)
        {
            printf("F ");
        }
    }
}

treeNode *makeTreeNode(int val)
{
    treeNode *node = (treeNode *)malloc(sizeof(treeNode));
    if (!node)
    {
        printf("node memory allocation is fail!");
        exit(1);
    }
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

treeNode *makeBST(FILE *file, treeNode *head)
{
    int data;
    while (fscanf(file, "%d", &data) != EOF)
    {
        // 새로운 노드 생성
        treeNode *newNode = makeTreeNode(data);

        if (!head)
        {
            head = newNode;
            continue;
        }
        else
        {
            treeNode *temp = head;

            while (1)
            {
                if (temp->value < data)
                {
                    if (temp->right == NULL)
                    {
                        temp->right = newNode;
                        // printf("%d ", temp->value);
                        break;
                    }
                    else
                    {
                        temp = temp->right;
                    }
                }
                if (temp->value > data)
                {
                    if (temp->left == NULL)
                    {
                        temp->left = newNode;
                        // printf("%d ", temp->value);
                        break;
                    }
                    else
                    {
                        temp = temp->left;
                    }
                }
            }
        }
    }

    return head;
}