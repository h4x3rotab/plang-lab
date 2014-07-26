#ifndef __header_ast_h__
#define __header_ast_h__

/********************************************************************************
*
* File: ast.h
* The abstract syntax trees for the calculator
* Programmer: Leonidas Fegaras, UTA
* Date: 12/17/97
*
********************************************************************************/


#include <gc/gc.h>

/* Put the names of all the different kinds of ASTs here */

typedef enum 
{ 
    if_stat = 0, 
    eq_exp, lt_exp, gt_exp, le_exp, ne_exp, ge_exp, plus_exp, minus_exp,
    times_exp, div_exp, or_exp, and_exp, 
    not_exp, 
    call_exp, fnc_def,

    // here are added node types

    // -- binary operators
    fdiv_exp, mod_exp, neq_exp,
    
    // -- unary operators
    neg_exp, pos_exp,

    // -- other operators
    fcall_exp, finit_exp, ainit_exp,
    args_node, ids_node,
    idx_exp, mem_exp,
    fasg_node, fasg_exp, 
    aval_node, aval_exp,
    io_node, if_node, else_node,

    retn_stat, exit_stat, for_stat, while_stat, loop_stat,
    asgn_stat, read_stat, write_stat,
    
    // -- nodes
    body_node, stat_node,

    field_decl, proc_decl, type_decl, var_decl,
    param_node, param_sec,
    arr_type, rec_type,

    var_decls, type_decls, proc_decls,

    genr_node,

    ast_kind_size,
               
} ast_kind;

static const char* ast_names[] = 
{
    "if_stat", 
    "eq_exp", "lt_exp", "gt_exp", "le_exp", "ne_exp", "ge_exp", "plus_exp", "minus_exp",
    "times_exp", "div_exp", "or_exp", "and_exp", 
    "not_exp", 
    "call_exp", "fnc_def",
   
    // bin opt
    "float_div_exp", "mod_exp", "neq_exp",

    // unary opt
    "neg_exp", "pos_exp",

    // other opt
    "func_call_exp", "field_init_exp", "array_init_exp",
    "args_node", "ids_node",
    "index_exp", "member_exp",
    "field_inits_node", "field_init_assign",
    "array_values_node", "array_value_exp",
    "io_args_node", "if_element_node", "else_element_node",

    "return_stat", "exit_stat", "for_stat", "while_stat", "loop_stat",
    "assign_stat", "read_stat", "write_stat",

    // nodes
    "body_node", "stat_node",

    "field_decl", "procedure_decl", "type_decl", "var_decl",
    "param_node", "param_section",
    "array_type", "record_type",
    "var_decl_list", "type_decl_list", "proc_decl_list",

    "general_node",
};

typedef struct ast_loc_t
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} ast_loc;

/* This is a universal data structure that can capture any AST:
 * The node is an internal node and has a list of children (other ASTs),
 * while the other nodes are leaves       */

typedef enum { int_ast, real_ast, var_ast, str_ast, node_ast } ast_tag;

typedef struct ast {
    ast_tag tag;
    union 
    { 
        long          integer;
        double        real;
        char*         variable;
        char*         string;

        struct 
        { 
            ast_kind          tag;
            struct ast_list*  arguments;
        } node;

    } info;

    // for location support
    ast_loc location;

} ast;

typedef struct ast_list { 
  ast*             elem;
  struct ast_list* next;
} ast_list;


/* create an integer AST leaf */
ast* mk_int ( const void* loc, const long x );


/* create a floating point AST leaf */
ast* mk_real ( const void* loc, const double x );


/* create an AST leaf for a name */
ast* mk_var ( const void* loc, const char* x );


/* create a string AST leaf */
ast* mk_str ( const void* loc, const char* x );


/* create an internal AST node */
ast* mk_node ( const void* loc, const ast_kind tag, ast_list* args );
ast* mk_noder ( const void* locl, const void* locr, const ast_kind tag, ast_list* args );

// create an AST node for unary operation
ast* mk_unaryexp ( const void* loc, const ast_kind tag, ast* val );

// create an AST node for binary operation
ast* mk_binexp ( const void* loc, const ast_kind tag, ast* val1, ast* val2 );

ast* mk_statblock ( const void* loc, ast_list* revstat );

ast* mk_idlist( const void* locl, const void* locr, ast* firstid, ast_list* revlst );

/* put an AST e in the beginning of the list of ASTs r */
ast_list* cons ( ast* e, ast_list* r );

// create a list with serveral elements
ast_list* clst ( int n, ... );


/* the empty list of ASTs */
#define null NULL


/* size of an AST list */
short length ( ast_list* );

/* reverse the order of ASTs in an AST list */
ast_list* reverse ( ast_list* );


/* printing functions for ASTs */
void print_ast_list ( ast_list* r );

void print_ast ( ast* x );
void print_ast_internal ( ast* x );

#endif
