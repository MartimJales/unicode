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

void criaBlock(struct stack *ptr_STACK, char *token)
{
    // printf("entrei na criablock\n");
    //printf("CAIU NAS STRINGS!\n");
    int i = 0;
    // size = strlen(token);
    /*
    printf("Token na criaStr: \n\n");
    printf("%s\n", token);
*/
    //printf("Tudo ok com a strlen: %zu\n"), strlen(token);
    //printf("Tudo ok com a strlen: %d\n"), sizeof(token);
    struct elemento x;
    x.tipo = T_block;
    x.data.val_b = token;

    /*
    printf("Token[1]: %c\n", token[1]);
    x.data.val_s = *(token + 1);
    */
    //printf("Token[1]: %c\n", x.data.val_s[0]);

    while (token[i + 2] != '\0')
    {
        x.data.val_b[i] = (token[i + 1]);
        i++;
    }
    /*
    for (i = 0; i < size - 2; i++)
    {
        x.data.val_s[i] = token[i + 1];
    }
     x.data.val_s = "cona!!";
    printf("Poiinter criado no elemento na criaStr: \n\n");
    printf("%s\n", (x.data.val_s));

    //printf("%s\n", token);
*/
    x.data.val_b[i] = '\0';

    PUSH(ptr_STACK, x);
    // printf("o tipo do q pushei é : %d", x.tipo);
}

// Recebe um numero antes do bloco e aplic ao bloco ao numero!

void tilfunction(struct stack *ptr_STACK)
{
    // printf("entrou na tilfunction\n");

    char s[200];

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (y.tipo == T_int)
    {
        // s[0]=x.data.val_i;
        //  printf("entrou no int\n");
        //strcat(s, snum);
        sprintf(s, "%d", y.data.val_i);
    }
    else if (y.tipo == T_long)
    {
        //s[0]=x.data.val_l;
        // printf("entrou no long\n");
        sprintf(s, "%ld", y.data.val_l);
    }
    else if (y.tipo == T_float)
    {
        //s[0]=x.data.val_f;
        // printf("entrou no float \n");
        sprintf(s, "%.2f", y.data.val_f);
    }
    else if (y.tipo == T_double)
    {
        // s[0]=x.data.val_d;
        // printf("entrou no double \n");
        sprintf(s, "%.2f", y.data.val_d);
    }
    pinta_block(x.data.val_b);
    mystrcat4(s, " ");
    mystrcat4(s, x.data.val_b);

    //    printf("%s", s);

    parse_array(s, ptr_STACK);
}


char *pinta_block(char *line)
{
    // char *delimitadores = " \t\n";

    char copi[1000];
    int j = 0, i = 2;
    while (line[i + 2] != '\0')
    {
        copi[j] = line[i];
        i++;
        j++;
    }
    copi[j] = '\0';
    strcpy(line, copi);
    return line;
}

void percentagem_function(struct stack *ptr_STACK)
{
    // printf(" Caiu no filter_block!\n");
    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);
    //  PRINT_ARRAY(arr.data.val_p);

    int i;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    // printf(" Deu certo na criação da string s\n");
    int top = arr.data.val_p->top;
    //printf("Temos o top a %d\n", top);
    
    for (i = 0; i <= top; i++)
    {
        // arr.data.val_p->array[i].data.val_s = malloc(10000 * sizeof(char));

        //printf("O elem {%d} é do tipo %d\n", arr.data.val_p->array[i].data.val_i, arr.data.val_p->array[i].tipo);
        // printf("O elem {%ld} é do tipo %d\n", arr.data.val_p->array[i].data.val_l, arr.data.val_p->array[i].tipo);
        //printf("O elem {%f} é do tipo %d\n", arr.data.val_p->array[i].data.val_d, arr.data.val_p->array[i].tipo);
        //printf("O elem {%f} é do tipo %d\n", arr.data.val_p->array[i].data.val_f, arr.data.val_p->array[i].tipo);
        // printf("Temos aqui um elem do tipo %d\n", arr.data.val_p->array[i].tipo);

        //  convert_elem_s(arr.data.val_p->array[i]);

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

        // printf("temos a string: {%s}!\n", s);

        // mystrcat4(s, arr.data.val_p->array[i].data.val_s);
        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");
        // mystrcat4(s, " ");
        mystrcat4(s, aux);
       // printf("Na iteração %d temos a string: {%s}!\n", i, s);
    }
    for (int i = 0; i <= top; i++)
        POP(arr.data.val_p);
    parse_array(s, arr.data.val_p);
    // PRINT_ARRAY(arr.data.val_p);
    // printf("Estoirou!\n");
    PUSH(ptr_STACK, arr);
    // printf("O topo da stack tem um elemento do tipo %d\n", ptr_STACK->array[ptr_STACK->top].tipo);
}



