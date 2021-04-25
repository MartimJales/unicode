/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "g1.h"
#include <assert.h>

/**
 * \brief Função operador
 * 
 * É uma função auxiliar que recebe dois elementos e um apontador para o operando 
 * e calcula o resultado de ambos de acordo com o operando recebido.
 * 
 * É, de seguida, definida uma variável cuja constante associada à componente tipo será a mesma que a dos elementos recebidos
 * quando estes têm o mesmo tipo, caso contrário, é declarada como tendo um tipo constante T_int.
 * Posteriormente, de acordo com a constante da sua componente tipo a componente valor será igual ao valor da variável dres
 * 
 * @param x 
 * @param y
 * @param op (operando)
 * 
 * @returns Um struct elemento val
 */
struct elemento operador(struct elemento x, struct elemento y, char *op)
{
    float dx, dy, dres;

    dx = convertToDouble(x);
    dy = convertToDouble(y);
    dres = 0.0;
    switch (*op)
    {
    case '*':
        dres = dx * dy;
        break;
    case '+':
        dres = dx + dy;
        break;
    case '-':
        dres = dy - dx;
        break;
    case '/':
        dres = dy / dx;
        break;
    case '#':
        dres = pow(dy, dx);
        break;
    default:
        dres = operator_long(dx, dy, op);
        break;
    }

    return secondoperador(x, y, dres);
}

/**
 * \brief Função secondoperador
 * 
 * É uma função auxiliar que recebe dois elementos e o resultado da operação efetuada 
 * pela função anterior do operador.
 * 
 * É definida uma variável cuja constante associada à componente tipo será a mesma que a dos elementos recebidos
 * quando estes têm o mesmo tipo, caso contrário, é declarada como tendo um tipo constante T_int.
 * Posteriormente, de acordo com a constante da sua componente tipo a componente valor será igual ao valor da variável dres
 * 
 * @param x 
 * @param y
 * @param dres (resultado da operação em operdador)
 * 
 * @returns Um struct elemento val
 */
struct elemento secondoperador(struct elemento x, struct elemento y, float dres)
{
    struct elemento val;

    if (x.tipo == T_double || y.tipo == T_double)
    {
        val.tipo = T_double;
        sprintf(val.valor, "%.16g", (double)dres);
    }
    else if (x.tipo == T_float || y.tipo == T_float)
    {
        val.tipo = T_float;
        sprintf(val.valor, "%.16g", (float)dres);
    }
    else if (x.tipo == T_long || y.tipo == T_long)
    {
        val.tipo = T_long;
        sprintf(val.valor, "%ld", (long)dres);
    }
    else
    {
        val.tipo = T_int;
        sprintf(val.valor, "%d", (int)dres);
    }
    return val;
}

double operator_long(double dx, double dy, char *op)
{
    double dres = 0.0;
    switch (*op)
    {
    case '%':
        dres = (long)dy % (long)dx;
        break;

    case '&':
        dres = (long)dx & (long)dy;
        break;
    case '|':
        dres = (long)dx | (long)dy;
        break;
    case '^':
        dres = (long)dx ^ (long)dy;
        break;
    default:
        printf("Se cair aqui deu erro.");
        break;
    }
    return dres;
}