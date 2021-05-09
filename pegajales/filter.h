/**
 * @file Ficheiro que contém as funçẽs relativas ao filter da Stack
 */

int filter(char *token);

void poli_filter(struct stack *ptr_STACK, char *token);

void manhosos_filter(struct stack *ptr_STACK, char *token);

int isnumber(struct stack *ptr_STACK);

int haveonearray(struct stack *ptr_STACK);

int haveonestring(struct stack *ptr_STACK);

int onlynumber(struct stack *ptr_STACK);

int onlyarray(struct stack *ptr_STACK);
int onlystring(struct stack *ptr_STACK);
int onlychar(struct stack *ptr_STACK);
int secondarray(struct stack *ptr_STACK);
int secondstring(struct stack *ptr_STACK);
int stringnumber(struct stack *ptr_STACK);
int equal_type(struct stack *ptr_STACK);
int onlyblock(struct stack *ptr_STACK);
void percentagem_function(struct stack *ptr_STACK);
