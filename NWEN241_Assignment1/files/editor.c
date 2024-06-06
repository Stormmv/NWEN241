#include <stdio.h>
#include <string.h>

#include "editor.h"

int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos)
{
    // Check if the position is within the editing buffer
    if (pos >= 0 && pos < editing_buflen)
    {
        // Shift characters to the right
        for (int i = editing_buflen - 1; i > pos; i--)
        {
            // Shift characters to the right
            editing_buffer[i] = editing_buffer[i - 1];
        }
        // Insert the character at the specified position
        editing_buffer[pos] = to_insert;
        return 1;
    }
    return 0;
}

int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset)
{
    // Find the first occurrence of the character to delete
    for (int i = offset; i < editing_buflen; i++)
    {
        // Find the first occurrence of the character to delete
        if (editing_buffer[i] == to_delete)
        {
            // Shift characters to the left
            for (int j = i; j < editing_buflen - 1; j++)
            {
                // Shift characters to the left
                editing_buffer[j] = editing_buffer[j + 1];
            }
            return 1;
        }
    }
    return 0;
}

int editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset)
{
    int len = strlen(str);
    int repl_len = strlen(replacement);
    int i = offset;

    // Find the first occurrence of the string to replace
    while (i < editing_buflen)
    {
        int j = 0;
        // Compare the characters in the string to replace
        while (j < len && editing_buffer[i + j] == str[j])
        {
            // Increment the index of the string to replace
            j++;
        }
        // Check if the string to replace is found
        if (j == len)
        {
            // Check if the lengths of replacement and original word differ
            if (repl_len != len)
            {
                // Shift characters if the lengths of replacement and original word differ
                int diff = repl_len - len;
                if (diff > 0)
                {
                    // Move characters to the right
                    memmove(&editing_buffer[i + repl_len], &editing_buffer[i + len], editing_buflen - (i + len));
                }
                else
                {
                    // Move characters to the left
                    memmove(&editing_buffer[i + repl_len], &editing_buffer[i + len], editing_buflen - (i + len) + 1);
                }
            }

            // Replace characters with the replacement word
            memcpy(&editing_buffer[i], replacement, repl_len);
            return i + (repl_len - 1);
        }
        // Increment the index of the editing buffer
        i++;
    }
    return -1;
}
