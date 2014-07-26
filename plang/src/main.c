/********************************************************************************
*
* File: main.c
* Testing the PCAT parser
* Programmer: Leonidas Fegaras, UTA
* Date: 2/3/00
* 
********************************************************************************/

#include "ast.h"
#include <stdio.h>


int lineno = 1;
int columnno = 1;
ast* ast_root = NULL;

extern FILE* yyin;

void yyparse();


int main ( int argc, char* arg[] ) 
{
    if(sizeof(ast_names) / sizeof(char*) != ast_kind_size)
    {
        fprintf(stderr, "neg_exp: %s\n", ast_names[neg_exp]);
        fprintf(stderr, "Fatal error: count of ast_kind (%d) and ast_names (%d) mismatch!\n",
                    (int)ast_kind_size, (int)(sizeof(ast_names) / sizeof(char*)));
        return -1;
    }

    if (argc>1)
        yyin = fopen(arg[1],"r");

    yyparse();

    printf("[END]\n");

    return 0;
}
