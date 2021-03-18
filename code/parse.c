#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"

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
            long y = POP();
            PUSH(y % x);
        }
        else if (strcmp(token, "#") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(pow(y, x));
        }
        else if (strcmp(token, "&") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y & x);
        }
        else if (strcmp(token, "|") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y | x);
        }
        else if (strcmp(token, "^") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y ^ x);
        }
        else if (strcmp(token, "~") == 0)
        {
            long x = POP();
            PUSH(~x);
        }
    }
    PRINT_STACK();
}

long POP()
{
    top--;
    return stack[top + 1];
}

void PUSH(long val_i)
{
    top++;
    stack[top] = val_i;
}

void PRINT_STACK()
{
    for (int i = 0; i <= top; i++)
    {
        printf("%ld", stack[i]);
    }
    printf("\n");
}
