/**
 * @file Ficheiro que contém as funções relativas ao guião 5
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
#include "g5.h"
#include <assert.h>

/**
 * \brief Função criaBlock do programa
 * 
 * que cria o bloco e envia-o para a stack.
 * 
 * @param ptr_STACK (apontador para a Stack)
 * @param token (operando)
 */
void criaBlock(struct stack *ptr_STACK, char *token)
{
    int i = 0;
    struct elemento x;
    x.tipo = T_block;
    x.data.val_b = token;

    while (token[i + 2] != '\0')
    {
        x.data.val_b[i] = (token[i + 1]);
        i++;
    }
    x.data.val_b[i] = '\0';

    PUSH(ptr_STACK, x);
}

/**
 * \brief Função tilfunction do programa
 * 
 * aplica a operação do bloco a um elemento
 * 
 * @param ptr_STACK (apontador para a Stack)
 */
void tilfunction(struct stack *ptr_STACK)
{
    char s[200];

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (y.tipo == T_int)
    {
        sprintf(s, "%d", y.data.val_i);
    }
    else if (y.tipo == T_long)
    {
        sprintf(s, "%ld", y.data.val_l);
    }
    else if (y.tipo == T_float)
    {
        sprintf(s, "%.2f", y.data.val_f);
    }
    else if (y.tipo == T_double)
    {
        sprintf(s, "%.2f", y.data.val_d);
    }
    pinta_block(x.data.val_b);
    mystrcat4(s, " ");
    mystrcat4(s, x.data.val_b);

    parse_array(s, ptr_STACK);
}

/**
 * \brief Função pinta_block do programa
 * 
 * prepara o bloco para as operações 
 * 
 * @param line (string que contem o bloco)
 * 
 * @returns um char
 */
char *pinta_block(char *line)
{
    char copi[1000];
    int j = 0, i = 1;
    while (line[i + 1] != '\0')
    {
        copi[j] = line[i];
        i++;
        j++;
    }
    copi[j] = '\0';
    strcpy(line, copi);
    return line;
}

/**
 * \brief Função percentagem_function do programa
 * 
 * aplica o bloco a um array /string
 * 
 * @param line (string que contem o bloco)
 */
void percentagem_function(struct stack *ptr_STACK)
{

    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);

    int i;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    int top = arr.data.val_p->top;

    for (i = 0; i <= top; i++)
    {
        switch (arr.data.val_p->array[i].tipo)
        {
        case T_int:
            sprintf(aux, "%d", arr.data.val_p->array[i].data.val_i);
            break;
        case T_float:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_f);
            break;
        case T_double:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_d);
            break;
        case T_long:
            sprintf(aux, "%ld", arr.data.val_p->array[i].data.val_l);
            break;
        case T_char:
            sprintf(aux, "%c", arr.data.val_p->array[i].data.val_c);
            break;
        case T_string:
            sprintf(aux, "%c", '"');
            mystrcat4(aux, arr.data.val_p->array[i].data.val_s);
            mystrcat4(aux, "\"");
            break;
        case T_array:
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }

        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");
        mystrcat4(s, aux);
    }
    for (int i = 0; i <= top; i++)
        POP(arr.data.val_p);
    parse_array(s, arr.data.val_p);
    PUSH(ptr_STACK, arr);
}

/**
 * \brief Função w_function do programa
 * 
 * Executa o bloco enquanto ele deixar um truthy
 * no topo da stack
 * 
 * @param ptr_stack (apontador para a stack)
 */
