/*
** EPITECH PROJECT, 2025
** exit
** File description:
** exit
*/

#include "shell.h"

/**
 * @brief Check if the string is numeric.
 *
 * This function checks if the given string represents a valid numeric value.
 * Checks each character to ensure it is a digit.
 *
 * @param str The string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
static int is_numeric(char *str)
{
    int i = 0;

    if (str && str[0] == '-')
        i = 1;
    for (; str[i]; i++) {
        if (!isdigit(str[i])) {
            dprintf(2, "exit: Expression Syntax.\n");
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Exit the shell with the specified exit value.
 *
 * This function checks if the user provided an exit value. If the value is
 * numeric, it sets the shell's exit status and returns -1 to indicate exit.
 * If the value is not numeric, it prints an error message and returns 1.
 *
 * @param tab The array of command line arguments.
 * @param env The linked list of environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return -1 if exit is successful, 1 if there was an error.
 */
int exit_shell(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    if (!tab || !env || !old_path || !shell)
        return 0;
    if (tab[1]) {
        if (is_numeric(tab[1])) {
            shell->is_exit = true;
            shell->exit_value = atoi(tab[1]);
            return -1;
        }
        return 1;
    }
    return -1;
}
