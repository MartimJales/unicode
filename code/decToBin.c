#include <stdio.h>
#include <math.h>
#include <assert.h>



// Função que compara bit a bit o número inserido e devolve um array com 0s e 1s.

void binario (int n,char Str[])
{
int c;

    for (c=0;c<=15;c++)
    {
        if (n & (int) pow(2,c)) Str[15-c]= '1';
        else Str[15-c]= '0';
    }
    Str[16]=0;
}

// se encontrar na mesma posiçao do binario nos dois nr o bit 1, torna a posiçao em 1.

void jales (int n1,int n2)
{
int var = (n1 & n2);
printf ("%d",var);
}

// se encontrar um 1 num dos binarios em comparaçao, torna a posiçao em 1.

void hugo (int n1,int n2)
{
int var = (n1 | n2);
printf ("%d",var);
}

// se encontrar na mesma posiçao do binario nos dois nr o bit 1, torna 1 em 0.

void benny (int n1,int n2)
{
int var = (n1 ^ n2);
printf ("%d",var);
}

// transforma o input no simetrico, em complemento para 2.

void rafinha (int n1)
{
int var = (~ n1);
printf ("%d",var);
}


// Função que recebe um número em decimal e insere-o na função binario
// Para usares o array com o input em binário, basta chamares uma funçao dentro do main e dar lhe como um dos argumentos o arrayBinario.


void main() 
{
int n;
char arrayBinario[17];

scanf ("%d",&n);

    binario (n,arrayBinario);
    printf ("%s\n",arrayBinario);
    // jales (6,5);
    // hugo (6,5);
    // benny (6,5);
    rafinha (-1);
}




