
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
    for (int i = 0; i < x.data.val_i; i++)
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

    for (int i = y.data.val_p->top - x.data.val_i + 1; i <= y.data.val_p->top; i++)
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
    s1.data.val_s = malloc(100 * sizeof(char));
    printf("S1: %s\n", s1.data.val_s);

    s1.data.val_s[0] = test1;
    s1.data.val_s[1] = test2;
    s1.data.val_s[2] = '\0';

    PUSH(ptr_STACK, s1);
}

void mystrcat2(struct elemento s1, struct elemento s2, struct stack *ptr_STACK)
{
    char test1 = s1.data.val_c;
    s1.tipo = T_string;
    s1.data.val_s = malloc(100 * sizeof(char));
    s1.data.val_s[0] = test1;

    mystrcat4(s1.data.val_s, s2.data.val_s);

    PUSH(ptr_STACK, s1);
}

void mystrcat3(struct elemento s1, struct elemento s2, struct stack *ptr_STACK)
{
    char test1 = s2.data.val_c;
    s2.tipo = T_string;
    s2.data.val_s = malloc(100 * sizeof(char));
    s2.data.val_s[0] = test1;

    mystrcat4(s1.data.val_s, s2.data.val_s);

    PUSH(ptr_STACK, s1);
}

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
}

void concaString(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (y.tipo == T_char && x.tipo == T_char)
    {
        // printf("DOIS CHARS!\n");
        mystrcat(y, x, ptr_STACK);
    }

    else if (y.tipo == T_char && x.tipo == T_string)
    {
        // printf("1-char 2 -string!\n");
        mystrcat2(y, x, ptr_STACK);
    }

    else if (y.tipo == T_string && x.tipo == T_char)
    {
        mystrcat3(y, x, ptr_STACK);
    }

    else if (y.tipo == T_string && x.tipo == T_string)
    {
        mystrcat4(y.data.val_s, x.data.val_s);
        PUSH(ptr_STACK, y);
    }
}

void repeteStr(struct stack *ptr_STACK)
{
    int i, j;

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);
    struct elemento copy;
    copy.tipo = T_string;
    copy.data.val_s = malloc(10000 * sizeof(char));
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

void catch_elem_Str(struct stack *ptr_STACK)
{
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    /*
    struct elemento z;
    z.data.val_s = malloc(100 * sizeof(char));
    z.tipo = T_string;
*/

    if (x.tipo == T_int)
    {
        y.data.val_s[x.data.val_i] = '\0';
        /*
        for (i = 0; i < x.data.val_i; i++)
        {
            z.data.val_s[i] = y.data.val_s[i];
        }
        */
    }
    else if (x.tipo == T_long)
    {
        y.data.val_s[x.data.val_l] = '\0';
        /*
        for (i = 0; i < x.data.val_l; i++)
        {
            z.data.val_s[i] = y.data.val_s[i];
        }
        */
    }
    else
        printf("Deu merd na função catch_elem_Str\n");
    PUSH(ptr_STACK, y);
    //PUSH(ptr_STACK, z);
}

void catch_ultimos_Str(struct stack *ptr_STACK)
{
    int i = 0;
    long j = 0;
    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    int len = strlen(y.data.val_s);

    if (x.tipo == T_int)
    {
        while (y.data.val_s[len - x.data.val_i + i])
        {
            y.data.val_s[i] = y.data.val_s[len - x.data.val_i + i];
            i++;
        }
        y.data.val_s[i] = '\0';
    }
    else if (x.tipo == T_long)
    {
        while (y.data.val_s[len - x.data.val_l + j] != '\0')
        {
            y.data.val_s[j] = y.data.val_s[len - x.data.val_l + j];
            j++;
        }
        y.data.val_s[j] = '\0';
    }
    else
        printf("Deu merd na função catch_elem_Str\n");

    PUSH(ptr_STACK, y);
}

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
    struct elemento y = POP(ptr_STACK);
    int t = strlen(y.data.val_s);
    struct elemento w;
    w.tipo = T_char;

    w.data.val_c = y.data.val_s[t - 1];
    y.data.val_s[t - 1] = '\0';

    PUSH(ptr_STACK, y);
    PUSH(ptr_STACK, w);
}

