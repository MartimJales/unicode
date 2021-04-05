/**
 * @file Ficheiro que contém as função parse, a par, das funções que lhe dão suporte, POP, PUSH e PRINT_STACK
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"
#include <assert.h>





int top = -1;
struct elemento stack[10];

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
            struct elemento val;
            val.tipo = T_long;
            sprintf(val.valor,"%ld",val_i); 
            PUSH(val);
        }
        else if (strcmp(token, "l") == 0) //ler linha
        {
            struct elemento x ;
            assert(fgets(x.valor, 100, stdin) != NULL);
            x.tipo=T_string;
            PUSH(x);
        }
        else if (strcmp(token, "i") == 0) //converter para int
        {
            struct elemento x = POP() ;
            x.tipo=T_int;
            PUSH(x);
        }
        else if (strcmp(token, "f") == 0) //converter para float
        {
            struct elemento x = POP() ;
            x.tipo=T_float;
            PUSH(x);
        }
        else if (strcmp(token, "+") == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(operador(x , y,'+'));
        }
        else if (strcmp(token, "*") == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(operador(x , y,'*'));
        }
        else if (strcmp(token, "/") == 0)
        {
            struct elemento y = POP();
            struct elemento x = POP();

            PUSH(operador(x , y,'/'));
        }
        else if (strcmp(token, "-") == 0)
        {
            struct elemento y = POP();
            struct elemento x = POP();
            PUSH(operador(x , y,'-'));
        }
        else if (strcmp(token, ")") == 0)
        {
            struct elemento x = POP();
            long l=atol(x.valor);
            sprintf(x.valor,"%ld",++l);
            PUSH(x);
        }
        else if (strcmp(token, "(") == 0)
        {
            struct elemento x = POP();
            long l=atol(x.valor);
            sprintf(x.valor,"%ld",--l);
            PUSH(x);
        }
        else if (strcmp(token, "%") == 0)
        {
            struct elemento y = POP();
            struct elemento x = POP();
            PUSH(operador(x , y,'%'));
        }
        else if (strcmp(token, "#") == 0)
        {
            struct elemento y = POP();
            struct elemento x = POP();
            PUSH(operador(x , y,'#'));
        }
        else if (strcmp(token, "&") == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(operador(x , y,'&'));
        }
        else if (strcmp(token, "|") == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(operador(x , y,'|'));
        }
        else if (strcmp(token, "^") == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(operador(x , y,'^'));
        }
        else if (strcmp(token, "~") == 0)
        {
            struct elemento x = POP();
            long l=atol(x.valor);
            l=~l;
            sprintf(x.valor,"%ld",l);
            PUSH(x);
        }
        else if (strcmp(token, "_") == 0)
        {
            struct elemento x = POP();
            PUSH(x);
            PUSH(x);
        }
        else if (strcmp(token, ";") == 0)
        {
            struct elemento x = POP();
        }
        else if (strcmp(token, "\\" ) == 0)
        {
            struct elemento x = POP();
            struct elemento y = POP();
            PUSH(x);
            PUSH(y);
        }
        else if (strcmp(token, "c" ) == 0)
        {
            struct elemento x = POP();
            x.valor[0]=atoi(x.valor);
            x.valor[1]=0;
            x.tipo=T_string;
            PUSH(x);
        }  
printf("STACK:");
 PRINT_STACK_DEBUG();

    }

    printf("STACK FINAL:");
    PRINT_STACK();
}

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um inteiro long, cujo resultado é o valor no topo da Stack.
 */
struct elemento POP()
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
void PUSH(struct elemento val_i)
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
        printf("%s",stack[i].valor);
    }
    printf("\n");
}

void PRINT_STACK_DEBUG()
{
    for (int i = 0; i <= top; i++)
    {
        printf("%d %s " ,stack[i].tipo,stack[i].valor);
    }
    printf("\n");
}

double convertToDouble(struct elemento x)
{
    double ret;

    ret=0.0;
    if (x.tipo == T_int || x.tipo == T_long || x.tipo == T_double || x.tipo == T_float)
    {
        //no campo valor temos algo como "200", "323.2" ..
        ret=strtod(x.valor,NULL);
    }
    return ret;

}


struct elemento operador (struct elemento x,struct elemento y,char op) 
{
    double dx, dy,dres;

    dx=convertToDouble(x);
    dy=convertToDouble(y);

    if (op == '*')
    {
        dres=dx*dy;
    }
    else if (op == '+')
    {
        dres=dx+dy;
    }
    else if (op == '-')
    {
        dres=dx-dy;
    }
    else if (op == '/')
    {
        dres=dx/dy;
    }
    else if (op == '#')
    {
        dres=pow(dx,dy);
    }
    else if (op == '%')
    {
        dres=(long)dx % (long)dy;
    }
    else if (op == '&')
    {
        dres=(long)dx & (long)dy;
    }
    else if (op == '|')
    {
        dres=(long)dx |(long)dy;
    }
    else if (op == '^')
    {
        dres=(long)dx ^ (long)dy;
    }
    struct elemento val;
    val.tipo = x.tipo;
    if (val.tipo==T_int)
        sprintf(val.valor,"%d",(int)dres);
    else if (val.tipo==T_long)
        sprintf(val.valor,"%ld",(long)dres);
    else if (val.tipo==T_float)
        sprintf(val.valor,"%f",(float)dres);
    else if (val.tipo==T_double)
        sprintf(val.valor,"%lf",(double)dres);
              
    return val;


}

