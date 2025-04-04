#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define INFIX_SIZE 100

typedef enum
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
} precedence;

typedef struct
{
    precedence val;
} element;

// 함수 선언
void checkFile(FILE *f);
void initInfixArr(FILE *f, char *infix);
precedence getToken(char *symbol, char expr[], int *n);
void postfix(element *stack, char expr[], char *postfix);
int isEmpty(int top);
int isFull(int top);
precedence pop(element *stack, int *top);
void push(element *stack, int *top, precedence val);
void printToken(precedence token);
int evalPostfix(char *postfix);

// main
int main()
{
    FILE *infixFile = fopen("in.txt", "r");
    checkFile(infixFile);

    char infixArr[INFIX_SIZE];
    initInfixArr(infixFile, infixArr);
    fclose(infixFile);

    element stack[STACK_SIZE];
    char postFix[INFIX_SIZE] = {0};

    postfix(stack, infixArr, postFix);
    printf("%s\n", postFix);

    int result = evalPostfix(postFix);
    printf("%d\n", result);

    return 0;
}

// 후위 표기식 생성
void postfix(element *stack, char expr[], char *postfix)
{
    int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};  // in-stack precedence
    int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; // incoming precedence

    int n = 0, top = -1, index = 0;
    char symbol;
    precedence token;

    stack[++top].val = eos;
    token = getToken(&symbol, expr, &n);

    while (token != eos)
    {
        if (token == operand)
        {
            postfix[index++] = symbol;
        }
        else if (token == rparen)
        {
            while (stack[top].val != lparen)
            {
                precedence popped = pop(stack, &top);
                switch (popped)
                {
                case plus:
                    postfix[index++] = '+';
                    break;
                case minus:
                    postfix[index++] = '-';
                    break;
                case times:
                    postfix[index++] = '*';
                    break;
                case divide:
                    postfix[index++] = '/';
                    break;
                case mod:
                    postfix[index++] = '%';
                    break;
                default:
                    break;
                }
            }
            pop(stack, &top); // '(' 제거
        }
        else
        {
            while (isp[stack[top].val] >= icp[token])
            {
                precedence popped = pop(stack, &top);
                switch (popped)
                {
                case plus:
                    postfix[index++] = '+';
                    break;
                case minus:
                    postfix[index++] = '-';
                    break;
                case times:
                    postfix[index++] = '*';
                    break;
                case divide:
                    postfix[index++] = '/';
                    break;
                case mod:
                    postfix[index++] = '%';
                    break;
                default:
                    break;
                }
            }
            push(stack, &top, token);
        }
        token = getToken(&symbol, expr, &n);
    }

    while ((token = pop(stack, &top)) != eos)
    {
        switch (token)
        {
        case plus:
            postfix[index++] = '+';
            break;
        case minus:
            postfix[index++] = '-';
            break;
        case times:
            postfix[index++] = '*';
            break;
        case divide:
            postfix[index++] = '/';
            break;
        case mod:
            postfix[index++] = '%';
            break;
        default:
            break;
        }
    }
    postfix[index] = '\0';
}

// 후위 표기식 평가
int evalPostfix(char *postfix)
{
    int stack[STACK_SIZE];
    int top = -1;
    char symbol;
    int i = 0, op1, op2;

    while ((symbol = postfix[i++]) != '\0')
    {
        if (symbol >= '0' && symbol <= '9')
        {
            stack[++top] = symbol - '0';
        }
        else
        {
            op2 = stack[top--];
            op1 = stack[top--];
            switch (symbol)
            {
            case '+':
                stack[++top] = op1 + op2;
                break;
            case '-':
                stack[++top] = op1 - op2;
                break;
            case '*':
                stack[++top] = op1 * op2;
                break;
            case '/':
                stack[++top] = op1 / op2;
                break;
            case '%':
                stack[++top] = op1 % op2;
                break;
            }
        }
    }
    return stack[top];
}

// 토큰 얻기
precedence getToken(char *symbol, char expr[], int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '/':
        return divide;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

// push / pop
void push(element *stack, int *top, precedence val)
{
    if (!isFull(*top))
    {
        stack[++(*top)].val = val;
    }
}

precedence pop(element *stack, int *top)
{
    if (!isEmpty(*top))
    {
        return stack[(*top)--].val;
    }
    return eos;
}

int isFull(int top)
{
    return top >= STACK_SIZE - 1;
}

int isEmpty(int top)
{
    return top == -1;
}

// 파일 열기 확인
void checkFile(FILE *f)
{
    if (!f)
    {
        printf("File open error\n");
        exit(1);
    }
}

// 파일에서 수식 읽기
void initInfixArr(FILE *f, char *infix)
{
    fscanf(f, "%s", infix); // 한 줄 수식 읽기
}
