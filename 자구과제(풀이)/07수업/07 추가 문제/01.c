// 지역 변수로 푼거거

#include <stdio.h>
#include <stdlib.h>
#define MAZE_SIZE 100
#define FALSE 0
#define TRUE 1

// stack
typedef struct
{
    short int row;
    short int col;
    short int dir;
} element;

// maze 크기
typedef struct
{
    int row;
    int col;
} location;

// 좌표 이동
typedef struct
{
    short int vert;
    short int horiz;
} offsets;

void isFileOpen(FILE *f);
void initMaze(int maze[MAZE_SIZE][MAZE_SIZE]);
void makeEdge(int maze[MAZE_SIZE][MAZE_SIZE], int row, int col);
void printMaze(int maze[MAZE_SIZE][MAZE_SIZE], int row, int col);
location inputValueForMaze(FILE *f, int maze[MAZE_SIZE][MAZE_SIZE]);
void push(element *stack, int *top, element inValue);
void printStack(element *stack, int top);
element pop(element *stack, int *top);
int isEmpty(int top);
int isFull(int top);
void path(int maze[MAZE_SIZE][MAZE_SIZE], int **mark, int *top, element *stack, offsets move[], location start, location end, location mazeSize);
void printMark(int **mark, location markSize);
void printPath(int maze[MAZE_SIZE][MAZE_SIZE], int **mark, location mazeSize);

int main()
{
    // 파일 포인터 할당후 검사
    FILE *fileReedMaze = fopen("in.txt", "r");
    isFileOpen(fileReedMaze);

    // start, end 좌표 선언
    location start, end;
    scanf("%d %d %d %d", &start.row, &start.col, &end.row, &end.col);

    // maze 초기화 및 값 입력
    int maze[MAZE_SIZE][MAZE_SIZE];
    initMaze(maze);
    location mazeSize = inputValueForMaze(fileReedMaze, maze);

    // mark 초기화
    int **mark = (int **)malloc(sizeof(int *) * (mazeSize.row + 1));
    for (int i = 0; i < mazeSize.row + 1; i++)
    {
        mark[i] = (int *)malloc(sizeof(int) * (mazeSize.col + 1));
    }
    for (int i = 0; i < mazeSize.row + 1; i++)
    {
        for (int j = 0; j < mazeSize.col + 1; j++)
        {
            mark[i][j] = 0;
        }
    }

    // offsets 선언
    offsets move[4] = {
        {0, 1},
        // {-1, 1},
        {-1, 0},
        // {1, 1},
        {1, 0},
        // {1, -1},
        {0, -1},
        // {-1, -1},
    };

    // stack 선언
    element *stack = (element *)malloc(sizeof(element) * (MAZE_SIZE * MAZE_SIZE));
    int top = 0;

    // 경로 찾기
    path(maze, mark, &top, stack, move, start, end, mazeSize);

    // 경로 출력
    // printPath(maze, mark, mazeSize);

    // free
    free(stack);
    for (int i = 0; i < mazeSize.row + 1; i++)
    {
        free(mark);
    }
    free(mark);
    fclose(fileReedMaze);
}

void printPath(int maze[MAZE_SIZE][MAZE_SIZE], int **mark, location mazeSize)
{
    printf("<path>\n");
    for (int i = 0; i < mazeSize.row + 1; i++)
    {
        for (int j = 0; j < mazeSize.col + 1; j++)
        {
            if (mark[i][j] == 1)
            {
                printf("%c ", 'X');
            }
            else
            {
                printf("%d ", maze[i][j]);
            }
        }
        printf("\n");
    }
}

