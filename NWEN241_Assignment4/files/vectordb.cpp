/**
 * vectordb.cpp
 * C++ source file that should contain implementation for member functions
 * - rows()
 * - get()
 * - add()
 * - update()
 * - remove()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Task 3)
 */ 

#include "vectordb.hpp"

namespace nwen
{
    VectorDbTable::VectorDbTable()
    {
    }

    VectorDbTable::~VectorDbTable()
    {
    }

    int VectorDbTable::rows() const
    {
        return table.size();
    }

    movie* VectorDbTable::get(int index) const
    {
        if (index < 0 || index >= rows())
        {
            return nullptr;
        }
        return const_cast<movie*>(&table[index]);
    }

    bool VectorDbTable::add(const movie& m)
    {
        for (const auto& item : table)
        {
            if (item.id == m.id)
            {
                return false;
            }
        }
        table.push_back(m);
        return true;
    }

    bool VectorDbTable::update(unsigned long id, const movie& m)
    {
        for (auto& item : table)
        {
            if (item.id == id)
            {
                item = m;
                return true;
            }
        }
        return false;
    }

    bool VectorDbTable::remove(unsigned long id)
    {
        for (auto it = table.begin(); it != table.end(); ++it)
        {
            if (it->id == id)
            {
                table.erase(it);
                return true;
            }
        }
        return false;
    }
}