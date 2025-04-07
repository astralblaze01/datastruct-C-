#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE * fileA = fopen("a.txt", "r");
    checkFile(fileA);
    FILE * fileB = fopen("b.txt","r");
    checkFile(fileB);
    

}

void checkFile(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}