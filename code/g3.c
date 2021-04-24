/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"
#include "stack.h"
#include "g1.h"
#include "g3.h"
#include <assert.h>

void greater(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_long;
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (y_ret > x_ret)
        sprintf(val.valor, "%d", 1);
    else
        sprintf(val.valor, "%d", 0);
    PUSH(ptr_STACK, val);
}

void smaller(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_long;
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (y_ret < x_ret)
        sprintf(val.valor, "%d", 1);
    else
        sprintf(val.valor, "%d", 0);
    PUSH(ptr_STACK, val);
}

void equal(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_long;
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (y_ret == x_ret)
        sprintf(val.valor, "%d", 1);
    else
        sprintf(val.valor, "%d", 0);
    PUSH(ptr_STACK, val);
}

void no(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_long;
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    if (x_ret)
        sprintf(val.valor, "%d", 0);
    else
        sprintf(val.valor, "%d", 1);
    PUSH(ptr_STACK, val);
}

void ifthenelse(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    struct elemento condition = POP(ptr_STACK);
    if (strcmp(condition.valor, "0") == 0)
        PUSH(ptr_STACK, x);
    else
        PUSH(ptr_STACK, y);
}

void efunction(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '>':
        ebigger(ptr_STACK);
        break;
    case '<':
        esmaller(ptr_STACK);
        break;
    case '&':
        eshortcut(ptr_STACK);
        break;
    case '|':
        orshortcut(ptr_STACK);
        break;
    default:
        epequeno(ptr_STACK);
        break;
    }
}

void ebigger(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (y_ret > x_ret)
        PUSH(ptr_STACK, y);
    else
        PUSH(ptr_STACK, x);
}

void esmaller(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (y_ret > x_ret)
        PUSH(ptr_STACK, x);
    else
        PUSH(ptr_STACK, y);
}

void eshortcut(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);

    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (strcmp(y.valor, "0") == 0)
    {
        PUSH(ptr_STACK, y);
    }
    else if (strcmp(x.valor, "0") == 0)
    {
        PUSH(ptr_STACK, x);
    }
    else if (x_ret > y_ret)
    {
        PUSH(ptr_STACK, x);
    }
    else if (y_ret > x_ret)
    {
        PUSH(ptr_STACK, y);
    }
}

void orshortcut(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (x_ret == 0 && y_ret == 0)
    {
        PUSH(ptr_STACK, x);
    }
    else if (y_ret != 0)
    {
        PUSH(ptr_STACK, y);
    }
    else
        PUSH(ptr_STACK, x);
}

void epequeno(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = strtof(x.valor, NULL);
    struct elemento y = POP(ptr_STACK);
    double y_ret = strtof(y.valor, NULL);
    if (strcmp(y.valor, "0") == 0)
    {
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(x.valor, "0") == 0)
    {
        PUSH(ptr_STACK, y);
    }
    else if (x_ret > y_ret)
    {
        PUSH(ptr_STACK, y);
    }
    else
    {
        PUSH(ptr_STACK, x);
    }
}

void variables1(struct stack *ptr_STACK, char *token)
{
    int i = *token % 65;
    PUSH(ptr_STACK, (*ptr_STACK).vars[i].elemento);
}

void variables2(struct stack *ptr_STACK, char *token)
{
    if (strcmp(token, "N") == 0)
    {
        struct elemento x;
        x.tipo = T_string;
        sprintf(x.valor, "%s", "\n");
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "S") == 0)
    {
        struct elemento x;
        x.tipo = T_string;
        sprintf(x.valor, "%s", " ");
        PUSH(ptr_STACK, x);
    }
    else if (*token == ':')
    {
        int i = *(token + 1) % 65;
        (*ptr_STACK).vars[i].elemento = ptr_STACK->array[(*ptr_STACK).top];
    }
}
