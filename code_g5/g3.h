/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

/**
 * \brief Função ifthenelse do programa
 * 
 * é responsável por testar se o valor lógico do 3º elemento dado pela stack é verdadeiro,se sim devolve o 2º elemento dado pela stack
 * caso contrário devolve o primeiro
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void ifthenelse(struct stack *ptr_STACK);

/**
 * \brief Função equal do programa
 * 
 * é responsável por atribuir valor logico 1 ou 0 se a igualdade se verificar ou não,respetivamente
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void equal(struct stack *ptr_STACK);

/**
 * \brief Função smaller do programa
 * 
 * é responsável por devolver valor logico 1 caso o 2º elemento dado pela stack seja menor  que o primeiro ou 0 caso contrário.
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void smaller(struct stack *ptr_STACK);

/**
 * \brief Função greater do programa
 * 
 * é responsável por devolver valor logico 0 caso o 2º elemento dado pela stack seja menor  que o primeiro ou 1 caso contrário.
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void greater(struct stack *ptr_STACK);

/**
 * \brief Função not do programa
 * 
 * é responsável por atribuir o valor lógico contrário à variável dada pelo topo da stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void no(struct stack *ptr_STACK);

/**
 * \brief Função efunction do programa
 * 
 * é responsável por separar os operadores q têm "e<","e>","e|","e" ou "e&"
 * 
 * @param ptr_STACK (apontador para a stack)
 * @param token (apontador para o token que é resultado da função parser)
 */
void efunction(struct stack *ptr_STACK, char *token);

/**
 * \brief Função esmaller  do programa
 * 
 * é responsável pela operação "e<" que devolve o menor dos dois valores
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void esmaller(struct stack *ptr_STACK);

/**
 * \brief Função ebigger  do programa
 * 
 * é responsável pela operação "e>" que devolve o maior dos dois valores
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void ebigger(struct stack *ptr_STACK);

/**
 * \brief Função eshortcut  do programa
 * 
 * é responsável pela operação "e&" que devolve o maior dos dois valores caso ambos sejam maiores que 0 ,caso algum deles seja 0 ,devolve 0. 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void eshortcut(struct stack *ptr_STACK);

/**
 * \brief Função orshortcut  do programa
 * 
 * é responsável pela operação "e|" que devolve o primeiro valor que aparecer caso ambos sejam diferentes de 0
 * caso algum deles seja 0 devolve o outro 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void orshortcut(struct stack *ptr_STACK);

/**
 * \brief Função epequeno do programa
 * 
 * é responsável pela operação "e" que devolve o menor caso ambos sejam diferentes de 0.
 * caso algum deles seja 0 devolve o outro 
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void epequeno(struct stack *ptr_STACK);

/**
 * \brief Função variables1  do programa
 * 
 * dado uma variável ,coloca essa variável na stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void variables1(struct stack *ptr_STACK, char *token);

/**
 * \brief Função variables2  do programa
 * 
 * caso o input seja N ou S realiza as devidas ações de "\n" ou " " , ou caso seja ":" altera o conteudo da variável
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void variables2(struct stack *ptr_STACK, char *token);

int validade(struct elemento val);