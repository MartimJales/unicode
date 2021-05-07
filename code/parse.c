/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
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
#include "filter.h"
#include <assert.h>

/**
 * \brief Função check_type do programa
 * 
 * recebe um token, um apontador para o resto_num da função e outro apontador para o tipo desse token.
 * Irá verificar o tipo correspondente ao token e atualizar a stack com o elemento correspondente.
 *
 * @param resto_num
 * @param token
 * @param val_tipo 
 */
void check_type(char **resto_num, char **token, int *val_tipo)
{
    char *p = strstr(*token, ".");
    if (p)
    {
        strtod(*token, resto_num);
        *val_tipo = T_double;
    }
    else
    {
        strtol(*token, resto_num, 10);
        *val_tipo = T_long;
    }
}

/**
 * \brief Função convertToDouble
 * 
 * é uma função auxiliar que recebe um elemento e converte-o para Double
 * 
 * @param x 
 * 
 * @returns double, representado pela variável ret.
 */
float convertToDouble(struct elemento x)
{
    double ret;

    ret = 0.0;
    switch (x.tipo)
    {
    case T_int:
        ret = x.data.val_i * 1.0;
        break;
    case T_long:
        ret = x.data.val_l * 1.0;
        break;
    case T_float:
        ret = x.data.val_f * 1.0;
        break;
    case T_double:
        ret = x.data.val_d * 1.0;
        break;
    case T_char:
        ret = (float)x.data.val_c * 1.0;
        break;
    default: //falta as strings e os arrays
        break;
    }
    //printf("O retorno da função converto double é : %f ", ret);
    return ret;
}

/**
 * \brief Função put_token do programa
 *  int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    int y_tipo = (*ptr_STACK).array[(*ptr_STACK).top - 1].tipo;
    if (x_tipo = T_array || y_tipo == T_array)
        return 1;
    else
 * recebe um token, um apontador para o resto_num da função e outro apontador para a stack.
 * Irá colocar o token respetivo a um elemento na stack.
 *
 * @param resto_num
 * @param token
 * @param val_tipo 
 */
void put_token(struct stack *ptr_STACK, int val_tipo, char *token)
{
    struct elemento val;
    switch (val_tipo)
    {
    case T_int:
        val.tipo = T_int;
        val.data.val_i = atoi(token);
        break;
    case T_float:
        val.tipo = T_float;
        val.data.val_f = atof(token);
        break;
    case T_char:
        printf("Está a dar merda por causa do char!!!!! path: put_token\n");
        val.tipo = T_char;
        val.data.val_c = atoi(token);
        break;
    case T_double:
        val.tipo = T_double;
        val.data.val_d = atof(token);
        break;
    case T_long:
        val.tipo = T_long;
        val.data.val_l = atol(token);
        break;
    case T_string:
        printf("Está a dar merda por causa da string!!!!! path: put_token\n");
        val.tipo = T_string;
        val.data.val_i = atoi(token);
        break;
    case T_array:
        printf("Está a dar merda por causa do array!!!!! path: put_token\n");
        val.tipo = T_array;
        val.data.val_i = atoi(token);
        break;

    default:
        break;
    }
    PUSH(ptr_STACK, val);
}

/**
 * \brief Função go_filter do programa
 * 
 * verifica o nosso token e seleciona a função auxiliar correspondente à operação
 * desejada.
 *
 * @param token
 * @param val_tipo 
 */
void go_filter(struct stack *ptr_STACK, char *token)
{
    // printf("Caiu na go_filter como token %c!\n", *token);
    switch (filter(token))
    {
    case 0:
        // printf("Deu zero!\n");
        poli_filter(ptr_STACK, token);
        break;
    case 1:
        // printf("Deu um!\n");
        maths(ptr_STACK, token);
        break;
    case 2:
        // printf("Deu dois!\n");
        manstack(ptr_STACK, token);
        break;
    case 3:
        // printf("Deu tres!\n");
        conversion(ptr_STACK, token);
        break;
    case 4:
        // printf("Deu quatro!\n");
        inoutput(ptr_STACK, token);
        break;
    case 5:
        // printf("Deu cinco!\n");
        logic(ptr_STACK, token);
        break;
    case 6:
        // printf("Deu seis!\n");
        variables1(ptr_STACK, token);
        break;
    case 7:
        // printf("Deu sete!\n");
        variables2(ptr_STACK, token);
        break;
    default:
        printf("Deu bagalho no go_filter!\n");
        break;
    }
}

