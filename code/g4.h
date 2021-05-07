

void concatenarray(struct stack *ptr_STACK);

void manarray(struct stack *ptr_STACK, char *token);
void parse_array(char *line, struct stack *ptr_STACK);
void empurraarray(struct stack *ptr_STACK);
void repetearray(struct stack *ptr_STACK);
void tamanho_array(struct stack *ptr_STACK);

void left_elementos(struct stack *ptr_STACK);
void right_elementos(struct stack *ptr_STACK);

void range_array(struct stack *ptr_STACK);

void left_parentesis(struct stack *ptr_STACK);
void right_parentesis(struct stack *ptr_STACK);

void buscavalindice(struct stack *ptr_STACK);

void criaStr(struct stack *ptr_STACK, char *token);

void concaString(struct stack *ptr_STACK);

void repeteStr(struct stack *ptr_STACK);

void tamanho_str(struct stack *ptr_STACK, struct elemento x);
void val_index_Str(struct stack *ptr_STACK, struct elemento x);

void catch_elem_Str(struct stack *ptr_STACK);
void catch_ultimos_Str(struct stack *ptr_STACK);

void delete_fst_Str(struct stack *ptr_STACK);
void delete_snd_Str(struct stack *ptr_STACK);
void find_subStr(struct stack *ptr_STACK);
void read_All_Str(struct elemento *ptr_STACK, char *line);

void sub_String(struct stack *ptr_STACK);
void div_WhiteS_Str(struct stack *ptr_STACK);

void div_newLines_Str(struct stack *ptr_STACK);

void mystrcat(struct elemento s1, struct elemento s2, struct stack *ptr_STACK);
void mystrcat2(struct elemento s1, struct elemento s2, struct stack *ptr_STACK);
void mystrcat3(struct elemento s1, struct elemento s2, struct stack *ptr_STACK);
void mystrcat4(char s1[], char s2[]);

int compareStrandSub(char str[], char substr[], int N, int i);
void pinta_a_linda(char aux[], char main[], int j, int i);