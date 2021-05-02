/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "g1.h"
#include "g3.h"
#include <assert.h>

/**
 * \brief Função greater do programa
 * 
 * é responsável por devolver valor logico 0 caso o 2º elemento dado pela stack seja menor  que o primeiro ou 1 caso contrário.
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void greater(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (y_ret > x_ret)
        val.data.val_i = 1;
    else
        val.data.val_i = 0;
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função smaller do programa
 * 
 * é responsável por devolver valor logico 1 caso o 2º elemento dado pela stack seja menor  que o primeiro ou 0 caso contrário.
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void smaller(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (y_ret < x_ret)
        val.data.val_i = 1;
    else
        val.data.val_i = 0;
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função equal do programa
 * 
 * é responsável por atribuir valor logico 1 ou 0 se a igualdade se verificar ou não,respetivamente
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void equal(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (y_ret == x_ret)
        val.data.val_i = 1;
    else
        val.data.val_i = 0;
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função no do programa
 * 
 * é responsável por atribuir o valor lógico contrário à variável dada pelo topo da stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void no(struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    //printf("Esta menina deu: %f\n", x_ret);
    if (x_ret)
        val.data.val_i = 0;
    else
        val.data.val_i = 1;
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função ifthenelse do programa
 * 
 * é responsável por testar se o valor lógico do 3º elemento dado pela stack é verdadeiro,se sim devolve o 2º elemento dado pela stack
 * caso contrário devolve o primeiro
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void ifthenelse(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    struct elemento condition = POP(ptr_STACK);
    if (condition.data.val_i)
        PUSH(ptr_STACK, y);
    else
        PUSH(ptr_STACK, x);
}

/**
 * \brief Função efunction do programa
 * 
 * é responsável por separar os operadores q têm "e<","e>","e|","e" ou "e&"
 * 
 * @param ptr_STACK (apontador para a stack)
 * @param token (apontador para o token que é resultado da função parser)
 */
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

/**
 * \brief Função ebigger  do programa
 * 
 * é responsável pela operação "e>" que devolve o maior dos dois valores
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void ebigger(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (y_ret > x_ret)
        PUSH(ptr_STACK, y);
    else
        PUSH(ptr_STACK, x);
}

/**
 * \brief Função esmaller  do programa
 * 
 * é responsável pela operação "e<" que devolve o menor dos dois valores
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void esmaller(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (y_ret > x_ret)
        PUSH(ptr_STACK, x);
    else
        PUSH(ptr_STACK, y);
}

/**
 * \brief Função eshortcut  do programa
 * 
 * é responsável pela operação "e&" que devolve o maior dos dois valores caso ambos sejam maiores que 0 ,caso algum deles seja 0 ,devolve 0. 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void eshortcut(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);

    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (!(y.data.val_i))
    {
        PUSH(ptr_STACK, y);
    }
    else if (!(x.data.val_i))
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

/**
 * \brief Função orshortcut  do programa
 * 
 * é responsável pela operação "e|" que devolve o primeiro valor que aparecer caso ambos sejam diferentes de 0
 * caso algum deles seja 0 devolve o outro 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void orshortcut(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
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

/**
 * \brief Função epequeno do programa
 * 
 * é responsável pela operação "e" que devolve o menor caso ambos sejam diferentes de 0.
 * caso algum deles seja 0 devolve o outro 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void epequeno(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    double x_ret = convertToDouble(x);
    struct elemento y = POP(ptr_STACK);
    double y_ret = convertToDouble(y);
    if (!(y.data.val_i))
    {
        PUSH(ptr_STACK, x);
    }
    else if (!(x.data.val_i))
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

/**
 * \brief Função variables1  do programa
 * 
 * dado uma variável ,coloca essa variável na stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void variables1(struct stack *ptr_STACK, char *token)
{
    int i = *token % 65;
    PUSH(ptr_STACK, (*ptr_STACK).vars[i].elemento);
}

/**
 * \brief Função variables2  do programa
 * 
 * caso o input seja N ou S realiza as devidas ações de "\n" ou " " , ou caso seja ":" altera o conteudo da variável
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void variables2(struct stack *ptr_STACK, char *token)
{
    if (strcmp(token, "N") == 0)
    {
        struct elemento x;
        x.tipo = T_string;
        sprintf(x.data.val_s, "\n");
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "S") == 0)
    {
        struct elemento x;
        x.tipo = T_string;
        sprintf(x.data.val_s, " ");
        PUSH(ptr_STACK, x);
        //printf("O menino é um:[%s]\n", ptr_STACK->array[ptr_STACK->top].data.val_s);
    }
    else if (*token == ':')
    {
        int i = *(token + 1) % 65;
        (*ptr_STACK).vars[i].elemento = ptr_STACK->array[(*ptr_STACK).top];
    }
}
