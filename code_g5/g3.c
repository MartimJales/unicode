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
#include "g4.h"
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
    struct elemento r;
    r.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (x.tipo == T_string && y.tipo == T_string)
    {
        if (strcmp(y.data.val_s, x.data.val_s) > 0)
        {
            r.data.val_i = 1;
        }
        else
        {
            r.data.val_i = 0;
        }
        PUSH(ptr_STACK, r);
    }
    else if (x.tipo == T_char && y.tipo == T_char)
    {
        if (x.data.val_c > y.data.val_c)
        {
            r.data.val_i = 1;
        }
        else
        {
            r.data.val_i = 0;
        }
        PUSH(ptr_STACK, r);
    }
    else
    {
        struct elemento val;
        double x_ret = convertToDouble(x);
        double y_ret = convertToDouble(y);
        val.tipo = T_int;
        if (y_ret > x_ret)
            val.data.val_i = 1;
        else
            val.data.val_i = 0;
        PUSH(ptr_STACK, val);
    }
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
    struct elemento r;
    r.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (x.tipo == T_string && y.tipo == T_string)
    {
        // printf("resultado do strcmp %d\n", strcmp(y.data.val_s, x.data.val_s));
        if (strcmp(y.data.val_s, x.data.val_s) < 0)
        {
            r.data.val_i = 1;
        }
        else
        {
            r.data.val_i = 0;
        }
        PUSH(ptr_STACK, r);
    }
    else if (x.tipo == T_char && y.tipo == T_char)
    {
        if (x.data.val_c < y.data.val_c)
        {
            r.data.val_i = 1;
        }
        else
        {
            r.data.val_i = 0;
        }
        PUSH(ptr_STACK, r);
    }
    else
    {
        r.tipo = T_int;
        struct elemento val;
        val.tipo = T_int;
        double x_ret = convertToDouble(x);
        double y_ret = convertToDouble(y);
        if (y_ret < x_ret)
            val.data.val_i = 1;
        else
            val.data.val_i = 0;
        PUSH(ptr_STACK, val);
    }
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
    struct elemento r;
    r.tipo = T_int;
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (x.tipo == T_string && y.tipo == T_string)
    {
        // printf("entrou aqui fofinho \n");
        if (strcmp(x.data.val_s, y.data.val_s) == 0)
            r.data.val_i = 1;
        else
            r.data.val_i = 0;
        PUSH(ptr_STACK, r);
    }
    else if (x.tipo == T_char && y.tipo == T_char)
    {
        if (x.data.val_c == y.data.val_c)
        {
            r.data.val_i = 1;
        }
        else
        {
            r.data.val_i = 0;
        }
        PUSH(ptr_STACK, r);
    }
    else
    {

        struct elemento val;
        val.tipo = T_int;
        double x_ret = convertToDouble(x);
        double y_ret = convertToDouble(y);
        if (y_ret == x_ret)
            val.data.val_i = 1;
        else
            val.data.val_i = 0;
        PUSH(ptr_STACK, val);
    }
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
    if (validade(condition))
        PUSH(ptr_STACK, y);
    else
        PUSH(ptr_STACK, x);
}