/**
 * \brief Função go_filter_array do programa.
 * 
 * Iremos verificar se esse token é o sinal +.
 * Se essa condição se verificar vamos chamar a função check_somma_array 
 * (Verifica as restrições para as ações com somas ou concatenações de arrays).
 * Se não se verificar, chamamos a função check_all_array
 * (Verifica as restrições para as outras operações com arrays). 
 * 
 * @param ptr_STACK Apontador para a stack.
 * @param token Token atual.
 */
void go_filter_array(struct stack *ptr_STACK, char *token)
{
    if (existe_array(ptr_STACK))
    {
        //printf("QUEREMOS UM ARRAY!!!\n");
        switch (*token)
        {
        case '+':
            concatenarray(ptr_STACK);
            break;
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
            // printf("VAPOVAPO\n");
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
        }
    }
    else if (existe_string(ptr_STACK))
    {
        //printf("QUEREMOS UMA STRING!!!\n");
        switch (*token)
        {
        case '+':
            concaString(ptr_STACK);
            break;
        case '*':
            //printf("entrei na repetestring \n");
            repeteStr(ptr_STACK);
            break;
        case ',':
            tamanho_str(ptr_STACK, POP(ptr_STACK));
            break;
        case '=':
            // printf("VAPOVAPO\n");
            val_index_Str(ptr_STACK, POP(ptr_STACK));
            break;
        }
    }
    else
    {
        go_filter(ptr_STACK, token);
    }
}
/* 
        case '<':
            struct elemento x = POP(ptr_STACK);
            catch_elem_Str(ptr_STACK, x);
            break;
        case '>':
            right_elementos(ptr_STACK);
            break;
        case '(':
            delete_fst_Str(ptr_STACK);
            break;
        case ')':void go_filter_array(struct stack *ptr_STACK, char *token)
{
    if (existe_array(ptr_STACK))
    {
        //printf("QUEREMOS UM ARRAY!!!\n");
        switch (*token)
        {
        case '+':
            concatenarray(ptr_STACK);
            break;
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
            // printf("VAPOVAPO\n");
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
        }
    }
    else if (existe_string(ptr_STACK))
    {
        //printf("QUEREMOS UMA STRING!!!\n");
        switch (*token)
        {
        case '+':
            concaString(ptr_STACK);
            break;
        case '*':
            //printf("entrei na repetestring \n");
            repeteStr(ptr_STACK);
            break;
        case ',':
            tamanho_str(ptr_STACK, POP(ptr_STACK));
            break;
        case '=':
            // printf("VAPOVAPO\n");
            val_index_Str(ptr_STACK, POP(ptr_STACK));
            break;
        }
    }
    else
    {
        go_filter(ptr_STACK, token);
    }
}

        case '<':
            struct elemento x = POP(ptr_STACK);
            catch_elem_Str(ptr_STACK, x);
            break;
            struct elemento x = POP(ptr_STACK);
            find_subStr(ptr_STACK, x);
            break;
        case '/':
            struct elemento x = POP(ptr_STACK);
            sub_String(ptr_STACK, x);
            break;

             case 'S/':
            div_WhiteS_Str(ptr_STACK);
            break;
        case 'N/':
            div_newlines_Str(ptr_STACK);
            break;
            
        default:
            printf("Chegou ao fim da filter pa strings ");
        }
    }
    else
    {
        go_filter(ptr_STACK, token);
    }
}
*/

int existe_array(struct stack *ptr_STACK)
{
    if (ptr_STACK->array[ptr_STACK->top].tipo == T_array || ptr_STACK->array[ptr_STACK->top - 1].tipo == T_array)
        return 1;
    return 0;
}

int existe_string(struct stack *ptr_STACK)
{
    if (ptr_STACK->array[ptr_STACK->top].tipo == T_string || ptr_STACK->array[ptr_STACK->top - 1].tipo == T_string)
        return 1;
    return 0;
}

/**
 * \brief Função parse do programa
 * 
 * Inicia-se um apontador de caracteres (delimitadores).
 * 
 * Posteriormente, através de um ciclo, inicia-se uma nova variável (um apontador de carateres (token)),
 * com a condição de paragem quando esse token for NULL. 
 * A cada iteração o tokeS
 */
