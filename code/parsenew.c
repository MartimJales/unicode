/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"
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
 * 
 * @returns Não devolve nada (void).
 */
void parse(char *line)
{
    // Top index
    int top = -1;
    int *top_ptr = &top;

    // Stack;
    struct elemento stack[100];
    struct elemento *stack_ptr;

    char *delimitadores = " \t \n";
    for (char *token = strtok(line, delimitadores); token != NULL; token = strtok(NULL, delimitadores))
    {
        char *resto;
        int val_tipo;

        // Mudnça do apontador da stack em cada iteração
        stack_ptr = &stack[top];

        //  printf("ANTES token=%s resto=%s \n", token,resto);
        char *p = strstr(token, ".");

        if (p)
        {
            strtod(token, &resto);
            val_tipo = T_double;
        }
        else
        {
            strtol(token, &resto, 10);
            val_tipo = T_long;
        }
        // printf("DEPOIS token=%s resto=%s \n", token,resto);
        if (strlen(resto) == 0)
        {
            struct elemento val;
            val.tipo = val_tipo;

            sprintf(val.valor, "%s", token);
            printf("Before test! Top -> %d\n", top);
            for (int i = 0; i < 10; i++)
            {
                printf("Array[%d] -> %s\n", i, stack[i].valor);
            }
            PUSH(top_ptr, stack_ptr, val);
            printf("After test! Top -> %d\n", top);
            for (int i = 0; i < 10; i++)
            {
                printf("Array[%d] -> %s\n", i, stack[i].valor);
            }
            printf("\n>>>>>Done<<<<<<<\n");
        }
        else if (strcmp(token, "l") == 0) //ler linha
        {
            struct elemento x;
            convToLong(&x);
        }
        else if (strcmp(token, "i") == 0) //converter para int
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            convToInt(&x);
        }
        else if (strcmp(token, "f") == 0) //converter para float
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            convtoFloat(&x);
        }
        else if (strcmp(token, "+") == 0)
        {
            printf("Before test! Top -> %d\n", top);
            struct elemento x = POP(top_ptr, stack_ptr);
            printf("After test! Top -> %d  | X -> %s\n", top, x.valor);

            printf("\n>>>>>Done<<<<<<<\n");
            //struct elemento y = POP();
            //PUSH(operador(x, y, '+'));
        }
        else if (strcmp(token, "*") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '*'));
        }
        else if (strcmp(token, "/") == 0)
        {
            struct elemento y = POP(top_ptr, stack_ptr);
            struct elemento x = POP(top_ptr, stack_ptr);

            PUSH(operador(x, y, '/'));
        }
        else if (strcmp(token, "-") == 0)
        {
            struct elemento y = POP(top_ptr, stack_ptr);
            struct elemento x = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '-'));
        }
        else if (strcmp(token, ")") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            increment(&x);
        }
        else if (strcmp(token, "(") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            decrement(&x);
        }
        else if (strcmp(token, "%") == 0)
        {
            struct elemento y = POP(top_ptr, stack_ptr);
            struct elemento x = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '%'));
        }
        else if (strcmp(token, "#") == 0)
        {
            struct elemento y = POP(top_ptr, stack_ptr);
            struct elemento x = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '#'));
        }
        else if (strcmp(token, "&") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '&'));
        }
        else if (strcmp(token, "|") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '|'));
        }
        else if (strcmp(token, "^") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            PUSH(operador(x, y, '^'));
        }
        else if (strcmp(token, "~") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            complement(&x);
        }
        else if (strcmp(token, "_") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            cpyStackTop(&x);
        }
        else if (strcmp(token, ";") == 0)
        {
            POP(top_ptr, stack_ptr);
        }
        else if (strcmp(token, "\\") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            swapStackTop(&x, &y);
        }
        else if (strcmp(token, "c") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            convToChar(&x);
        }
        else if (strcmp(token, "@") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            struct elemento y = POP(top_ptr, stack_ptr);
            struct elemento z = POP(top_ptr, stack_ptr);
            rot_three_elem_StackTop(&x, &y, &z);
        }
        else if (strcmp(token, "$") == 0)
        {
            struct elemento x = POP(top_ptr, stack_ptr);
            int i = atoi(x.valor);
            struct elemento y = stack[top - i];
            cpy_N_elem_of_Stack_ToTop(&y);
        }
        // printf("STACK:");
        // PRINT_STACK_DEBUG();
    }

    // printf("STACK FINAL:");
    //PRINT_STACK();
}

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um inteiro long, cujo resultado é o valor no topo da Stack.
 */
