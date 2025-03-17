#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long ul;

int inDegree();
void fiboArr(ul *fArr, int fVal);
void printArr(ul *priArr, int priVal);
int reFibo(int n);

int main()
{
    clock_t start, finish;
    double elapsed;
    int n = inDegree();
    ul *array = (ul *)malloc(sizeof(ul) * (n + 1));

    
    
    start = clock();
    // 수행 시간을 측정할 프로그램 코드
    
    // array로 fibo 구현
    fiboArr(array, n);

    // fibo 재귀귀
    int result = reFibo(n);

    finish = clock();
    printf("array : %d\n", array[n-1] + array[n-2]);
    printf("reFibo : %d\n", result);


    // start와 finish 사이의 명령이 수행되는데 걸린 시간을 millisecond 단위로 환산해서 출력력
    elapsed = ((double)(finish) - (double)(start)) / CLOCKS_PER_SEC;
    printf("time : %f\n", elapsed * 1000.0);
    return 0;
}

int inDegree()
{
    int val;
    scanf("%d", &val);
    if (val < 0 || val > 45)
    {
        printf("range of n is incorrect");
        exit(1);
    }
    else
    {
        return val;
    }
}

void fiboArr(ul *fArr, int fVal)
{
    fArr[0] = 0;
    fArr[1] = 1;
    for (int i = 2; i < fVal; i++)
    {
        fArr[i] = fArr[i - 1] + fArr[i - 2];
    }
}

void printArr(ul *priArr, int priVal)
{
    for (int i = 0; i < priVal; i++)
    {
        printf("%u \n", priArr[i]);
    }
}

int reFibo(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return reFibo(n - 1) + reFibo(n - 2);
    }
}