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
 */
void parse(char *line)
{
    struct stack lady;
    lady.top = -1;
    struct stack *ptr_lady = &lady;

    char *delimitadores = " \t \n";
    for (char *token = strtok(line, delimitadores); token != NULL; token = strtok(NULL, delimitadores))
    {
        char *resto;
        int val_tipo;

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
        if (strlen(resto) == 0)
        {
            struct elemento val;
            val.tipo = val_tipo;

            sprintf(val.valor, "%s", token);
            PUSH(ptr_lady, val);
        }
        else
        {
            switch (filter(token))
            {
            case 1:
                maths(ptr_lady, token);
                break;
            case 2:
                manstack(ptr_lady, token);
                break;
            case 3:
                conversion(ptr_lady, token);
                break;
            case 4:
                inoutput(ptr_lady, token);
                break;
            default:
                //Esta é referente aos próximos guiões e ainda não estão definidas!
                break;
            }
        }
    }
    PRINT_STACK(ptr_lady);
}

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um valor inteiro que é o valor do novo topo da stack
 */
struct elemento POP(struct stack *stack)
{
    (*stack).top--;
    return (*stack).array[(*stack).top + 1];
}

/**
 * \brief Função PUSH do programa
 * 
 * Função que vai à Stack adicionar uma célula acima da última.
 * 
 * @param stack
 * @param n
 */
void
PUSH(struct stack *stack, struct elemento n)
{
    (*stack).top++;
    (*stack).array[(*stack).top] = n;
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
 * @param stack
 */
void PRINT_STACK(struct stack *stack)
{
    char *resto;
    for (int i = 0; i <= (*stack).top; i++)
    {
        if ((*stack).array[i].tipo == T_int || (*stack).array[i].tipo == T_long)
            printf("%ld", strtol((*stack).array[i].valor, &resto, 10));
        else if ((*stack).array[i].tipo == T_float || (*stack).array[i].tipo == T_double)
            printf("%.6g", strtod((*stack).array[i].valor, &resto));
        else if ((*stack).array[i].tipo == T_char)
        {
            char str[2];
            str[0] = atoi((*stack).array[i].valor);
            str[1] = 0;
            printf("%s", str);
        }
        else
            printf("%s", (*stack).array[i].valor);
    }
    printf("\n");
}

/**
 * \brief Função convertToDouble
 * 
 * É uma função auxiliar que recebe um elemento e converte-o para Double
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
 * @param op
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
    case '%':
        dres = (long)dy % (long)dx;
        break;
    case '#':
        dres = pow(dy, dx);
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
        printf("DEU BAGULHO____ABORT ABORT!!!");
        break;
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

/**
 * \brief Função get_the_kid do programa
 * 
 * A função get_the_kid recebe como parâmetros um apontador para a struct stack e uma variável i
 * e dá o valor apontado pelo topo da stack menos o valor de i.
 * 
 * @param stack
 * @param i
 * 
 * @returns Um elemento da Stack.
 */
struct elemento get_the_kid(struct stack *stack, int i)
{
    return (*stack).array[(*stack).top - i];
}

/**
 * \brief Função filter do programa
 * 
 * A função filter compara o token com os diferentes apontadores para operar segundo
 * um dos ciclos while da função.
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
    char *io = "l";

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
    return 0;
}

/**
 * \brief Função maths do programa
 * 
 * A função efetua o cálculo das operações aritméticas.
 * 
 * @param ptr_lady
 * @param token
 */
void maths(struct stack *ptr_lady, char *token)
{
    if (*token == '(')
    {
        struct elemento x = POP(ptr_lady);
        long l = atol(x.valor);
        sprintf(x.valor, "%ld", --l);
        PUSH(ptr_lady, x);
    }
    else if (*token == ')')
    {
        struct elemento x = POP(ptr_lady);
        long l = atol(x.valor);
        sprintf(x.valor, "%ld", ++l);
        PUSH(ptr_lady, x);
    }
    else
    {
        struct elemento x = POP(ptr_lady);
        struct elemento y = POP(ptr_lady);
        PUSH(ptr_lady, operador(x, y, token));
    }
}

/**
 * \brief Função manstack do programa
 * 
 * A função efetua o cálculo das operações para manipulação da Stack.
 * 
 * @param ptr_lady
 * @param token
 */
void manstack(struct stack *ptr_lady, char *token)
{
    if (strcmp(token, "_") == 0)
    {
        struct elemento x = POP(ptr_lady);
        PUSH(ptr_lady, x);
        PUSH(ptr_lady, x);
    }
    else if (strcmp(token, ";") == 0)
    {
        POP(ptr_lady);
    }
    else if (strcmp(token, "\\") == 0)
    {
        struct elemento x = POP(ptr_lady);
        struct elemento y = POP(ptr_lady);
        PUSH(ptr_lady, x);
        PUSH(ptr_lady, y);
    }
    else if (strcmp(token, "@") == 0)
    {
        struct elemento x = POP(ptr_lady);
        struct elemento y = POP(ptr_lady);
        struct elemento z = POP(ptr_lady);
        PUSH(ptr_lady, y);
        PUSH(ptr_lady, x);
        PUSH(ptr_lady, z);
    }
    else if (strcmp(token, "$") == 0)
    {
        struct elemento x = POP(ptr_lady);
        int i = atoi(x.valor);
        struct elemento y = get_the_kid(ptr_lady, i);
        PUSH(ptr_lady, y);
    }
}

/**
 * \brief Função conversion do programa
 * 
 * A função efetua a conversão dos elementos da Stack.
 * 
 * @param ptr_lady
 * @param token
 */
void conversion(struct stack *ptr_lady, char *token)
{
    if (strcmp(token, "i") == 0) //converter para int
    {
        struct elemento x = POP(ptr_lady);
        x.tipo = T_int;
        PUSH(ptr_lady, x);
    }
    else if (strcmp(token, "f") == 0) //converter para float
    {
        struct elemento x = POP(ptr_lady);
        x.tipo = T_float;
        PUSH(ptr_lady, x);
    }
    else if (strcmp(token, "c") == 0) //converter para char
    {
        struct elemento x = POP(ptr_lady);
        x.tipo = T_char;
        PUSH(ptr_lady, x);
    }
}

/**
 * \brief Função inoutput do programa
 * 
 * A função inoutput é responsável pelas ações de in/output.
 * 
 * @param ptr_lady
 * @param token
 */
void inoutput(struct stack *ptr_lady, char *token)
{
    if (strcmp(token, "l") == 0) //ler linha
    {
        struct elemento x;
        assert(fgets(x.valor, 100, stdin) != NULL);
        x.tipo = T_string;
        PUSH(ptr_lady, x);
    }
}