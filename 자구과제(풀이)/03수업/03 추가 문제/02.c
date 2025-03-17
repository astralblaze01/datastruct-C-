#include <stdio.h>

int isEven(int val);
int binRepresentation(int val, int cnt);

int main()
{

    // // k값이 나머지 값인데 출력할때는 거꾸로 출력해야함
    // // 근데 거꾸로 출력할 이유 없고 우리는 1의 갯수 구하는거니까
    // // 그냥 이대로 재귀함수 구현해도 상관없음
    // int n = 2022111603;
    // int remain;
    // scanf("%d", &n);
    // int cnt = 0;
    // while (n > 0)
    // {
    //     remain = n % 2;
    //     if (remain)
    //     {
    //         cnt++;
    //     }
    //     n = n / 2;
    //     printf("%d", remain);
    // }
    // printf("\ncnt : %d\n", cnt);

    int result, n;

    while (1)
    {
        scanf("%d", &n);
        if (n < 0)
        {
            break;
        }

        result = binRepresentation(n, 0);
        printf("result : %d\n", result);
    }
}

// 짝수면 1 홀수면 0
int isEven(int val)
{
    if (!(val % 2))
    {
        return 1;
    }
    return 0;
}

int binRepresentation(int val, int cnt)
{
    if (val <= 0)
    {
        return cnt;
    }
    else
    {
        if (!isEven(val))
        {
            return binRepresentation(val / 2, ++cnt);
        }
        else
        {
            return binRepresentation(val / 2, cnt);
        }
    }
}