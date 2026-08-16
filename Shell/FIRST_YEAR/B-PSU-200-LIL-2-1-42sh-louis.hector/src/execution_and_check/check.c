/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** check
*/

#include "shell.h"

/**
 * @brief Check if the last command was an echo with "$?" argument.
 *
 * This function checks if the first argument of the command is "echo"
 * and if the second argument is "$?". If so, it prints the return value
 * of the last command executed and returns 1. Otherwise, it returns 0.
 *
 * @param commands The command structure.
 * @param shell The shell structure.
 * @return 1 if the last command was an echo with "$?", 0 otherwise.
 */
int return_status_last_command(command_t *commands, shell_t *shell)
{
    if (strcmp(commands->args[0], "echo") == 0 && commands->args[1]
        && strcmp(commands->args[1], "$?") == 0) {
        printf("%d", shell->return_value);
        for (int i = 2; commands->args[i] != NULL; i++)
            printf(" %s", commands->args[i]);
        printf("\n");
        shell->return_value = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief Check the operator type and execute the corresponding command.
 *
 * This function checks the operator type of the command list and
 * executes the corresponding command. It handles pipes and redirections.
 *
 * @param commands The command structure.
 * @param env The environment variables.
 * @param shell The shell structure.
 * @return 1 if a pipe or redirection was found, 0 otherwise.
 */
int check_operator(command_t **commands, env_t **env, shell_t *shell)
{
    command_t *start = *commands;

    if (return_status_last_command(start, shell) == 1)
        return 1;
    if (check_alias_cmd(&shell->alias, start->args, shell) == 1)
        return 1;
    if (start->op == PIPE) {
        while (*commands && (*commands)->op == PIPE)
            *commands = (*commands)->next;
        shell->return_value = execute_pipe_sequence(start, env, shell);
        return 1;
    }
    if (start->redir != NONE_REDIR) {
        shell->return_value = check_redirection(start, env, shell);
        return 1;
    }
    return 0;
}

/**
 * @brief Check for null commands in the command list.
 *
 * This function checks if there are any null commands in the command list.
 * A null command is defined as a command with no arguments and either a
 * logical operator or a redirection operator. If such a command is found,
 * an error message is printed, and the shell's return value is set to 1.
 *
 * @param commands The command structure.
 * @param shell The shell structure.
 * @return 1 if a null command is found, 0 otherwise.
 */
int check_null_command(command_t *commands, shell_t *shell)
{
    command_t *current = commands;

    for (; current; current = current->next) {
        if ((current->args[0] == NULL && (current->op != NONE
            || current->redir != NONE_REDIR))) {
            dprintf(2, "Invalid null command.\n");
            shell->return_value = 1;
            return 1;
        }
        if (current->op != NONE && current->next->args[0] == NULL) {
            dprintf(2, "Invalid null command.\n");
            shell->return_value = 1;
            return 1;
        }
        if (commands->args[0] == NULL)
            return 0;
    }
    return 0;
}
