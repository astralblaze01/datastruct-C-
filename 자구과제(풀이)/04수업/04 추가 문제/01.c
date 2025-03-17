// 아직 구현 못함
// test

    #include <stdio.h>
#include <stdlib.h>

FILE *initFile(const char *fileName, const char *type);
int isOpen(FILE *f);
int fileSize(FILE *f);
int *initArray(FILE *f, int aSize);
int *initCheckArr(int *arr, int size);

int main()
{
    FILE *fp = initFile("in.txt", "r");
    int size = fileSize(fp);
    int *check = (int *)malloc(sizeof(int) * size);
    int *setArr = (int *)malloc(sizeof(int) * size);

    setArr = initArray(fp, size);
    check = initCheckArr(check, size);
}

// check 배열 초기화
int *initCheckArr(int *arr, int size)
{
    while (size)
    {
        arr[--size] = 0;
    }
    return arr;
}

// 배열 초기화화
int *initArray(FILE *f, int aSize)
{
    int *initArr = (int *)malloc(sizeof(int) * aSize);

    if (!initArr)
    {
        printf("memory allocation is fail");
        exit(1);
    }

    for (int i = 0; i < aSize; i++)
    {
        fscanf(f, "%d", &initArr[i]);
    }

    fseek(f, 0, SEEK_SET);

    return initArr;
}

// 파일 크기 나타내는 함수
int fileSize(FILE *f)
{
    int fVal, fSize = 0;

    while (!feof(f)) // feof : 값이 있으면 0 없으면 1, 마지막에 도달했으면 1
    {
        fscanf(f, "%d", &fVal);
        fSize++;
    }

    fseek(f, 0, SEEK_SET);

    return fSize;
}

// 열리면 1 없으면 0
int isOpen(FILE *f)
{
    if (!f)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// 파일 포인터 할당
FILE *initFile(const char *fileName, const char *type)
{
    FILE *rp;

    rp = fopen(fileName, type);

    if (!(isOpen(rp)))
    {
        printf("file is not open");
        exit(1);
    }
    else
    {
        return rp;
    }
}