/*
** EPITECH PROJECT, 2025
** browse builtins
** File description:
** browse builtins
*/

#include "builtin.h"
#include "shell.h"

/**
 * @brief Frees the old path if the return value is -1.
 *
 * This function checks if the return value is -1 and frees the old path
 * if it is. It returns the original return value.
 *
 * @param return_value The return value to check.
 * @param old_path The old path to free if return_value is -1.
 * @return The original return value.
 */
int free_old_path(int return_value, char *old_path)
{
    if (return_value == -1) {
        free(old_path);
        return -1;
    }
    return return_value;
}

/**
 * @brief Checks if the command is a built-in command and executes it.
 *
 * This function iterates through the list of built-in commands and
 * checks if the current command matches any of them. If a match is found,
 * it executes the corresponding built-in function.
 *
 * @param current The current command to check.
 * @param env The environment variables.
 * @param shell The shell structure.
 * @return 0 if a built-in command was executed, 1 if not, -1 on error.
 */
int check_builtins(command_t *current, env_t **env, shell_t *shell)
{
    static char *old_path = NULL;
    int return_value = shell->return_value;

    for (int i = 0; i < 14; i++) {
        if (strcmp(current->args[0], builtins[i].name) == 0) {
            return_value = builtins[i].builtins(current->args,
                env, &old_path, shell);
            return free_old_path(return_value, old_path);
        }
    }
    return 2;
}
