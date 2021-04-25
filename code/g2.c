/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "g1.h"
#include "g2.h"
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
void dollarfunction(struct stack *ptr_STACK)
{

    struct elemento x = POP(ptr_STACK);
    int i = atoi(x.valor);
    struct elemento y = (*ptr_STACK).array[(*ptr_STACK).top - i];
    PUSH(ptr_STACK, y);
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
    switch (*token)
    {
    case '(':
        decrement(ptr_STACK);
        break;
    case ')':
        increment(ptr_STACK);
        break;
    case '~':
        complement(ptr_STACK);
        break;
    default:
        call_operator(ptr_STACK, token);
        break;
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
    switch (*token)
    {
    case '_':
        double_top(ptr_STACK);
        break;
    case ';':
        POP(ptr_STACK);
        break;
    case '\\':
        switch_top(ptr_STACK);
        break;
    case '@':
        rotate_elem(ptr_STACK);
        break;
    case '$':
        dollarfunction(ptr_STACK);
        break;
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
    switch (*token)
    {
    case 'i':
        convert_i(ptr_STACK);
        break;
    case 'f':
        convert_f(ptr_STACK);
        break;
    case 'c':
        convert_c(ptr_STACK);
        break;
    case 's':
        convert_s(ptr_STACK);
        break;
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
    switch (*token)
    {
    case 'l':
        read_line(ptr_STACK);
        break;
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

void double_top(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, x);
}

void switch_top(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, y);
}

void rotate_elem(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    struct elemento z = POP(ptr_STACK);
    PUSH(ptr_STACK, y);
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, z);
}

void convert_i(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_int;
    PUSH(ptr_STACK, x);
}

void convert_f(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_float;
    PUSH(ptr_STACK, x);
}

void convert_c(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_char;
    PUSH(ptr_STACK, x);
}

void convert_s(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_string;
    PUSH(ptr_STACK, x);
}

void read_line(struct stack *ptr_STACK)
{
    struct elemento x;
    assert(fgets(x.valor, 100, stdin) != NULL);
    x.tipo = T_string;
    PUSH(ptr_STACK, x);
}

void decrement(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", --l);
    PUSH(ptr_STACK, x);
}

void increment(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", ++l);
    PUSH(ptr_STACK, x);
}
void complement(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", ~l);
    PUSH(ptr_STACK, x);
}

void call_operator(struct stack *ptr_STACK, char *token)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    PUSH(ptr_STACK, operador(x, y, token));
}