void w_function(struct stack *ptr_STACK)
{
    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);

    int i, j;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    int top = arr.data.val_p->top;

    struct elemento final;
    final.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    final.data.val_p = new_stack;

    for (i = 0; i <= top && arr.data.val_p->array[i].data.val_l != 0; i++)
    {
        switch (arr.data.val_p->array[i].tipo)
        {
        case T_int:
            sprintf(aux, "%d", arr.data.val_p->array[i].data.val_i);
            break;
        case T_float:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_f);
            break;
        case T_double:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_d);
            break;
        case T_long:
            sprintf(aux, "%ld", arr.data.val_p->array[i].data.val_l);
            break;
        case T_char:
            sprintf(aux, "%c", arr.data.val_p->array[i].data.val_c);
            break;
        case T_string:
            sprintf(aux, "%c", '"');
            mystrcat4(aux, arr.data.val_p->array[i].data.val_s);
            mystrcat4(aux, "\"");
            break;
        case T_array:
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }

        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");
        mystrcat4(s, aux);
    }

    parse_array(s, final.data.val_p);

    int topo = arr.data.val_p->top;

    for (i = 0, j = 0; (j != 1); i++)
    {
        switch (final.data.val_p->array[i].tipo)
        {
        case T_int:
            if (final.data.val_p->array[i].data.val_i != 0)
            {
                PUSH(arr.data.val_p, arr.data.val_p->array[i]);
                j = 1;
            }
            break;

        case T_float:
            if (final.data.val_p->array[i].data.val_f != 0)
            {
                PUSH(new_stack, arr.data.val_p->array[i]);
                j = 1;
            }
            break;

        case T_double:
            if (final.data.val_p->array[i].data.val_d != 0)
            {
                PUSH(new_stack, arr.data.val_p->array[i]);
                j = 1;
            }
            break;

        case T_long:
            if (final.data.val_p->array[i].data.val_l != 0)
            {
                PUSH(new_stack, arr.data.val_p->array[i]);
                j = 1;
            }
            break;

        default:
            printf("Deu bagulho na função 2_function\n");
            break;
        }
    }
    while (i <= topo + 1)
    {
        POP(arr.data.val_p);
        i++;
    }
    PUSH(ptr_STACK, arr);
}

/**
 * \brief Função filter_function do programa
 * 
 * Executa um bloco e devolve os verdadeiros
 * 
 * @param ptr_stack (apontador para a stack)
 */
