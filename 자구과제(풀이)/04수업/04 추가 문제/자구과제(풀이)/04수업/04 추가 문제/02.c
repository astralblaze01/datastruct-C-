#include <stdio.h>
#include <stdlib.h>

int recursivePrime(int x, int y);

int main()
{
    FILE *fp = fopen("in.txt", "r");
    if (!fp)
    {
        printf("file is not open");
        exit(-1);
    }

    int valx, valy;

    while (fscanf(fp, "%d %d", &valx, &valy) != EOF)
    {
        if (recursivePrime(valx, valy) == -1)
        {
            break;
        }
        else if (recursivePrime(valx, valy))
        {
            printf("%d %d true\n", valx, valy);
        }
        else
        {
            printf("%d %d flase\n", valx, valy);
        }
    }

    fclose(fp);
}

int recursivePrime(int x, int y)
{
    if (x < 0 || y < 0)
    {
        return -1;
    }
    else
    {

        if (x == 1 || y == 1)
        {
            return 1;
        }
        else if (x == y)
        {
            return 0;
        }
        else if (x < y)
        {
            return recursivePrime(x, y - x);
        }
        else if (x > y)
        {
            return recursivePrime(x - y, y);
        }
        else
        {
            return 0;
        }
    }
}