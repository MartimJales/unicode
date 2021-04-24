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
#define T_int 1
#define T_char 2
#define T_float 3
#define T_long 4
#define T_double 5
#define T_string 6
/**
 * \brief Struct elemento
 * 
 * com um inteiro referente ao tipo, e uma string que armazena o valor do mesmo.
 * 
 */
struct elemento
{
    int tipo;
    char valor[100];
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
    int index;
    struct elemento elemento;
};

/**
 * \brief Struct stack
 * 
 * com um inteiro referente ao topo da stack. Um array de elementos referente à stack.
 * 
 */
struct stack
{
    int top;
    struct elemento array[100];
    struct var vars[26];
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

void initStack(struct stack *ptr_STACK);