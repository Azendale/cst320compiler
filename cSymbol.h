#pragma once
#include <string>
// 2016-01-19 Imported from file from example provided by Phil Howard

using std::string;

class cSymbol
{
    public:
        cSymbol(string name)
        {
            m_id = ++nextId;
            m_name = name;
        }

        string ToString()
        {
            string result("<sym id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\" />";

            return result;
        }

        string GetName() { return m_name; }
    protected:
        static long long nextId;
        long long m_id;
        string m_name;
};
