/********************************************************************************
*
* File: ast.c
* The abstract syntax trees for the calculator
* Programmer: Leonidas Fegaras, UTA
* Date: 12/17/97
*
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"

const void* comb_loc(const void* locl, const void* locr);

void setloc( ast* tree, const void* loc )
{
    const ast_loc* locptr = (ast_loc*) loc;
    if(tree && locptr) tree->location = *locptr;
}

ast* mk_int ( const void* loc, const long x ) {
  ast* res = (ast*) malloc(sizeof(ast));
  res->tag = int_ast;
  res->info.integer = x;
  setloc(res, loc);
  return res;
};


ast* mk_real ( const void* loc, const double x ) {
  ast* res = (ast*) malloc(sizeof(ast));
  res->tag = real_ast;
  res->info.real = x;
  setloc(res, loc);
  return res;
};


ast* mk_var ( const void* loc, const char* x ) {
  ast* res = (ast*) malloc(sizeof(ast));
  res->tag = var_ast;
  res->info.variable = (char*) malloc(strlen(x)+1);
  strcpy(res->info.variable,x);
  setloc(res, loc);
  return res;
};


ast* mk_str ( const void* loc, const char* x ) {
  ast* res = (ast*) malloc(sizeof(ast));
  res->tag = str_ast;
  res->info.variable = (char*) malloc(strlen(x)+1);
  strcpy(res->info.variable,x);
  setloc(res, loc);
  return res;
};


ast* mk_node (const void* loc, const ast_kind tag, ast_list* args ) 
{
    ast* res = (ast*) malloc(sizeof(ast));
    res->tag = node_ast;
    res->info.node.tag = tag;
    res->info.node.arguments = args;

    const ast_loc* locptr = (ast_loc*) loc;
    if(locptr) res->location = *locptr;

    /*{
        print_ast(res);
        printf("\n");
    }*/

    return res;
};

ast* mk_noder ( const void* locl, const void* locr, const ast_kind tag, ast_list* args )
{
    return mk_node(comb_loc(locl, locr), tag, args);
}

ast_list* cons ( ast* e, ast_list* r ) {
  ast_list* res = (ast_list*) malloc(sizeof(ast_list));
  res->elem = e;
  res->next = r;
  return res;
};


short length ( ast_list* r ) {
  short i = 0;
  for(; r != null; r=r->next) i++;
  return i;
};


ast_list* rev ( ast_list* r, ast_list* s ) {
  if (r == null)
     return s;
  return rev(r->next,cons(r->elem,s));
};


ast_list* reverse ( ast_list* r ) {
  return rev(r,null);
};


void print_ast_list ( ast_list* r ) {
  if (r == null)
     return;
  printf(" ");
  print_ast_internal(r->elem);
  print_ast_list(r->next);
};

static int tabs = 0;
static ast_loc* lastloc = NULL;

void print_ast(ast* x)
{
    tabs = 0;
    lastloc = NULL;
    print_ast_internal(x);
}

void print_ast_internal ( ast* x ) 
{
    if(x)
    {
        switch (x->tag) 
        {
            case int_ast: printf("%ld",x->info.integer); break;
            case real_ast: printf("%lf",x->info.real); break;
            case var_ast: printf("%s",x->info.variable); break;
            case str_ast: printf("\"%s\"",x->info.string); break;
            case node_ast: 
            {
                // deal with indent
                int dtabs = 0;

                if(lastloc && x->location.first_line > lastloc->first_line)
                    dtabs = 1;
                
                lastloc = &x->location;
                tabs += dtabs;

                if(dtabs)
                {
                    printf("\n");
                    for(int i=0; i<tabs; i++)
                        printf("\t");
                }
                
                // print ast
                printf("(%s[%d,%d:%d]",ast_names[x->info.node.tag],
                        x->location.first_line,
                        x->location.first_column, x->location.last_column);
                print_ast_list(x->info.node.arguments);
                printf(")");

                // indent(tail)
                tabs -= dtabs;
                break;
            }
        }
    }
    else printf("(null)");
}


// -------------

static ast_loc comb_loc_result;
const void* comb_loc(const void* locl, const void* locr)
{
    ast_loc ll = *(ast_loc*)locl;
    ast_loc lr = *(ast_loc*)locr;

    comb_loc_result.first_line = ll.first_line;
    comb_loc_result.last_line = lr.last_line;
    comb_loc_result.first_column = ll.first_column;
    comb_loc_result.last_column = lr.last_column;

    return &comb_loc_result;
}

// add
ast* mk_unaryexp ( const void* loc, const ast_kind tag, ast* val )
{
    ast_list* children = cons(val, NULL);
    ast* r = mk_node(loc, tag, children);
    return r;
}

// add
ast* mk_binexp ( const void* loc, const ast_kind tag, ast* val1, ast* val2 )
{
    ast_list* rch = cons(val2, NULL);
    ast_list* lch = cons(val1, rch);
    ast* r = mk_node(loc, tag, lch);
    return r;
}

ast* mk_statblock ( const void* loc, ast_list* revstat )
{
    ast* r = mk_node(loc, stat_node, reverse(revstat));
    return r;
}

ast* mk_idlist( const void* locl, const void* locr, ast* firstid, ast_list* revlst )
{
    ast* r;
    ast_list* lst = reverse(revlst);

    if(firstid)
        lst = cons(firstid, lst);

    r = mk_node(comb_loc(locl, locr), ids_node, lst);
    return r;
}

ast_list* clst ( int n, ... )
{
    ast_list* r = NULL;

    va_list vl;
    va_start(vl,n);
    {
        int i;
        for(i=0; i<n; i++)
            r = cons(va_arg(vl, ast*), r);
    }
    va_end(vl);

    r = reverse(r);
    return r;
}