void w_function(struct stack *ptr_STACK)
{
    // printf(" Caiu no filter_block!\n");
    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);
    //  PRINT_ARRAY(arr.data.val_p);

    int i,j;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    // printf(" Deu certo na criação da string s\n");
    int top = arr.data.val_p->top;
    //printf("Temos o top a %d\n", top);

    struct elemento final;
    final.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    final.data.val_p = new_stack;


    for(i = 0; i <= top && arr.data.val_p->array[i].data.val_l!=0; i++)
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

        // printf("temos a string: {%s}!\n", s);

        // mystrcat4(s, arr.data.val_p->array[i].data.val_s);
        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");
        // mystrcat4(s, " ");
        mystrcat4(s, aux);
       // printf("Na iteração %d temos a string: {%s}!\n", i, s);
    }

parse_array(s, final.data.val_p);
PRINT_ARRAY(final.data.val_p);
printf("\n");
PRINT_ARRAY(arr.data.val_p);
printf("\n");


int topo = arr.data.val_p->top;

    for(i=0,j=0;i<=final.data.val_p->array[i].data.val_l!=0 && j!=1;i++)
    {
        switch (final.data.val_p->array[i].tipo)
        {
        case T_int:
        if(final.data.val_p->array[i].data.val_i!=0)
        {
            PUSH(arr.data.val_p, arr.data.val_p->array[i]);
            j=1;
        }
        break;

        case T_float:
        if(final.data.val_p->array[i].data.val_f!=0)
        {
            PUSH(new_stack, arr.data.val_p->array[i]);
            j=1;
        }
        break;

        case T_double:
        if(final.data.val_p->array[i].data.val_d!=0)
        {
            PUSH(new_stack, arr.data.val_p->array[i]);
            j=1;
        }
            break;

        case T_long:
        if(final.data.val_p->array[i].data.val_l!=0)
        {
            PUSH(new_stack, arr.data.val_p->array[i]);
            j=1;
        }
        break;

        default:
            printf("Deu bagulho na função 2_function\n");
            break;
        }
        
    }
//printf("o top é: %d\n",arr.data.val_p->top);
for (i;i<=arr.data.val_p->top+1;i++)
{
//    printf("o i é: %d\n",i);

    POP(arr.data.val_p);
}

    // PRINT_ARRAY(arr.data.val_p);
    // printf("Estoirou!\n");
    PUSH(ptr_STACK, arr);
    // printf("O topo da stack tem um elemento do tipo %d\n", ptr_STACK->array[ptr_STACK->top].tipo);
}





void filter_function(struct stack *ptr_STACK)
{
    // printf(" Caiu no filter_block!\n");
    struct elemento block = POP(ptr_STACK);
    pinta_block(block.data.val_b);
    struct elemento arr = POP(ptr_STACK);
    //  PRINT_ARRAY(arr.data.val_p);

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


    int i,j;
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    // printf(" Deu certo na criação da string s\n");
    int top = arr.data.val_p->top;
    //printf("Temos o top a %d\n", top);
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

        // printf("temos a string: {%s}!\n", s);

        // mystrcat4(s, arr.data.val_p->array[i].data.val_s);
        mystrcat4(aux, " ");
        mystrcat4(aux, block.data.val_b);
        mystrcat4(aux, " ");
        // mystrcat4(s, " ");
        mystrcat4(s, aux);
        //printf("Na iteração %d temos a string: {%s}!\n", i, s);
    }
    parse_array(s, val.data.val_p);
    //printf("proximo é o val");
    //PRINT_ARRAY(val.data.val_p);
    //printf("\n");

    for(i=0,j=0;i<=val.data.val_p->top;i++)
    {
        if(val.data.val_p->array[i].data.val_l!=0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if(val.data.val_p->array[i].data.val_i!=0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if(val.data.val_p->array[i].data.val_d!=0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
        else if(val.data.val_p->array[i].data.val_f!=0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
      /*  
        else if(((val.data.val_p->array[i].data.val_c)-'\0')!=0)
        {
            PUSH(new_stack2, arr.data.val_p->array[i]);
            j++;
        }
      */
    }
    //PRINT_ARRAY(final.data.val_p);
    //printf("\n");


    PUSH(ptr_STACK, final);
    // printf("O topo da stack tem um elemento do tipo %d\n", ptr_STACK->array[ptr_STACK->top].tipo);
}




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

void convert_arr_string(struct elemento arr, char *s)
{
    // printf("Recbi do array a linha {%s}\n", s);

    char *aux = malloc(1000 * sizeof(char));

    int top = arr.data.val_p->top;
    sprintf(s, "%s", "[ ");

    for (int i = 0; i <= top; i++)
    {
        // Switch para pssar cada elemento para string

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
            //  printf("Vamos fazer a convert_arr_string\n");
            convert_arr_string(arr.data.val_p->array[i], aux);
            break;
        default:
            printf("Deu bagulho na função filter_block\n");
            break;
        }

        // Adiconar o espaço

        mystrcat4(aux, " ");

        // Adicionar à string principal;

        mystrcat4(s, aux);
    }

    // printf("temos a string: {%s}!\n", s);
    mystrcat4(s, "] ");

    //  printf("Temos a string: {%s}!\n", s);
}