/**
 * @file Ficheiro que contém a função as funções auxiliares do programa
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
 * \brief Struct stack
 * 
 * com um inteiro referente ao topo da stack. Um array de elementos referente à stack.
 * 
 */
struct stack
{
    int top;
    struct elemento array[100];
};

/**
 * \brief Função operador
 * 
 * É uma função auxiliar que recebe dois elementos e um apontador para o operando 
 * e calcula o resultado de ambos de acordo com o operando recebido.
 * 
 * É, de seguida, definida uma variável cuja constante associada à componente tipo será a mesma que a dos elementos recebidos
 * quando estes têm o mesmo tipo, caso contrário, é declarada como tendo um tipo constante T_int.
 * Posteriormente, de acordo com a constante da sua componente tipo a componente valor será igual ao valor da variável dres
 * 
 * @param x 
 * @param y
 * @param op (operando)
 * 
 * @returns Um struct elemento val
 */
struct elemento operador(struct elemento x, struct elemento y, char *op);

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
 * \brief Função dollarfunction do programa
 * 
 * recebe como parâmetros um apontador para a struct stack e uma variável i
 * e devolve o valor apontado para esse índice.
 * 
 * @param stack
 * @param i (índice)
 * 
 * @returns Um elemento da Stack.
 */
struct elemento dollarfunction(struct stack *stack, int i);

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

// falta comentar estas meninas

void not(struct stack * ptr_STACK);
void ifthenelse(struct stack *ptr_STACK);
void equal(struct stack *ptr_STACK);
void smaller(struct stack *ptr_STACK);
void greater(struct stack *ptr_STACK);