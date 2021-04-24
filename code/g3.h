/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

void ifthenelse(struct stack *ptr_STACK);
void equal(struct stack *ptr_STACK);
void smaller(struct stack *ptr_STACK);
void greater(struct stack *ptr_STACK);
void no(struct stack *ptr_STACK);

void efunction(struct stack *ptr_STACK, char *token);
void esmaller(struct stack *ptr_STACK);
void ebigger(struct stack *ptr_STACK);
void eshortcut(struct stack *ptr_STACK);
void orshortcut(struct stack *ptr_STACK);
void epequeno(struct stack *ptr_STACK);

void variables1(struct stack *ptr_STACK, char *token);
void variables2(struct stack *ptr_STACK, char *token);
