/*
** EPITECH PROJECT, 2025
** which
** File description:
** which
*/

#include "shell.h"

/**
 * @brief Check if the command is a built-in command.
 *
 * This function checks if the command is a built-in command
 * and prints its name if it is. It also increments the index
 * of the arguments to skip the built-in command.
 *
 * @param tabs The array of command line arguments.
 * @param index_args The index of the current argument.
 * @return 1 if the command is a built-in command, 0 otherwise.
 */
int confirm_builtins(char **tabs, int *index_args)
{
    char *builtins_command[8] = {"cd", "where", "exit", "history",
        "setenv", "unsetenv", "foreach", "echo"};

    for (int i = 0; i < 8; i++) {
        if (strcmp(builtins_command[i], tabs[*index_args]) == 0) {
            printf("%s: shell built-in command.\n", tabs[*index_args]);
            *index_args += 1;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Check if the command is a built-in command and execute it.
 *
 * This function iterates through the list of built-in commands and
 * checks if the current command matches any of them. If a match is found,
 * it executes the corresponding built-in function.
 *
 * @param tab The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 */
void confirm_args_which(char **tab, char **env_array, shell_t *shell)
{
    char *path = NULL;

    for (int i = 1; tab[i] != NULL; i++) {
        shell->return_value = 0;
        path = getpath(tab + i, env_array);
        if (confirm_builtins(tab, &i) == 1) {
            i--;
            continue;
        }
        if (path == NULL) {
            dprintf(2, "%s: Command not found.\n", tab[i]);
            shell->return_value = 1;
            continue;
        }
        printf("%s\n", path);
        free(path);
    }
}

/**
 * @brief Check if the command is a built-in command and execute it.
 *
 * This function checks if the command is a built-in command and
 * executes it. If the command is not found, it prints an error message.
 *
 * @param tab The array of command line arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 0 on success, 1 on failure.
 */
int which(char **tab, env_t **env, char **old_path, shell_t *shell)
{
    char **env_array = from_list_to_array(env);

    if (!old_path || !shell || !env)
        return 1;
    if (tab[1] == NULL) {
        shell->return_value = 1;
        dprintf(2, "which: Too few arguments.\n");
        free_array(env_array);
        return 1;
    }
    confirm_args_which(tab, env_array, shell);
    free_array(env_array);
    return 0;
}
