#include <stdio.h>

FILE *initFile(const char *fileName, const char *type);
int isOpen(FILE *f);

int main()
{
    FILE *fp = initFile("in.txt", "r");

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