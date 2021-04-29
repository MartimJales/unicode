#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>


int isDelim(char c,char *delim)
{
    int bRet=0;

    for(int i=0;delim[i];i++)
    {
        if (delim[i]==c)
            bRet=1;
    }
    return bRet;
}

// verifica se é delimitador

int isLim (char token)
{
    if (token == ' ' ||token == '\n' ||token == '\t')
    {
        return 1;
    } 
    else return 0;
}



// número de delimitadores seguidos

char *cleanLim(char line[]){
    int i,j;
    for (i=0; line[i] != '\0'; i++){
        if(isLim(line[i]) && (line[i+1] == line[i])){
            for (j=i; line[j] != '\0'; j++){
                line[j] = line[j+1];
            }
            line[j]= '\0';
            i--;
        }
    }
    return line;

}



char * get_token(char *delim, char *line,char **rest)
{
    char *pRet=NULL;
    int i,bTratado=0;
    int iToken=0;

    //printf("get_token('%s' ###  %s  ###)\n",delim,line);

    //printf("-- %c %d --\n",line[0],isDelim(line[0],delim));

    for(i=0;line[i] && isDelim(line[i],delim)==0 && bTratado==0 ;i++)
    {
        if (line[i]=='[')
        {
            int nParentesis=1;
            int j;
           
            for(j=1;nParentesis>0 && line[i+j];j++)
            {
                if (line[i+j]==']')
                    nParentesis--;
                if (line[i+j]=='[')
                    nParentesis++;        
            }
            if (nParentesis>0)
            {
                printf("Falta ]");
            }
            else
            {
               line[i+j]=0;
               *rest=line+i+j+1;
               bTratado=1;
         
            }
        }
        if (line[i]=='"')
        {
            int nAspas=1;
            int j;
           
            for(j=1;nAspas>0 && line[i+j];j++)
            {
                if (line[i+j]=='"' )
                    nAspas--;      
            }
            if (nAspas>0)
            {
                printf("Falta Fechar Aspas");
            }
            else
            {
               line[i+j]=0;
               *rest=line+i+j+1;
               bTratado=1;
            }
        }
    }

    if(bTratado==0)
    {
        if (isDelim(line[i],delim))
        {
                line[i]=0;
                *rest=line+i+1; // problema está aqui
        }
        else  
        {
            *rest=line+i;
        }
    }
    return line;
}


void main()
{
    char line[500];
    char delimitadores[10];
    char *token;
    char *resto;

    strcpy(delimitadores," \n\t");
    strcpy(line,"1402 2 [ 1 3 4 ] 7 8 9");
    



    for(token=get_token(delimitadores,cleanLim(line), &resto);strcmp(token,"")!=0;token=get_token(delimitadores, resto, &resto))
    {
        printf("%s\n",token);

    }
}