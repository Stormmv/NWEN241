/**
 * abstractdb.cpp
 * C++ source file that should contain implementation for member functions
 * - loadCSV()
 * - saveCSV()
 *
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Tasks 4 and 5)
 */

#include "abstractdb.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

/**
 * @namespace nwen
 * @brief This namespace contains the definitions for the movie database operations.
 *
 * It includes the AbstractDbTable class, which provides methods to manipulate a table of movies and to load and save this data from and to a CSV file.
 */
namespace nwen
{
    bool AbstractDbTable::loadCSV(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string id;
            std::string title;
            std::string year;
            std::string director;

            if (!std::getline(ss, id, ','))
            {
                return false;
            }
            if (!std::getline(ss, title, ','))
            {
                return false;
            }
            if (!std::getline(ss, year, ','))
            {
                return false;
            }
            if (!std::getline(ss, director, ','))
            {
                return false;
            }

            movie m;
            m.id = std::stoul(id);
            title = title.substr(1, title.size() - 2); // Remove quotes
            std::strcpy(m.title, title.c_str());
            m.year = std::stoi(year);
            director = director.substr(1, director.size() - 2); // Remove quotes
            std::strcpy(m.director, director.c_str());

            add(m);
        }

        file.close();
        return true;
    }

    bool AbstractDbTable::saveCSV(const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            return false;
        }

        for (int i = 0; i < rows(); i++)
        {
            movie *m = get(i);
            file << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"" << std::endl;
        }

        file.close();
        return true;
    }
}