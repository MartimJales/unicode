/**
 * @file Ficheiro que contém as funçẽs relativas ao parse da Stack
 */

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
 * \brief Função secondoperador
 * 
 * É uma função auxiliar que recebe dois elementos e o resultado da operação efetuada 
 * pela função anterior do operador.
 * 
 * É definida uma variável cuja constante associada à componente tipo será a mesma que a dos elementos recebidos
 * quando estes têm o mesmo tipo, caso contrário, é declarada como tendo um tipo constante T_int.
 * Posteriormente, de acordo com a constante da sua componente tipo a componente valor será igual ao valor da variável dres
 * 
 * @param x 
 * @param y
 * @param dres (resultado da operação em operdador)
 * 
 * @returns Um struct elemento val
 */
struct elemento secondoperador(struct elemento x, struct elemento y, float dres);

/**
 * \brief Função convertToDouble do programa
 * 
 * é responsável por converter um elemento caso seja do tipo longo 
 * ou double ou inteiro ou float converte para double para
 * posteriormente serem feitas as opeações
 * 
 * @param xs
 * 
 * @returns Um float
 */
float convertToDouble(struct elemento x);

/**
 * \brief Função secondoperador
 * 
 * É uma função auxiliar para aplicar as operações com os elementos com tipo long.
 * 
 * Retorna um double que representa o resultado da operaçõa desejada.
 * 
 * @param dx 
 * @param dy
 * @param op (operação para fazer)
 * 
 * @returns double dres (Resultado)
 */
double operator_long(double dx, double dy, char *op);