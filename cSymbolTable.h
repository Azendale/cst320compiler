#pragma once

// Erik Andersen <erik.andersen@oit.edu>, 2016-01-19

#include "cSymbol.h"
#include <unordered_map>
#include <list>
#include <iostream>


class cSymbolTable
{
public:
    void IncreaseScope()
    {
        // Create new hash table and add it to the stack
        symbolstack.push_front(std::unordered_map<std::string, cSymbol *>());
    }
    void DecreaseScope()
    {
        if (!symbolstack.empty())
        {
            // Remove one hash table from the top of the stack
            symbolstack.pop_front();
        }
    }
    cSymbol* Insert(const std::string & toAdd)
    {
        // Is there a matching symbol in this context?
        cSymbol * returnValue = InnerLookup(toAdd);
        // No -- let's add it
        if (nullptr == returnValue)
        {
            // create a pair for the key and value
            std::pair<std::string, cSymbol *> keyValuePair;
            // Set key and value
            keyValuePair.first = toAdd;
            keyValuePair.second = new cSymbol(toAdd);
            // Put the new symbol into the hash table on the top/front of the list/stack
            symbolstack.front().insert(keyValuePair);
            // Should be able to combine this line into the one before, since the one before should return a pair with first thing being an interator to the item
            returnValue = (*(symbolstack.front().find(toAdd))).second;
        }
        // Yes -- just return the current one
        else
        {
            return returnValue;
        }
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
        std::list<std::unordered_map<std::string, cSymbol *>>::iterator stacktop = symbolstack.begin(); // Tracks the current level of the stack we are looking at
        std::list<std::unordered_map<std::string, cSymbol *>>::iterator stackbottom = symbolstack.end(); // Points to below the bottom of the stack. 
        
        std::unordered_map<std::string, cSymbol* >::iterator location = (*stacktop).find(toFind); // Priming search of the top level of the stack
        for (; stacktop != stackbottom && location == (*stacktop).end(); ++stacktop) // Until the bottom of the stack, or we find it on the current level
        {
            location = (*stacktop).find(toFind); // Search the current level for the item
        }
        if (stacktop == stackbottom) // Iterator for current symbol context pointing at item below the bottom of the stack -- meaning we went through all levels of the stack without finding the item
        {
            return nullptr; // Went to bottom of stack looking for it
        }
        else
        {
            // Our loop stopped because we found it.
            return (*location).second; // "dereference" the iterator to get pair of key, value. Select the second item to get the cSymbol pointer value so we can return it.
        }
    }
    void showtable()
    {
        //prints a list of hash tables, using's python's syntax to represent it
        std::cout << "[";
        for (auto it = symbolstack.begin(); it != symbolstack.end(); ++it)
        {
            std::cout << "{";
            for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
            {
                std::cout << "\"" << (*it2).first << "\" : \"" << (*it2).second->ToString() << "\", ";
            }
            std::cout << "}," << std::endl;
        }
        std::cout << "]" << std::endl;
    }
protected:
    
private:
    std::list<std::unordered_map<std::string, cSymbol *>> symbolstack;
};