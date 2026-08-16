/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** free_history
*/

#include "shell.h"

/**
 * @brief Free the memory allocated for the command history.
 *
 * This function releases all dynamically allocated memory associated with
 * the 'history_t' linked list, including the history path, command strings,
 * and timestamp strings.
 *
 * @param history Pointer to the head of the 'history_t' linked list.
 * @param history_path Pointer to the string containing the history file path.
 *        If not NULL, it will also be freed.
 */
void free_history(history_t *history, char *history_path)
{
    history_t *current = history;
    history_t *previous = NULL;

    if (history_path != NULL)
        free(history_path);
    while (current != NULL) {
        previous = current;
        current = current->next;
        if (previous->command != NULL)
            free(previous->command);
        if (previous->time != NULL)
            free(previous->time);
        free(previous);
    }
}
