#include <iostream>
#include "lex.h"
#include "utils.h"

static int g_token = -1;

//*******************************************
void Error(std::string expecting)
{
    std::cout << "Found '" << yytext << "' when expecting a " << expecting;
    std::cout << " in line " << yylineno << std::endl;
}
//*******************************************
int PeekToken()
{
    if (g_token < 0) g_token = yylex();

    return g_token;
}
//*******************************************
int AdvanceToken()
{
    g_token = yylex();

    return g_token;
}
