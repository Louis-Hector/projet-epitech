/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** pipe.c
*/

#include "shell.h"

/**
 * @brief Handles redirection and execution of the command.
 *
 * This function checks for redirection, built-in commands,
 * and executes the command if necessary.
 *
 * @param cmd The command to execute.
 * @param env The environment variables.
 * @param shell The shell structure.
 */
static void handle_redirection_and_execution(command_t *cmd,
    env_t **env, shell_t *shell)
{
    if (cmd->redir != NONE_REDIR) {
        if (check_redirection(cmd, env, shell) == 1) {
            free_command(&cmd);
            exit(1);
        }
    }
    if (check_builtins(cmd, env, shell) != 2) {
        free_command(&cmd);
        exit(shell->return_value);
    }
    execute_command(shell, env, cmd);
    free_command(&cmd);
    exit(shell->return_value);
}

/**
 * @brief Executes the command with the given pipe file descriptors.
 *
 * This function sets up the input and output redirection for the
 * command and executes it using execvp.
 *
 * @param cmd The command to execute.
 * @param tube The pipe file descriptors.
 * @param env The environment variables.
 * @param shell The shell structure.
 */
static void exec_pipe(command_t *cmd,
    int tube[2], env_t **env, shell_t *shell)
{
    if (cmd->op == PIPE) {
        close(tube[0]);
        if (dup2(tube[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            free_command(&cmd);
            exit(1);
        }
        close(tube[1]);
    }
    handle_redirection_and_execution(cmd, env, shell);
}

/**
 * @brief Updates the parent process with the current pipe status.
 *
 * This function closes the previous file descriptor and updates
 * the current pipe file descriptor for the next command.
 *
 * @param prev_fd Pointer to the previous file descriptor.
 * @param tube The current pipe file descriptors.
 * @param cmd The current command.
 */
static void update_parent(int *prev_fd, int tube[2], command_t *cmd)
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmd->op == PIPE) {
        close(tube[1]);
        *prev_fd = tube[0];
    } else {
        *prev_fd = -1;
    }
}

/**
 * @brief Checks if there is a previous file descriptor to use.
 *
 * This function checks if the previous file descriptor is valid
 * and redirects the input to it.
 *
 * @param prev_fd Pointer to the previous file descriptor.
 */
void check_previous_file(int *prev_fd)
{
    if (*prev_fd != -1) {
        if (dup2(*prev_fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(*prev_fd);
            exit(1);
        }
        close(*prev_fd);
    }
}

/**
 * @brief Waits for all child processes
 * to finish and captures their exit status.
 *
 * This function waits for all child processes to finish and captures
 * their exit status. It updates the shell's return value accordingly.
 *
 * @param prev_fd The previous file descriptor.
 * @param status Pointer to the exit status variable.
 * @param shell The shell structure.
 * @return Returns 0 on success, or 1 if an error occurs.
 */
int end_pipe(int prev_fd, int *status, shell_t *shell)
{
    int last_return_value = 0;

    if (prev_fd != -1)
        close(prev_fd);
    while (wait(status) > 0) {
        if (WIFEXITED(*status))
            last_return_value = WEXITSTATUS(*status);
        if (WIFSIGNALED(*status))
            last_return_value = 128 + WTERMSIG(*status);
    }
    shell->return_value = last_return_value;
    return last_return_value == 0 ? 0 : 1;
}

/**
 * @brief Launches a child process to execute the command.
 *
 * This function forks a new process and executes the command
 * in the child process. It handles the piping and redirection
 * as necessary.
 *
 * @param cmd The command to execute.
 * @param context The context containing the previous file descriptor
 * and other necessary information.
 * @return Returns 0 on success, or -1 if an error occurs.
 */
static int launch_child(command_t *cmd, pipe_context_t *context)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        check_previous_file(context->prev_fd);
        exec_pipe(cmd, context->tube, context->env, context->shell);
    }
    update_parent(context->prev_fd, context->tube, cmd);
    return 0;
}

/**
 * @brief Skips invalid commands that cannot be executed.
 *
 * This function checks if the next command in the pipeline is valid.
 * If the next command is invalid, it is skipped, and the function
 * returns true. Otherwise, it returns false.
 *
 * @param cmd The current command.
 * @param env The environment variables.
 * @return Returns true if the next command is invalid, false otherwise.
 */
static bool skip_invalid(command_t *cmd, env_t **env)
{
    command_t *next = cmd->next;

    if (cmd->op != PIPE || !next)
        return false;
    if (!is_valid_cmd(next, env))
        return true;
    return false;
}

/**
 * @brief Handles the creation of a pipe for inter-process communication.
 *
 * This function creates a pipe for the given command if the command
 * involves piping (i.e., cmd->op == PIPE). It returns 0 on success
 * or -1 if an error occurs.
 *
 * @param cmd The command for which to create a pipe.
 * @param tube The pipe file descriptors.
 * @return Returns 0 on success, or -1 if an error occurs.
 */
static int handle_pipe(command_t *cmd, int tube[2])
{
    if (cmd->op != PIPE)
        return 0;
    if (pipe(tube) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

/**
 * @brief Executes a single command in the pipeline.
 *
 * This function executes a single command in the pipeline,
 * handling pipes and redirections as necessary.
 *
 * @param cmd The command to execute.
 * @param context The context containing the previous file descriptor
 * and other necessary information.
 * @return Returns 0 on success, or -1 if an error occurs.
 */
static int execute_single_command(command_t *cmd, pipe_context_t *context)
{
    if (skip_invalid(cmd, context->env))
        return 0;
    if (handle_pipe(cmd, context->tube) == -1)
        return -1;
    if (launch_child(cmd, context) == -1)
        return -1;
    return 0;
}

/**
 * @brief Executes a sequence of commands connected by pipes.
 *
 * This function executes a sequence of commands, each connected
 * by pipes. It handles the creation of pipes and the execution
 * of each command in the pipeline.
 *
 * @param cmds The list of commands to execute.
 * @param env The environment variables.
 * @param shell The shell structure.
 * @return Returns 0 on success, or -1 if an error occurs.
 */
int execute_pipe_sequence(command_t *cmds, env_t **env, shell_t *shell)
{
    pipe_context_t context = { .prev_fd = NULL, .env = env, .shell = shell };
    int status = 0;
    int result = 0;

    context.prev_fd = malloc(sizeof(int));
    if (!context.prev_fd)
        return -1;
    *context.prev_fd = -1;
    for (; cmds; cmds = cmds->next) {
        if (execute_single_command(cmds, &context) == -1) {
            free(context.prev_fd);
            return -1;
        }
        if (cmds->op != PIPE)
            break;
    }
    result = end_pipe(*context.prev_fd, &status, shell);
    free(context.prev_fd);
    return result;
}
