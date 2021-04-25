/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

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
 */
void parse(char *line);

/**
 * \brief Função check_type do programa
 * 
 * recebe um token, um apontador para o resto da função e outro apontador para o tipo desse token.
 * Irá verificar o tipo correspondente ao token e atualizar a stack com o elemento correspondente.
 *
 * @param resto
 * @param token
 * @param val_tipo 
 */
void check_type(char **resto, char **token, int *val_tipo);

/**
 * \brief Função push_token
 * 
 * é uma função auxiliar nos casos em que o token representa um elemento
 * e não temos que fazer nenhuma operação ela coloca na Stack o mesmo.
 * 
 * @param val_tipo (Tipo do elemento)
 * @param token (Token que representa o elemento)
 * @param ptr_STACK (Ponteiro para a Stack)
 * 
 */
void token_push(char *token, int val_tipo, struct stack *ptr_STACK);

/**
 * \brief Função go_filter
 * 
 * é uma função auxiliar que recebe um token e um apontador para a Stack e verifica 
 * para que função auxiliar é que a operação é suposto continuar consoante 
 * o resultado da função filter. 
 * 
 * @param ptr_STACK
 * @param token
 */
void go_filter(struct stack *ptr_STACK, char *token);

/**
 * \brief Função filter do programa
 * 
 * recebe um token e devolve o número correspondente ao conjunto de operações onde o mesmo pertence.
 *
 * 
 * @param token 
 * 
 * @returns Um inteiro 
 */
int filter(char *token);
