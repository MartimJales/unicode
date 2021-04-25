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
#include "g2.h"
#include "g3.h"
#include <assert.h>

/**
 * \brief Função parse do programa
 * 
 * Inicia-se um apontador de caracteres (delimitadores).
 * 
 * Posteriormente, através de um ciclo, inicia-se uma nova variável (um apontador de carateres (token)),
 * com a condição de paragem quando esse token for NULL. 
 * A cada iteração o token é atualizado.
 * 
 * Através de condições if verifica-se o valor a devolver ao topo da pilha, 
 * se à partida, a string contiver apenas números é imediatamente devolvida, 
 * caso contrário, através da função 'strcmp' verificar-se-à que valor/es 
 * terão que se devolver.
 * 
 * @param line Linha, onde a função parse atuará, e que já foi lida.
 */
void parse(char *line)
{
    struct stack STACK;
    struct stack *ptr_STACK = &STACK;
    initStack(ptr_STACK);

    char *delimitadores = " \t \n";
    for (char *token = strtok(line, delimitadores); token != NULL; token = strtok(NULL, delimitadores))
    {
        //Coloquei o resto a iniciar a abc porcausa das flags
        // mas temos de ver se isto não provoca merda

        char *resto = "abc";
        int val_tipo;

        check_type(&resto, &token, &val_tipo);

        if (strlen(resto) == 0)
        {
            //token_push(token, val_tipo, ptr_STACK);
        }
        else
        {
            go_filter(ptr_STACK, token);
        }
    }
    PRINT_STACK(ptr_STACK);
}

/**
 * \brief Função check_type do programa
 * 
 * recebe um token, um apontador para o resto da função e outro apontador para o tipo desse token.
 * Irá verificar o tipo correspondente ao token e atualizar a stack com o elemento correspondente.
 *
 * @param resto
 * @param token
 * @param val_tipo 
 */
void check_type(char **resto, char **token, int *val_tipo)
{
    char *p = strstr(*token, ".");
    if (p)
    {
        strtod(*token, resto);
        *val_tipo = T_double;
    }
    else
    {
        strtol(*token, resto, 10);
        *val_tipo = T_long;
    }
}

/**
 * \brief Função go_filter
 * 
 * é uma função auxiliar que recebe um token e um apontador para a Stack e verifica 
 * para que função auxiliar é que a operação é suposto continuar consoante 
 * o resultado da função filter. 
 * 
 * @param ptr_STACK
 * @param token
 */
/*
void go_filter(struct stack *ptr_STACK, char *token)
{
    switch (filter(token))
    {
    case 1:
        maths(ptr_STACK, token);
        break;
    case 2:
        manstack(ptr_STACK, token);
        break;
    case 3:
        conversion(ptr_STACK, token);
        break;
    case 4:
        inoutput(ptr_STACK, token);
        break;
    case 5:
        logic(ptr_STACK, token);
        break;
    case 6:
        variables1(ptr_STACK, token);
        break;
    case 7:
        variables2(ptr_STACK, token);
        break;
    default:
        //Esta é referente aos próximos guiões e ainda não estão definidas (case 7)
        break;
    }
}
*/
/**
 * \brief Função push_token
 * 
 * é uma função auxiliar nos casos em que o token representa um elemento
 * e não temos que fazer nenhuma operação ela coloca na Stack o mesmo.
 * 
 * @param val_tipo (Tipo do elemento)
 * @param token (Token que representa o elemento)
 * @param ptr_STACK (Ponteiro para a Stack)
 * 
 */
/*void token_push(char *token, int val_tipo, struct stack *ptr_STACK)
{
    struct elemento val;
    val.tipo = val_tipo;

    sprintf(val.valor, "%s", token);
    PUSH(ptr_STACK, val);
}*/

/**
 * \brief Função convertToDouble
 * 
 * é uma função auxiliar que recebe um elemento e converte-o para Double
 * 
 * @param x 
 * 
 * @returns double, representado pela variável ret.
 */
float convertToDouble(struct elemento x)
{
    double ret;

    ret = 0.0;
    if (x.tipo == T_int || x.tipo == T_long || x.tipo == T_double || x.tipo == T_float)
    {
        ret = strtof(x.valor, NULL);
    }
    return ret;
}

/**
 * \brief Função filter do programa
 * 
 * recebe um token e devolve o número correspondente ao conjunto de operações onde o mesmo pertence.
 *
 * 
 * @param token 
 * 
 * @returns Um inteiro 
 */
int filter(char *token)
{
    char *maths = "+-/*%#&|^()~";
    char *manstack = "_;\\@$";
    char *conversion = "ifcs";
    char *logic = "=><!?e";
    char *io = "l";
    char *variables1 = "ABCDEFGHIJKLMOPQRTUVWXYZ";
    char *variables2 = "NS:";

    while (*maths)
    {
        if (*token == *maths)
        {
            return 1;
        }
        maths++;
    }
    while (*manstack)
    {
        if (*token == *manstack)
        {
            return 2;
        }
        manstack++;
    }
    while (*conversion)
    {
        if (*token == *conversion)
        {
            return 3;
        }
        conversion++;
    }
    while (*io)
    {
        if (*token == *io)
        {
            return 4;
        }
        io++;
    }
    while (*logic)
    {
        if (*token == *logic)
            return 5;
        logic++;
    }
    while (*variables1)
    {
        if (*token == *variables1)
        {
            return 6;
        }
        variables1++;
    }
    while (*variables2)
    {
        if (*token == *variables2)
        {
            return 7;
        }
        variables2++;
    }
    return 0;
}
