
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

struct elemento operador (struct elemento x,struct elemento y,char op) ;

void parse(char *line);
void PUSH(struct elemento val);
struct elemento POP();
void PRINT_STACK();
void PRINT_STACK_DEBUG();
