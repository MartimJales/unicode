/**
 * @file Ficheiro que contém as funções realtivas à Stack essenciais 
 * nomeadamente 
 * initStack,
 * PUSH,
 * POP,
 * printSTACK.
 * 
 * Contém também todas as estrusturas criadas para a resolução dos guiões.
 */

/**
 * \brief T_int 1
 * 
 * o nº 1 representa o tipo "int".
 * 
 */
#define T_int 1

/**
 * \brief T_char 2
 * 
 * o nº 2 representa o tipo "char".
 * 
 */
#define T_char 2

/**
 * \brief T_float 3
 * 
 * o nº 3 representa o tipo "float".
 * 
 */
#define T_float 3

/**
 * \brief T_long 4
 * 
 * o nº 4 representa o tipo "long".
 * 
 */
#define T_long 4

/**
 * \brief T_double 5
 * 
 * o nº 5 representa o tipo "double".
 * 
 */
#define T_double 5

/**
 * \brief T_string 6
 * 
 * o nº 6 representa o tipo "string".
 * 
 */
#define T_string 6

/**
 * \brief Struct elemento
 * 
 * com um inteiro referente ao tipo, e uma string que armazena o valor do mesmo.
 * 
 */
struct elemento
{
    int tipo;/**< Representa o tipo do elemento */
    char valor[100];/**< Representa o valor do elemento */
};

/**
 * \brief Struct var
 * 
 * com um char referente à variável que estamos a utilizar
 * e um elemento que a mesma representa.
 * 
 */
struct var
{
    int index;/**< Representa o índice da variável */
    struct elemento elemento;/**< Representa o conteúdo da variável */
};

/** @struct stack
 *  @brief Esta struct representa a stack.
 */
struct stack
{
    int top;/**< Representa a variavél do topo da stack */
    struct elemento array[100];/**< Representa o array de elementos */
    struct var vars[26];/**< Representa as variáveis do programa */
};

/**
 * \brief Função PUSH do programa
 * 
 *que adiciona uma célula à Stack .
 * 
 * @param stack
 * @param n (elemento a adicionar).
 */
void PUSH(struct stack *stack, struct elemento n);

/**
 * \brief Função POP do programa
 * 
 * Função que vai à Stack tirar a última célula.
 * 
 * @returns Um valor elemento .
 */
struct elemento POP(struct stack *stack);

/**
 * \brief Função PRINT_STACK do programa.
 * 
 * Inicia-se um ciclo for, onde uma variável é incializada também,
 * a condição de paragem ocorre se a variável é maior
 * que o topo da da Stack, a cada iteração incrementa-se a variável.
 * 
 * É imprimido o valor da Stack no índice da variável, de acordo
 * com o seu valor a cada iteração.
 * 
 * @param stack
 */
void PRINT_STACK(struct stack *stack);

/**
 * \brief Função initStack  do programa
 * 
 * inicia a stack
 * 
 * @param ptr_STACK (apontador para a stack)
 */
void initStack(struct stack *ptr_STACK);