void parse(char *line)
{
    struct var *vars = malloc(26 * sizeof(struct var));
    struct var *ptr_vars = vars;
    initVars(ptr_vars);

    struct stack STACK;
    struct stack *ptr_STACK = &STACK;
    initStack(ptr_STACK, ptr_vars);
    char *token;
    char *resto;

    char *delimitadores = " \t \n";
    for (token = get_token(delimitadores, (line), &resto); strcmp(token, "") != 0; token = get_token(delimitadores, resto, &resto))
    {
        //Coloquei o resto_num a iniciar a abc porcausa das flags
        // mas temos de ver se isto não provoca merda

        char *resto_num = "abc";
        int val_tipo;
        //printf("Token atual: %s!\n", token);
        check_type(&resto_num, &token, &val_tipo);

        // printf("tipo dps %d\n", val_tipo);

        if (strlen(resto_num) == 0)
            put_token(ptr_STACK, val_tipo, token);
        else if (*token == '[')
        {
            //  printf("ARRAY!\n");
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
        else if (*token == 'S' || *token == 'N')
        {
            manhosos_filter(ptr_STACK, token);
        }
        else
        {
            //  printf("Caiu no filter suposto como token %c!\n", *token);
            go_filter(ptr_STACK, token);
        }
    }
    PRINT_STACK(ptr_STACK);
}

void initVars(struct var *ptr_vars)
{
    struct elemento val;
    val.tipo = T_int;
    struct var var_tmp;

    for (int i = 0; i < 6; i++)
    {
        val.data.val_i = 10 + i;
        var_tmp.index = i;
        var_tmp.elemento = val;
        *(ptr_vars + i) = var_tmp;
    }
    val.data.val_i = 0;
    var_tmp.index = 23;
    *(ptr_vars + 23) = var_tmp;
    var_tmp.elemento = val;
    val.data.val_i = 1;
    var_tmp.index = 24;
    *(ptr_vars + 24) = var_tmp;
    var_tmp.elemento = val;
    val.data.val_i = 2;
    var_tmp.index = 25;
    *(ptr_vars + 25) = var_tmp;
    var_tmp.elemento = val;
}

/**
 * \brief Função check_soma_array do programa.
 * 
 * Iremos verificar se algum dos elementos do topo é array.
 * Se essa condição se verificar vamos concatenar o array. 
 * (concatenarray).
 * Se não se verificar, chamamos o operador para somar os dois elementos.
 *  
 * @param ptr_STACK Apontador para a stack.
 * @param token Token atual.
 */
/*
void check_soma_array(struct stack *ptr_STACK, char *token)
{
    int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    int y_tipo = (*ptr_STACK).array[(*ptr_STACK).top - 1].tipo;

    if ((x_tipo == T_array || y_tipo == T_array) && *token == '+')
    {
        concatenarray(ptr_STACK);
    }
    else if ((x_tipo == T_array || y_tipo == T_array) && *token == '*')
    {
        //printf("cai na check soma array\n");
        repetearray(ptr_STACK);
    }
    else
    {
        struct elemento x = POP(ptr_STACK);
        struct elemento y = POP(ptr_STACK);
        struct elemento val = operador(x, y, token);
        PUSH(ptr_STACK, val);
    }
}
*/
/**
 * \brief Função check_all_array do programa.
 * 
 * Iremos verificar se o topo da stack é array.
 * Se essa condição se verificar vamos chamar a função manarray. 
 * (Aplica as operações com arrays).
 * Se não se verificar, chamamos a função go_filter
 * (Aplica as operações dos guiões 1/2/3). 
 * 
 * @param ptr_STACK Apontador para a stack.
 * @param token Token atual.
 */
/*
void check_all_array(struct stack *ptr_STACK, char *token)
{
    int x_tipo = (*ptr_STACK).array[(*ptr_STACK).top].tipo;
    if (x_tipo == T_array)
    {
        manarray(ptr_STACK, token);
    }
    else
        go_filter(ptr_STACK, token);
}
*/
/**
 * \brief Função put_array do programa.
 * 
 * Responsável por colocar o array na STACK.
 * 
 * @param ptr_STACK Apontador para a stack.
 * @param token Token atual.
 */
void put_array(struct stack *ptr_STACK, char *token, struct elemento *ptr_elem)
{
    parse_array(token, ptr_elem->data.val_p);
    // printf("put_array na localização %ld\n", (long)ptr_STACK);
    //   printf("Top antes %d\n", ptr_STACK->top);
    PUSH(ptr_STACK, *ptr_elem);
    //   printf("Top depois %d\n", ptr_STACK->top);
}

/**
 * \brief Função pinta_array do programa.
 * 
 * Recebe um apontador para a STACK e um token.
 * Iremos verificar se o topo da stack é array.
 * Se essa condição se verificar vamos chamar a função manarray. 
 * (Aplica as operações com arrays).
 * Se não se verificar, chamamos a função go_filter
 * (Aplica as operações dos guiões 1/2/3). 
 * 
 * @param pointer Apontador para a stack.
 * @param line Token atual.
 */
void pinta_array(char *line)
{
    // char *delimitadores = " \t\n";

    char copi[10000];
    int j = 0, i = 2;
    while (line[i + 2] != '\0')
    {
        copi[j] = line[i];
        i++;
        j++;
    }
    copi[j] = '\0';
    strcpy(line, copi);
}

/**
 * \brief Função check_array do programa.
 * 
 * Recebe um apontador para a Stack e um token.
 * Inicializa um apontador para uma string 
 * para testar se o token pertence a algum desses símbolos, 
 * se pertence retorna 1, caso contrário, 0.
 * 
 * @param ptr_STACK Apontador para a Stack
 * @param token Token atual
 * 
 * @return Um inteiro, pode ser 0 ou 1.
 */
int check_array(char *token)
{
    char *arrays = "+~<>()*=,#/N";
    while (*arrays)
    {
        if (*token == *arrays)
        {
            return 1;
        }
        arrays++;
    }
    return 0;
}

// FUction get_delimited

/**
 * \brief Função isDelim do programa.
 * 
 * Recebe o caractere c e incializa uma variável do tipo inteiro a 0.
 * Percorrendo os delimitadores, se c pertencer a essa lista devolve 1,
 * caso contrário, 0.
 * 
 * @param c Caracter c
 * @param delim Apontador para delimitadores
 * 
 * @return bRet que corresponde a 0 ou 1
 */
int isDelim(char c, char *delim)
{
    int bRet = 0;

    for (int i = 0; delim[i]; i++)
    {
        if (delim[i] == c)
            bRet = 1;
    }
    return bRet;
}

// verifica se é delimitador

/**
 * \brief Função isLim do programa.
 * 
 * testa se o token é um delimitador.
 * 
 * @param token
 * 
 * @return 0 ou 1
 */
int isLim(char token)
{
    if (token == ' ' || token == '\n' || token == '\t')
    {
        return 1;
    }
    else
        return 0;
}

// número de delimitadores seguidos

/**
 * \brief Função cleanLim do programa.
 * 
 * remove os delimitadores da linha recebida.
 * 
 * @param line
 * 
 * @return line
 */
char *cleanLim(char line[])
{
    int i, j;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (isLim(line[i]) && isLim(line[i + 1]))
        {
            for (j = i; line[j] != '\0'; j++)
            {
                line[j] = line[j + 1];
            }
            line[j] = '\0';
            i--;
        }
    }
    return line;
}