void filter_function(struct stack *ptr_STACK)
{

    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    struct elemento final;
    final.tipo = T_array;
    struct stack *new_stack2 = malloc(sizeof(struct stack));
    initStack(new_stack2, ptr_STACK->vars);
    final.data.val_p = new_stack2;

    int i, j;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));

    int top = arr.data.val_p->top;
    for (i = 0; i <= top; i++)
    {
        switch (arr.data.val_p->array[i].tipo)
        {
        case T_int:
            sprintf(aux, "%d", arr.data.val_p->array[i].data.val_i);
            break;
        case T_float:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_f);
            break;
        case T_double:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_d);
            break;
        case T_long:
            sprintf(aux, "%ld", arr.data.val_p->array[i].data.val_l);
            break;
        case T_char:
            sprintf(aux, "%c", arr.data.val_p->array[i].data.val_c);
            break;
        case T_string:
            sprintf(aux, "%c", '"');
            mystrcat4(aux, arr.data.val_p->array[i].data.val_s);
            mystrcat4(aux, "\"");
            break;
        case T_array:
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }

        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");

        mystrcat4(s, aux);
    }
    parse_array(s, val.data.val_p);

    for (i = 0, j = 0; i <= val.data.val_p->top; i++)
    {
        if (val.data.val_p->array[i].data.val_l != 0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if (val.data.val_p->array[i].data.val_i != 0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if (val.data.val_p->array[i].data.val_d != 0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if (val.data.val_p->array[i].data.val_f != 0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
    }
    PUSH(ptr_STACK, final);
}

/**
 * \brief Função convert_elem_s do programa
 * 
 * converte o elemento dado para string
 * 
 * @param val (struct elemento)
 */
void convert_elem_s(struct elemento val)
{
    switch (val.tipo)
    {
    case T_int:
        val.tipo = T_string;
        sprintf(val.data.val_s, "%d", val.data.val_i);
        break;
    case T_float:
        val.tipo = T_string;
        sprintf(val.data.val_s, "%f", val.data.val_f);
        break;
    case T_double:
        val.tipo = T_string;
        sprintf(val.data.val_s, "%f", val.data.val_d);
        break;
    case T_long:
        val.tipo = T_string;
        sprintf(val.data.val_s, "%ld", val.data.val_l);
        break;
    case T_char:
        val.tipo = T_string;
        break;
    default:
        printf("Deu bagulho na função convert_s\n");
        break;
    }
}

/**
 * \brief Função convert_arr_string do programa
 * 
 * converte o elemento dado do tipo array para string
 * 
 * @param arr (struct elemento)
 * @param s (string resultado)
 */
void convert_arr_string(struct elemento arr, char *s)
{

    char *aux = malloc(1000 * sizeof(char));

    int top = arr.data.val_p->top;
    sprintf(s, "%s", "[ ");

    for (int i = 0; i <= top; i++)
    {

        switch (arr.data.val_p->array[i].tipo)
        {
        case T_int:
            sprintf(aux, "%d", arr.data.val_p->array[i].data.val_i);
            break;
        case T_float:
            sprintf(aux, "%.2f", arr.data.val_p->array[i].data.val_f);
            break;
        case T_double:
            sprintf(aux, "%.2f", arr.data.val_p->array[i].data.val_d);
            break;
        case T_long:
            sprintf(aux, "%ld", arr.data.val_p->array[i].data.val_l);
            break;
        case T_char:
            sprintf(aux, "%c", arr.data.val_p->array[i].data.val_c);
            break;
        case T_string:
            sprintf(aux, "%c", '"');
            mystrcat4(aux, arr.data.val_p->array[i].data.val_s);
            mystrcat4(aux, "\"");
            sprintf(aux, "%s", arr.data.val_p->array[i].data.val_s);
            break;
        case T_array:
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }

        mystrcat4(aux, " ");

        mystrcat4(s, aux);
    }
    mystrcat4(s, "] ");
}

/**
 * \brief Função dollar_block do programa
 * 
 * ordena usando o bloco
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void dollar_block(struct stack *ptr_STACK)
{
    struct elemento block = POP(ptr_STACK);

    struct elemento arr = POP(ptr_STACK);

    struct stack *new_stack2 = malloc(sizeof(struct stack));

    pinta_block(block.data.val_b);

    if (strcmp(block.data.val_b, " ") == 0)
    {
        sprintf(block.data.val_b, "%s", " < ");
    }

    mergeSort(arr.data.val_p->array, 0, arr.data.val_p->top, block.data.val_b, new_stack2);
    PUSH(ptr_STACK, arr);
}

/**
 * \brief Função merge do programa
 * 
 * Dá merge de dois arrays na ordem correta 
 * 
 * @param arr (array)
 * @param l (int)
 * @param m (int)
 * @param r (int)
 * @param bloco (string)
 * @param final (apontador para uma stack)
 */
void merge(struct elemento arr[], int l, int m, int r, char *bloco, struct stack *final)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct elemento L[n1];
    struct elemento R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {

        if (checka(L[i], R[j], bloco, final))
        {

            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * \brief Função mergeSort do programa
 * 
 * Realiza a função de ordenação.
 * 
 * @param arr (array)
 * @param l (int)
 * @param r (int)
 * @param bloco (string)
 * @param final (apontador para uma stack)
 */
void mergeSort(struct elemento arr[], int l, int r, char *bloco, struct stack *final)
{

    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, bloco, final);
        mergeSort(arr, m + 1, r, bloco, final);

        merge(arr, l, m, r, bloco, final);
    }
}

/**
 * \brief Função checka do programa
 * 
 * Compara dois elementos em relação à operação realizada pelo bloco e retorna 1 se se verificar .0 Caso contrário.
 * 
 * @param fst (struct elemento)
 * @param snd (struct elemento)
 * @param bloco (string)
 * @param final (apontador para uma stack)
 */
int checka(struct elemento fst, struct elemento snd, char *bloco, struct stack *final)
{
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    switch (fst.tipo)
    {
    case T_int:
        sprintf(aux, "%d", fst.data.val_i);
        break;
    case T_float:
        sprintf(aux, "%f", fst.data.val_f);
        break;
    case T_double:
        sprintf(aux, "%f", fst.data.val_d);
        break;
    case T_long:
        sprintf(aux, "%ld", fst.data.val_l);
        break;
    case T_char:
        sprintf(aux, "%c", fst.data.val_c);
        break;
    case T_string:
        sprintf(aux, "%c", '"');
        mystrcat4(aux, fst.data.val_s);
        mystrcat4(aux, "\"");
        break;
    case T_array:
        convert_arr_string(fst, aux);
        break;
    default:
        printf("Deu bagulho na função filter_block\n");
        break;
    }

    mystrcat4(aux, " ");
    mystrcat4(s, aux);

    switch (snd.tipo)
    {
    case T_int:
        sprintf(aux, "%d", snd.data.val_i);
        break;
    case T_float:
        sprintf(aux, "%f", snd.data.val_f);
        break;
    case T_double:
        sprintf(aux, "%f", snd.data.val_d);
        break;
    case T_long:
        sprintf(aux, "%ld", snd.data.val_l);
        break;
    case T_char:
        sprintf(aux, "%c", snd.data.val_c);
        break;
    case T_string:
        sprintf(aux, "%c", '"');
        mystrcat4(aux, snd.data.val_s);
        mystrcat4(aux, "\"");
        break;
    case T_array:
        convert_arr_string(snd, aux);
        break;
    default:
        printf("Deu bagulho na função filter_block\n");
        break;
    }

    mystrcat4(aux, bloco);

    mystrcat4(s, aux);
    parse_array(s, final);

    double y = convertToDouble(final->array[final->top]);

    return y;
}

/**
 * \brief Função fold_function do programa
 * 
 * Aplica o fold a um array/string
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void fold_function(struct stack *ptr_STACK)
{
    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);

    int i;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    int top = arr.data.val_p->top;

    switch (arr.data.val_p->array[0].tipo)
    {
    case T_int:
        sprintf(aux, "%d", arr.data.val_p->array[0].data.val_i);
        break;
    case T_float:
        sprintf(aux, "%f", arr.data.val_p->array[0].data.val_f);
        break;
    case T_double:
        sprintf(aux, "%f", arr.data.val_p->array[0].data.val_d);
        break;
    case T_long:
        sprintf(aux, "%ld", arr.data.val_p->array[0].data.val_l);
        break;
    case T_char:
        sprintf(aux, "%c", arr.data.val_p->array[0].data.val_c);
        break;
    case T_string:
        sprintf(aux, "%c", '"');
        mystrcat4(aux, arr.data.val_p->array[0].data.val_s);
        mystrcat4(aux, "\"");
        break;
    case T_array:
        convert_arr_string(arr.data.val_p->array[0], aux);
        break;
    default:
        printf("Deu bagulho na função filter_block\n");
        break;
    }

    mystrcat4(aux, " ");

    mystrcat4(s, aux);

    for (i = 1; i <= top; i++)
    {
        switch (arr.data.val_p->array[i].tipo)
        {
        case T_int:
            sprintf(aux, "%d", arr.data.val_p->array[i].data.val_i);
            break;
        case T_float:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_f);
            break;
        case T_double:
            sprintf(aux, "%f", arr.data.val_p->array[i].data.val_d);
            break;
        case T_long:
            sprintf(aux, "%ld", arr.data.val_p->array[i].data.val_l);
            break;
        case T_char:
            sprintf(aux, "%c", arr.data.val_p->array[i].data.val_c);
            break;
        case T_string:
            sprintf(aux, "%c", '"');
            mystrcat4(aux, arr.data.val_p->array[i].data.val_s);
            mystrcat4(aux, "\"");
            break;
        case T_array:
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }
        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");

        mystrcat4(s, aux);
    }
    for (int i = 0; i <= top; i++)
        POP(arr.data.val_p);
    parse_array(s, arr.data.val_p);

    PUSH(ptr_STACK, arr);
}
