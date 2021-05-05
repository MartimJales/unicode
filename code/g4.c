
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "parse.h"
#include "g1.h"
#include "g2.h"
#include "g3.h"
#include "g4.h"
#include <assert.h>

//falta testar (dentro dos PUSH o 1º elemento temos que vereficar se necessita de apontadores ou nao)

void concatenarray(struct stack *ptr_STACK)
{
    printf("Cheguei ao concatena!\n");
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    if ((x.tipo == T_array) && (y.tipo == T_array))
    {
        printf("Temos dois arrays!!!!\n");
        printf("Topo do array %d\n", x.data.val_p->top);

        for (int i = 0; i <= x.data.val_p->top; i++)
        {
            PUSH(y.data.val_p, x.data.val_p->array[i]);
        }
        PUSH(ptr_STACK, y);
    }
    else if ((x.tipo != T_array) && (y.tipo == T_array))
    {
        PUSH(y.data.val_p, x);
        PUSH(ptr_STACK, y);
    }
    else if ((x.tipo == T_array) && (y.tipo != T_array))
    {
        printf("Caiu aqui\n");
        struct elemento array;
        array.tipo = T_array;
        struct stack *new_stack = malloc(sizeof(struct stack));
        initStack(new_stack);
        array.data.val_p = new_stack;
        PUSH(array.data.val_p, y);
        for (int i = 0; i <= x.data.val_p->top; i++)
        {
            PUSH(array.data.val_p, x.data.val_p->array[i]);
        }
        PUSH(ptr_STACK, array);
    }
}

void empurraarray(struct stack *ptr_STACK)
{
    int i = 0;
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_array;
    for (i; i <= x.data.val_p->top; i++)
    {
        PUSH(ptr_STACK, x.data.val_p->array[i]);
    }
}

void repetearray(struct stack *ptr_STACK)
{
    int i = 0, n = 0;

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (x.tipo = T_int)
    {
        n = x.data.val_i;
    }

    else if (x.tipo = T_long)
    {
        n = x.data.val_l;
    }

    for (i; i < n; i++)
    {
        PUSH(ptr_STACK, y);
    }
}

void parse_array(char *line, struct stack *ptr_STACK)
{
    char *token;
    char *resto;

    char *delimitadores = " \t \n";
    for (token = get_token(delimitadores, cleanLim(line), &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        char *resto_num = "abc";
        int val_tipo;
        printf("Token atual da parse array: %s!\n", token);
        check_type(&resto_num, &token, &val_tipo);

        if (strlen(resto_num) == 0)
            put_token(ptr_STACK, val_tipo, token);
        else if (*token == '[')
        {
            printf("ARRAY!\n");
            pinta_array(&token, token);
            struct elemento val;
            val.tipo = T_array;
            struct stack *new_stack = malloc(sizeof(struct stack));
            initStack(new_stack);
            val.data.val_p = new_stack;
            put_array(ptr_STACK, token, &val);
        }
        else if (check_array(token))
            go_filter_array(ptr_STACK, token);
        else
            go_filter(ptr_STACK, token);
    }
}

void tamanho_array(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    int i = x.data.val_p->top + 1;
    struct elemento n;
    n.tipo = T_int;
    n.data.val_i = i;
    PUSH(ptr_STACK, n);
}

void range_array(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função range");

    struct elemento y;
    y.tipo = T_int;

    struct elemento array;
    array.tipo = T_array;
    struct stack new;
    array.data.val_p = &new;
    //struct array *ptr_array = (array.data.val_p);
    int i = 0;

    for (i; i < x.data.val_i; i++)
    {
        y.data.val_i = i;
        PUSH(&new, y);
    }
    PUSH(ptr_STACK, array);
}

void buscavalindice(struct stack *ptr_STACK)
{
    printf("entrei na busaca val indice \n");
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função range");

    struct elemento y = POP(ptr_STACK);

    int len = x.data.val_i;

    PUSH(ptr_STACK, y.data.val_p->array[len]);
}

void left_elementos(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função left_elementos");

    struct elemento y = POP(ptr_STACK);
    for (int i = 0; i < x.data.val_i; i++)
    {
        PUSH(ptr_STACK, y.data.val_p->array[i]);
    }
}

void right_elementos(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função range");
    struct elemento y = POP(ptr_STACK);
    for (int i = y.data.val_p->top; i > x.data.val_i; i--)
    {
        PUSH(ptr_STACK, y.data.val_p->array[i]);
    }
}
/*
void right_parentesis(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento new;
    POP(x.data.val_p);
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, y.data.val_p->array[y.data.array.top - 1]);
}*/

void left_parentesis(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento new = x.data.val_p->array[0];
    POP(x.data.val_p);
    for (int i = 0; i < x.data.val_p->top - 1; i++)
    {
        x.data.val_p->array[i] = x.data.val_p->array[i + 1];
    }
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, new);
}

void manarray(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '~':
        empurraarray(ptr_STACK);
        break;

    case '*':
        printf("entrei na manarray \n");
        repetearray(ptr_STACK);
        break;
    case ',':
        printf("Caiu na virgula");
        tamanho_array(ptr_STACK);
        break;
    case '=':
        printf("VAPOVAPO\n");
        buscavalindice(ptr_STACK);
        break;
    case '<':
        left_elementos(ptr_STACK);
        break;
    case '>':
        right_elementos(ptr_STACK);
        break;
    case '(':
        left_parentesis(ptr_STACK);
        break;

    /*case ')':
        right_parentesis(ptr_STACK);
        break;
        */
    default:
        call_operator(ptr_STACK, token);
        break;
    }
}
