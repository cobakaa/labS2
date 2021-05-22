#include "token.h"
#include <stdio.h>

void token_print(Token *t)
{
    switch (t->type) {
        case FLOAT:
            printf("%g", t->data.value_float);
            break;
        case VARIABLE:
            printf("%s", t->data.variable_name);
            break;
        case UNARY_OPERATOR: case OPERATOR:
            printf("%c", t->data.operator_name);
            break;
    }
}
