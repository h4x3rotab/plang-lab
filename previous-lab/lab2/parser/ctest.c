#include <stdio.h>
#include <stdlib.h>

#include "ast.h"


int main()
{
    ast* a = mk_int(123);
    ast* b = mk_str("ha");

    ast_list* lst = conslist(2, a, b);

    ast* node = mk_node(body_node, lst);

    print_ast_list(lst);
    print_ast(node);


    return 0;
}
