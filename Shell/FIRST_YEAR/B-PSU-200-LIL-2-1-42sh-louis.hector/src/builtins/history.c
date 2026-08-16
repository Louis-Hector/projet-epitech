/*
** EPITECH PROJECT, 2025
** history
** File description:
** history
*/

#include "shell.h"

/**
 * @brief Display the command history.
 *
 * This function iterates through the history linked list and prints
 * each command along with its index and timestamp.
 *
 * @param tab The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 if there are too many arguments.
 */
int display_history(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    history_t *current = shell->history;

    if (!tab || !env || !old_path)
        return 0;
    while (current != NULL) {
        printf("     %d  ", current->index + 1);
        printf("%s   ", current->time);
        printf("%s\n", current->command);
        current = current->next;
    }
    return 0;
}
