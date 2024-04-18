
%{
#include <stdio.h>

extern char* last_token_text;
extern int line_number; // declared in lexer file

%}

%union {
    char *strval;
    int intval;
}

%token <strval> id STRINGCON
%token <intval> INTCON
%token CHARCON

%token IF ELSE WHILE FOR RETURN
%token VOID EXTERN
%token CHAR INT
%token '+' '-' '*' '/' EQ NE LE LT GE GT AND OR NOT

%left LOWER_THAN_ELSE

%%

prog    : prog dcl ';'  |  prog func | /* empty */
        ;

dcl     : type var_decl { /* handle declaration */ printf("type variable declaration");}
        | EXTERN type id '(' parm_types ')' { /* handle function declaration */ printf("extern type function declaration"); }
        | type id '(' parm_types ')' { /* handle function declaration */ printf("type function declaration"); }
        | EXTERN VOID id '(' parm_types ')' { /* handle void function declaration */ printf("void function declaration"); }
        ;

var_decl: id '[' INTCON ']'
        | id
        | '*' id
        ;

type    : CHAR
        | INT
        ;

parm_types: VOID
        | type id '[' ']' { /* handle parameter types */ }
        | type id
        | type '*' id
        ;

func    : type id '(' parm_types ')' '{' var_decls stmts '}'
        | VOID id '(' parm_types ')' '{' var_decls stmts '}'
        ;

var_decls: type var_decl ';' var_decls
        | /* empty */
        ;

stmts   : stmt stmts
        | /* empty */
        ;

stmt    : if_stmt
        | while_stmt
        | for_stmt
        | return_stmt
        | assg ';'
        | func_call ';'
        | '{' stmts '}'
        | ';'
        ;

if_stmt : IF '(' expr ')' stmt %prec LOWER_THAN_ELSE
        | IF '(' expr ')' stmt ELSE stmt
        ;

while_stmt: WHILE '(' expr ')' stmt
        ;

for_stmt: FOR '(' assg ';' expr ';' assg ')' stmt
        ;

return_stmt: RETURN expr ';'
        | RETURN ';'
        ;

assg    : id '[' expr ']' '=' expr
        | id '=' expr
        ;

func_call: id '(' exprs ')'
        ;

exprs   : expr ',' exprs
        | expr
        ;

expr    : '-' expr
        | '!' expr
        | expr '+' expr
        | expr '-' expr
        | expr '*' expr
        | expr '/' expr
        | expr EQ expr
        | expr NE expr
        | expr LE expr
        | expr LT expr
        | expr GE expr
        | expr GT expr
        | expr AND expr
        | expr OR expr
        | id
        | id '[' expr ']'
        | '(' expr ')'
        | INTCON
        | CHARCON
        | STRINGCON
        | '*' id
        ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_number, s);
    fprintf(stderr, "Unexpected token: %s\n", last_token_text);
}