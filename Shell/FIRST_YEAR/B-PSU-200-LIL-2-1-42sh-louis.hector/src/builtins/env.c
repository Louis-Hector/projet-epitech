/*
** EPITECH PROJECT, 2025
** env
** File description:
** env
*/

#include "shell.h"

/**
 * @brief Check if the command line arguments for env are valid.
 *
 * This function checks if the command line arguments for the env command
 * are valid. If there are more than one argument, it prints an error message
 * and sets the shell's return value to 1.
 *
 * @param tab The array of command line arguments.
 * @param shell The shell structure.
 * @return 1 if there are too many arguments, 0 otherwise.
 */
int verif_env_argument(char **tab, shell_t *shell)
{
    int count = 0;

    for (int i = 0; tab[i] != NULL; i++)
        count++;
    if (count > 1) {
        dprintf(2, "env: %s: No such file or directory\n", tab[1]);
        shell->return_value = 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Display the environment variables.
 *
 * This function iterates through the linked list of environment variables
 * and prints each variable in the format "key=value". If the value is NULL,
 * it prints just the key.
 *
 * @param tab The array of command line arguments.
 * @param env The linked list of environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 if there are too many arguments.
 */
int display_env(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    env_t *current = *env;

    if (!old_path)
        return 0;
    if (verif_env_argument(tab, shell) == 1)
        return 1;
    while (current != NULL) {
        printf("%s=", current->key);
        if (current->value != NULL)
            printf("%s\n", current->value);
        else
            printf("\n");
        current = current->next;
    }
    shell->return_value = 0;
    return 0;
}
