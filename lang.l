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
INT_VALUE        (([1-9][0-9]*)|0)
RSPACE           [ \n\t\v\r]+
RCHAR            [\[\];\+\-\*\/]
%%

    // token definitions go here. "if" is an example.
{RCHAR}                     DO_RETURN(*yytext);
"end"                       DO_RETURN(END);
{INT_VALUE}                 DO_RETURN(INT_VAL);
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
