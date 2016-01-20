#pragma once
#include "cSymbol.h"
#include <unordered_map>
#include <list>
#include <iostream>


class cSymbolTable
{
public:
    void IncreaseScope()
    {
        std::cout << "\033[0;31mPush scope.\033[0m" << std::endl << "\033[0;34h";
        showtable();
        symbolstack.push_front(std::unordered_map<std::string, cSymbol *>());
        std::cout << "\033[0;31h";
        showtable();
        std::cout << "\033[0m" << std::endl;
    }
    void DecreaseScope()
    {
        std::cout << "\033[0;31mPop scope.\033[0m" << std::endl << "\033[0;34h";
        showtable();
        if (!symbolstack.empty())
        {
            symbolstack.pop_front();
        }
        std::cout << "\033[0;31h";
        showtable();
        std::cout << "\033[0m" << std::endl;
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
            returnValue = (*(symbolstack.front().find(toAdd))).second;
        }
        showtable();
        return returnValue;
    }
    cSymbol* InnerLookup(const std::string & toFind)
    {
        std::unordered_map<std::string, cSymbol *> & stacktop = symbolstack.front();
        std::unordered_map<std::string, cSymbol* >::iterator location = stacktop.find(toFind);
        if (location != stacktop.end())
        {
            return (*location).second;
        }
        return nullptr;
    }
    cSymbol* AllLookup(const std::string & toFind)
    {
        std::list<std::unordered_map<std::string, cSymbol *>>::iterator stacktop = symbolstack.begin();
        std::list<std::unordered_map<std::string, cSymbol *>>::iterator stackbottom = symbolstack.end();
        std::unordered_map<std::string, cSymbol* >::iterator location = (*stacktop).find(toFind);
        
        for (; stacktop != stackbottom && location == (*stacktop).end(); stacktop++) // Until the bottom of the stack, or we find it
        {
            location = (*stacktop).find(toFind);
        }
        if (stacktop == stackbottom)
        {
            return nullptr; // Went to bottom of stack looking for it
        }
        return (*location).second;
    }
    void showtable()
    {
        std::cout << "\033[0;32m[";
        for (auto it = symbolstack.begin(); it != symbolstack.end(); ++it)
        {
            std::cout << "{";
            for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            {
                std::cout << "\"" << (*it2).first << "\" : \"" << (*it2).second->ToString() << "\", ";
            }
            std::cout << "}," << std::endl;
        }
        std::cout << "]\033[0m" << std::endl;
    }
protected:
    
private:
    std::list<std::unordered_map<std::string, cSymbol *>> symbolstack;
};