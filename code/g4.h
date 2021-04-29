/**
 * @file Ficheiro que contém as funçẽs relativas ao guião 4
 */

/**
 * \brief Função concatenarray do programa
 * 
 * que faz o pop dos dois arrays no topo da Stack e concatena-os.
 * 
 * @param ptr_STACK Apontador para a Stack
 */
void concatenarray(struct stack *ptr_STACK);

/**
 * \brief Função manaarray do programa.
 * 
 * ao receber o token aplica a função que se destina a cada token.
 * 
 * @param ptr_STACK
 * @param token
 */
void manarray(struct stack *ptr_STACK, char *token);

/**
 * \brief Função concatenarray do programa
 * 
 * que faz o pop dos dois arrays no topo da Stack e concatena-os.
 * 
 * @param ptr_STACK Apontador para a Stack
 */

void parse_array(char *line, struct stack *ptr_STACK);

/**
 * \brief Função empurra_array do programa
 * 
 * esta função faz POP do topo da Stack e, depois de colocar o tipo desse elemento como array, 
 * invoca a função parse_array para tratar esse array internamente.
 * 
 * @param ptr_STACK 
 */
void empurraarray(struct stack *ptr_STACK);

/**
 * \brief Função repetearray do programa
 * 
 * faz POP do topo da stack e converte esse valor para um longo, 
 * posteriormente, faz POP de um outro elemento (que seja do tipo array)
 * e repete-o tantas vezes quantas o valor do elemento 
 * convertido para long.
 * 
 * @param ptr_STACK 
 */
void repetearray(struct stack *ptr_STACK);

/**
 * \brief Função tamanho_range do programa
 * 
 * descobre a quantidade de elementos presentes no array e,
 * após isto faz PUSH deste valor para o topo da Stack.
 * 
 * @param ptr_STACK 
 */
void tamanho_range(struct stack *ptr_STACK);

/**
 * \brief Função buscavalindice do programa
 * 
 * faz POP do elemento no topo da Stack, depois faz POP do segundo elemento no topo da Stack (do tipo array)
 * e procura no array o elemento com o indice do valor do primeiro POP.
 * 
 * @param ptr_STACK
 */
void buscavalindice(struct stack *ptr_STACK)