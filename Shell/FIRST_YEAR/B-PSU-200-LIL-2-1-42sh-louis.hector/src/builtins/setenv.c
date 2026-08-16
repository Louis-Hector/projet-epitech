/*
** EPITECH PROJECT, 2025
** setenv
** File description:
** setenv
*/

#include "shell.h"

/**
 * @brief Check if the number of arguments is valid for setenv.
 *
 * This function checks if the number of arguments provided for setenv
 * is valid. It returns 1 if the number of arguments is invalid, 0 otherwise.
 *
 * @param env The linked list of environment variables.
 * @param nb_arg The number of arguments provided.
 * @param tab The array of command line arguments.
 * @return 1 if the number of arguments is invalid, 0 otherwise.
 */
int set_env(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    int nb_arg = 0;

    if (!old_path)
        return 0;
    if (env == NULL)
        return 1;
    for (int i = 0; tab[i] != NULL; i++)
        nb_arg++;
    if (check_arg_number(env, nb_arg, tab) == 1
        || is_data_present(tab, env) == 1
        || is_data_missing(tab, env) == 1) {
            shell->return_value = 1;
        return 1;
    }
    shell->return_value = 0;
    return 0;
}
