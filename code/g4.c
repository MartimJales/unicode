
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

//falta testar (dentro dos PUSH o 1º elemento temos que vereficar se necessita de apontadores ou nao)

void concatenarray(struct stack *ptr_STACK)
{
    //printf("Cheguei ao concatena!\n");
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    if ((x.tipo == T_array) && (y.tipo == T_array))
    {
        //printf("Temos dois arrays!!!!\n");
        //printf("Topo do array %d\n", x.data.val_p->top);

        for (int i = 0; i <= x.data.val_p->top; i++)
        {
            PUSH(y.data.val_p, x.data.val_p->array[i]);
        }
        PUSH(ptr_STACK, y);
    }
    else if ((x.tipo != T_array) && (y.tipo == T_array))
    {
        PUSH(y.data.val_p, x);
        PUSH(ptr_STACK, y);
    }
    else if ((x.tipo == T_array) && (y.tipo != T_array))
    {
        //printf("Caiu aqui\n");
        struct elemento array;
        array.tipo = T_array;
        struct stack *new_stack = malloc(sizeof(struct stack));
        initStack(new_stack, ptr_STACK->vars);
        array.data.val_p = new_stack;
        PUSH(array.data.val_p, y);
        for (int i = 0; i <= x.data.val_p->top; i++)
        {
            PUSH(array.data.val_p, x.data.val_p->array[i]);
        }
        PUSH(ptr_STACK, array);
    }
}

void empurraarray(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    x.tipo = T_array;
    for (int i = 0; i <= x.data.val_p->top; i++)
    {
        PUSH(ptr_STACK, x.data.val_p->array[i]);
    }
}

void repetearray(struct stack *ptr_STACK)
{
    int n = 0;
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    if (x.tipo == T_int)
    {
        n = x.data.val_i;
    }

    else if (x.tipo == T_long)
    {
        n = x.data.val_l;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= y.data.val_p->top; j++)
        {
            PUSH(new_stack, y.data.val_p->array[j]);
        }
    }
    PUSH(ptr_STACK, val);
}

void parse_array(char *line, struct stack *ptr_STACK)
{
    char *token;
    char *resto;

    char *delimitadores = " \t \n";
    for (token = get_token(delimitadores, cleanLim(line), &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        char *resto_num = "abc";
        int val_tipo;
        // printf("Token atual da parse array: %s!\n", token);
        check_type(&resto_num, &token, &val_tipo);

        if (strlen(resto_num) == 0)
            put_token(ptr_STACK, val_tipo, token);
        else if (*token == '[')
        {
            //printf("ARRAY!\n");
            pinta_array(token);
            struct elemento val;
            val.tipo = T_array;
            struct stack *new_stack = malloc(sizeof(struct stack));
            initStack(new_stack, ptr_STACK->vars);
            val.data.val_p = new_stack;
            put_array(ptr_STACK, token, &val);
        }
        else if (*token == '"')
        {
            criaStr(ptr_STACK, token);
        }
        else
        {
            go_filter(ptr_STACK, token);
        }
    }
}

void criaStr(struct stack *ptr_STACK, char *token)
{
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
    x.tipo = T_string;
    x.data.val_s = token;
    /*
    printf("Token[1]: %c\n", token[1]);
    x.data.val_s = *(token + 1);
    */
    //printf("Token[1]: %c\n", x.data.val_s[0]);

    while (token[i + 2] != '\0')
    {
        x.data.val_s[i] = token[i + 1];
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
    x.data.val_s[i] = '\0';

    PUSH(ptr_STACK, x);
}

void tamanho_array(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    int i = x.data.val_p->top + 1;
    struct elemento n;
    n.tipo = T_int;
    n.data.val_i = i;
    PUSH(ptr_STACK, n);
}

void range_array(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função range");

    struct elemento y;
    y.tipo = T_int;

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    //struct array *ptr_array = (array.data.val_p);
    // printf("Range: %d\n\n", x.data.val_i);
    for (int i = 0; i < x.data.val_i; i++)
    {
        y.data.val_i = i;
        PUSH(new_stack, y);
    }
    PUSH(ptr_STACK, val);
}

void buscavalindice(struct stack *ptr_STACK)
{
    //printf("entrei na busaca val indice \n");
    struct elemento x = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função range");

    struct elemento y = POP(ptr_STACK);

    int len = x.data.val_i;

    PUSH(ptr_STACK, y.data.val_p->array[len]);
}

void left_elementos(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
        printf("Deu erro na função left_elementos");

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;
    for (int i = 0; i <= x.data.val_i; i++)
    {
        PUSH(new_stack, y.data.val_p->array[i]);
    }
    PUSH(ptr_STACK, val);
}

// feita e empurra o array.flta saber se empurra array ou elemento a elemento
void right_elementos(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    //  printf("Tipo do y: %d\n", y.tipo);
    if (x.tipo == T_long)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_l;
    }
    else if (x.tipo == T_int)
    {
    }
    else if (x.tipo == T_float)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_f;
    }
    else if (x.tipo == T_double)
    {
        x.tipo = T_int;
        x.data.val_i = (int)x.data.val_d;
    }
    else
    {
        printf("Deu erro na função range");
    }

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    for (int i = x.data.val_i; i <= y.data.val_p->top; i++)
    {
        //printf("Quero o elemento  : %d\n", y.data.val_p->array[i].data.val_i);
        PUSH(new_stack, y.data.val_p->array[i]);
    }
    PUSH(ptr_STACK, val);
}

