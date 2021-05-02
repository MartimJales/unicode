
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "parse.h"
#include "g1.h"
#include "g3.h"
#include "g3.h"
#include "g4.h"
#include <assert.h>

//funciona 100%
/*
void concatenarray(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_array;
    struct elemento y = POP(ptr_STACK);

    y.tipo = T_array;
    y.data.val_p = , "%s", strcat(y.valor, x.valor));
    PUSH(ptr_STACK, y);
}*/
/*
void parse_array(char *line, struct stack *ptr_STACK)
{
    char *token;
    char *resto;

    char *delimitadores = " \t \n";
    for (token = get_token(delimitadores, cleanLim(line), &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        char *resto_num = "abc";
        int val_tipo;

        check_type(&resto_num, &token, &val_tipo);

        if (strlen(resto_num) == 0)
            put_token_array(, val_tipo, token);
        else if (*token == '[')
        {
            printf("ARRAY!\n");
            struct elemento val;
            pinta_array(&token, token);
            printf("TOKEN: %s\n", token);
            //val.tipo = T_array;
            //sprintf(val.valor, "%s", token);
        }
        /*else if (check_array(ptr_STACK, token))
            go_filter_array(ptr_STACK, token);
        else
            go_filter(ptr_STACK, token);
        
printf("Token atual da parse array: %s!\n", token);
}
}

void empurraarray(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_array;
    parse_array(x.valor, ptr_STACK);
}

void repetearray(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    int n = strtol(x.valor, NULL, 10);
    struct elemento y = POP(ptr_STACK);
    for (n; n > 0; n--)
    {
        PUSH(ptr_STACK, y);
    }
}

void tamanho_range(struct stack *ptr_STACK)
{

    char *token;
    char *resto;
    char *delimitadores = " \t \n";
    struct elemento line = POP(ptr_STACK);
    long n = 0;
    //printf("tipo line = %d", line.tipo);
    printf("line = %s\n", line.valor);
    for (token = get_token(delimitadores, cleanLim(line.valor), &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        printf("n = %ld\n", n);
        n++;
    }
    struct elemento val;
    val.tipo = T_long;
    sprintf(val.valor, "%ld", n);
    PUSH(ptr_STACK, val);
}

void buscavalindice(struct stack *ptr_STACK)
{
    int i = 0;
    char *token;
    char *resto;
    char *resto_num;
    char *delimitadores = " \t \n";
    struct elemento x = POP(ptr_STACK);
    int n = strtol(x.valor, NULL, 10);

    struct elemento line = POP(ptr_STACK);
    int val_tipo;

    for (token = get_token(delimitadores, line.valor, &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        if (i == n)
        {
            struct elemento val;
            check_type(&resto_num, &token, &val_tipo);

            if (strlen(resto_num) == 0)
                put_token(ptr_STACK, val_tipo, token);
            else if (*token == '[')
            {
                printf("ARRAY!\n");
                pinta_array(&token, token);
                struct elemento val;
                val.tipo = T_array;
                sprintf(val.valor, "%s", token);
            }
            PUSH(ptr_STACK, val);
            break;
        }
        i++;
    }
}

void manarray(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '~':
        empurraarray(ptr_STACK);
        break;

    case '*':
        repetearray(ptr_STACK);
        break;

        //falta fazer o caso (5 ,)

    case ',':
        tamanho_range(ptr_STACK);
        break;

    case '=':
        buscavalindice(ptr_STACK);
        break;
    case '<':
        buscaantes(ptr_STACK);
        break;
    case '>':
        buscadepois(ptr_STACK);
        break;
    case '(':
        removeantes(ptr_STACK);
        break;
    case ')':
        removedepois(ptr_STACK);
        break;
    default:
        call_operator(ptr_STACK, token);
        break;
    }
}
*/