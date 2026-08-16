/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** verif_pipe
*/

#include "shell.h"

/**
 * @brief Checks if the command is valid for execution.
 *
 * This function checks if the command can be executed by verifying
 * if the path is valid and if the command is not a built-in command.
 *
 * @param cmd The command to check.
 * @param env The environment variables.
 * @return Returns true if the command is valid, false otherwise.
 */
bool is_valid_cmd(command_t *cmd, env_t **env)
{
    char **env_array = from_list_to_array(env);
    char *path = getpath(cmd->args, env_array);
    bool is_valid = false;

    if (path != NULL) {
        is_valid = true;
        free(path);
    }
    free_array(env_array);
    return is_valid;
}
