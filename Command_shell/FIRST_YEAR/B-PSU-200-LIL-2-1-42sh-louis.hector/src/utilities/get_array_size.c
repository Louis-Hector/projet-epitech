/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** get_array_size
*/

#include "shell.h"

/**
 * @brief Get the size of a null-terminated array of strings.
 *
 * This function counts the number of elements in a null-terminated
 * array of strings (char **array) and returns the count.
 *
 * @param array The null-terminated array of strings.
 * @return The size of the array (number of strings).
 */
int get_array_size(char **array)
{
    int i = 0;

    while (array[i])
        i++;
    return i;
}
