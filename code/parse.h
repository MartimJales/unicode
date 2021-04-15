#define T_int 1
#define T_char 2
#define T_float 3
#define T_long 4
#define T_double 5
#define T_string 6

struct elemento
{
    int tipo;
    char valor[100];
};

struct stack
{
    int top;
    struct elemento array[100];
};

struct elemento operador(struct elemento x, struct elemento y, char *op);

void parse(char *line);
void PUSH(struct stack *stack, struct elemento n);
struct elemento POP(struct stack *stack);
void PRINT_STACK(struct stack *stack);
struct elemento dollarfunction(struct stack *stack, int i);

int filter(char *token);

void maths(struct stack *ptr_STACK, char *token);
void manstack(struct stack *ptr_STACK, char *token);
void conversion(struct stack *ptr_STACK, char *token);
void inoutput(struct stack *ptr_STACK, char *token);