struct elemento POP(int *top, struct elemento *stack)
{
    *top = *top - 1;
    printf("Elemento que é suposto dar POP -> %s!\n", (*stack).valor);
    struct elemento val = *stack;
    return val;
}
/**
 * \brief Função PUSH do programa
 * 
 * Função que vai à Stack adicionar uma célula acima da última.
 * 
 * @param long val_i 
 * 
 * @returns Não devolve nada (void).
 */
void
PUSH(int *top, struct elemento *stack, struct elemento val_i)
{
    *top = *top + 1;
    *(stack + 1) = val_i;
}

/**
 * \brief Função PRINT_STACK do programa
 * 
 * Inicia-se um ciclo for, onde uma variável é incializada também,
 * a condição de paragem ocorre se a variável é maior
 * que o topo da da Stack, a cada iteração incrementa-se a variável.
 * 
 * É imprimido o valor da Stack no índice da variável, de acordo
 * com o seu valor a cada iteração.
 * 
 * @returns Não devolve nada (void).
 */
/*
void PRINT_STACK()
{
    char *resto;
    for (int i = 0; i <= top; i++)
    {

        if (stack[i].tipo == T_int || stack[i].tipo == T_long)
            printf("%ld", strtol(stack[i].valor, &resto, 10));
        else if (stack[i].tipo == T_float || stack[i].tipo == T_double)
            printf("%.6g", strtod(stack[i].valor, &resto));
        else if (stack[i].tipo == T_char)
        {
            char str[2];
            str[0] = atoi(stack[i].valor);
            str[1] = 0;
            printf("%s", str);
        }
        else
            printf("%s", stack[i].valor);
    }
    printf("\n");
}

void PRINT_STACK_DEBUG()
{
    for (int i = 0; i <= top; i++)
    {
        printf("%d %s ", stack[i].tipo, stack[i].valor);
    }
    printf("\n");
}
*/
float convertToDouble(struct elemento x)
{
    double ret;

    ret = 0.0;
    if (x.tipo == T_int || x.tipo == T_long || x.tipo == T_double || x.tipo == T_float)
    {
        //no campo valor temos algo como "200", "323.2" ..
        ret = strtof(x.valor, NULL);
    }
    return ret;
}

struct elemento operador(struct elemento x, struct elemento y, char op)
{
    float dx, dy, dres;

    dx = convertToDouble(x);
    dy = convertToDouble(y);
    dres = 0.0;
    if (op == '*')
    {
        dres = dx * dy;
    }
    else if (op == '+')
    {
        dres = dx + dy;
    }
    else if (op == '-')
    {
        dres = dx - dy;
    }
    else if (op == '/')
    {
        dres = dx / dy;
    }
    else if (op == '#')
    {
        dres = pow(dx, dy);
    }
    else if (op == '%')
    {
        dres = (long)dx % (long)dy;
    }
    else if (op == '&')
    {
        dres = (long)dx & (long)dy;
    }
    else if (op == '|')
    {
        dres = (long)dx | (long)dy;
    }
    else if (op == '^')
    {
        dres = (long)dx ^ (long)dy;
    }
    struct elemento val;

    if (x.tipo == T_double || y.tipo == T_double)
        val.tipo = T_double;
    else if (x.tipo == T_float || y.tipo == T_float)
        val.tipo = T_float;
    else if (x.tipo == T_long || y.tipo == T_long)
        val.tipo = T_long;
    else
        val.tipo = T_int;

