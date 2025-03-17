#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *initFile(const char *fileName, const char *type);
int isOpen(FILE *f);
char *wordVal(FILE *f, char *vWord);
char *lowerWord(char *lWord, int size);
void palindrome(char *pWord);
int isLast(FILE *f);

int main()
{
    FILE *fp = initFile("in02.txt", "r");
    char *word = (char *)malloc(sizeof(char) * 20);

    printf("복학하고 싶은 2022111603 황현태\n");

    // 각 줄의 알파벳 연산
    while (isLast(fp))
    {
        word = wordVal(fp, word);
        palindrome(word);
    }

    fclose(fp);
}

// 소문자로 변환
char *lowerWord(char *lWord, int size)
{
    while (size > 0)
    {
        size--;
        if (lWord[size] >= 'A' && lWord[size] <= 'Z')
        {
            lWord[size] = lWord[size] + 32;
        }
    }

    return lWord;
}

// palindrome판별후 출력
void palindrome(char *pWord)
{
    int len = strlen(pWord);
    int countLen = len / 2;
    int lastIndex = len - 1;
    int firstIndex = 0;

    // 깊은복사 앝은 복사
    char *lWord = (char *)malloc(sizeof(char) * 20);
    strcpy(lWord, pWord);
    lWord = lowerWord(lWord, len);

    while (firstIndex != len / 2)
    {
        if (lWord[firstIndex] == lWord[lastIndex])
        {
            countLen--;
        }
        else
        {
            break;
        }
        firstIndex++;
        lastIndex--;
    }

    if (countLen == 0)
    {
        printf("%d %s is a palindrome\n", len, pWord);
    }
    else
    {
        printf("%d %s is not a palindrome\n", len, pWord);
    }
}

// 파일 안에 word값 1개씩 반환
char *wordVal(FILE *f, char *vWord)
{

    fscanf(f, "%s", vWord);
    return vWord;
}

// 파일 마지막 부분일 경우이면 0 아니면 1
int isLast(FILE *f)
{
    if ((feof(f)))
    {
        return 0;
    }
    else
        return 1;
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