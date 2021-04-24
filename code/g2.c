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

/**
 * \brief Função dollarfunction do programa
 * 
 * recebe como parâmetros um apontador para a struct stack e uma variável i
 * e devolve o valor apontado para esse índice.
 * 
 * @param stack
 * @param i (índice)
 * 
 * @returns Um elemento da Stack.
 */
struct elemento dollarfunction(struct stack *stack, int i)
{
    return (*stack).array[(*stack).top - i];
}

/**
 * \brief Função maths do programa
 * 
 * efetua o cálculo das operações aritméticas.
 * 
 * @param ptr_STACK
 * @param token
 */
void maths(struct stack *ptr_STACK, char *token)
{
    if (*token == '(')
    {
        struct elemento x = POP(ptr_STACK);
        long l = atol(x.valor);
        sprintf(x.valor, "%ld", --l);
        PUSH(ptr_STACK, x);
    }
    else if (*token == ')')
    {
        struct elemento x = POP(ptr_STACK);
        long l = atol(x.valor);
        sprintf(x.valor, "%ld", ++l);
        PUSH(ptr_STACK, x);
    }
    else if (*token == '~')
    {
        struct elemento x = POP(ptr_STACK);
        long l = atol(x.valor);
        sprintf(x.valor, "%ld", ~l);
        PUSH(ptr_STACK, x);
    }
    else
    {
        struct elemento x = POP(ptr_STACK);
        struct elemento y = POP(ptr_STACK);
        PUSH(ptr_STACK, operador(x, y, token));
    }
}

/**
 * \brief Função manstack do programa
 * 
 * efetua o cálculo das operações para manipulação da Stack.
 * 
 * @param ptr_STACK
 * @param token
 */
void manstack(struct stack *ptr_STACK, char *token)
{
    if (strcmp(token, "_") == 0)
    {
        struct elemento x = POP(ptr_STACK);
        PUSH(ptr_STACK, x);
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, ";") == 0)
    {
        POP(ptr_STACK);
    }
    else if (strcmp(token, "\\") == 0)
    {
        struct elemento x = POP(ptr_STACK);
        struct elemento y = POP(ptr_STACK);
        PUSH(ptr_STACK, x);
        PUSH(ptr_STACK, y);
    }
    else if (strcmp(token, "@") == 0)
    {
        struct elemento x = POP(ptr_STACK);
        struct elemento y = POP(ptr_STACK);
        struct elemento z = POP(ptr_STACK);
        PUSH(ptr_STACK, y);
        PUSH(ptr_STACK, x);
        PUSH(ptr_STACK, z);
    }
    else if (strcmp(token, "$") == 0)
    {
        struct elemento x = POP(ptr_STACK);
        int i = atoi(x.valor);
        struct elemento y = dollarfunction(ptr_STACK, i);
        PUSH(ptr_STACK, y);
    }
}

/**
 * \brief Função conversion do programa
 * 
 *  efetua a conversão dos elementos da Stack para um dado tipo.
 * 
 * @param ptr_STACK
 * @param token
 */
void conversion(struct stack *ptr_STACK, char *token)
{
    if (strcmp(token, "i") == 0) //converter para int
    {
        struct elemento x = POP(ptr_STACK);
        x.tipo = T_int;
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "f") == 0) //converter para float
    {
        struct elemento x = POP(ptr_STACK);
        x.tipo = T_float;
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "c") == 0) //converter para char
    {
        struct elemento x = POP(ptr_STACK);
        x.tipo = T_char;
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "s") == 0) //converter para
    {
        struct elemento x = POP(ptr_STACK);
        x.tipo = T_string;
        PUSH(ptr_STACK, x);
    }
}

/**
 * \brief Função inoutput do programa
 * 
 * é responsável pelas ações de in/output.
 * 
 * @param ptr_STACK
 * @param token
 */
void inoutput(struct stack *ptr_STACK, char *token)
{
    if (strcmp(token, "l") == 0) //ler linha
    {
        struct elemento x;
        assert(fgets(x.valor, 100, stdin) != NULL);
        x.tipo = T_string;
        PUSH(ptr_STACK, x);
    }
}

/**
 * \brief Função logic do programa
 * 
 * é responsável pelas ações de lógica e condições.
 * 
 * @param ptr_STACK
 * @param token
 */
void logic(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '>':
        greater(ptr_STACK);
        break;
    case '<':
        smaller(ptr_STACK);
        break;
    case '=':
        equal(ptr_STACK);
        break;
    case '!':
        no(ptr_STACK);
        break;
    case '?':
        ifthenelse(ptr_STACK);
        break;
    default:
        efunction(ptr_STACK, (token + 1));
        break;
    }
}