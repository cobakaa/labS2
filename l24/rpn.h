#ifndef __RPN_H__
#define __RPN_H__

#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "vector.h"

bool delim(char c);
bool is_op(char c);
int op_priority(char c);
Vector to_rpn(char * str);

#endif