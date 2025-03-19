#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int coef;  // 숫자
    int expon; // 지수
} polynomial;

int isOpen(FILE *f);
int addPolynomial(polynomial *final, int paSize, int pbSize);
FILE *initFile(const char *fileName, const char *type);
polynomial *initArray(FILE *fFirst, FILE *fEnd, int fSize, int eSize);
void printFinal(polynomial *final, int start, int end);

int main()
{
    FILE *fa = initFile("a.txt", "r");
    FILE *fb = initFile("b.txt", "r");
    FILE *fc = initFile("c.txt", "w");

    // 배열 크기 받기기
    int arrASize, arrBSize;
    fscanf(fa, "%d", &arrASize);
    fscanf(fb, "%d", &arrBSize);

    polynomial *final = initArray(fa, fb, arrASize, arrBSize);
    int finSize = addPolynomial(final, arrASize, arrBSize);

    // 출력
    printFinal(final, arrBSize + arrASize, finSize);

    // free
    free(final);

    // 파일 닫기
    fclose(fa);
    fclose(fb);
    fclose(fc);
}

// 출력
void printFinal(polynomial *final, int start, int end)
{
    FILE *fin = initFile("c.txt", "w");

    fprintf(fin, "복학하고 싶어요 2022111603 황현태\n");
    fprintf(fin, "%d\n", end - start);
    for (int i = start; i < end; i++)
    {
        fprintf(fin, "%d %d ", final[i].coef, final[i].expon);
    }

    fclose(fin);
}

int addPolynomial(polynomial *final, int paSize, int pbSize)
{
    int cIndex = pbSize + paSize, x = 0, y = paSize;

    while (x < paSize && y < paSize + pbSize)
    {
        // a와 b의 지수가 같은 경우
        if (final[x].expon == final[y].expon)
        {
            if (!(final[x].coef + final[y].coef))
            {
                x++;
                y++;
            }
            else
            {
                final[cIndex].coef = final[x].coef + final[y].coef;
                final[cIndex].expon = final[x].expon;
                cIndex++;
                x++;
                y++;
            }
        }
        // a의 지수가 b의 지수보다 큰 경우
        else if (final[x].expon > final[y].expon)
        {
            final[cIndex] = final[x];
            cIndex++;
            x++;
        }
        // a의 지수가 b의 지수보다 작은 경우
        else
        {
            final[cIndex] = final[y];
            cIndex++;
            y++;
        }
    }

    // a 다항식에 남은 항 처리
    while (x < paSize)
    {
        final[cIndex] = final[x];
        cIndex++;
        x++;
    }

    // b 다항식에 남은 항 처리
    while (y < paSize + pbSize)
    {
        final[cIndex] = final[y];
        cIndex++;
        y++;
    }

    return cIndex;
}
// 배열 초기화화
polynomial *initArray(FILE *fFirst, FILE *fEnd, int fSize, int eSize)
{
    int size = (fSize + eSize);

    polynomial *initArr = (polynomial *)malloc(sizeof(polynomial) * size * 2);

    if (!initArr)
    {
        printf("memory allocation is fail");
        exit(1);
    }

    for (int i = 0; i < fSize; i++)
    {
        fscanf(fFirst, "%d %d", &(initArr[i].coef), &(initArr[i].expon));
    }

    for (int i = fSize; i < size; i++)
    {
        fscanf(fEnd, "%d %d", &(initArr[i].coef), &(initArr[i].expon));
    }

    return initArr;
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
