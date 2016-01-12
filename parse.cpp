//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"

//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
    if (!FindSTMTS()) return false;
    int token = PeekToken();
    if (END != token)
    {
        Error("'end'");
        return false;
    }
    return true;
}
//*******************************************
// Find a STMTS non-terminal
bool FindSTMTS()
{
    while (FindSTMT())
    {
    }
    return true;
}
//*******************************************
// Find a STMT non-terminal
bool FindSTMT()
{
    if (!FindEXPR()) return false;
    int token = PeekToken();
    if (';' != token)
    {
        Error("';'");
        return false;
    }
    return true;
}
//*******************************************
// Find a EXPR non-terminal
bool FindEXPR()
{
    int token = PeekToken();
    if ('(' == token) 
    {
        AdvanceToken();
        if (!FindEXPR()) return false;
        if (')' != PeekToken() )
        {
            Error("')'");
            return false;
        }
        AdvanceToken();
        if (!FindEXPR_P()) return false;
        return true;
    }
    else if (!FindTERM()) return false; // Could have error here that they could have missed an open paren.
    return true;
}
//*******************************************
// Find a EXPR_P non-terminal
bool FindEXPR_P()
{
    if (FindPLUSOP())
    {
        int token = PeekToken();
        if ('(' != token )
        {
            Error("'('");
            return false;
        }
        AdvanceToken(); // Advance past '('
        if (!FindEXPR()) return false;
        token = PeekToken();
        if (')' != token)
        {
            Error("'('");
            return false;
        }
        AdvanceToken(); // Advance past ')'
        if (!FindEXPR_P()) return false;
    }
    return true; // Lamba production
}
//*******************************************
// Find a TERM non-terminal
bool FindTERM()
{
    int token = PeekToken();
    if ('[' == token)
    {
        AdvanceToken(); // Move past '['
        if (!FindEXPR()) return false;
        token = PeekToken();
        if (']' != token)
        {
            Error("']'");
            return false;
        }
        AdvanceToken(); // Move past ']'
        if (!FindTERM_P()) return false;
        return true;
    }
    else if (NUM != token)
    {
        Error("a number");
        return false;
    }
    return true;
}


/*******************************************
bool FindExample()
{
    if (!FindPART1()) return false;
    
    int token = PeekToken();
    if (token != '+') return false;
    AdvanceToken();         // past '+'

    if (!FindPART2()) return false;

    return true;
}
*/

