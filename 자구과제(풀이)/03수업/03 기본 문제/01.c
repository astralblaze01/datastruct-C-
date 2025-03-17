// 이진 탐색
// 종료 조건 : letf 값이 right값 보다 커질경우, 값을 찾을경우

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *initFile(const char *type);
int isOpen(FILE *f);
int fileSize(FILE *f);
int *initArray(FILE *f, int aSize);

int seqsearch(int *sArr, int sVal, int sSize);
int iterativeBinarySearch(int *iterArr, int iterVal, int iterSize);
int recursiveBinarySearch(int *reArr, int reVal, int left, int right);
void priArray(int *pArr, int pSize);
void timeSeqsearch(int *tArr, int tSize);
void timeIterativeBinarySearch(int *tArr, int tSize);
void timeRecursiveBinarySearch(int *reArr, int reSize);

int main()
{
    FILE *fp = initFile("r");
    int size = fileSize(fp);
    int *array = initArray(fp, size);
    // 학부, 학번, 이름 출력
    printf("복학할래 2022111603 황현태\n");

    // 단계 1
    timeSeqsearch(array, size);

    // 단계 2
    timeIterativeBinarySearch(array, size);

    // 단계 3
    timeRecursiveBinarySearch(array, size);

    free(array);
    fclose(fp);
    return 0;
}

void timeIterativeBinarySearch(int *tArr, int tSize)
{
    int freq = 100000, start, end;
    printf("iterative binary search\n");

    start = clock();
    for (int i = 0; i < freq; i++)
    {
        int res = iterativeBinarySearch(tArr, i, tSize); // 함수 이름;

        if (i < 10)
        {
            printf("search %d result : %d\n", i, res);
        }
    }
    end = clock();
    printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);
}

int iterativeBinarySearch(int *iterArr, int iterVal, int iterSize)
{
    int left = 0, right = iterSize;
    int center = left + (right - left) / 2;

    while (left <= right)
    {
        center = left + (right - left) / 2;

        if (iterArr[center] == iterVal)
        {
            return center;
        }

        if (iterArr[center] < iterVal)
        {
            left = center + 1;
            continue;
        }

        if (iterArr[center] > iterVal)
        {
            right = center - 1;
        }
    }

    return -1;
}

void timeRecursiveBinarySearch(int *reArr, int reSize)
{
    int freq = 100000, start, end;
    printf("recursive binary search\n");

    start = clock();
    for (int i = 0; i < freq; i++)
    {
        int res = recursiveBinarySearch(reArr, i, 0, reSize); // 함수 이름;

        if (i < 10)
        {
            printf("search %d result : %d\n", i, res);
        }
    }
    end = clock();
    printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);
}

int recursiveBinarySearch(int *reArr, int reVal, int left, int right)
{

    if (left > right)
    {
        return -1;
    }

    int center = left + (right - left) / 2;

    if (reArr[center] == reVal)
    {
        return center;
    }

    else if (reArr[center] < reVal)
    {
        return recursiveBinarySearch(reArr, reVal, center + 1, right);
    }

    else
    {
        return recursiveBinarySearch(reArr, reVal, left, center - 1);
    }
}

int seqsearch(int *sArr, int sVal, int sSize)
{
    for (int i = 0; i < sSize; i++)
    {
        if (sArr[i] == sVal)
        {
            return i;
        }
    }
    return -1;
}

// 시간측정
void timeSeqsearch(int *tArr, int tSize)
{
    int freq = 100000, start, end;
    printf("sequential search\n");

    start = clock();
    for (int i = 0; i < freq; i++)
    {
        int res = seqsearch(tArr, i, tSize); // 함수 이름;

        if (i < 10)
        {
            printf("search %d result : %d\n", i, res);
        }
    }
    end = clock();
    printf("computation time: %fms\n\n", 1000 * ((double)end - (double)start) / CLOCKS_PER_SEC);
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

void priArray(int *pArr, int pSize)
{
    printf("array : ");
    for (int i = 0; i < pSize; i++)
    {
        printf("%d ", pArr[i]);
    }
    printf("\n");
}

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

FILE *initFile(const char *type)
{
    FILE *rp;

    rp = fopen("in.txt", type);

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
