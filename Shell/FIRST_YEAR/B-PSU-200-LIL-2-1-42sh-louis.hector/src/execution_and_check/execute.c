/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** executions
*/

#include "shell.h"

/**
 * @brief Handles the execution of a command.
 *
 * This function checks for globbing, built-in commands,
 * and executes the command if necessary.
 *
 * @param cmd The command to execute.
 * @param tmp Temporary command structure.
 * @param shell The shell structure.
 * @param env The environment variables.
 * @return 0 on success, -1 on error.
 */
int handle_command_execution(command_t *cmd,
    command_t *tmp, shell_t *shell, env_t **env)
{
    int value_build = 0;

    if (check_globbins(cmd, shell) == 1)
        return 0;
    modif_alias_cmd(&shell->alias, cmd->args, shell);
    value_build = check_builtins(cmd, env, shell);
    if (value_build == 0 || value_build == 1)
        return 0;
    if (value_build == -1) {
        free(shell->tmp_command);
        free_command(&tmp);
        return -1;
    }
    if (execute_command(shell, env, cmd) == -1) {
        free(shell->tmp_command);
        free_command(&tmp);
        return -1;
    }
    return 0;
}

/**
 * @brief Executes a loop of commands with logical operators.
 *
 * This function iterates through the list of commands and executes them
 * based on the logical operators (AND, OR) between them.
 *
 * @param tmp Temporary command structure.
 * @param commands The list of commands to execute.
 * @param shell The shell structure.
 * @param env The environment variables.
 * @return 0 on success, -1 on error.
 */
int execute_loop(command_t *tmp,
    command_t *commands, shell_t *shell, env_t **env)
{
    if (!commands || !shell || !env) {
        dprintf(2, "Invalid arguments to execute_loop\n");
        return -1;
    }
    if (check_null_command(commands, shell)
    || commands->args[0] == NULL)
        return 0;
    for (; commands; commands = commands->next) {
        if (check_operator(&commands, env, shell) == 1)
            continue;
        if (handle_command_execution(commands, tmp, shell, env) == -1)
            return -1;
        if (commands->op == OR && shell->return_value == 0)
            return 0;
        if (commands->op == AND && shell->return_value != 0)
            commands = commands->next;
    }
    return 0;
}

/**
 * @brief Executes the shell command.
 *
 * This function handles input, parses it into commands,
 * and executes the commands in a loop.
 *
 * @param env The environment variables.
 * @param shell_arg The shell structure.
 * @param history The command history.
 * @return 0 on success, -1 on error, 1 if no command to execute.
 */
int execute(env_t **env,
    shell_t *shell_arg, history_t **history)
{
    command_t *commands = NULL;
    int status = handle_input_and_parse(env, shell_arg, history, &commands);

    if (status == -1 || status == 1)
        return status;
    return execute_parsed_commands(commands, shell_arg, env);
}

/**
 * @brief Executes the parsed commands.
 *
 * This function executes the parsed commands in a loop,
 * handling logical operators and redirections.
 *
 * @param commands The list of commands to execute.
 * @param shell_arg The shell structure.
 * @param env The environment variables.
 * @return 0 on success, -1 on error.
 */
int execute_parsed_commands(command_t *commands,
    shell_t *shell_arg, env_t **env)
{
    command_t *tmp = commands;

    if (!shell_arg || !env) {
        dprintf(2, "Invalid arguments to execute_parsed_commands\n");
        return -1;
    }
    if (shell_arg->command != NULL) {
        free(shell_arg->command);
        shell_arg->command = NULL;
    }
    if (commands && execute_loop(tmp, commands, shell_arg, env) == -1)
        return -1;
    free(shell_arg->tmp_command);
    shell_arg->tmp_command = NULL;
    free_command(&tmp);
    return 0;
}
