
void criaBlock(struct stack *ptr_STACK, char *token);
void tilfunction(struct stack *ptr_STACK);
char *pinta_block(char *line);
void percentagem_function(struct stack *ptr_STACK);
char *tilfunction2(struct elemento y, char *line, struct stack *array);
void convert_elem_s(struct elemento val);
// void filter_block(struct stack *ptr_STACK);
void convert_arr_string(struct elemento arr, char *s);
void filter_function(struct stack *ptr_STACK);
void fold_function(struct stack *ptr_STACK);
void dollar_block(struct stack *ptr_STACK);

void mergeSort(struct elemento arr[], int l, int r, char *bloco, struct stack *final);
void merge(struct elemento arr[], int l, int m, int r, char *bloco, struct stack *final);
int checka(struct elemento fst, struct elemento snd, char *bloco, struct stack *final);
int comichoes(struct elemento fst, struct elemento snd);