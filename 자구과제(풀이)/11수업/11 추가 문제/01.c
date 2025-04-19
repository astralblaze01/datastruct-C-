#include <stdlib.h>
#include <stdio.h>

typedef struct element
{
    int data;
    struct element *next;
} element;

void checkFile(FILE *f);
void checkMalloc(element *node);
element *createNode(int data);
void printList(element *head);
void insertLinkedList(element **head, int data);
void inputdata(FILE *f, element **head);
void setList(element **head);

int main()
{
    FILE *file = fopen("in.txt", "r");
    checkFile(file);

    element *head = createNode(2022111603);
    head = NULL;

    printf("2022111603 황현태\n");
    inputdata(file, &head);
    printList(head);
    setList(&head);
    printList(head);
}

void setList(element **head)
{
    element *temp = *head;
    element *deletNode;

    while (temp->next != NULL)
    {
        if (temp->data == temp->next->data)
        {
            deletNode = temp->next;
            temp->next = deletNode->next;
            free(deletNode);
            continue;
        }
        temp = temp->next;
    }
}

void inputdata(FILE *f, element **head)
{
    int data;
    while (fscanf(f, "%d", &data) != EOF)
    {
        insertLinkedList(head, data);
    }
}

void insertLinkedList(element **head, int data)
{
    element *newNode = createNode(data);

    if (*head == NULL || (*head)->data >= data)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    element *temp = *head;
    while (temp->next != NULL && temp->next->data < data)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

element *createNode(int data)
{
    element *node = (element *)malloc(sizeof(element));
    checkMalloc(node);
    node->data = data;
    node->next = NULL;
    return node;
}

void checkMalloc(element *node)
{
    if (!node)
    {
        printf("malloc is fail");
        exit(1);
    }
}

void checkFile(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}

void printList(element *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}