#include <stdio.h>
#include <stdlib.h>

int isOpen(FILE *f);
FILE *initFile(const char *type);
int fileSize(FILE *f);
int *initArray(FILE *f, int aSize);
void priArray(int *pArr, int pSize);
int deleteArrVal(int *delArr, int dVal, int dSize);

int main()
{
    FILE *fp = initFile("r");

    int size = fileSize(fp);
    int *array = initArray(fp, size);
    int value = 2022111603;
    int newSize = size;

    printf("복학할래 2022111603 황현태\n");
    printf("N : %d\n", size);
    // priArray(array, size);

    while (value > 0)
    {
        priArray(array, newSize);
        scanf("%d", &value);
        newSize = deleteArrVal(array, value, newSize);
        if(newSize <= 0)
        {
            printf("array is empty\n");
            break;
        }
    }

    free(array);
    fclose(fp);
    return 0;
}

int deleteArrVal(int *delArr, int dVal, int dSize)
{
    int tempArr[100];
    int index = 0;

    for (int i = 0; i < dSize; i++)
    {
        if (delArr[i] != dVal)
        {
            tempArr[index++] = delArr[i];
        }
    }

        for (int i = 0; i < index; i++)
        {
            delArr[i] = tempArr[i];
        }

        return index;
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
    // fscanf를 이용하면 f값이 계속해서 이동함
    // 파일안에 4 5 6 7 8이 있다고 가정하자
    // 이때 fscnaf를 처음 이용하면 f는 4를 가르키고 있음
    // 그 후에 fsncaf를 또 실행하면 f는 5를 가르키고 있는거임
    // 근데 내가 printf("%p", f)했을때 while문을 실행하기 전이랑 후의 주솟값이 똑같았잖아
    // 그게 f의 "파일포인터의 주소는 변하지 않지만 파일 포인터가 가리키는 위치가 변화해서 그런거임"
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