void path(int maze[MAZE_SIZE][MAZE_SIZE], int **mark, int *top, element *stack, offsets move[], location start, location end, location mazeSize)
{
    int row, col, nextRow, nextCol, dir, found = FALSE;
    element position;

    mark[start.row][start.col] = 1;

    position.row = start.row;
    position.col = start.col;
    position.dir = 0;
    push(stack, top, position);

    while (*top > 0 && !found)
    {
        position = pop(stack, top);

        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 4 && !found)
        {
            // dir 방향으로 이동
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;

            // 출구 찾았을때때
            if (nextRow == end.row && nextCol == end.col)
            {
                found = TRUE;
                mark[nextRow][nextCol] = 1;
            }
            // 한번도 안갔을때
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
            {
                mark[nextRow][nextCol] = 1;

                position.row = row;
                position.col = col;
                position.dir = ++dir;

                push(stack, top, position);

                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
            {
                ++dir;
            }
        }
    }

    // 경로 찾았을때때
    if (found)
    {
        // printMark(mark, mazeSize);
        printPath(maze, mark, mazeSize);
    }
    else
    {
        printf("No path\n");
    }
}

void printMark(int **mark, location markSize)
{
    printf("<mark>\n");
    for (int i = 0; i < markSize.row + 1; i++)
    {
        for (int j = 0; j < markSize.col + 1; j++)
        {
            printf("%d ", mark[i][j]);
        }
        printf("\n");
    }
}

int isFull(int top)
{
    // 가득 찬경우
    if (top > MAZE_SIZE * MAZE_SIZE)
    {
        printf("stack is full\n");
        return 0;
    }
    return 1;
}

int isEmpty(int top)
{
    // 값이 없는경우우
    if (top < 0)
    {
        printf("stack is empty\n");
        return 0;
    }
    return 1;
}

void push(element *stack, int *top, element inValue)
{
    if (isFull(*top))
    {
        stack[*top].row = inValue.row;
        stack[*top].col = inValue.col;
        stack[*top].dir = inValue.dir;
        (*top)++;
    }
}

element pop(element *stack, int *top)
{
    if (isEmpty(*top))
    {
        // printf("<pop>\n");
        // printf("top : %d | row: %d | col : %d | dir : %d\n", *top, stack[*top].row, stack[*top].col, stack[*top].dir);
        (*top)--;
        return stack[*top];
    }
}

void printStack(element *stack, int top)
{
    for (int i = 0; i < top; i++)
    {
        printf("<print Stack>\n");
        printf("top : %d | row: %d | col : %d | dir : %d\n", top, stack[i].row, stack[i].col, stack[i].dir);
    }
}

// 배열 출력
void printMaze(int maze[MAZE_SIZE][MAZE_SIZE], int row, int col)
{
    for (int i = 0; i < row + 1; i++)
    {
        for (int j = 0; j < col + 1; j++)
        {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

// 파일로부터 배열값 입력;
location inputValueForMaze(FILE *f, int maze[MAZE_SIZE][MAZE_SIZE])
{
    char value;
    location result;
    result.row = 1, result.col = 1;

    while (fscanf(f, "%c", &value) != EOF)
    {
        if (value == '\n')
        {
            result.row++;
            result.col = 1;
            continue;
        }
        else
        {
            if (value == ' ')
            {
                continue;
            }
            else
            {
                maze[result.row][result.col] = value - '0';
                result.col++;
            }
        }
    }
    result.row++;

    // 테두리 만들기
    makeEdge(maze, result.row, result.col);

    // maze 출력
    // printMaze(maze, result.row, result.col);

    return result;
}

// 벽만들기기
void makeEdge(int maze[MAZE_SIZE][MAZE_SIZE], int row, int col)
{
    // 기로 체우기기
    for (int i = 0; i < col + 1; i++)
    {
        maze[0][i] = 1;
        maze[row][i] = 1;
    }

    // 세로 체우기
    for (int j = 1; j < col; j++)
    {
        maze[j][0] = 1;
        maze[j][col] = 1;
    }
}

// maze 초기화;
void initMaze(int maze[MAZE_SIZE][MAZE_SIZE])
{
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        for (int j = 0; j < MAZE_SIZE; j++)
        {
            maze[i][j] = -1;
        }
    }
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