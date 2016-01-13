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
// Updated by Erik Andersen <erik.andersen@oit.edu> 2016-01-12

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

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
    AdvanceToken(); //Move past END token
    return true;
}
//*******************************************
// Find a STMTS non-terminal
bool FindSTMTS()
{
    while (END != PeekToken() && FindSTMT())
    {
    }
    return true;
}
void SyncSTMT()
{
    int token = PeekToken();
    while (token != 0 && token != ';' && token != END) // Stop trying to wind forward when we find a ;, the end of the file, or the end Keyword (so program can get it)
    {
        token = AdvanceToken(); // Move forward. Loop checks to see if we now are at the end of file or found a ;
    }
    if (';' == token)
    {
        AdvanceToken(); // If we didn't hit the end of the file, wind to the place after the semicolon
    }
}
//*******************************************
// Find a STMT non-terminal
bool FindSTMT()
{
    if (FindEXPR())
    {
        int token = PeekToken();
        if (';' == token)
        {
            AdvanceToken(); // Advance past ';'
            std::cout << "Found a statement" << std::endl;
        }
        else
        {
            Error("';'");
            SyncSTMT();
        }
    }
    else
    {
        SyncSTMT();
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
        AdvanceToken(); // Advance past '('
        if (!FindEXPR()) return false;
        if (')' != PeekToken() )
        {
            Error("')'");
            return false;
        }
        AdvanceToken(); // Advance past ')'
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
    int token = PeekToken();
    if (('+' == token || '-' == token) && FindPLUSOP())
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
    else if (INT_VAL != token)
    {
        Error("a number");
        return false;
    }
    else
    {
        AdvanceToken(); // Advance past the number
    }
    return true;
}
//*******************************************
// Find a TERM_P non-terminal
bool FindTERM_P()
{
    int token = PeekToken();
    if (('*' == token || '/' == token) && FindTIMESOP())
    {
        int token = PeekToken();
        if ('[' != token )
        {
            Error("'['");
            return false;
        }
        AdvanceToken(); // Advance past '['
        if (!FindEXPR()) return false;
        token = PeekToken();
        if (']' != token)
        {
            Error("']'");
            return false;
        }
        AdvanceToken(); // Advance past ']'
        if (!FindTERM_P()) return false;
    }
    return true; // Lamba production
}
//*******************************************
// Find a TIMESOP non-terminal
bool FindTIMESOP()
{
    int token = PeekToken();
    if ( ('*' == token) || ('/' == token) )
    {
        AdvanceToken();
        return true;
    }
    Error("'*' or '/'");
    return false;

}
//*******************************************
// Find a PLUSOP non-terminal
bool FindPLUSOP()
{
    int token = PeekToken();
    if ( ('+' == token) || ('-' == token) )
    {
        AdvanceToken();
        return true;
    }
    Error("'+' or '-'");
    return false;

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

