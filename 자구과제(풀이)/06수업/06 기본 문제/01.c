#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int col;
    int row;
    int values;
} term;

void isFileOpen(FILE *f);
int **allocationMatrix(int **matrix, int col, int row);
void printMatrix(int **matrix, int col, int row);
void initMatrix(FILE *f, int **matrix, int col, int row);
int createSparseMatrix(int **matrix, term *threeTuple, int col, int row);
void printTuple(term *threeTuple, int size);
void FilePrintTuple(FILE *f, term *threeTuple, int size);
void fastTranspose(term *a, term *b);

int main()
{
    // 파일 포인터 초기화화
    FILE *fReed, *fOut;
    fReed = fopen("in.txt", "r");
    isFileOpen(fReed);
    fOut = fopen("out.txt", "w");
    isFileOpen(fOut);

    // 행 & 열, tuple Max size 초기화화
    int aCol, aRow;
    fscanf(fReed, "%d %d", &aCol, &aRow);

    // 배열 초기화
    int **aMatrix = allocationMatrix(aMatrix, aCol, aRow);
    initMatrix(fReed, aMatrix, aCol, aRow);

    // tuple 선언
    int maxTupleSize = aCol * aRow;
    term *threeTupleA = (term *)malloc(sizeof(term) * maxTupleSize);
    term *threeTupleB = (term *)malloc(sizeof(term) * maxTupleSize);
    maxTupleSize = createSparseMatrix(aMatrix, threeTupleA, aCol, aRow);

    // tupleA 출력
    printTuple(threeTupleA, maxTupleSize);

    // 전치
    fastTranspose(threeTupleA, threeTupleB);

    // tupleB 출력력
    FilePrintTuple(fOut, threeTupleB, maxTupleSize);
    printTuple(threeTupleB, maxTupleSize);

    // 파일 닫기기
    fclose(fReed);
    fclose(fOut);

    // free
    free(threeTupleA);
    free(threeTupleB);
    for (int i = 0; i < aRow; i++)
    {
        free(*(aMatrix + i));
    }
    free(aMatrix);
}


void fastTranspose(term *a, term *b)
{
    int *rowTerms = (int *)malloc(sizeof(int) * a[0].col);
    int *startingPos = (int *)malloc(sizeof(int) * a[0].col);

    int i, j, numCols = a[0].col, numTerms = a[0].values;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].values = numTerms;

    if (numTerms <= 0)
    {
        free(rowTerms);
        free(startingPos);
        return;
    }

    else
    {
        for (i = 0; i < numCols; i++)
            rowTerms[i] = 0;

        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;

        startingPos[0] = 1;

        for (i = 1; i < numCols; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

        for (i = 1; i <= numTerms; i++)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].values = a[i].values;
        }

        free(rowTerms);
        free(startingPos);
    }
}


void FilePrintTuple(FILE *f, term *threeTuple, int size)
{

    fprintf(f, "복학즘 하자 이제 2022111603 황현태\n");
    for (int i = 0; i < size; i++)
    {
        fprintf(f, "%d %d %d\n", threeTuple[i].col, threeTuple[i].row, threeTuple[i].values);
    }
}


void printTuple(term *threeTuple, int size)
{
    printf("복학즘 하자 이제 2022111603 황현태\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d %d %d\n", threeTuple[i].col, threeTuple[i].row, threeTuple[i].values);
    }
}


int createSparseMatrix(int **matrix, term *threeTuple, int col, int row)
{
    int sizeOfTuple = 1;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if (matrix[i][j] != 0)
            {
                threeTuple[sizeOfTuple].col = i;
                threeTuple[sizeOfTuple].row = j;
                threeTuple[sizeOfTuple].values = matrix[i][j];
                sizeOfTuple++;
            }
        }
    }

    threeTuple[0].col = col, threeTuple[0].row = row, threeTuple[0].values = sizeOfTuple - 1;

    return sizeOfTuple;
}

// 배열 값 넣기
void initMatrix(FILE *f, int **matrix, int col, int row)
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            fscanf(f, "%d", &matrix[i][j]);
        }
    }
}

// 배열 출력
void printMatrix(int **matrix, int col, int row)
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 배열 동적 할당
int **allocationMatrix(int **matrix, int col, int row)
{
    matrix = (int **)malloc(sizeof(int *) * col);
    for (int i = 0; i < col; i++)
    {
        *(matrix + i) = (int *)malloc(sizeof(int) * row);
    }

    return matrix;
}

// 파일 검사
void isFileOpen(FILE *f)
{
    if (!f)
    {
        printf("file is not open");
        exit(1);
    }
}