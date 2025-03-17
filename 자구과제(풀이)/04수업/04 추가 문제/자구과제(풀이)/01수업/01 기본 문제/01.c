#include <stdio.h>
#include <stdlib.h>

void arrPrint(int *arrP, int size);
void insertionSort(int *arrS, int arrSS);
void duplicationValue(int *arrD, int sizeD);

int main()
{
    int arrSize;
    int *arr = (int *)malloc(sizeof(int) * arrSize);

    printf("민간인(진) 23-71005654 황현태\n");

    scanf("%d", &arrSize);
    for (int i = 0; i < arrSize; i++)
    {
        scanf("%d", &arr[i]);
    }

    insertionSort(arr, arrSize);
    arrPrint(arr, arrSize);
    duplicationValue(arr, arrSize);

    return 0;
}

// 삽입정렬
void insertionSort(int *arrS, int arrSS)
{
    int i, j, key;

    for (i = 1; i < arrSS; i++)
    {
        key = arrS[i];

        for (j = i - 1; j >= 0 && arrS[j] > key; j--)
        {
            arrS[j + 1] = arrS[j];
        }

        arrS[j + 1] = key;
    }
}

// 중복값 찾기
void duplicationValue(int *arrD, int sizeD)
{

    int temp = arrD[0];
    int cnt = 0, k = 0;

    for (int i = 1; i < sizeD; i++)
    {
        if (temp == arrD[i])
        {
            cnt++;
        }
        else
        {
            temp = arrD[i];
            if (cnt != 0)
            {
                printf("%d ", arrD[i - 1]);
                k++;
            }
            cnt = 0;
        }
    }

    if (cnt != 0)
    {
        printf("%d ", temp);
    }
    if (k == 0)
    {
        printf("중복값 없음");
    }
}

// 출력 test
void arrPrint(int *arrP, int sizeP)
{
    printf("n : %d\n", sizeP);
    printf("L : ");
    for (int i = 0; i < sizeP; i++)
    {
        printf("%d ", arrP[i]);
    }
    printf("\n");
}