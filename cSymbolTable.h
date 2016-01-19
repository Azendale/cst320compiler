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
    cSymbol* InnerLookup(const std::string & toFind)
    {
        std::unordered_map<std::string, cSymbol *> & stacktop = symbolstack.front();
        std::unordered_map<std::string, cSymbol* >::iterator location = stacktop.find(toFind);
        if (location != stacktop.end())
        {
            return *location;
        }
        return nullptr;
    }
    cSymbol* AllLookup(const std::string & toFind)
    {
        std::list<std::unordered_map<std::string, cSymbol *>> stacktop = symbolstack.begin();
        std::list<std::unordered_map<std::string, cSymbol *>> stackbottom = symbolstack.end();
        std::unordered_map<std::string, cSymbol* >::iterator location = stacktop.find(toFind);
        
        for (; stacktop != stackbottom && location == stacktop.end(); stacktop++) // Until the bottom of the stack, or we find it
        {
            location = stacktop.find(toFind);
        }
        if (stacktop == stackbottom)
        {
            return nullptr; // Went to bottom of stack looking for it
        }
        return *location;
    }
protected:
    
private:
    std::list<std::unordered_map<std::string, cSymbol *>> symbolstack;
};