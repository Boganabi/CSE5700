#include <stdio.h>
// #include "y.tab.h" 
#include "parser.tab.h" // include yacc/bison generated header file

extern FILE* yyin;
extern int yyparse();

int main() {
    yyin = stdin; // redirect input to stdin
    yyparse(); // start parsing
    return 0;
}
/*

\n        { printf("token eol\n"); line_number++; return EOL; }

*/

/*
^#include.* { printf("token include\n"); return INCLUDE; }
[0-9]+    { 
            printf("Token: NUMBER, Value: %s\n", yytext); 
            // yylval.num = atoi(yytext); 
            return NUMBER; 
          }
\"[^\n\"]*\"   { 
                           printf("Token: STRING_LITERAL, Value: %s\n", yytext); 
                           // yylval.str = strdup(yytext); // Assuming str is a member of yylval to store string literals
                           return STRING_LITERAL; 
                         }
[ \t]     ; // Skip whitespace
.         { printf("other: %s\n", yytext); return *yytext; } // Return any other single character
*/

/*


%token INCLUDE STRING_LITERAL NUMBER PLUS MINUS TIMES DIVIDE

%%

program : /* empty 
        | program statement
        ;

statement : expr
          | include_statement
          ;

expr : expr PLUS expr
     | expr MINUS expr
     | expr TIMES expr
     | expr DIVIDE expr
     | NUMBER
     ;

include_statement : INCLUDE STRING_LITERAL
                  ;

%%

*/
/* since c-- isnt a real language, heres just an example test to analyze with */