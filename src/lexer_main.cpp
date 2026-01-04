#include <iostream>
#include "ast.h"
#include "parser.hpp"

// Define yylval as it is declared extern in parser.hpp but we are not linking parser.cpp
YYSTYPE yylval;

extern int yylex();
extern char* yytext;

int main() {
    int token;
    while ((token = yylex())) {
        std::cout << "Token: " << token << ", Text: " << yytext << std::endl;
    }
    return 0;
}
