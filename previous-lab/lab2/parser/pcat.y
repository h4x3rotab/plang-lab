%{

extern int lineno;
extern int columnno;

#include "ast.h"

#include "pcat.tab.h"
#include "pcat.yy.c"

void yyerror(const char* s);  // error handler defined in pcat.lex

%}

%locations 

%union {
    char*       Tstring;
    int         Tint;
    double      Treal;
    ast*        Tast;
    ast_list*   Tast_list;
}

%token <Tast>   IDENTIFIER INTEGERT REALT STRINGT
                PROGRAM IS BEGINT END VAR TYPE PROCEDURE ARRAY RECORD
                IN OUT READ WRITE IF THEN ELSE ELSIF WHILE DO LOOP
                FOR EXIT RETURN TO BY AND OR NOT OF DIV MOD
                LPAREN  RPAREN LBRACKET RBRACKET LBRACE RBRACE COLON DOT
                SEMICOLON COMMA ASSIGN PLUS MINUS STAR SLASH BACKSLASH EQ
                NEQ LT LE GT GE LABRACKET RABRACKET ERROR

%token <int>    EOFF 0;


/* nonterminals */

%type <Tast>    program 
                body 
                declaration
                var_decl
                type_decl
                type_name opt_typename
                compound_type
                procedure_decl
                field_decl
                formal_params
                formal_section
                statement
                statement_if_opt_else
                statement_for_opt_by
                statement_return_opt_expr
                read_args
                write_args
                write_expr
                expression
                l_value
                arguments
                field_inits
                array_values
                array_value
                number
                id
                string

%type <Tast_list>   declaration_array
                    var_decl_array
                    type_decl_array
                    procedure_decl_array
                    field_decl_array
                    //formal_params
                    formal_params_optext
                    statement_array
                    statement_if_opt_elseif
                    //read_args
                    read_args_optext
                    //write_args
                    write_args_optext
                    //arguments
                    arguments_optext
                    //field_inits
                    field_inits_optext
                    //array_values
                    array_values_optext
                    id_array_optext


/* operation precedence */

%left EQ NEQ GT LT GE LE
%left PLUS MINUS OR
%left STAR SLASH MOD DIV AND
%right NOT UOPT

