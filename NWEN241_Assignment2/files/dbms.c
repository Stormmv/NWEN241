#include "dbms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Task 1
// Function to display the row of the database table\
// Returns 1 if the row is displayed successfully, 0 otherwise
// The function takes a pointer to a database table and an unsigned integer as arguments
// The unsigned integer represents the row number to display
int db_show_row(const struct db_table *db, unsigned int row)
{
    // Check if the row number is greater than the number of rows used in the database table
    if (row >= db->rows_used)
    {
        // Return 0 if the row number is greater than the number of rows used in the database table
        return 0;
    }
    // Print the row number, title, artist, and year of the album
    struct album *a = db->table + row;
    printf("%6d:%20.*s:%20s:%4d\n", a->id, 20, a->title, a->artist, a->year);
    // Return 1 if the row is displayed successfully
    return 1;
}

// Task 2
// Function to add a row to the database table
// Returns 1 if the row is added successfully, 0 otherwise
// The function takes a pointer to a database table and a pointer to an album as arguments
// The album pointer represents the album to add to the database table
int db_add_row(struct db_table *db, struct album *a)
{
    // Check if the number of rows used in the database table is less than the total number of rows in the database table
    if (db->rows_used < db->rows_total)
    {
        // Add the album to the database table
        db->table[db->rows_used] = *a;
        db->rows_used++;
        return 1;
    }
    // If the number of rows used in the database table is equal to the total number of rows in the database table
    else
    {
        // Reallocate memory for the database table to increase the total number of rows by 5
        struct album *new_table = realloc(db->table, (db->rows_total + 5) * sizeof(struct album));
        // Check if memory reallocation was successful
        if (new_table == NULL)
        {
            // Return 0 if memory reallocation failed
            return 0;
        }
        // Update the database table with the new memory allocation
        db->table = new_table;
        db->table[db->rows_used] = *a;
        db->rows_used++;
        db->rows_total += 5;
        return 1;
    }
}

// Task 3
// Function to remove a row from the database table
// Returns 1 if the row is removed successfully, 0 otherwise
// The function takes a pointer to a database table and an unsigned long integer as arguments
// The unsigned long integer represents the ID of the album to remove from the database table
int db_remove_row(struct db_table *db, unsigned long id)
{
    // Find the row with the specified ID in the database table
    int i;
    for (i = 0; i < db->rows_used; i++)
    {
        // Check if the ID of the album matches the specified ID
        if (db->table[i].id == id)
        {
            // Remove the album from the database table
            break;
        }
    }
    // Return 0 if the album with the specified ID is not found in the database table
    if (i == db->rows_used)
    {
        return 0;
    }
    // Shift the rows to the left to remove the album from the database table
    for (int j = i; j < db->rows_used - 1; j++)
    {
        // Shift the rows to the left
        db->table[j] = db->table[j + 1];
    }
    // Decrement the number of rows used in the database table
    db->rows_used--;
    // Check if the number of rows used is a multiple of 5
    if (db->rows_used % 5 == 0)
    {
        // Reallocate memory for the database table to reduce the total number of rows by 5
        struct album *new_table = realloc(db->table, (db->rows_total - 5) * sizeof(struct album));
        // Check if memory reallocation was successful
        if (new_table == NULL)
        {
            return 0;
        }
        // Update the database table with the new memory allocation
        db->table = new_table;
        db->rows_total -= 5;
    }
    // Check if the number of rows used is 0
    if (db->rows_used == 0)
    {
        // Free the memory allocated for the database table
        free(db->table);
        // Set the database table to NULL and the total number of rows to 0
        db->table = NULL;
        db->rows_total = 0;
    }
    // Return 1 if the row is removed successfully
    return 1;
}
