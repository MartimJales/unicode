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

    int i, j;
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

    for (i = 0, j = 0; /* (i <= final.data.val_p->array[i].data.val_l != 0)&&*/ (j != 1); i++)
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
    //printf("o top é: %d\n",arr.data.val_p->top);

    while (i <= topo + 1)
    {
        POP(arr.data.val_p);
        i++;
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

    int i, j;
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

void dollar_block(struct stack *ptr_STACK)
{
    // printf(" Caiu no dollar_block!\n");
    struct elemento block = POP(ptr_STACK);

    struct elemento arr = POP(ptr_STACK);
    //  PRINT_ARRAY(arr.data.val_p);

    // << porque : A, gosta : B, > A B ? >> ;

    struct stack *new_stack2 = malloc(sizeof(struct stack));

    pinta_block(block.data.val_b);

    //  printf("Bloco recebido: {%s}\n", block.data.val_b);
    if (strcmp(block.data.val_b, " ") == 0)
    {
        // printf(" Caiu no bloco burro!\n");
        sprintf(block.data.val_b, "%s", " < ");
    }
    /*  printf("Bloco antes do megeSot: {%s}\n", block.data.val_b);

    int n[10] = {3, 2, 1, 4, 3, 5, 66, 321, 4, 5};

    printf("Array antes: ");
    printArray(n, 10);
    printf(" \n");
    mergeSort1(n, 0, 9);
    printf("Array depois: ");
    printArray(n, 10);

    printf(" \n");
*/
    // printf("Top antes do mergeSort: %d\n", arr.data.val_p->top);

    mergeSort(arr.data.val_p->array, 0, arr.data.val_p->top, block.data.val_b, new_stack2);
    // printf("Bloco depois do megeSot: {%s}\n", block.data.val_b);
    PUSH(ptr_STACK, arr);
}

/// Funções da net:::

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
    /*
    printf("No merge eu recebi o array: ");
    for (int i = 0; i < n1; i++)
    {
        printf("%ld - ", L[i].data.val_l);
    }
    printf(" e recebi tbm o array: ");

    for (int i = 0; i < n2; i++)
    {
        printf("%ld - ", R[i].data.val_l);
    }
    printf("\n");
*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        //   printf("Vamos comparar os elementos: %ld e %ld\n", L[i].data.val_l, R[j].data.val_l);
        if (checka(L[i], R[j], bloco, final)) /// L[i] <= R[i]
        {
            //  printf("Mandei o elemento: %ld\n", L[i].data.val_l);
            arr[k] = L[i];
            i++;
        }
        else
        {
            //   printf("Mandei o elemento: %ld\n", R[j].data.val_l);
            //  printf("O elem 1 é SUPERIOR ao elem2\n");
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

    printf("No fim do merge eu devolvi o seguinte: ");
    for (int i = 0; i < k; i++)
    {
        printf("%ld - ", arr[i].data.val_l);
    }
    printf("\n");
}

int count = 0;

void mergeSort(struct elemento arr[], int l, int r, char *bloco, struct stack *final)
{

    /*
    printf("No merge Sort %d temos o array: ", count);
    count++;
    if (count == 0)
    {
        for (int i = 0; i <= r; i++)
        {
            printf("%ld - ", arr[i].data.val_l);
        }
    }
    printf("\n");*/

    if (l < r)
    {
        int m = l + (r - l) / 2;
        /* printf("l: %d  r: %d  m: %d \n", l, r, m);
          printf(" Array da esquerda: ");
        for (l; l <= m; l++)
        {
            printf("%ld - ", arr[l].data.val_l);
        }
        printf("\n");
        printf("Array da direita: ");
        for (m; m <= r; m++)
        {
            printf("%ld - ", arr[m + 1].data.val_l);
        }
        printf("\n");
        */

        /* printf("Estou a analisar o array: ");
        for (int i = l; i <= r; i++)
        {
            printf("%ld - ", arr[i].data.val_l);
        }
    
        printf("\n");*/

        mergeSort(arr, l, m, bloco, final);
        mergeSort(arr, m + 1, r, bloco, final);

        merge(arr, l, m, r, bloco, final);
    }
}
// Devolve 1    <<fst bloco snd>> == true
// Devolve 0    <<fst bloco snd>> == false
/*

1. Construir a linha 
2. Criar uma stack à toa
2. Fazer o parse dessa linha para uma stack à toa
3. Verificar o que está na topo da stack!
4. Se topo == fst devolve true
5. Se topo == snd devolve false 

*/

int checka(struct elemento fst, struct elemento snd, char *bloco, struct stack *final)
{
    // Comparação se os dois elementos são iguais!!!

    // printf(" Caiu no checka!\n");

    //  PRINT_ARRAY(arr.data.val_p);
    char *s = malloc(10000 * sizeof(char));
    char *aux = malloc(1000 * sizeof(char));
    // printf(" Deu certo na criação da string s\n");

    // Construir a linha

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

    //printf("Depois da checka temos a string: {%s}!\n", s);
    parse_array(s, final);

    // double x = convertToDouble(fst);
    double y = convertToDouble(final->array[final->top]);

    //printf("O tipo do que está na stack é: %d\n", final->array[final->top].tipo);
    // printf("O tipo do nosso fst é: %d\n", fst.tipo);

    // printf("O result: %f\n", y);

    return y;
    // return (x ==y);
    //    return comichoes(final->array[final->top], fst); // Esta está comentada!!!
}
/*
int comichoes(struct elemento x, struct elemento y)
{
    if (y.tipo != x.tipo)
        return 0;

    if (y.tipo == T_int && x.tipo == T_int)
    {
        if (y.data.val_i != x.data.val_i)
            return 0;
    }

    if (y.tipo == T_float && x.tipo == T_float)
    {
        if (y.data.val_f != x.data.val_f)
            return 0;
    }

    if (y.tipo == T_double && x.tipo == T_double)
    {
        if (y.data.val_d != x.data.val_d)
            return 0;
    }

    if (y.tipo == T_long && x.tipo == T_long)
    {
        if (y.data.val_l != x.data.val_l)
            return 0;
    }

    if (y.tipo == T_char && x.tipo == T_char)
    {
        if (y.data.val_c != x.data.val_c)
            return 0;
    }

    if (y.tipo == T_string && x.tipo == T_string)
    {

        if (strcmp(y.data.val_s, x.data.val_s) != 0)
            return 0;
    }

    if (y.tipo == T_array && x.tipo == T_array)
    {
        if (y.data.val_p->top != x.data.val_p->top)
            return 0;
    }
    return 
}*/

void fold_function(struct stack *ptr_STACK)
{
    // printf(" Caiu no fold_block!\n");
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
    //  printf("Na iteração %d temos a string: {%s}!\n", 0, s);

    for (i = 1; i <= top; i++)
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
        //  printf("Na iteração %d temos a string: {%s}!\n", i, s);
    }
    for (int i = 0; i <= top; i++)
        POP(arr.data.val_p);
    parse_array(s, arr.data.val_p);
    // PRINT_ARRAY(arr.data.val_p);
    // printf("Estoirou!\n");
    PUSH(ptr_STACK, arr);
    // printf("O topo da stack tem um elemento do tipo %d\n", ptr_STACK->array[ptr_STACK->top].tipo);
}

void merge1(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
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

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort1(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort1(arr, l, m);
        mergeSort1(arr, m + 1, r);

        merge1(arr, l, m, r);
    }
}

void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}