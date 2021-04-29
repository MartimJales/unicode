/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
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

/**
 * \brief Função check_type do programa
 * 
 * recebe um token, um apontador para o resto_num da função e outro apontador para o tipo desse token.
 * Irá verificar o tipo correspondente ao token e atualizar a stack com o elemento correspondente.
 *
 * @param resto_num
 * @param token
 * @param val_tipo 
 */
void check_type(char **resto_num, char **token, int *val_tipo)
{
    char *p = strstr(*token, ".");
    if (p)
    {
        strtod(*token, resto_num);
    }
    else
    {
        strtol(*token, resto_num, 10);
        *val_tipo = T_long;
    }
}

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
int filter(char *token, int array)
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

/**
 * \brief Função put_token do programa
 *  int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    int y_tipo = (*ptr_STACK).array[(*ptr_STACK).top - 1].tipo;
    if (x_tipo = T_array || y_tipo == T_array)
        return 1;
    else
 * recebe um token, um apontador para o resto_num da função e outro apontador para a stack.
 * Irá colocar o token respetivo a um elemento na stack.
 *
 * @param resto_num
 * @param token
 * @param val_tipo 
 */
void put_token(struct stack *ptr_STACK, int val_tipo, char *token)
{
    struct elemento val;
    val.tipo = val_tipo;

    sprintf(val.valor, "%s", token);
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função go_filter do programa
 * 
 * verifica o nosso token e seleciona a função auxiliar correspondente à operação
 * desejada.
 *
 * @param token
 * @param val_tipo 
 */
void go_filter(struct stack *ptr_STACK, char *token)
{
    switch (filter(token, check_array(ptr_STACK, token)))
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

void go_filter_array(struct stack *ptr_STACK, char *token)
{
    if (*token == '+')
    {
        check_soma_array(ptr_STACK, token);
    }
    else
        check_all_array(ptr_STACK, token);
}
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
    char *token;
    char *resto;

    char *delimitadores = " \t \n";
    for (token = get_token(delimitadores, line, &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        //Coloquei o resto_num a iniciar a abc porcausa das flags
        // mas temos de ver se isto não provoca merda

        char *resto_num = "abc";
        int val_tipo;

        check_type(&resto_num, &token, &val_tipo);

        if (strlen(resto_num) == 0)
            put_token(ptr_STACK, val_tipo, token);
        else if (*token == '[')
        {
            printf("ARRAY!\n");
            pinta_array(&token, token);
            put_array(ptr_STACK, token);
        }
        else if (check_array(ptr_STACK, token))
            go_filter_array(ptr_STACK, token);
        else
            go_filter(ptr_STACK, token);

        printf("Token atual: %s!\n", token);
    }
    PRINT_STACK(ptr_STACK);
}

void check_soma_array(struct stack *ptr_STACK, char *token)
{

    int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    int y_tipo = (*ptr_STACK).array[(*ptr_STACK).top - 1].tipo;

    if (x_tipo == T_array || y_tipo == T_array)
    {
        concatenarray(ptr_STACK);
    }
    else
    {
        struct elemento x = POP(ptr_STACK);
        struct elemento y = POP(ptr_STACK);
        struct elemento val = operador(x, y, token);
        PUSH(ptr_STACK, val);
    }
}

void check_all_array(struct stack *ptr_STACK, char *token)
{
    int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    if (x_tipo = T_array)
    {
        manarray(ptr_STACK, token);
    }
    else
        go_filter(ptr_STACK, token);
}

void put_array(struct stack *ptr_STACK, char *token)
{
    struct elemento val;
    val.tipo = T_array;

    sprintf(val.valor, "%s", token);
    PUSH(ptr_STACK, val);
}

void pinta_array(char **pointer, char *line)
{
    char *delimitadores = " \t\n";
    char *token;
    char *resto;

    char copi[100];
    int j = 0, i = 2;
    while (line[i + 2] != '\0')
    {
        copi[j] = line[i];
        i++;
        j++;
    }
    copi[j] = '\0';
    strcpy(line, copi);
}

int check_array(struct stack *ptr_STACK, char *token)
{
    char *arrays = "+~<>()*=,#/SN";
    while (*arrays)
    {
        if (*token == *arrays)
        {
            return 1;
        }
        arrays++;
    }
    return 0;
}

// FUction get_delimited

int isDelim(char c, char *delim)
{
    int bRet = 0;

    for (int i = 0; delim[i]; i++)
    {
        if (delim[i] == c)
            bRet = 1;
    }
    return bRet;
}

char *get_token(char *delim, char *line, char **rest)
{
    char *pRet = NULL;
    int i, bTratado = 0;
    int iToken = 0;

    //printf("get_token('%s' ###  %s  ###)\n",delim,line);

    //printf("-- %c %d --\n",line[0],isDelim(line[0],delim));

    for (i = 0; line[i] && isDelim(line[i], delim) == 0 && bTratado == 0; i++)
    {
        if (line[i] == '[')
        {
            int nParentesis = 1;
            int j;

            for (j = 1; nParentesis > 0 && line[i + j]; j++)
            {
                if (line[i + j] == ']')
                    nParentesis--;
                if (line[i + j] == '[')
                    nParentesis++;
            }
            if (nParentesis > 0)
            {
                printf("Falta ]");
            }
            else
            {
                line[i + j] = 0;
                *rest = line + i + j + 1;
                bTratado = 1;
            }
        }
        if (line[i] == '"')
        {
            int nAspas = 1;
            int j;

            for (j = 1; nAspas > 0 && line[i + j]; j++)
            {
                if (line[i + j] == '"')
                    nAspas--;
            }
            if (nAspas > 0)
            {
                printf("Falta Fechar Aspas");
            }
            else
            {
                line[i + j] = 0;
                *rest = line + i + j + 1;
                bTratado = 1;
            }
        }
    }

    if (bTratado == 0)
    {
        if (isDelim(line[i], delim))
        {
            line[i] = 0;
            *rest = line + i + 1;
        }
        else
        {
            *rest = line + i;
        }
    }
    return line;
}