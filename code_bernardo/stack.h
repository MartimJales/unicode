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

enum stack_type
{
    T_int,
    T_char,
    T_float,
    T_long,
    T_double,
    T_string,
    T_array,
    T_block
};

struct elemento
{
    enum stack_type tipo;
    union
    {
        char val_c;
        char *val_s;
        int val_i;
        long val_l;
        float val_f;
        double val_d;
        struct stack *val_p;
        char *val_b; 

    } data;
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
    int index;                /**< Representa o índice da variável **/
    struct elemento elemento; /**< Representa o conteúdo da variável **/
};

typedef struct stack *Stack;

struct stack
{
    int top;
    int capacity;
    struct elemento array[20000];
    struct var *vars;
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
 * @param ptr_vars (apontador para o array das variáveis)
 */
void initStack(struct stack *ptr_STACK, struct var *ptr_vars);

// Funções que faltam comentar
/*
void print_array(struct array *array);

void initArray(struct array *array);

void dupArray(struct array *s);

void pushArray(struct array *arr, struct elemento x);
*/

void parse_array(char *line, struct stack *ptr_STACK);

void PRINT_ARRAY(struct stack *stack);