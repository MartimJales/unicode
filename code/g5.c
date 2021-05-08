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
    printf("entrei na criablock\n");
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
    printf("o tipo do q pushei é : %d", x.tipo);
}

void tilfunction(struct stack *ptr_STACK)
{

    //char *snum;

    printf("entrou aqui \n");

    char s[200];

    int num = 321;
    char snum[200] = {0};

    // convert 123 to string [buf]
    //itoa(num, snum, 10);

    // print our string
    //printf("%s\n", snum);

    struct elemento x = POP(ptr_STACK);
    struct elemento y = POP(ptr_STACK);

    if (y.tipo == T_int)
    {
        // s[0]=x.data.val_i;
        printf("entrou no int\n ");
        strcat(s, snum);
        //sprintf (s,"%d",y.data.val_i);
    }
    else if (y.tipo == T_long)
    {
        //s[0]=x.data.val_l;
        printf("entrou no long\n ");
        sprintf(s, "%ld", y.data.val_l);
    }
    else if (y.tipo == T_float)
    {
        //s[0]=x.data.val_f;
        printf("entrou no float \n ");
        sprintf(s, "%.2f", y.data.val_f);
    }
    else if (y.tipo == T_double)
    {
        // s[0]=x.data.val_d;
        printf("entrou no double \n ");
        sprintf(s, "%.2f", y.data.val_d);
    }
    /*
else if (x.tipo == T_string) {
        s[0]=x.data.val_s;

   // sprintf (s,"%f",x.data.val_d);
}
*/
    /*
else if (x.tipo == T_char) {
       s[0]=x.data.val_c;

    //sprintf (s,"%c",x.data.val_c);
}*/

    s[20] = '\0';
    printf("%s", s);
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
