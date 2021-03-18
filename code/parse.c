#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"

void PUSH(long val);
long POP();
void PRINNT_STACK();

// Tenho que arranjar maneia de tirar estas globais
int top = -1;
long stack[10240];

void parse(char *line)
{
    char *delimitadores = " \t \n";
    for (char *token = strtok(line, delimitadores); token != NULL; token = strtok(NULL, delimitadores))
    {
        char *resto;
        long val_i = strtol(token, &resto, 10);
        if (strlen(resto) == 0)
        {
            PUSH(val_i);
        }
        else if (strcmp(token, "+") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(x + y);
        }
        else if (strcmp(token, "*") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(x * y);
        }
        else if (strcmp(token, "/") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y / x);
        }
        else if (strcmp(token, "-") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y - x);
        }
        else if (strcmp(token, ")") == 0)
        {
            long x = POP();
            PUSH(x + 1);
        }
        else if (strcmp(token, "(") == 0)
        {
            long x = POP();
            PUSH(x - 1);
        }
        else if (strcmp(token, "%") == 0)
        {
            long x = POP();
            if (x < 0)
                PUSH((-1) * x);
            else
                PUSH(x);
        }
        else if (strcmp(token, "#") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(pow(x, y));
        }
    }
    PRINT_STACK();
}

long POP()
{
    int loc_top = top;
    if (top == -1)
    {
        printf("Stack vazia velho!!!\n");
        return 0;
    }
    else
    {
        printf("Popei %lu!!\n", stack[top]);
        top--;
        loc_top = top;
        return stack[top + 1];
    }
}

void PUSH(long val_i)
{
    if (top == 10240)
        printf("Stack cheia velho!!!\n");
    else
    {
        top++;
        stack[top] = val_i;
        printf("Pushei %lu!!\n", stack[top]);
    }
}

void PRINT_STACK()
{
    for (int i = 0; i <= top; i++)
    {
        printf("%lu", stack[i]);
        printf("/");
    }
    printf("\n");
}
