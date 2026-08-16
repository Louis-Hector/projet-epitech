/*
** EPITECH PROJECT, 2025
** unvsetenv
** File description:
** unsetenv
*/

#include "shell.h"

/**
 * @brief Remove an environment variable from the linked list.
 *
 * This function iterates through the linked list of environment variables
 * and removes the specified variable if found.
 *
 * @param current The current node in the linked list.
 * @param prev The previous node in the linked list.
 * @param env The linked list of environment variables.
 */
int unset_env(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    env_t *current = *env;
    env_t *prev = NULL;

    if (!old_path || !shell)
        return 0;
    if (tab[1] == NULL) {
        shell->return_value = 1;
        dprintf(2, "unsetenv: Too few arguments.\n");
        return 1;
    }
    while (current) {
        if (strcmp(current->key, tab[1]) == 0) {
            remove_node(&current, &prev, env);
            return 0;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return 0;
}
