%{
#include <stdio.h>
#include "parser.tab.h" // Include yacc/bison generated header file
%}

%% 
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return TIMES; }
"/"     { return DIVIDE; }
[0-9]+  { return NUMBER; }
\n      { return EOL; }
[ \t]   ; // Skip whitespace
.       { return *yytext; } // Return any other single character
%%

int yywrap() {
    return 1;
}
