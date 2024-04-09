#include <stdio.h>
// #include "y.tab.h" // Include yacc/bison generated header file
#include "parser.tab.h"

extern FILE* yyin;
extern int yyparse();

int main() {
    yyin = stdin; // Redirect input to stdin
    yyparse(); // Start parsing
    return 0;
}
