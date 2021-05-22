#include "rpn.h"
#include <string.h>

bool delim(char c) {
    return c == ' ' || c == '\n';
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^';
}


int op_priority(char c) {
    switch (c)
    {
        case '(': return 0;
        case ')': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        case '^': return 4;
        
        default: return -1;
    }
}


Vector to_rpn(char * str) {
    Vector ops;
    vector_create(&ops);
    char res[256];
    Vector res_vector;
    vector_create(&res_vector);
    int k = 0, point = 0;
    while (str[k] != '\0') {
        if (delim(str[k])) {
            k++;
            continue;
        }
        if (str[k] == ')') {
            while (vector_back(&ops).item.data.operator_name != '(') {
                VItem tmp = vector_back(&ops);
                push_back(&res_vector, tmp);
                pop_back(&ops);
            }
            pop_back(&ops);
        }

        bool unary = false;

        if (str[k] == '+' || str[k] == '-') {

            int prev = k - 1;

            while (delim(str[prev]) && prev != 0) {
                prev--;
            }

            int next = k + 1;

            while (delim(str[prev]) && str[next] != '\0') {
                next++;
            }

            if ((k == 0) || (k != 0 && is_op(str[prev]) && str[prev] != ')')) {
                unary = true;
                // if (str[next] != '(')
                //     k++;
            }
        }

        if (!is_op(str[k])) {
            point = 0;
            if (unary) {
                res[point++] = str[k-1];
            }
            while (!is_op(str[k]) && !delim(str[k]) && str[k] != '\0') {
                res[point++] = str[k++];
            }
            res[point] = '\0';
            VItem tmp;
            tmp.item.type = VARIABLE;
            strcpy(tmp.item.data.variable_name, res);
            // for (int i = 0; res[i - 1] != '\0'; ++i) {
            //     tmp.var[i] = res[i];
            // }
            // tmp.var[point] = '\0';
            push_back(&res_vector, tmp);
            continue;
        }

        if (str[k] == '(') {
            VItem tmp;
            tmp.item.type = OPERATOR;
            tmp.item.data.operator_name = str[k];
            push_back(&ops, tmp);
        }

        if (is_op(str[k]) && str[k] != '(' && str[k] != ')') {
            if (vector_is_empty(&ops)) {
                VItem tmp;
                if (unary) {
                    tmp.item.type = UNARY_OPERATOR;
                } else {
                    tmp.item.type = OPERATOR;
                }
                tmp.item.data.operator_name = str[k];
                push_back(&ops, tmp);
            } else {
                if (op_priority(vector_back(&ops).item.data.operator_name) < op_priority(str[k])) {
                    VItem tmp;
                    if (unary) {
                        tmp.item.type = UNARY_OPERATOR;
                    } else {
                        tmp.item.type = OPERATOR;
                    }
                    tmp.item.data.operator_name = str[k];
                    push_back(&ops, tmp);
                } else {
                    while (!vector_is_empty(&ops) && ((str[k] != '^' && op_priority(vector_back(&ops).item.data.operator_name) >= op_priority(str[k])) ||
                     (str[k] == '^' && op_priority(vector_back(&ops).item.data.operator_name) > op_priority(str[k])))) {
                        VItem tmp = vector_back(&ops);
                        push_back(&res_vector, tmp);
                        pop_back(&ops);
                    }
                    VItem tmp;
                    if (unary) {
                        tmp.item.type = UNARY_OPERATOR;
                    } else {
                        tmp.item.type = OPERATOR;
                    }
                    tmp.item.data.operator_name = str[k];
                    push_back(&ops, tmp);
                }
            }
        }
        k++;
    }

    while(!vector_is_empty(&ops)) {
        VItem tmp = vector_back(&ops);
        push_back(&res_vector, tmp);
        pop_back(&ops);
    }
    // res[point] = '\0';
    vector_destroy(&ops);
    return res_vector;
}
