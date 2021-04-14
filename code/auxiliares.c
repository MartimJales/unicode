
/*   Este ficheiro contém as funções auxiliares, junto com os comentários, e contém
os comentários das funções principais que faltavam comentar no ficheiro parse.c. 

*/

// "l" ---------------------------------------

/**
 * \brief Função convToLong
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num long. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToLong(struct elemento x)
{
    assert(fgets(x.valor, 100, stdin) != NULL);
    x.tipo = T_string;
    PUSH(x);
}

//"i" -----------------------------------------

/**
 * \brief Função convToInt
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num integer. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToInt(struct elemento x)
{
    x.tipo = T_int;
    PUSH(x);
}

//"f" --------------------------------------------

/**
 * \brief Função convToFloat
 * 
 * É uma função auxiliar que converte o elemento do parâmentro num float. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToFloat(struct elemento x)
{
    x.tipo = T_float;
    PUSH(x);
}

//")" ----------------------------------------------

/**
 * \brief Função increment
 * 
 * É uma função auxiliar que incrementa o elemento que recebe como parâmetro. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento increment(struct elemento x)
{
    //printf("antes %s \n" ,x.valor);
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", ++l);

    // printf("depois %s \n" ,x.valor);
    PUSH(x);
}

//"(" -----------------------------------------------

/**
 * \brief Função decrement
 * 
 * É uma função auxiliar que decrementa o elemento que recebe como parâmetro. 
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento decrement(struct elemento x)
{
    long l = atol(x.valor);
    sprintf(x.valor, "%ld", --l);
    PUSH(x);
}

//"~" -----------------------------------------------

struct elemento complement(struct elemento x)
{
    long l = atol(x.valor);
    l = ~l;
    sprintf(x.valor, "%ld", l);
    PUSH(x);
}

// "_" ------------------------------------------------

/**
 * \brief Função cpyStackTop
 * 
 * É uma função auxiliar que copia para o topo da stack o elemento que já tem no topo da stack.
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento cpyStackTop(struct elemento x)
{
    PUSH(x);
    PUSH(x);
}

//";"------------------------------------------------

/**
 * \brief Função rmStackTop
 * 
 * É uma função auxiliar que retira da stack o elemento do topo.
 * 
 * @returns struct elemento.
 */
struct elemento rmStackTop()
{
    POP();
}

//"\\" ---------------------------------------------

/**
 * \brief Função swapStackTop
 * 
 * É uma função auxiliar que troca de posições na stack os dois elementos do topo.
 * 
 * @param x 
 * @param y
 * 
 * 
 * @returns struct elemento.
 */
struct elemento swapStackTop(struct elemento x, struct elemento y)
{
    PUSH(x);
    PUSH(y);
}

//"c" -------------------------------------------

/**
 * \brief Função convToChar
 * 
 * É uma função auxiliar que converte para char o elemento do topo da stack.
 * 
 * @param x 
 * 
 * @returns struct elemento.
 */
struct elemento convToChar(struct elemento x)
{
    x.tipo = T_char;
    PUSH(x);
}

//"@" --------------------------------------------

/**
 * \brief Função convToChar
 * 
 * É uma função auxiliar que muda de posições os três elementos do topo da stack, isto é,
 * o elemento na no topo desce para a posição abaixo, o elemento, inicialmente, a seguir ao topo 
 * desce para a posição seguinte e o elemento que se encontrava a na 3ª posição a contar do topo
 * vem para o topo da stack.
 * 
 * @param x
 * @param y
 * @param z
 *  
 * @returns struct elemento.
 */
struct elemento rot_three_elem_StackTop(struct elemento x, struct elemento y, struct elemento z)
{
    PUSH(y);
    PUSH(x);
    PUSH(z);
}

//"$" --------------------------------------------

/**
 * \brief Função cpy_N_elem_of_Stack_ToTop
 * 
 * É uma função auxiliar que procura o n-ésimo (dado por parâmetro) elemento da stack a contar a partir do topo
 * e copia-o para o topo da stack.
 * 
 * @param x
 * 
 * @returns struct elemento.
 */
struct elemento cpy_N_elem_of_Stack_ToTop(struct elemento x)
{
    int i = atoi(x.valor);
    struct elemento y = stack[top - i];
    PUSH(y);
}

// --------------- convertToDouble ------------------- //
/**
 * \brief Função convertToDouble
 * 
 * É uma função auxiliar que recebe um elemento e converte-o para Double
 * 
 * @param x 
 * 
 * @returns double, representado pela variável ret.
 */

// --------------- operador ------------------- //
/**
 * \brief Função operador
 * 
 * É uma função auxiliar que recebe dois elementos e um operando e calcula o resultado de ambos de acordo 
 * com o operando recebido.
 * É definida uma variável cuja constante associada à componente tipo será a mesmo que a dos elementos recebidos
 * quando estes têm o mesmo tipo, caso contrário, é declarada como tendo um tipo constante T_int.
 * Posteriormente, de acordo com a constante da sua componente tipo a componente valor será igual ao valor da variável dres
 * 
 * @param x 
 * @param y
 * @param op
 * 
 * @returns struct elemento, representado pela variável val.
 */
