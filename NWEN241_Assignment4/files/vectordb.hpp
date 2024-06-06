/**
 * vectordb.hpp
 * C++ header file that should contain declaration for
 * - VectorDbTable class
 *
 * You need to modify this file to declare VectorDbTable class
 * as specified in the hand-out (Task 2)
 */

#ifndef __VECTOR_DB_HPP__
#define __VECTOR_DB_HPP__

#include <vector>
#include "abstractdb.hpp"

/**
 * @namespace nwen
 * @brief This namespace contains the definitions for the movie database operations.
 *
 * It includes the VectorDbTable class, which is an implementation of the AbstractDbTable interface using a std::vector.
 * This class provides methods to manipulate a table of movies stored in a std::vector.
 */
namespace nwen
{
    /**
     * @class VectorDbTable
     * @brief This class provides an implementation of the AbstractDbTable interface using a std::vector.
     *
     * It provides methods to manipulate a table of movies stored in a std::vector.
     */
    class VectorDbTable : public AbstractDbTable
    {
    public:
        /**
         * @brief Construct a new VectorDbTable object
         */
        VectorDbTable();

        /**
         * @brief Destroy the VectorDbTable object
         */
        ~VectorDbTable();

        /**
         * @brief Get the number of rows in the table
         * @return int The number of rows
         */
        int rows() const override;

        /**
         * @brief Get a movie from the table
         * @param int The index of the movie to get
         * @return movie* A pointer to the movie
         */
        movie *get(int index) const override;

        /**
         * @brief Add a movie to the table
         * @param movie The movie to add
         * @return bool Whether the addition was successful
         */
        bool add(const movie& m) override;

        /**
         * @brief Update a movie in the table
         * @param unsigned long The index of the movie to update
         * @param movie The new movie data
         * @return bool Whether the update was successful
         */
        bool update(unsigned long id, const movie& m) override;

        /**
         * @brief Remove a movie from the table
         * @param unsigned long The index of the movie to remove
         * @return bool Whether the removal was successful
         */
        bool remove(unsigned long id) override;

    private:
        /**
         * @brief A std::vector to store the movie data
         */
        std::vector<movie> table;
    };
}

#endif /* __VECTOR_DB_HPP__ */