void right_parentesis(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK); // array;
    // printf("Teste de debgging manhoso antes!!!\n");
    // PRINT_ARRAY(x.data.val_p);
    // printf("\n");
    // printf("Topo do array antes: %d!\n", x.data.val_p->top);
    // printf("\n");
    struct elemento new = POP(x.data.val_p);
    // printf("TEste de debgging manhoso depois!!!\n");
    // PRINT_ARRAY(x.data.val_p);
    // printf("\n");

    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, new);
}

void left_parentesis(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);           // array;
    struct elemento new = x.data.val_p->array[0]; // elemento inicial do array;
    //printf("New -> %d\n", new.data.val_i);

    for (int i = 0; i < x.data.val_p->top; i++)
    {
        x.data.val_p->array[i] = x.data.val_p->array[i + 1];
    }
    x.data.val_p->top--;
    PUSH(ptr_STACK, x);
    PUSH(ptr_STACK, new);
}

void manarray(struct stack *ptr_STACK, char *token)
{
    switch (*token)
    {
    case '~':
        empurraarray(ptr_STACK);
        break;
    case '*':
        //printf("entrei na manarray \n");
        repetearray(ptr_STACK);
        break;
    case ',':
        //printf("Caiu na virgula");
        tamanho_array(ptr_STACK);
        break;
    case '=':
        //printf("VAPOVAPO\n");
        buscavalindice(ptr_STACK);
        break;
    case '<':
        left_elementos(ptr_STACK);
        break;
    case '>':
        right_elementos(ptr_STACK);
        break;
    case '(':
        left_parentesis(ptr_STACK);
        break;
    case ')':
        right_parentesis(ptr_STACK);
        break;
    default:
        call_operator(ptr_STACK, token);
        break;
    }
}

void mystrcat(struct elemento s1, struct elemento s2, struct stack *ptr_STACK)
{
    char test1 = s1.data.val_c;
    char test2 = s2.data.val_c;

    s1.tipo = T_string;
    s1.data.val_s[0] = test1;
    s1.data.val_s[1] = test2;
    s1.data.val_s[2] = '\0';

    PUSH(ptr_STACK, s1);
}
/*
char *mystrcat2(char s1, char s2[])
{
    int t = strlen(s2) + 1;
    char total[t];
    int i, j;
    total[0] = s1;

    for (i = 0; s2[i] != '\0'; i++)
        total[i + 1] = s2[i];
    total[i + 1] = '\0';
    return total;
}

char *mystrcat3(char s2[], char s1)
{
    int i;
    int t = strlen(s2) + 2;
    char total[t];

    for (i = 0; s2[i] != '\0'; i++)
        total[i] = s2[i];

    total[t] = s1;

    total[t + 1] = '\0';

    return total;
}
*/
void mystrcat4(char s1[], char s2[])
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++)
        ;
    for (j = 0; s2[j] != '\0'; j++)
    {
        s1[i] = s2[j];
        i++;
    }
    s1[i] = '\0';
    //return s1;
}

void concaString(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (y.tipo == T_char || x.tipo == T_char)
    {
        printf("DOIS CHARS!\n");
        mystrcat(y, x, ptr_STACK);
    } /*
    else if (y.tipo == T_char || x.tipo == T_string)
    {
        mystrcat2(y.data.val_c, x.data.val_s);
    }
    else if (y.tipo == T_string || x.tipo == T_char)
    {
        mystrcat3(y.data.val_s, x.data.val_c);
    }*/
    else if (y.tipo == T_string || x.tipo == T_string)
    {
        mystrcat4(y.data.val_s, x.data.val_s);
    }

    //printf("Deu certo com o strcat!\n");
    PUSH(ptr_STACK, y);
}

