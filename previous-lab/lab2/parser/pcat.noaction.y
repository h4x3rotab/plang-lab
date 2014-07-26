%{

extern int lineno;

#include "ast.h"

#include "pcat.tab.h"
#include "pcat.yy.c"

void yyerror(const char* s);  // error handler defined in pcat.lex

%}

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
                FOR EXIT RETURN TO BY /*AND OR NOT*/ OF /*DIV MOD*/
                LPAREN  RPAREN LBRACKET RBRACKET LBRACE RBRACE COLON DOT
                SEMICOLON COMMA ASSIGN /*PLUS MINUS STAR SLASH*/ BACKSLASH /*EQ*/
                /*NEQ LT LE GT GE*/ LABRACKET RABRACKET EOFF ERROR


/* nonterminals */

%type <Tast>    program 
/*
                body 
                declaration declaration_array
                var_decl var_decl_array
*/
            
                
                
                


/* operation precedence */

%left EQ NEQ GT LT GE LE
%left PLUS MINUS OR
%left STAR SLASH MOD DIV AND
%right NOT UOPT



%%

                     start: program EOFF             { print_ast($1); };

                   program: PROGRAM IS body SEMICOLON;

                      body: declaration_array BEGINT statement_array END;

               declaration: VAR var_decl var_decl_array
                          | TYPE type_decl type_decl_array
                          | PROCEDURE procedure_decl procedure_decl_array;
         declaration_array: /* empty */ 
                          | declaration_array declaration;

                  var_decl: id id_array_optext opt_typename ASSIGN expression SEMICOLON;
            var_decl_array: /* empty */ 
                          | var_decl_array var_decl;

                 type_decl: type_name IS compound_type SEMICOLON;
           type_decl_array: /* empty */ 
                          | type_decl_array type_decl;

                 type_name: id;
              opt_typename: /* empty */
                          | COLON type_name;

             compound_type: ARRAY OF type_name
                          | RECORD field_decl field_decl_array END;

            procedure_decl: id formal_params opt_typename IS body SEMICOLON;
      procedure_decl_array: /* empty */
                          | procedure_decl_array procedure_decl;

                field_decl: id COLON type_name SEMICOLON;
          field_decl_array: /* empty */
                          | field_decl_array field_decl;

             formal_params: LPAREN formal_section formal_params_optext RPAREN
                          | LPAREN RPAREN;
      formal_params_optext: /* empty */
                          | formal_params_optext SEMICOLON formal_section;

            formal_section: id id_array_optext COLON type_name;

                 statement: l_value ASSIGN expression SEMICOLON
                          | id arguments SEMICOLON
                          | READ read_args SEMICOLON
                          | WRITE write_args SEMICOLON
                          | IF expression THEN 
                                statement_array
                            statement_if_opt_elseif
                            statement_if_opt_else
                            END SEMICOLON
                          | WHILE expression DO statement_array END SEMICOLON
                          | LOOP statement_array END SEMICOLON
                          | FOR l_value ASSIGN expression TO expression statement_for_opt_by DO
                                statement_array
                            END SEMICOLON
                          | EXIT SEMICOLON
                          | RETURN statement_return_opt_expr SEMICOLON;

           statement_array: /* empty */
                          | statement_array statement;

   statement_if_opt_elseif: /* empty */
                          | statement_if_opt_elseif ELSIF expression THEN statement_array;

     statement_if_opt_else: /* empty */
                          | ELSE statement_array

      statement_for_opt_by: /* empty*/
                          | BY expression;
                            
 statement_return_opt_expr: /* empty */
                          | expression;

                 read_args: LPAREN l_value read_args_optext RPAREN;
          read_args_optext: /* empty */
                          | read_args_optext COMMA l_value;

                write_args: LPAREN write_expr write_args_optext RPAREN
                          | LPAREN RPAREN;
         write_args_optext: /* empty */
                          | write_args_optext COMMA write_expr;

                write_expr: string
                          | expression;

                expression: number
                          | l_value
                          | LPAREN expression RPAREN
                          | unary_op expression %prec UOPT
                          //| expression binary_op expression
                          | expression PLUS expression
                          | expression MINUS expression
                          | expression STAR expression
                          | expression SLASH expression
                          | expression DIV expression
                          | expression MOD expression
                          | expression OR expression
                          | expression AND expression
                          | expression GT expression
                          | expression LT expression
                          | expression EQ expression
                          | expression GE expression
                          | expression LE expression
                          | expression NEQ expression
                          | id arguments
                          | id field_inits
                          | id array_values;

                   l_value: id
                          | l_value LBRACKET expression RBRACKET
                          | l_value DOT id;

                 arguments: LPAREN expression arguments_optext RPAREN
                          | LPAREN RPAREN;
          arguments_optext: /* empty */
                          | arguments_optext COMMA expression;

               field_inits: LBRACE id ASSIGN expression field_inits_optext RBRACE;
        field_inits_optext: /* empty */
                          | field_inits_optext COMMA id ASSIGN expression;

              array_values: LBRACE LBRACE array_value array_values_optext RBRACE RBRACE;
       array_values_optext: /* empty */
                          | array_values_optext COMMA array_value;

               array_value: expression
                          | expression OF expression;

                    number: INTEGERT    //{ $$ = mk_int(yylval.Tint); }
                          | REALT       //{ $$ = mk_real(yylval.Treal); };

                  unary_op: PLUS | MINUS | NOT;

                        id: IDENTIFIER  //{ $$ = mk_var(yylval.Tstring); };
           id_array_optext: /* empty */
                          | id_array_optext COMMA id;

                    string: STRINGT;


%%