    if (val.tipo == T_int)
        sprintf(val.valor, "%d", (int)dres);
    else if (val.tipo == T_long)
        sprintf(val.valor, "%ld", (long)dres);
    else if (val.tipo == T_float)
        sprintf(val.valor, "%.16g", (float)dres);
    else if (val.tipo == T_double)
        sprintf(val.valor, "%.16g", (double)dres);

    return val;
}

// "l" ---------------------------------------

/**
 * \brief Função convToLong
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num long. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToLong(struct elemento *x)
{
    assert(fgets(x.valor, 100, stdin) != NULL);
    x.tipo = T_string;
    PUSH(x);
}

//"i" -----------------------------------------

/**
 * \brief Função convToInt
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num integer. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToInt(struct elemento *x)
{
    x.tipo = T_int;
    PUSH(x);
}

//"f" --------------------------------------------

/**
 * \brief Função convToFloat
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num float. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToFloat(struct elemento *x)
{
    x.tipo = T_float;
    PUSH(x);
}

//")" ----------------------------------------------

/**
 * \brief Função increment
 * 
 * É uma função auxiliar que incrementa o elemento que recebe como parâmetro. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento increment(struct elemento *x)
{
    //printf("antes %s \n" ,x.valor);
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", ++l);

    // printf("depois %s \n" ,x.valor);
    PUSH(x);
}

//"(" -----------------------------------------------

/**
 * \brief Função decrement
 * 
 * É uma função auxiliar que decrementa o elemento que recebe como parâmetro. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento decrement(struct elemento *x)
{
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", --l);
    PUSH(x);
}

//"~" -----------------------------------------------

struct elemento complement(struct elemento *x)
{
    long l = atol(x.valor);
    l = ~l;
    sprintf(x.valor, "%ld", l);
    PUSH(x);
}

// "_" ------------------------------------------------

/**
 * \brief Função cpyStackTop
 * 
 * É uma função auxiliar que copia para o topo da stack o elemento que já tem no topo da stack.
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento cpyStackTop(struct elemento *x)
{
    PUSH(x);
    PUSH(x);
}

//";"------------------------------------------------

/**
 * \brief Função rmStackTop
 * 
 * É uma função auxiliar que retira da stack o elemento do topo.
 * 
 * @returns struct elemento.
 */
struct elemento rmStackTop()
{
    POP();
}

//"\\" ---------------------------------------------

/**
 * \brief Função swapStackTop
 * 
 * É uma função auxiliar que troca de posições na stack os dois elementos do topo.
 * 
 * @param x 
 * @param y
 * 
 * 
 * @returns struct elemento.
 */
struct elemento swapStackTop(struct elemento *x, struct elemento *y)
{
    PUSH(x);
    PUSH(y);
}

//"c" -------------------------------------------

/**
 * \brief Função convToChar
 * 
 * É uma função auxiliar que converte para char o elemento do topo da stack.
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToChar(struct elemento *x)
{
    x.tipo = T_char;
    PUSH(x);
}

//"@" --------------------------------------------

/**
 * \brief Função convToChar
 * 
 * É uma função auxiliar que muda de posições os três elementos do topo da stack, isto é,
 * o elemento na no topo desce para a posição abaixo, o elemento, inicialmente, a seguir ao topo 
 * desce para a posição seguinte e o elemento que se encontrava a na 3ª posição a contar do topo
 * vem para o topo da stack.
 * 
 * @param x
 * @param y
 * @param z
 *  
 * @returns struct elemento.
 */
struct elemento rot_three_elem_StackTop(struct elemento *x, struct elemento *y, struct elemento *z)
{
    PUSH(y);
    PUSH(x);
    PUSH(z);
}

//"$" --------------------------------------------

/**
 * \brief Função cpy_N_elem_of_Stack_ToTop
 * 
 * É uma função auxiliar que procura o n-ésimo (dado por parâmetro) elemento da stack a contar a partir do topo
 * e copia-o para o topo da stack.
 * 
 * @param x
 * 
 * @returns struct elemento.
 */
struct elemento cpy_N_elem_of_Stack_ToTop(struct elemento *y)
{
    PUSH(&y);
}