int isSubstring(char *haystack, char *needle)
{
    size_t d;
    int i = 0;
    if (strlen(haystack) >= strlen(needle))
    {
        for (i = strlen(haystack) - strlen(needle); i >= 0; i--)
        {
            int found = 1;
            for (d = 0; d < strlen(needle); d++)
            {
                if (haystack[i + d] != needle[d])
                {
                    found = 0;
                    break;
                }
            }
            if (found == 1)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

void find_subStr(struct stack *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);
    struct elemento x = POP(ptr_STACK);

    struct elemento z;
    z.tipo = T_int;

    z.data.val_i = isSubstring(x.data.val_s, y.data.val_s);

    PUSH(ptr_STACK, z);
}

void sub_String(struct stack *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);
    struct elemento x = POP(ptr_STACK);
    // printf("String_x: %s\n", x.data.val_s);
    // printf("String_y: %s\n", y.data.val_s);
    int tamanho = strlen(x.data.val_s);
    int t = strlen(y.data.val_s);
    // printf("Tamanho de x: %d, tamnho de y: %d\n", tamanho, t);

    // Criação do array!

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    // Criação da string auxiliar paa trnsferir os elementos para o array!
    struct elemento string;
    string.tipo = T_string;
    string.data.val_s = malloc(t * sizeof(char));

    int true = 0;
    int i = 0;
    int j = i;
    for (i = 0; x.data.val_s[i] != '\0'; i++)
    {
        true = compareStrandSub(x.data.val_s, y.data.val_s, t, i);
        // printf("Index do menino >>> %d --- true >>>%d\n", i, true);
        if (true)
        {
            pinta_a_linda(string.data.val_s, x.data.val_s, j, i);
            // printf("Meti a linda: %s\n", string.data.val_s);
            // printf("Big boy: %s\n", x.data.val_s);
            PUSH(val.data.val_p, string);
            string.data.val_s = malloc(tamanho * sizeof(char));
            j = i + t;
        }
        //        printf("Esta aqui o resultado ---->>> %s\n\n\n", string);
    }
    if (i != j)
    {
        pinta_a_linda(string.data.val_s, x.data.val_s, j, i);
        PUSH(val.data.val_p, string);
    }
    PUSH(ptr_STACK, val);
}

void pinta_a_linda(char *aux, char *main, int begin, int j)
{
    // printf("Main: %s\n", main);
    // printf("Estamos com o begin a %d e o i a %d\n", begin, j);
    int i;
    // printf("Querida criei: ");
    for (i = 0; i + begin < j; i++)
    {
        // printf("%d", i);
        // printf("%c", main[begin + i]);
        aux[i] = main[i + begin];
    }
    aux[i] = '\0';
}

int compareStrandSub(char str[], char substr[], int N, int i)
{
    int j = 0;
    while (str[i] != '\0' && j < N)
    {
        if (str[i] != substr[j])
            return 0;
        j++;
        i++;
    }
    if (substr[j] == '\0')
        return 1;
    return 0;
}

void div_WhiteS_Str(struct stack *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);

    // printf("%s \n", y.data.val_s);

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    int t = strlen(y.data.val_s);
    struct elemento string;
    string.tipo = T_string;
    string.data.val_s = malloc(t * sizeof(char));
    int j = 0;

    int count = 0;
    for (int i = 0; i < t; i++)
    {
        if (y.data.val_s[i] == ' ' || y.data.val_s[i] == '\n')
        {
            string.data.val_s[i] = '\0';
            // printf("String tratda: {%s} ---> ", string.data.val_s);
            if (strlen(string.data.val_s) != 0)
            {
                count++;
                // printf("Levou push!  %d", count);
                PUSH(val.data.val_p, string);
            }
            //printf("\n");
            // printf("String tratda: %s\n", val.data.val_p->array[val.data.val_p->top].data.val_s);
            string.data.val_s = malloc(t * sizeof(char));
            j = -1;
        }
        string.data.val_s[j] = y.data.val_s[i];
        j++;
    }
    if (strlen(string.data.val_s) != 0)
    {
        string.data.val_s[j] = '\0';
        //printf("String tratda: {%s} ---> ", string.data.val_s);
        //count++;
        //printf("Levou push!  %d\n", count);
        PUSH(val.data.val_p, string);
    }
    PUSH(ptr_STACK, val);
}

void div_newLines_Str(struct stack *ptr_STACK)
{
    struct elemento y = POP(ptr_STACK);

    // printf("%s \n", y.data.val_s);

    struct elemento val;
    val.tipo = T_array;
    struct stack *new_stack = malloc(sizeof(struct stack));
    initStack(new_stack, ptr_STACK->vars);
    val.data.val_p = new_stack;

    int t = strlen(y.data.val_s);
    struct elemento string;
    string.tipo = T_string;
    string.data.val_s = malloc(t * sizeof(char));
    int j = 0;

    for (int i = 0; i < t; i++)
    {
        if (i == t - 1 && y.data.val_s[i] == '\n')

            //string.data.val_s[i + 1] = '\0';
            // printf("String tratada: %s\n", string.data.val_s);
            //PUSH(val.data.val_p, string);
            // printf("String tratda: %s\n", val.data.val_p->array[val.data.val_p->top].data.val_s);
            //printf("caiu no sitio certo\n Com um char (%c)", y.data.val_s[i]);
            break;

        if (y.data.val_s[i] == '\n')
        {
            string.data.val_s[i + 1] = '\0';
            // printf("String tratada: %s\n", string.data.val_s);
            PUSH(val.data.val_p, string);
            // printf("String tratda: %s\n", val.data.val_p->array[val.data.val_p->top].data.val_s);
            string.data.val_s = malloc(t * sizeof(char));
            j = -1;
        }
        string.data.val_s[j] = y.data.val_s[i];
        j++;
    }
    string.data.val_s[j] = '\0';
    //  printf("String tratda: %s\n", string.data.val_s);
    PUSH(val.data.val_p, string);
    // printf("String tratda: %s\n", val.data.val_p->array[val.data.val_p->top].data.val_s);

    PUSH(ptr_STACK, val);
}
