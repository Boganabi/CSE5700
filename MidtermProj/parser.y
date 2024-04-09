%{
#include <stdio.h>
void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
%}


%token NUMBER PLUS MINUS TIMES DIVIDE EOL

%%
input: /* empty */
      | input line
      ;

line: expr EOL { printf("Result: %d\n", $1); }
    ;

expr: expr PLUS expr { $$ = $1 + $3; }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr TIMES expr { $$ = $1 * $3; }
    | expr DIVIDE expr { $$ = $1 / $3; }
    | NUMBER { $$ = $1; }
    ;

%%
