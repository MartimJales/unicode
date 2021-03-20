/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"

int top = -1;
long stack[10240];

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
    char *delimitadores = " \t \n";
    for (char *token = strtok(line, delimitadores); token != NULL; token = strtok(NULL, delimitadores))
    {
        char *resto;
        long val_i = strtol(token, &resto, 10);
        if (strlen(resto) == 0)
        {
            PUSH(val_i);
        }
        else if (strcmp(token, "+") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(x + y);
        }
        else if (strcmp(token, "*") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(x * y);
        }
        else if (strcmp(token, "/") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y / x);
        }
        else if (strcmp(token, "-") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y - x);
        }
        else if (strcmp(token, ")") == 0)
        {
            long x = POP();
            PUSH(x + 1);
        }
        else if (strcmp(token, "(") == 0)
        {
            long x = POP();
            PUSH(x - 1);
        }
        else if (strcmp(token, "%") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y % x);
        }
        else if (strcmp(token, "#") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(pow(y, x));
        }
        else if (strcmp(token, "&") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y & x);
        }
        else if (strcmp(token, "|") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y | x);
        }
        else if (strcmp(token, "^") == 0)
        {
            long x = POP();
            long y = POP();
            PUSH(y ^ x);
        }
        else if (strcmp(token, "~") == 0)
        {
            long x = POP();
            PUSH(~x);
        }
    }
    PRINT_STACK();
}

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um inteiro long, cujo resultado é o valor no topo da Stack.
 */
long POP()
{
    top--;
    return stack[top + 1];
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
void PUSH(long val_i)
{
    top++;
    stack[top] = val_i;
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
void PRINT_STACK()
{
    for (int i = 0; i <= top; i++)
    {
        printf("%ld", stack[i]);
    }
    printf("\n");
}
