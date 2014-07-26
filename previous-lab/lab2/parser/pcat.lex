%{

#include "ast.h"

#ifndef _cplusplus
#   ifndef bool
#       define bool  char
#       define true  1
#       define false 0
#   endif
#endif

#define min(a, b) ((a) < (b)) ? (a) : (b)
#define printable_ascii(ch)  ((0x20 <= (ch) && (ch) <= 0x7E && (ch) != '"'))

#define YY_USER_ACTION yylex_updatelocation();

    char* create_cstr();
    void yyerror(const char* message);
    void yyerror_unknownchar(char ch);
    void yylex_updatelocation();

%}

%x COMMENT

whitespace  [\ \t\r]+
digit       [0-9]
alpha       [a-zA-Z]

hexdigit    [0-9A-Fa-f]
hexint      ${hexdigit}+

digits      {digit}+
exp         e[+-]?{digit}+

INTEGERT    {digits}
 /*|{hexint}*/
REALT       ({digits}\.{digits}?|{digits}?\.{digits}){exp}?
IDENTIFIER  [a-zA-Z][a-zA-Z0-9_$]*
STRINGT     \"([^"\n])*\"
BADSTR      \"([^"\n])*

COMMENTS    \(\*.*\*\)

LPAREN      \(
RPAREN      \)
LBRACKET    \[
RBRACKET    \]
LBRACE      \{
RBRACE      \}
COLON       :
DOT         \.
SEMICOLON	;  
COMMA	    ,  
ASSIGN	    := 
PLUS	    \+  
MINUS	    -  
STAR	    \*  
SLASH	    \/  
BACKSLASH	\\  
EQ		    =  
NEQ		    <> 
LT		    <  
LE		    <= 
GT		    >  
GE		    >= 
LABRACKET	\[<
RABRACKET	>\]

 /* keywords are not listed here */



%%
    
{whitespace} { }
\n          { /*lineno++; columnno = 1;*/ } 

 /* comment */
"(*"                { BEGIN(COMMENT); }
<COMMENT>[^)*\n]+
<COMMENT>\n         { /*lineno++;*/ columnno = 1; }
<COMMENT><<EOF>>    { yyerror("Unterminated comment"); return EOFF; }
<COMMENT>"*)"       { BEGIN(INITIAL); }
<COMMENT>[*)]

{LPAREN}    { return LPAREN; }
{RPAREN}    { return RPAREN; }
{LBRACKET}  { return LBRACKET; }
{RBRACKET}  { return RBRACKET; }
{LBRACE}    { return LBRACE; }
{RBRACE}    { return RBRACE; }
{COLON}     { return COLON; }
{DOT}       { return DOT; }
{SEMICOLON} { return SEMICOLON; }
{COMMA}     { return COMMA; }
{ASSIGN}    { return ASSIGN; }
{PLUS}      { return PLUS; }
{MINUS}     { return MINUS; }
{STAR}      { return STAR; }
{SLASH}     { return SLASH; }
{BACKSLASH} { return BACKSLASH; }
{EQ}        { return EQ; }
{NEQ}       { return NEQ; }
{LT}        { return LT; }
{LE}        { return LE; }
{GT}        { return GT; }
{GE}        { return GE; }
{LABRACKET} { return LABRACKET; }
{RABRACKET} { return RABRACKET; }

PROGRAM     { return PROGRAM; }
IS          { return IS; }
BEGIN       { return BEGINT; }
END         { return END; }
VAR         { return VAR; }
TYPE        { return TYPE; }
PROCEDURE   { return PROCEDURE; }
ARRAY       { return ARRAY; }
RECORD      { return RECORD; }
IN          { return IN; }
OUT         { return OUT; }
READ        { return READ; }
WRITE       { return WRITE; }
IF          { return IF; }
THEN        { return THEN; }
ELSE        { return ELSE; }
ELSIF       { return ELSIF; }
WHILE       { return WHILE; }
DO          { return DO; }
LOOP        { return LOOP; }
FOR         { return FOR; }
EXIT        { return EXIT; }
RETURN      { return RETURN; }
TO          { return TO; }
BY          { return BY; }
AND         { return AND; }
OR          { return OR; }
NOT         { return NOT; }
OF          { return OF; }
DIV         { return DIV; }
MOD         { return MOD; }

{IDENTIFIER}    {
    if(yyleng < 256)
    {
        yylval.Tstring = yytext;
        return IDENTIFIER; 
    }

    yyerror("Identifier too long");
    return ERROR;
}

{STRINGT}       {
    if(yyleng-2 < 256)
    {
        int i;
        for(i=1; i<yyleng-1; i++)
            if(!printable_ascii(yytext[i])) {
                yyerror_unknownchar(yytext[i]);
                return ERROR;
            }

        yylval.Tstring = create_cstr();
        return STRINGT; 
    }

    yyerror("String too long");
    return ERROR;
}

{INTEGERT}      {
    if(yyleng <= 10)
    {
        int val = atoi(yytext);
        if(val >= 0)
        {
            yylval.Tint = (long)val;
            return INTEGERT; 
        }
    }

    yyerror("Integer out of range");
    return ERROR;
}

{REALT}         {
    double val = atof(yytext);
    yylval.Treal = val;
    return REALT; 
}


{BADSTR}        { yyerror("Unterminated string"); return ERROR; }
                
 /* return EOFF not work for bison
<<EOF>>         { return EOFF; }  
 */
            
 /* fallback */
.               { yyerror_unknownchar(yytext[0]); return ERROR;}


%%

void yyerror(const char *message)
{
    static char preview[14] = "??????????...";
    memcpy(preview, yytext, min(yyleng+1, 10));

    if(yytext)
        fprintf(stdout,"*** \"%s\" (line: %d, token:`%s')\n",
            message, lineno, preview);
}

void yyerror_unknownchar(char ch)
{
    if(yytext)
        fprintf(stderr,"Error: \"Illegal character`\\%03o' ignored\" in line %d.\n",
            ch, lineno);
}

char* create_cstr()
{
    if(!yytext) return NULL;

    char* str = (char*)malloc(yyleng-1);
    memcpy(str, yytext+1, sizeof(char) * (yyleng-2));
    str[yyleng-2] = '\0';

    return str;
}

void calc_column(int column, int* delta_line, int* end_column)
{
    int dline = 0;
    for(int i=0; i<yyleng; i++)
    {
        if(yytext[i] == '\n')
            column = 1,
            dline++;
        else
            column++;
    }

    if(end_column) *end_column = column;
    if(delta_line) *delta_line = dline;
}

void yylex_updatelocation()
{
    int delta_line;
    int end_column;

    calc_column(columnno, &delta_line, &end_column);

    yylloc.first_line = lineno;
    yylloc.last_line = lineno + delta_line;
    yylloc.first_column = columnno;
    yylloc.last_column = end_column;

    lineno = lineno + delta_line;
    columnno = end_column;
}

int yywrap()
{
    return 1;
}