/**
 * \brief Função get_token do programa.
 * 
 * ---------------------------------------------------------------------------
 * 
 * @param delim Apontador para delimitadores
 * @param line Apontador para a linha que será lida
 * @param rest
 * 
 * @return bRet que corresponde a 0 ou 1
 */
char *get_token(char *delim, char *line, char **rest)
{
    //char *pRet = NULL;
    int i, bTratado = 0;
    //int iToken = 0;

    //printf("get_token('%s' ###  %s  ###)\n",delim,line);

    //printf("-- %c %d --\n",line[0],isDelim(line[0],delim));

    for (i = 0; line[i] && isDelim(line[i], delim) == 0 && bTratado == 0; i++)
    {
        if (line[i] == '[')
        {
            int nParentesis = 1;
            int j;

            for (j = 1; nParentesis > 0 && line[i + j]; j++)
            {
                if (line[i + j] == ']')
                    nParentesis--;
                if (line[i + j] == '[')
                    nParentesis++;
            }
            if (nParentesis > 0)
            {
                printf("Falta ]");
            }
            else
            {
                line[i + j] = 0;
                *rest = line + i + j + 1;
                bTratado = 1;
            }
        }
        if (line[i] == '"')
        {
            int nAspas = 1;
            int j;

            for (j = 1; nAspas > 0 && line[i + j]; j++)
            {
                if (line[i + j] == '"')
                    nAspas--;
            }
            if (nAspas > 0)
            {
                //  printf("Falta Fechar Aspas");
            }
            else
            {
                line[i + j] = 0;
                *rest = line + i + j + 1;
                bTratado = 1;
            }
        }
    }

    if (bTratado == 0)
    {
        if (isDelim(line[i], delim))
        {
            line[i] = 0;
            *rest = line + i + 1; // problema está aqui
        }
        else
        {
            *rest = line + i;
        }
    }
    return line;
}
