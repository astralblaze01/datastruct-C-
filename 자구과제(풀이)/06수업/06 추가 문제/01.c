#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int row;
    int col;
    int value;
} term;

void isFileOpen(FILE *f);
int **allocationMatrix(int **matrix, int row, int col);
int **initMatrix(FILE *f, int **mtrx, int row, int col);
void printMatrix(int **matrix, int row, int col);
int *initKey(FILE *f, int *key, int size);
int createSparseMatrix(int **matrix, term *tuple, int row, int col);
term patternMatch(int **matrix, term *tuple, int tupleSize, int *key, int keySize, int zeroindex);
void printTuple(term *threeTuple, int size);
int isKey(int **matrix, int *key, int keySize, term *index, int zeroindex);
int countZeroInKey(int *key, int keySize);

int main()
{
    // file 선언
    FILE *fReed = fopen("in1.txt", "r");
    FILE *fKey = fopen("key1.txt", "r");
    isFileOpen(fReed);
    isFileOpen(fKey);

    // 행 열 key size추가
    int matrixRow, matrixCol;
    int keySize;
    fscanf(fReed, "%d %d", &matrixRow, &matrixCol);
    fscanf(fKey, "%d", &keySize);

    // 배열 초기화
    int **matrix = initMatrix(fReed, matrix, matrixRow, matrixCol);

    // 배열 출력력
    // printMatrix(matrix, matrixRow, matrixCol);

    // key값
    int *key = (int *)malloc(sizeof(int) * keySize);
    key = initKey(fKey, key, keySize);
    // key앞에 0인 값값
    int foruntZeroNum = countZeroInKey(key, keySize);

    // tuple
    term *tuple = (term *)malloc(sizeof(term) * (matrixRow * matrixCol));
    int tupleSize = createSparseMatrix(matrix, tuple, matrixRow, matrixCol);

    // tuple 출력
    // printTuple(tuple, tupleSize);

    // find
    term result = patternMatch(matrix, tuple, tupleSize, key, keySize, foruntZeroNum);
    printf("이제 복학즘 하자 2022111603 황현태\n");
    printf("(%d,%d)", result.row, result.col);
}

int countZeroInKey(int *key, int keySize)
{
    int cnt = 0;

    for (int i = 0; i < keySize; i++)
    {
        if (key[i] == 0)
        {
            cnt++;
        }
        else
        {
            break;
        }
    }
    return cnt;
}

term patternMatch(int **matrix, term *tuple, int tupleSize, int *key, int keySize, int zeroindex)
{
    int x, y;
    term index;

    for (int i = 1; i < tupleSize; i++)
    {
        if (tuple[i].value == key[zeroindex])
        {
            index.row = tuple[i].row;
            index.col = tuple[i].col;

            if (isKey(matrix, key, keySize, &index, zeroindex))
            {
                index.col = index.col - zeroindex;
                return index;
            }
        }
    }

    index.row = -1;
    index.col = -1;
    return index;
}

int isKey(int **matrix, int *key, int keySize, term *index, int zeroindex)
{
    int flag = 0;
    int zeroN = zeroindex;

    for (int i = 0; i < keySize; i++)
    {
        if (matrix[index->row][index->col + i] == key[zeroindex])
        {
            flag++;
        }
        zeroindex++;
    }

    if (flag == keySize - zeroN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printTuple(term *threeTuple, int size)
{
    printf("복학즘 하자 이제 2022111603 황현태\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d %d %d\n", threeTuple[i].row, threeTuple[i].col, threeTuple[i].value);
    }
}

int createSparseMatrix(int **matrix, term *tuple, int row, int col)
{
    int sizeOfTuple = 1;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] != 0)
            {
                tuple[sizeOfTuple].row = i;
                tuple[sizeOfTuple].col = j;
                tuple[sizeOfTuple].value = matrix[i][j];
                sizeOfTuple++;
            }
        }
    }

    tuple[0].col = col, tuple[0].row = row, tuple[0].value = sizeOfTuple - 1;

    return sizeOfTuple;
}

// key값 초기화화
int *initKey(FILE *f, int *key, int size)
{
    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%d", &key[i]);
    }
    return key;
}

// 배열 출력
void printMatrix(int **matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **allocationMatrix(int **matrix, int row, int col)
{
    matrix = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        *(matrix + i) = (int *)malloc(sizeof(int) * col);
    }

    return matrix;
}

int **initMatrix(FILE *f, int **mtrx, int row, int col)
{
    mtrx = allocationMatrix(mtrx, row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(f, "%d", &mtrx[i][j]);
        }
    }

    return mtrx;
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