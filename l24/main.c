#include "rpn.h"
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

int main() {

    char str[256];
    fgets(str, sizeof(str), stdin);

    Vector post = to_rpn(str);
    vector_print(&post);

    // vector_create(&post);
    // vector_copy(&post, &to_rpn(str));
    
    Tree *root = NULL;
    tree_create(&root, &post);

    printf("Expression tree:\n");
    tree_print(root, 0);

   

    printf("Resulting expression:\n");
    tree_infix(root);
    printf("\n");

    printf("-------\n");
    tree_transform(&root);
    printf("Expression tree:\n");
    tree_print(root, 0);


    printf("Resulting expression:\n");
    tree_infix(root);
    printf("\n");


    vector_destroy(&post);

    return 0;
}
