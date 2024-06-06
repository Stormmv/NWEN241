/**
 * abstractdb.hpp
 * C++ header file that should contain declaration for
 * - struct movie (given)
 * - AbstractDbTable abstract class
 *
 * You need to modify this file to declare AbstractDbTable abstract class
 * as specified in the hand-out (Task 1)
 */

#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <string>

namespace nwen
{
    struct movie
    {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };
}

/**
 * @namespace nwen
 * @brief This namespace contains the definitions for the movie database operations.
 *
 * It includes the AbstractDbTable class and the movie struct, which are used to manipulate and store movie data.
 */
namespace nwen
{
    class AbstractDbTable
    {
    public:
        virtual ~AbstractDbTable() {}

        /**
         * @brief Get the number of rows in the table
         * @return int The number of rows
         */
        virtual int rows() const = 0;

        /**
         * @brief Get a movie from the table
         * @param int The index of the movie to get
         * @return movie* A pointer to the movie
         */
        virtual movie* get(int) const = 0;

        /**
         * @brief Add a movie to the table
         * @param movie The movie to add
         */
        virtual bool add(const movie&) = 0;

        /**
         * @brief Update a movie in the table
         * @param unsigned long The index of the movie to update
         * @param movie The new movie data
         * @return bool Whether the update was successful
         */
        virtual bool update(unsigned long, const movie&) = 0;

        /**
         * @brief Remove a movie from the table
         * @param unsigned long The index of the movie to remove
         * @return bool Whether the removal was successful
         */
        virtual bool remove(unsigned long) = 0;

        /**
         * @brief Load the table from a CSV file
         * @param std::string The path to the CSV file
         * @return bool Whether the load was successful
         */
        bool loadCSV(const std::string&);

        /**
         * @brief Save the table to a CSV file
         * @param std::string The path to the CSV file
         * @return bool Whether the save was successful
         */
        bool saveCSV(const std::string&);
    };
}

#endif /* __ABSTRACT_DB_HPP__ */