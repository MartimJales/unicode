#include <stdio.h>
#include <stdlib.h>

enum stack_type
{
    T_int,
    T_char,
    T_float,
    T_long,
    T_double,
    T_string,
    T_array
};

struct elemento
{
    enum stack_type tipo;
    union
    {
        char val_c;
        char val_s[200];
        int val_i;
        long val_l;
        float val_f;
        double val_d;
        struct array *val_p;
    } data;
};

/**
 * \brief Struct var
 * 
 * com um char referente à variável que estamos a utilizar
 * e um elemento que a mesma representa.
 * 
 */
struct array
{
    int index;
    int capacity;
    struct elemento *values;
};

void dupArray(struct array *s)
{
    int r = 0, i;
    struct elemento *t = malloc(2 * s->capacity * sizeof(struct elemento));

    if (t == NULL)
        r = 1;
    else
    {
        for (i = 0; i < s->capacity; i++)
            t[i] = s->values[i];
        free(s->values);
        s->values = t;
        s->capacity *= 2;
    }
}

void pushArray(struct array *cona, struct elemento x)
{
    int r = 0;
    printf(">>> COMEÇOU O PUSH <<<\n");
    printf("index  push : %d capacity = %d \n", cona->index, cona->capacity);
    if (cona->index == cona->capacity)
    {
        dupArray(cona);
    }
    if (!r)
    {
        cona->values[cona->index] = x;
        cona->index++;
    }

    printf("index depois : %d capacity = %d \n", cona->index, cona->capacity);
}

void print_array(struct array *array)
{
    int i;
    for (i = 0; i < array->index; i++)
    {
        switch (array->values[i].tipo)
        {
        case T_int:
            printf("%d", array->values[i].data.val_i);
            break;
        case T_long:
            printf("%ld", array->values[i].data.val_l);
            break;
        case T_float:
            printf("%.6g", array->values[i].data.val_f);
            break;
        case T_double:
            //  printf("double: ");
            printf("%.6g", array->values[i].data.val_d);
            break;
        case T_char:
            //  printf("char: ");
            printf("%c", array->values[i].data.val_c);
            break;
        case T_string:
            //  printf("string: ");
            printf("%s", array->values[i].data.val_s);
            break;
        case T_array:
            //  printf("array: ");
            print_array(array->values[i].data.val_p);
            break;
        default: //falta as strings e os arrays
            break;
        }
        putchar('\n');
    }
}

/*
void free_array(struct array *array)
{
    free(array->values);
}
*/

void initArray(struct array *array)
{
    printf("Caiu no inicio \n");
    array->index = 0;
    array->capacity = 10;
    array->values = malloc(array->capacity * sizeof(struct elemento));
}

int main()
{
    struct elemento array;
    array.tipo = T_array;
    struct array *new = malloc(sizeof(struct array));
    array.data.val_p = new;
    struct array *ptr_array = (array.data.val_p);
    struct elemento x;
    x.tipo = T_int;
    x.data.val_i = 3;
    initArray(ptr_array);
    pushArray(ptr_array, x);
    x.tipo = T_int;
    x.data.val_i = 4;
    pushArray(ptr_array, x);
    print_array(ptr_array);
    printf("Caiu aqte aqui!");
    free(ptr_array);
}
