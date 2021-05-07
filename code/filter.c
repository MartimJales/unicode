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
#include "filter.h"
#include <assert.h>

// FIlter com os simbolos singulares que não interferem com polimorfismos

int filter(char *token)
{
    //printf("Caiu no filter com o tokeen %c!\n", *token);
    char *maths = "-&|^";
    char *manstack = "_;\\@";
    char *conversion = "ifcs";
    char *logic = "!?e";
    char *io = "ltp";
    char *variables1 = "ABCDEFGHIJKLMOPQRTUVWXYZ";
    char *variables2 = ":";

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
    // printf("Caiu no sitio certo!\n");
    return 0;
}

void poli_filter(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '+':
        // printf("Caiu na soma\n");
        if (isnumber(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            struct elemento y = POP(ptr_STACK);
            PUSH(ptr_STACK, operador(x, y, token));
        }
        else if (haveonearray(ptr_STACK))
        {
            concatenarray(ptr_STACK);
        }
        else
        {
            concaString(ptr_STACK);
        }
        break;
    case '/':
        if (isnumber(ptr_STACK))
        {
            //    printf("Cai na divisão de nums\n");
            struct elemento x = POP(ptr_STACK);
            struct elemento y = POP(ptr_STACK);
            PUSH(ptr_STACK, operador(x, y, token));
        }
        else if (haveonestring(ptr_STACK))
        {
            sub_String(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: /\n");
        }
        break;
    case '(':
        if (isnumber(ptr_STACK))
        {
            decrement(ptr_STACK);
        }
        else if (onlyarray(ptr_STACK))
        {
            left_parentesis(ptr_STACK);
        }
        else if (onlystring(ptr_STACK))
        {
            delete_fst_Str(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: (\n");
        }
        break;
    case ')':
        if (isnumber(ptr_STACK))
        {
            increment(ptr_STACK);
        }
        else if (onlyarray(ptr_STACK))
        {
            right_parentesis(ptr_STACK);
        }
        else if (onlystring(ptr_STACK))
        {
            delete_snd_Str(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: )\n");
        }
        break;
    case '%':
        if (isnumber(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            struct elemento y = POP(ptr_STACK);
            PUSH(ptr_STACK, operador(x, y, token));
        }
        else if (secondarray(ptr_STACK))
        {
            // Aplicar o bloco a todos os elementos do array
        }
        else if (secondstring(ptr_STACK))
        {
            // Aplicar o bloco a todos os charda string
        }
        else
        {
            printf("Deu merda na condição do poli_filter: PERCENTAGEM \n");
        }
        break;
    case '#':
        if (isnumber(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            struct elemento y = POP(ptr_STACK);
            PUSH(ptr_STACK, operador(x, y, token));
        }
        else if (onlystring(ptr_STACK))
        {
            find_subStr(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: #\n");
        }
        break;
    case '~':
        if (onlynumber(ptr_STACK))
        {
            complement(ptr_STACK);
        }
        else if (onlyarray(ptr_STACK))
        {
            empurraarray(ptr_STACK);
        }
        /*
        else if (onlyblock(ptr_STACK))
        {
            // Aplicar o bloco a todos os charda string
        }*/
        else
        {
            printf("Deu merda na condição do poli_filter: ~\n Falta fazer a condição dos blocos \n");
        }
        break;
    case '$':
        if (onlynumber(ptr_STACK))
        {
            dollarfunction(ptr_STACK);
        }
        /*
        else if (onlyblock(ptr_STACK))
        {
            // Aplicar o bloco a todos os charda string
        }*/
        else
        {
            printf("Deu merda na condição do poli_filter: $\n Falta fazer a condição dos blocos \n");
        }
        break;
    case '=':
        if (equal_type(ptr_STACK))
        {
            equal(ptr_STACK);
        }
        else if (stringnumber(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            val_index_Str(ptr_STACK, x);
        }
        else if (haveonearray(ptr_STACK))
        {
            buscavalindice(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: =\n");
        }
        break;
    case '<':
        if (equal_type(ptr_STACK))
        {
            smaller(ptr_STACK);
        }
        else if (secondarray(ptr_STACK))
        {
            left_elementos(ptr_STACK);
        }
        else if (secondstring(ptr_STACK))
        {
            catch_elem_Str(ptr_STACK);
            // Retira os primeiros n-ésimos elementos da string
        }
        else
        {
            printf("Deu merda na condição do poli_filter: <\n");
        }
        break;
    case '>':
        if (equal_type(ptr_STACK))
        {
            greater(ptr_STACK);
        }
        else if (secondarray(ptr_STACK))
        {
            right_elementos(ptr_STACK);
        }
        else if (secondstring(ptr_STACK))
        {
            catch_ultimos_Str(ptr_STACK);
        }
        else
        {
            printf("Deu merda na condição do poli_filter: >\n");
        }
        break;
    case '*':
        if (isnumber(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            struct elemento y = POP(ptr_STACK);
            PUSH(ptr_STACK, operador(x, y, token));
        }
        else if (secondarray(ptr_STACK))
        {
            repetearray(ptr_STACK);
        }
        else if (secondstring(ptr_STACK))
        {
            repeteStr(ptr_STACK);
        } /*
        else if (onlyblock(ptr_STACK))
        {
            // Aplica o fold ao array ou à string
        }*/
        else
        {
            printf("Deu merda na condição do poli_filter: *\n");
        }
        break;
    case ',':
        if (onlynumber(ptr_STACK))
        {
            range_array(ptr_STACK);
        }
        else if (onlyarray(ptr_STACK))
        {
            tamanho_array(ptr_STACK);
        }
        else if (onlystring(ptr_STACK))
        {
            struct elemento x = POP(ptr_STACK);
            tamanho_str(ptr_STACK, x);
        }
        /*
        else if (onlyblock(ptr_STACK))
        {
            // Aplica um filter à string ou ao array -> Verificar se não é necessário mais uma condição neste caso!!!
        }*/
        else
        {
            printf("Deu merda na condição do poli_filter: ,\n Falta fazer a condição dos blocos \n");
        }
        break;
    }
}

void manhosos_filter(struct stack *ptr_STACK, char *token)
{
    //printf("Stack: %d\n", ptr_STACK->top);
    struct elemento val;
    val.tipo = T_string;

    if (strcmp(token, "S/") == 0)
    {
        div_WhiteS_Str(ptr_STACK);
    }
    else if (strcmp(token, "N/") == 0)
    {
        div_newLines_Str(ptr_STACK);
    }
    else if (*token == 'N')
    {
        val.data.val_s = token;
        val.data.val_s[0] = '\n';
        val.data.val_s[1] = '\0';
        PUSH(ptr_STACK, val);
    }
    else if (*token == 'S')
    {
        // printf("Caiu aqui a pikena!\n");
        //char space[] = " ";
        val.data.val_s = token;
        val.data.val_s[0] = ' ';
        val.data.val_s[1] = '\0';
        // printf("String depois das mudancças monstras : [%s]!\n", val.data.val_s);
        PUSH(ptr_STACK, val);
        // printf("O tipo do menino é %d\n", ptr_STACK->array[ptr_STACK->top].tipo);
        // printf("O menino é um:[%s]\n", ptr_STACK->array[ptr_STACK->top].data.val_s);
    }
    else
    {
        printf("Condições na função manhosos_filter estão dar merda!\n");
    }
}

int isnumber(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo1 != T_array && tipo1 != T_string && tipo1 != T_char && tipo2 != T_array && tipo2 != T_string && tipo2 != T_char)
    {
        return 1;
    }
    return 0;
}

int haveonearray(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo1 == T_array || tipo2 == T_array)
    {
        return 1;
    }
    return 0;
}

int haveonestring(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo1 == T_string || tipo2 == T_string)
    {
        return 1;
    }
    return 0;
}

int onlynumber(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    if (tipo1 != T_array && tipo1 != T_string && tipo1 != T_char)
    {
        return 1;
    }
    return 0;
}

int onlyarray(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    if (tipo1 == T_array)
    {
        return 1;
    }
    return 0;
}

int onlystring(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    if (tipo1 == T_string)
    {
        return 1;
    }
    return 0;
}

int secondarray(struct stack *ptr_STACK)
{
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo2 == T_array)
    {
        return 1;
    }
    return 0;
}

int secondstring(struct stack *ptr_STACK)
{
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo2 == T_string)
    {
        return 1;
    }
    return 0;
}

int stringnumber(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo1 != T_array && tipo1 != T_string && tipo1 != T_char && tipo2 == T_string)
    {
        return 1;
    }
    return 0;
}

int equal_type(struct stack *ptr_STACK)
{
    int tipo1 = ptr_STACK->array[ptr_STACK->top].tipo;
    int tipo2 = ptr_STACK->array[ptr_STACK->top - 1].tipo;
    if (tipo1 == tipo2)
    {
        return 1;
    }
    return 0;
}