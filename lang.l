%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
INT_VALUE       '[1-9][0-9]*'
FLOAT_VALUE     '-?(([1-9][0-9]*)|0)(\.[0-9]+)?'
RIDENTIFIER     '[_a-zA-Z][a-zA-Z0-9]*'
RSPACE          '[ \n\t\v]+'
RPUNCTUTION     [\(\)\{\}\[\];,\.\+\-\*\/%=]

%%

    // token definitions go here. "if" is an example.
{RPUNCTUTION}               DO_RETURN(*yytext);
"if"                        DO_RETURN(IF);
"endif"                     DO_RETURN(ENDIF);
"else"                      DO_RETURN(ELSE);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"char"                      DO_RETURN(CHAR);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);
{INT_VALUE}                 DO_RETURN(INT_VAL);
{FLOAT_VALUE}               DO_RETURN(FLOAT_VAL);
{RIDENTIFIER}               DO_RETURN(IDENTIFIER);
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);
{RSPACE}                    {}
"//".*$                     {}
.                           DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d on line %d\n", yytext, val, yylineno);
    return val;
}
