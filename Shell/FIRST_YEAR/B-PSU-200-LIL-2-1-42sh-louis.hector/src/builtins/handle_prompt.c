/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** handle_prompt
*/

#include "shell.h"

/**
 * @brief Handles the prompt command in the shell.
 *
 * This function checks if the command is "prompt" and updates the shell
 * prompt accordingly. If no argument is provided, it sets the prompt to
 * the current working directory followed by a '>'.
 *
 * @param commands The array of command arguments.
 * @param env The environment variables.
 * @param old_path The old path to free if necessary.
 * @param shell The shell structure.
 * @return 1 if the prompt was updated, 0 otherwise.
 */
int handle_prompt(char **commands,
    env_t **env, char **old_path, shell_t *shell)
{
    char cwd[PATH_MAX];

    if (commands[0] == NULL || !env || !old_path)
        return 0;
    if (strcmp(commands[0], "prompt") == 0
    && commands[1] != NULL) {
        free(shell->prompt);
        shell->prompt = strdup(commands[1]);
        return 1;
    }
    if (strcmp(commands[0], "prompt") == 0) {
        if (shell->prompt != NULL)
            free(shell->prompt);
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            strcat(cwd, ">");
            shell->prompt = strdup(cwd);
            return 1;
        }
    }
    return 0;
}
