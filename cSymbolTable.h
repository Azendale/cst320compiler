#pragma once
#include "cSymbol.h"
#include <unordered_map>
#include <list>


class cSymbolTable
{
public:
    void IncreaseScope()
    {
        symbolstack.push_front(std::unordered_map<std::string, cSymbol *>());
    }
    void DecreaseScope()
    {
        if (symbolstack.empty())
        {
            symbolstack.pop_front();
        }
    }
    cSymbol* Insert(const std::string & toAdd)
    {
        cSymbol * returnValue = InnerLookup(toAdd);
        if (nullptr == returnValue)
        {
            // symbolstack[toAdd] = new cSymbol(toAdd)
            std::pair<std::string, cSymbol *> keyValuePair;
            keyValuePair.first = toAdd;
            keyValuePair.second = new cSymbol(toAdd);
            symbolstack.front().insert(keyValuePair);
        }
    }
    cSymbol* InnerLookup(const std::string & toFind);
    cSymbol* AllLookup(const std::string & toFind);
protected:
    
private:
    std::list<std::unordered_map<std::string, cSymbol *>> symbolstack;
};