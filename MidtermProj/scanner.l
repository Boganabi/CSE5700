%{
#include <stdio.h>
#include "parser.tab.h" // yacc/bison generated header file

int line_number = 1; // track line number
char* last_token_text;
%}

%% 

int             { last_token_text = strdup(yytext); return INT; }
extern          { last_token_text = strdup(yytext); return EXTERN; }
char            { last_token_text = strdup(yytext); return CHAR; }
[a-zA-Z][a-zA-Z0-9_]*    { last_token_text = strdup(yytext); yylval.strval = strdup(yytext); return id; }
[0-9]+          { last_token_text = strdup(yytext); yylval.intval = atoi(yytext); return INTCON; }
'[^\\'\n]|\\n|\\0'   { last_token_text = strdup(yytext); yylval.strval = strdup(yytext); return CHARCON; }
\"[^"\n]*\"     { last_token_text = strdup(yytext); yylval.strval = strdup(yytext); return STRINGCON; }
\/\*[^*]*\*\/   { last_token_text = strdup(yytext); /* ignore comments */ }
[\t]+           ; /* ignore whitespace */
[ ]*            { last_token_text = strdup(yytext); }
\n              {last_token_text = strdup(yytext); line_number++;}

.               { last_token_text = strdup(yytext); /* ignore unrecognized characters */ }

%%

int yywrap() {
    return 1;
}
