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
 * \brief Função filter do programa
 * 
 * recebe um token e devolve o número correspondente ao conjunto de operações onde o mesmo pertence.
 *
 * 
 * @param token 
 * @param array
 * 
 * @returns Um inteiro 
 */
int filter(char *token, int array);

/**
 * \brief Função put_token do programa
 * 
 * recebe um token, um apontador para o resto da função e outro apontador para a stack.
 * Irá colocar o token respetivo a um elemento na stack.
 *
 * @param resto
 * @param token
 * @param val_tipo 
 */
void put_token(struct stack *ptr_STACK, int val_tipo, char *token);

/**
 * \brief Função go_filter do programa
 * 
 * verifica o nosso token e seleciona a função auxiliar correspondente à operação
 * desejada.
 *
 * @param token
 * @param val_tipo 
 */
void go_filter(struct stack *ptr_STACK, char *token);

char *get_token(char *delim, char *line, char **rest);
void separa_array(struct stack *ptr_STACK, char *token);

void put_array(struct stack *ptr_STACK, char *token);
void pinta_array(char **token, char *line);

int check_array(struct stack *ptr_STACK, char *token);

void go_filter_array(struct stack *ptr_STACK, char *token);
int check_array(struct stack *ptr_STACK, char *token);
void check_soma_array(struct stack *ptr_STACK, char *token);
void check_all_array(struct stack *ptr_STACK, char *token);
