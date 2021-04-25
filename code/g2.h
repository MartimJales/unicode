/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

/**
 * \brief Função dollarfunction do programa
 * 
 * recebe como parâmetros um apontador para a struct stack e uma variável i
 * e devolve o valor apontado para esse índice.
 * 
 * @param stack
 * @param i (índice)
 */
void dollarfunction(struct stack *stack);

/**
 * \brief Função maths do programa
 * 
 * efetua o cálculo das operações aritméticas.
 * 
 * @param ptr_STACK
 * @param token
 */
void maths(struct stack *ptr_STACK, char *token);

/**
 * \brief Função manstack do programa
 * 
 * efetua o cálculo das operações para manipulação da Stack.
 * 
 * @param ptr_STACK
 * @param token
 */
void manstack(struct stack *ptr_STACK, char *token);

/**
 * \brief Função conversion do programa
 * 
 *  efetua a conversão dos elementos da Stack para um dado tipo.
 * 
 * @param ptr_STACK
 * @param token
 */
void conversion(struct stack *ptr_STACK, char *token);

/**
 * \brief Função inoutput do programa
 * 
 * é responsável pelas ações de in/output.
 * 
 * @param ptr_STACK
 * @param token
 */
void inoutput(struct stack *ptr_STACK, char *token);

/**
 * \brief Função logic do programa
 * 
 * é responsável pelas ações de lógica e condições.
 * 
 * @param ptr_STACK
 * @param token
 */
void logic(struct stack *ptr_STACK, char *token);

void double_top(struct stack *ptr_STACK);

void switch_top(struct stack *ptr_STACK);

void rotate_elem(struct stack *ptr_STACK);

void convert_i(struct stack *ptr_STACK);

void convert_f(struct stack *ptr_STACK);

void convert_c(struct stack *ptr_STACK);

void convert_s(struct stack *ptr_STACK);

void read_line(struct stack *ptr_STACK);

void decrement(struct stack *ptr_STACK);

void increment(struct stack *ptr_STACK);
void complement(struct stack *ptr_STACK);

void call_operator(struct stack *ptr_STACK, char *token);