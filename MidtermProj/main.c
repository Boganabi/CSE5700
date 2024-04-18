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