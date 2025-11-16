%option c++
%option noyywrap

%{
#include <iostream>
using namespace std;
%}

ID      [a-zA-Z_][a-zA-Z0-9_]*
NUM     [0-9]+
WS      [ \t\r\n]+

%%

"int"           { cout << "KW_INT\n"; }
"return"        { cout << "KW_RETURN\n"; }
"if"            { cout << "KW_IF\n"; }
"else"          { cout << "KW_ELSE\n"; }
"while"         { cout << "KW_WHILE\n"; }

{ID}            { cout << "ID(" << YYText() << ")\n"; }
{NUM}           { cout << "NUM(" << YYText() << ")\n"; }

"=="            { cout << "EQ\n"; }
"!="            { cout << "NEQ\n"; }
"<="            { cout << "LE\n"; }
">="            { cout << "GE\n"; }
"="             { cout << "ASSIGN\n"; }
"<"             { cout << "LT\n"; }
">"             { cout << "GT\n"; }
"+"             { cout << "PLUS\n"; }
"-"             { cout << "MINUS\n"; }
"*"             { cout << "MUL\n"; }
"/"             { cout << "DIV\n"; }

";"             { cout << "SEMICOLON\n"; }
","             { cout << "COMMA\n"; }
"("             { cout << "LPAREN\n"; }
")"             { cout << "RPAREN\n"; }
"{"             { cout << "LBRACE\n"; }
"}"             { cout << "RBRACE\n"; }

"//".*          { /* ignore */ }
"/*"([^*]|(\*+[^*/]))*\*+"/"   { /* ignore */ }

{WS}            { /* ignore */ }


.               { cout << "UNKNOWN(" << YYText() << ")\n"; }

%%

int main() {
    yyFlexLexer lexer;
    lexer.yylex();
    return 0;
}
