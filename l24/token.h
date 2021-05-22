#ifndef __TOKEN_H__
#define __TOKEN_H__


#include <stdbool.h>

typedef enum {
    FLOAT,
    OPERATOR,
    UNARY_OPERATOR,
    VARIABLE
} TokenType;

typedef struct {
    TokenType type;
    union {
        float value_float;
        char  operator_name;
        char  variable_name[256];
    } data;
} Token;

void token_print(Token *t);

#endif