//Funciona a 100 %

void repeteStr(struct stack *ptr_STACK)
{
    int i, j;

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    struct elemento copy;
    copy.tipo = T_string;
    copy.data.val_s = malloc(1000 * sizeof(char));
    int t = x.data.val_i * strlen(y.data.val_s);

    for (i = 0, j = 0; i < t; i++, j++)
    {
        if (j == 3)
            j = 0;
        copy.data.val_s[i] = y.data.val_s[j];
    }

    PUSH(ptr_STACK, copy);
}

void tamanho_str(struct stack *ptr_STACK, struct elemento x)
{
    struct elemento z;
    z.tipo = T_int;
    z.data.val_i = strlen(x.data.val_s);
    // printf("entrou na tamanho str \n");

    PUSH(ptr_STACK, z);
}

void val_index_Str(struct stack *ptr_STACK, struct elemento x)
{
    struct elemento y = POP(ptr_STACK);
    struct elemento z;
    z.tipo = T_char;
    z.data.val_c = y.data.val_s[x.data.val_i];

    PUSH(ptr_STACK, z);
}

/*
void catch_elem_Str(struct stack *ptr_STACK, struct elemento x)
{
    int i;
    struct elemento y = POP(ptr_STACK);
    struct elemento z;
    z.tipo = T_string;

    for (i = 0; i < x.data.val_i; i++)
    {
        z.data.val_s[i] = y.data.val_s[i];
    }

    PUSH(ptr_STACK, z);
}
*/
void delete_fst_Str(struct stack *ptr_STACK)
{

    int i;
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    struct elemento w;
    w.tipo = T_char;
    w.data.val_c = y.data.val_s[0];

    for (i = 0; i < t; i++)
    {
        y.data.val_s[i] = y.data.val_s[i + 1];
    }
    PUSH(ptr_STACK, y);
    PUSH(ptr_STACK, w);
}

void delete_snd_Str(struct stack *ptr_STACK)
{

    int i;
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    struct elemento w;
    w.tipo = T_char;

    for (i = 0; i < t - 1; i++)
    {
        y.data.val_s[i] = y.data.val_s[i];
    }

    y.data.val_s[i] = '\0';
    w.data.val_c = y.data.val_s[t - 1];

    PUSH(ptr_STACK, y);
    PUSH(ptr_STACK, w);
}
/*
void find_subStr(struct stack *ptr_STACK, struct elemento x)
{
    int i;
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    struct elemento z;
    z.tipo = T_int;

    for (i = 0; i < t; i++)
    {
        if (ptr_STACK->array[i].tipo == T_string)
            z.data.val_i = i;
    }

    PUSH(ptr_STACK, z);
}

void read_All_Str(struct elemento *ptr_STACK, char *line)
{

    struct elemento x;
    x.tipo = T_string;
    *x.data.val_s = line;

    PUSH(ptr_STACK, x);
}

void sub_String(struct elemento *ptr_STACK, struct elemento z)
{
    int i;
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    char *copy;
    strcpy(copy, y.data.val_s);
    struct elemento x;
    x.tipo = T_string;
    *x.data.val_s = copy;

    for (i = 0; i < t; i++)
    {
        if (even(i))
            copy[i] = y.data.val_s[i];
        else
            copy[i] = z.data.val_s[i];
    }
    PUSH(ptr_STACK, x);
}

void div_WhiteS_Str(struct elemento *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    int i, j, u;
    char *copy;
    strcpy(copy, y.data.val_s);
    struct elemento x;
    x.tipo = T_string;
    *x.data.val_s = copy;

    for (i = 0; i < t; i++)
    {
        for (j = 0; j != " "; j++)
        {
            copy[j] = y.data.val_s[j];
        }

        PUSH(ptr_STACK, x);

        for (u = 0; u < t; u++)
        {
            copy[u] = '\0';
        }

        i = j + 1;
    }
}

void div_newLines_Str(struct elemento *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    int i;

    for (i = 0; i < t; i++)
    {
        if (y.data.val_s[i] == " ")
            y.data.val_s[i] = '\n';
    }
    PUSH(ptr_STACK, y);
}

*/