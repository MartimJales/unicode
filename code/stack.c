/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINSTACK_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include <assert.h>

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um valor elemento .
 */
struct elemento POP(struct stack *stack)
{
    stack->top--;
    return stack->array[stack->top + 1];
}

/**
 * \brief Função PUSH do programa
 * 
 *que adiciona uma célula à Stack .
 * 
 * @param stack
 * @param n (elemento a adicionar).
 */
void
PUSH(struct stack *stack, struct elemento n)
{
    //printf(" o tipo  do que pediste para empurrar é : %d\n", n.tipo);
    //printf("Top antes %d\n", stack->top);
    stack->top++;
    //printf("Top DEPOIS %d\n", stack->top);
    //printf(" o q empurrei foi :%ld\n", n.data.val_l);
    stack->array[stack->top] = n;
    //printf(" o q fixou no topo da stack foi : %ld\n", stack->array[stack->top].data.val_l);
    //printf(" o q empurrei  na verdade foi  %ld\n", stack->array[stack->top].data.val_l);
    long ptr_test = (long)stack;
    printf("Coloquei os meninos na localização %ld\n", ptr_test);
}

/**
 * \brief Função PRINSTACK_STACK do programa.
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
    printf("Print stack : \n");
    //char *resto;

    printf("Topo desta merda: %d!\n", (*stack).top);

    for (int i = 0; i <= (*stack).top; i++)
    {
        switch ((*stack).array[i].tipo)
        {
        case T_int:
            printf("int: ");
            printf("%d\n", (*stack).array[i].data.val_i);
            break;
        case T_long:
            printf("long: ");
            printf("%ld\n", (*stack).array[i].data.val_l);
            break;
        case T_float:
            printf("float: ");
            printf("%.6g\n", stack->array[i].data.val_f);
            break;
        case T_double:
            printf("double: ");
            printf("%.6g\n", stack->array[i].data.val_d);
            break;
        case T_char:
            printf("char: ");
            printf("%c\n", stack->array[i].data.val_c);
            break;
        case T_string:
            printf("string: ");
            printf("%s\n", stack->array[i].data.val_s);
            break;
        case T_array:
            printf("array: ");
            PRINT_ARRAY((stack->array[i].data.val_p));
            break;
        default:
            printf("FALTA AS STRINGS na print_array!\n");
            break;
        }
    }
    printf("\n");
}

void PRINT_ARRAY(struct stack *stack)
{
    printf("Print ARRAY : ");

    printf("Topo do array: %d!\n", (*stack).top);

    for (int i = 0; i <= (*stack).top; i++)
    {
        switch ((*stack).array[i].tipo)
        {
        case T_int:
            printf(" int: ");
            printf("%d", (*stack).array[i].data.val_i);
            break;
        case T_long:
            printf(" long: ");
            printf("%ld", (*stack).array[i].data.val_l);
            break;
        case T_float:
            printf(" float: ");
            printf("%.6g", stack->array[i].data.val_f);
            break;
        case T_double:
            printf(" double: ");
            printf("%.6g", stack->array[i].data.val_d);
            break;
        case T_char:
            printf(" char: ");
            printf("%c", stack->array[i].data.val_c);
            break;
        case T_string:
            printf(" string: ");
            printf("%s", stack->array[i].data.val_s);
            break;
        case T_array:
            printf(" array: ");
            PRINT_ARRAY((stack->array[i].data.val_p));
            break;
        default:
            printf("FALTA AS STRINGS na print_array!\n");
            break;
        }
    }
}

/**
 * \brief Função initStack  do programa
 * 
 * inicia a stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void initStack(struct stack *ptr_STACK)
{
    ptr_STACK->top = -1;
    struct var var_tmp;
    struct elemento val;
    val.tipo = T_int;
    for (int i = 0; i < 6; i++)
    {
        val.data.val_i = 10 + i;
        var_tmp.index = i;
        var_tmp.elemento = val;
        (*ptr_STACK).vars[i] = var_tmp;
    }
    val.data.val_i = 0;
    var_tmp.index = 23;
    var_tmp.elemento = val;
    (*ptr_STACK).vars[23] = var_tmp;
    val.data.val_i = 1;
    var_tmp.index = 24;
    var_tmp.elemento = val;
    (*ptr_STACK).vars[24] = var_tmp;
    val.data.val_i = 2;
    var_tmp.index = 25;
    var_tmp.elemento = val;
    (*ptr_STACK).vars[25] = var_tmp;
}

// Funções do ficheiro conaça
/*
void dupArray(struct array *s)
{
    int r = 0, i;
    struct elemento *t = malloc(2 * s->capacity * sizeof(struct elemento));

    if (t == NULL)
        r = 1;
    else
    {
        for (i = 0; i < s->capacity; i++)
            t[i] = s->values[i];
        free(s->values);
        s->values = t;
        s->capacity *= 2;
    }
}

void pushArray(struct array *arr, struct elemento x)
{
    int r = 0;
    printf(">>> COMEÇOU O PUSH <<<\n");
    printf("index  push : %d capacity = %d \n", arr->index, arr->capacity);
    if (arr->index == arr->capacity)
    {
        dupArray(arr);
    }
    if (!r)
    {
        arr->values[arr->index] = x;
        arr->index++;
    }

    printf("index depois : %d capacity = %d \n", arr->index, arr->capacity);
}

void PRINT_STACK(struct array *array)
{
    int i;
    for (i = 0; i < array->index; i++)
    {
        switch (array->values[i].tipo)
        {
        case T_int:
            printf("%d", array->values[i].data.val_i);
            break;
        case T_long:
            printf("%ld", array->values[i].data.val_l);
            break;
        case T_float:
            printf("%.6g", array->values[i].data.val_f);
            break;
        case T_double:
            //  printf("double: ");
            printf("%.6g", array->values[i].data.val_d);
            break;
        case T_char:
            //  printf("char: ");
            printf("%c", array->values[i].data.val_c);
            break;
        case T_string:
            //  printf("string: ");
            printf("%s", array->values[i].data.val_s);
            break;
        case T_array:
            //  printf("array: ");
            PRINT_STACK(array->values[i].data.val_p);
            break;
        default: //falta as strings e os arrays
            break;
        }
        putchar('\n');
    }
}

void free_array(struct array *array)
{
    free(array->values);
}

void initArray(struct array *array)
{
    printf("Caiu no inicio \n");
    array->index = 0;
    array->capacity = 10;
    array->values = malloc(array->capacity * sizeof(struct elemento));
}
*/