int validade(struct elemento val)
{
    switch (val.tipo)
    {
    case T_int:
        return val.data.val_i;
        break;
    case T_long:
        return val.data.val_l;
        break;
    case T_float:
        return val.data.val_f;
        break;
    case T_double:
        return val.data.val_d;
        break;
    case T_string:
        printf("Falta testar strigns no ifthenelse|\n");
        break;
    case T_char:
        printf("Falta testar char no ifthenelse|\n");
        break;
    case T_array:
        if (val.data.val_p->top == -1)
            return 0;
        else
            return 1;
        break;
    default:
        printf("Deu muita merda!!! abort!!!\n");
        return 0;
    }
    return 0;
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
    struct elemento y = POP(ptr_STACK);

    if (x.tipo == T_string && y.tipo == T_string)
    {
        // printf("resultado do strcmp %d\n", strcmp(y.data.val_s, x.data.val_s));
        if (strcmp(y.data.val_s, x.data.val_s) < 0)
        {
            PUSH(ptr_STACK, x);
        }
        else
        {
            PUSH(ptr_STACK, y);
        }
    }
    else if (x.tipo == T_char && y.tipo == T_char)
    {
        if (x.data.val_c < y.data.val_c)
        {
            PUSH(ptr_STACK, y);
        }
        else
        {
            PUSH(ptr_STACK, x);
        }
    }
    else
    {
        double x_ret = convertToDouble(x);
        double y_ret = convertToDouble(y);
        if (y_ret > x_ret)
            PUSH(ptr_STACK, y);
        else
            PUSH(ptr_STACK, x);
    }
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
    struct elemento y = POP(ptr_STACK);

    if (x.tipo == T_string && y.tipo == T_string)
    {
        // printf("resultado do strcmp %d\n", strcmp(y.data.val_s, x.data.val_s));
        if (strcmp(y.data.val_s, x.data.val_s) < 0)
        {
            PUSH(ptr_STACK, y);
        }
        else
        {
            PUSH(ptr_STACK, x);
        }
    }
    else if (x.tipo == T_char && y.tipo == T_char)
    {
        if (x.data.val_c < y.data.val_c)
        {
            PUSH(ptr_STACK, x);
        }
        else
        {
            PUSH(ptr_STACK, y);
        }
    }
    else
    {

        double x_ret = convertToDouble(x);
        double y_ret = convertToDouble(y);
        if (y_ret > x_ret)
            PUSH(ptr_STACK, x);
        else
            PUSH(ptr_STACK, y);
    }
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
        x.data.val_s = NULL;
        sprintf(x.data.val_s, "\n");
        PUSH(ptr_STACK, x);
    }
    else if (strcmp(token, "S") == 0)
    {
        struct elemento x;
        x.tipo = T_string;
        char space[] = " ";
        x.data.val_s = space;
        // x.data.val_s[0] = ' ';
        //x.data.val_s[1] = '\0';
        //char *space = " ";
        //sprintf(x.data.val_s, space);
        PUSH(ptr_STACK, x);
        printf("O menino é um:[%s]\n", ptr_STACK->array[ptr_STACK->top].data.val_s);
    }
    else if (*token == ':')
    {
        int i = *(token + 1) % 65;

        struct elemento new_elem = POP(ptr_STACK); // ptr_STACK->array[(*ptr_STACK).top];

        if (new_elem.tipo == T_array)
        {
            // printf("Caiuu nos arrays!\n");
            struct elemento val;
            val.tipo = T_array;
            struct stack *new_stack = malloc(sizeof(struct stack));
            initStack(new_stack, ptr_STACK->vars);
            val.data.val_p = new_stack;
            new_stack->top = new_elem.data.val_p->top;
            for (int i = 0; i <= new_elem.data.val_p->top; i++)
                new_stack->array[i] = new_elem.data.val_p->array[i];
            ptr_STACK->vars[i].elemento = val;
        }
        else if (new_elem.tipo == T_string)
        {
            // printf("CAIU NAS STRINGS!\n");

            int t = strlen(new_elem.data.val_s);
            // printf("Tamanho da var: %d\n", t);
            char *new_string = malloc((t + 1) * sizeof(char));

            //printf("A menina doida: %s\n", new_elem.data.val_s);
            mystrcat4(new_string, new_elem.data.val_s);
            //printf("A menina desejada: %s!", new_string);

            ptr_STACK->vars[i].elemento.tipo = T_string;
            ptr_STACK->vars[i].elemento.data.val_s = new_string;
        }
        else if (new_elem.tipo == T_block)
        {
            int t = strlen(new_elem.data.val_b);
            // printf("Tamanho da var: %d\n", t);
            char *new_string = malloc((t + 1) * sizeof(char));

            //printf("A menina doida: \"%s\"\n", new_elem.data.val_b);
            //mystrcat4(new_string, "{");
            mystrcat4(new_string, new_elem.data.val_b);
            // mystrcat4(new_string, "}");
            //  printf("A menina desejada: \"%s\"!\n", new_string);

            ptr_STACK->vars[i].elemento.tipo = T_block;
            ptr_STACK->vars[i].elemento.data.val_b = new_string;
        }
        else
        {
            ptr_STACK->vars[i].elemento = new_elem;
        }
        PUSH(ptr_STACK, new_elem);
    }
}