%%

                     start: program { printf("[Accepted]\n"); print_ast($1); printf("\n"); };

                   program: PROGRAM IS body SEMICOLON { $$ = $3 };

                      body: declaration_array BEGINT statement_array END    { $$ = mk_node(&(@$), body_node, clst(2, mk_node(&(@1), genr_node, reverse($1)), mk_statblock(&(@3), $3))); };

               declaration: VAR var_decl var_decl_array                     { $$ = mk_node(&(@$), var_decls, cons($2, reverse($3))); }
                          | TYPE type_decl type_decl_array                  { $$ = mk_node(&(@$),type_decls, cons($2, reverse($3))); }
                          | PROCEDURE procedure_decl procedure_decl_array   { $$ = mk_node(&(@$),proc_decls, cons($2, reverse($3))); };
         declaration_array: /* empty */                                     { $$ = NULL; }
                          | declaration_array declaration                   { $$ = cons($2, $1); };

                  var_decl: id id_array_optext opt_typename ASSIGN expression SEMICOLON     { $$ = mk_node(&(@$), var_decl, clst(3, mk_idlist(&(@1), &(@2), $1, $2), $3, $5)); };
            var_decl_array: /* empty */                                                     { $$ = NULL; }
                          | var_decl_array var_decl                                         { $$ = cons($2, $1); };

                 type_decl: type_name IS compound_type SEMICOLON    { $$ = mk_node(&(@$), type_decl, clst(1, $3)); };
           type_decl_array: /* empty */                             { $$ = NULL; }
                          | type_decl_array type_decl               { $$ = cons($2, $1); };

                 type_name: id;
              opt_typename: /* empty */     { $$ = NULL; }
                          | COLON type_name { $$ = $2};

             compound_type: ARRAY OF type_name                      { $$ = mk_node(&(@$), arr_type, clst(1, $3)); }
                          | RECORD field_decl field_decl_array END  { $$ = mk_node(&(@$), rec_type, cons($2, reverse($3))); };

            procedure_decl: id formal_params opt_typename IS body SEMICOLON     { $$ = mk_node(&(@$), proc_decl, clst(4, $1, $2, $3, $5)); };
      procedure_decl_array: /* empty */                                         { $$ = NULL; }
                          | procedure_decl_array procedure_decl                 { $$ = cons($2, $1); };

                field_decl: id COLON type_name SEMICOLON    { $$ = mk_node(&(@$), field_decl, clst(2, $1, $3)); };
          field_decl_array: /* empty */                     { $$ = NULL; }
                          | field_decl_array field_decl     { $$ = cons($2, $1); };

             formal_params: LPAREN formal_section formal_params_optext RPAREN   { $$ = mk_node(&(@$), param_node, cons($2, reverse($3))); }
                          | LPAREN RPAREN                                       { $$ = mk_node(&(@$), param_node, NULL); };
      formal_params_optext: /* empty */                                         { $$ = NULL; }
                          | formal_params_optext SEMICOLON formal_section       { $$ = cons($3, $1); };

            formal_section: id id_array_optext COLON type_name                  { $$ = mk_node(&(@$), param_sec, clst(2, mk_idlist(&(@1), &(@2), $1, $2), $4)); };

                 statement: l_value ASSIGN expression SEMICOLON                 { $$ = mk_node(&(@$), asgn_stat, clst(2, $1, $3)); }
                          | id arguments SEMICOLON                              { $$ = mk_node(&(@$), fcall_exp, clst(2, $1, $2)); }
                          | READ read_args SEMICOLON                            { $$ = mk_node(&(@$), read_stat, clst(1, $2)); }
                          | WRITE write_args SEMICOLON                          { $$ = mk_node(&(@$), write_stat, clst(1, $2)); }
                          | IF expression THEN 
                                statement_array
                            statement_if_opt_elseif
                            statement_if_opt_else
                            END SEMICOLON                                       { 
                                                                                    $$ = mk_node(&(@$), if_stat, 
                                                                                        clst
                                                                                        (
                                                                                            3, mk_noder(&(@1), &(@4), if_node, clst(2, $2, $4)),
                                                                                            mk_statblock(&(@5), $5),
                                                                                            $6
                                                                                        )
                                                                                    ); 
                                                                                }
                          | WHILE expression DO statement_array END SEMICOLON   { $$ = mk_node(&(@$), while_stat, clst(2, $2, mk_statblock(&(@4), $4))); }
                          | LOOP statement_array END SEMICOLON                  { $$ = mk_node(&(@$),  loop_stat, clst(1, mk_statblock(&(@2), $2))); }
                          | FOR l_value ASSIGN expression TO expression statement_for_opt_by DO
                                statement_array
                            END SEMICOLON                                       { 
                                                                                    $$ = mk_node(&(@$), for_stat, 
                                                                                        clst
                                                                                        (
                                                                                            5, $2, $4, $6, $7,
                                                                                            mk_statblock(&(@9), $9)
                                                                                        )
                                                                                    ); 
                                                                                }
                          | EXIT SEMICOLON                                      { $$ = mk_node(&(@$), exit_stat, NULL); }
                          | RETURN statement_return_opt_expr SEMICOLON          { $$ = mk_node(&(@$), retn_stat, clst(1, $2)); };

           statement_array: /* empty */                 { $$ = NULL; }
                          | statement_array statement   { $$ = cons($2, $1); };

   statement_if_opt_elseif: /* empty */                                                     { $$ = NULL; }
                          | statement_if_opt_elseif ELSIF expression THEN statement_array   { $$ = cons(mk_noder(&(@3), &(@5), if_node, clst(2, $3, $5)), $1); };

     statement_if_opt_else: /* empty */             { $$ = NULL; }
                          | ELSE statement_array    { $$ = mk_node(&(@$), else_node, clst(1, $2)); };

      statement_for_opt_by: /* empty*/      { $$ = NULL; }
                          | BY expression   { $$ = $2; };
                            
 statement_return_opt_expr: /* empty */ { $$ = NULL; }
                          | expression  { $$ = $1; };

                 read_args: LPAREN l_value read_args_optext RPAREN      { $$ = mk_node(&(@$), io_node, cons($2, reverse($3))); };
          read_args_optext: /* empty */                                 { $$ = NULL; }
                          | read_args_optext COMMA l_value              { $$ = cons($3, $1); };

                write_args: LPAREN write_expr write_args_optext RPAREN  { $$ = mk_node(&(@$), io_node, cons($2, reverse($3))); }
                          | LPAREN RPAREN                               { $$ = mk_node(&(@$), io_node, NULL); };
         write_args_optext: /* empty */                                 { $$ = NULL; }
                          | write_args_optext COMMA write_expr          { $$ = cons($3, $1); };

                write_expr: string          { $$ = $1; }
                          | expression      { $$ = $1; };

                expression: number                          { $$ = $1; }
                          | l_value                         { $$ = $1; }
                          | LPAREN expression RPAREN        { $$ = $2; }
                          //| unary_op expression
                          | PLUS expression %prec UOPT      { $$ = mk_unaryexp(&(@$), pos_exp, $2); }
                          | MINUS expression %prec UOPT     { $$ = mk_unaryexp(&(@$), neg_exp, $2); }
                          | NOT expression %prec UOPT       { $$ = mk_unaryexp(&(@$), not_exp, $2); }
                          //| expression binary_op expression
                          | expression PLUS expression      { $$ = mk_binexp(&(@$),  plus_exp, $1, $3); }
                          | expression MINUS expression     { $$ = mk_binexp(&(@$), minus_exp, $1, $3); }
                          | expression STAR expression      { $$ = mk_binexp(&(@$), times_exp, $1, $3); }
                          | expression SLASH expression     { $$ = mk_binexp(&(@$),  fdiv_exp, $1, $3); }
                          | expression DIV expression       { $$ = mk_binexp(&(@$),   div_exp, $1, $3); }
                          | expression MOD expression       { $$ = mk_binexp(&(@$),   mod_exp, $1, $3); }
                          | expression OR expression        { $$ = mk_binexp(&(@$),    or_exp, $1, $3); }
                          | expression AND expression       { $$ = mk_binexp(&(@$),   and_exp, $1, $3); }
                          | expression GT expression        { $$ = mk_binexp(&(@$),    gt_exp, $1, $3); }
                          | expression LT expression        { $$ = mk_binexp(&(@$),    lt_exp, $1, $3); }
                          | expression EQ expression        { $$ = mk_binexp(&(@$),    eq_exp, $1, $3); }
                          | expression GE expression        { $$ = mk_binexp(&(@$),    ge_exp, $1, $3); }
                          | expression LE expression        { $$ = mk_binexp(&(@$),    le_exp, $1, $3); }
                          | expression NEQ expression       { $$ = mk_binexp(&(@$),   neq_exp, $1, $3); }
                          | id arguments                    { $$ = mk_node(&(@$), fcall_exp, clst(2, $1, $2)); }
                          | id field_inits                  { $$ = mk_node(&(@$), finit_exp, clst(2, $1, $2)); }   // T { key1 := val1, ... }
                          | id array_values                 { $$ = mk_node(&(@$), ainit_exp, clst(2, $1, $2)); };  // T [< [n1 of] val1, ... >]

                   l_value: id
                          | l_value LBRACKET expression RBRACKET    { $$ = mk_node(&(@$), idx_exp, clst(2, $1, $3)); }
                          | l_value DOT id                          { $$ = mk_node(&(@$), mem_exp, clst(2, $1, $3)); };

                 arguments: LPAREN expression arguments_optext RPAREN   { $$ = mk_node(&(@$), args_node, cons($2, reverse($3))); }
                          | LPAREN RPAREN                               { $$ = mk_node(&(@$), args_node, NULL); };
          arguments_optext: /* empty */                                 { $$ = NULL; }
                          | arguments_optext COMMA expression           { $$ = cons($3, $1); };

               field_inits: LBRACE id ASSIGN expression field_inits_optext RBRACE   { $$ = mk_node(&(@$), fasg_node, cons(mk_noder(&(@2), &(@4), fasg_exp, clst(2, $2, $4)), reverse($5))); }
        field_inits_optext: /* empty */                                             { $$ = NULL; }
                          | field_inits_optext COMMA id ASSIGN expression           { $$ = cons(mk_noder(&(@3), &(@5), fasg_exp, clst(2, $3, $5)), $1); };

              array_values: LABRACKET array_value array_values_optext RABRACKET { $$ = mk_node(&(@$), aval_node, cons($2, reverse($3))); };
       array_values_optext: /* empty */                                         { $$ = NULL; }
                          | array_values_optext COMMA array_value               { $$ = cons($3, $1); };

               array_value: expression                  { $$ = mk_node(&(@$), aval_exp, clst(1, $1)); }
                          | expression OF expression    { $$ = mk_node(&(@$), aval_exp, clst(2, $1, $3)); };

                    number: INTEGERT    { $$ = mk_int(&(@$), yylval.Tint); }
                          | REALT       { $$ = mk_real(&(@$), yylval.Treal); };
                    string: STRINGT     { $$ = mk_str(&(@$), yylval.Tstring); };

                        id: IDENTIFIER                  { $$ = mk_var(&(@$), yylval.Tstring); };
           id_array_optext: /* empty */                 { $$ = NULL; }
                          | id_array_optext COMMA id    { $$ = cons($3, $1); };


%%
