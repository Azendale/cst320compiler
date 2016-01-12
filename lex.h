#pragma once
//**************************************
// lex.h
//
// Defines global symbols used the the flex generated lexer 
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//


int yylex();

extern char *yytext;
extern int yylineno;
extern int yynerrs;
extern FILE *yyin;

