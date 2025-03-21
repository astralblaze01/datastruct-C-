#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) ((x) > (y) ? 1 : ((x) < (y) ? -1 : 0))

int fileSize(FILE *f, int size);
void inputArr(FILE *f, int *fArr, int start, int end);
void isFileOpen(FILE *f);
void printArr(int *arr, int start, int end);
int unionSet(int *arr, int start, int end);

int main()
{
    FILE *fa = fopen("a.txt", "r"), *fb = fopen("b.txt", "r");

    isFileOpen(fa);
    isFileOpen(fb);

    int start = fileSize(fa, 0);
    int end = fileSize(fb, start);
    int resultSize = (start + end) * 2;

    int *result = (int *)malloc(sizeof(int) * resultSize);

    inputArr(fa, result, 0, start);
    // printArr(result, 0, start);
    // printf("\n");
    inputArr(fb, result, start, end);
    // printArr(result, start, end);
    // printf("\n");
    resultSize = unionSet(result, start, end);

    printArr(result, end, resultSize);
    free(result);
    return 0;
}

int unionSet(int *arr, int start, int end)
{
    int x = 1, y = start + 1, addSize = end;

    while (x < start && y < end)
    {
        switch (COMPARE(arr[x], arr[y]))
        {
        case 0:
            arr[addSize] = arr[x];
            x++, y++;
            break;

        case 1:
            arr[addSize] = arr[y];
            y++;
            break;

        case -1:
            arr[addSize] = arr[x];
            x++;
            break;
        }
        addSize++;
    }

    while (x < start)
    {
        arr[addSize] = arr[x];
        x++, addSize++;
    }

    while (y < end)
    {
        arr[addSize] = arr[y];
        y++, addSize++;
    }

    return addSize;
}

void printArr(int *arr, int start, int end)
{
    printf("복학하고 싶어요 2022111603 황현태\n");

    for (int i = start; i < end; i++)
    {
        printf("%d ", arr[i]);
    }
}

void inputArr(FILE *f, int *fArr, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        fscanf(f, "%d", &fArr[i]);
    }
}

void isFileOpen(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}

int fileSize(FILE *f, int size)
{
    int val;
    while (fscanf(f, "%d", &val) != EOF)
    {
        size++;
    }
    fseek(f, 0, SEEK_SET);
    return size;
}