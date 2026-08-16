/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** main
*/

#include "shell.h"

/**
 * @brief Launches the shell loop in interactive mode.
 *
 * This function displays a prompt, reads user input,
 * and executes the command in a loop until exit.
 *
 * @param linked_env Pointer to the linked list of environment variables.
 * @param history Pointer to the history list.
 * @param shell_arg Pointer to the shell structure.
 */
void launch_loop_interactive(env_t **linked_env,
    history_t **history, shell_t *shell_arg)
{
    int status_exit = 0;

    while (1) {
        printf(GREEN "-> " CYAN "%s "RESET, shell_arg->prompt);
        shell_arg->history = *history;
        browse_history(shell_arg);
        status_exit = execute(linked_env, shell_arg, history);
        if (status_exit == -1)
            return;
    }
}

/**
 * @brief Launches the shell loop in non-interactive mode using getline.
 *
 * This function reads user input from stdin using getline,
 * executes the command, and handles the exit status.
 *
 * @param linked_env Pointer to the linked list of environment variables.
 * @param history Pointer to the history linked list.
 * @param shell_arg Pointer to the shell structure.
 */
void launch_loop_getline(env_t **linked_env,
    history_t **history, shell_t *shell_arg)
{
    char *line = NULL;
    size_t size = 0;
    int status_exit = 0;

    while (getline(&line, &size, stdin) != -1) {
        line[strlen(line) - 1] = '\0';
        shell_arg->command = strdup(line);
        status_exit = execute(linked_env, shell_arg, history);
        if (status_exit == -1)
            return;
        if (shell_arg->return_value != 0)
            return;
    }
    free(line);
}

/**
 * @brief Launches the shell loop based on the input method.
 *
 * This function determines whether to run the shell in interactive mode
 * (using a terminal) or in non-interactive mode (using getline).
 * It calls the appropriate function to handle user input.
 *
 * @param linked_env Pointer to the linked list of environment variables.
 * @param history Pointer to the history list.
 * @param shell_arg Pointer to the shell structure.
 */
void launch_loop(env_t **linked_env,
    history_t **history, shell_t *shell_arg)
{
    if (isatty(0))
        launch_loop_interactive(linked_env, history, shell_arg);
    else
        launch_loop_getline(linked_env, history, shell_arg);
}

/**
 * @brief Main function of the shell.
 *
 * The entry point of the shell program. It initializes resources, processes
 * user input in a loop, and cleans up resources before exiting.
 *
 * @param ac Argument count.
 * @param av Argument vector.
 * @param env Environment variables.
 * @return Returns last exit status of the shell or
 *  returns 84 if an error occurs during initialization or execution.
 */
int main(int ac, char **av, char **env)
{
    env_t *linked_env = NULL;
    history_t *history = {NULL};
    shell_t shell_arg = {0};

    shell_arg.history_path = get_home_user("/.42sh_history");
    if (create_files(&shell_arg) == 84 || ac < 1 || !av[0])
        return 84;
    history = from_file_to_list(&history, shell_arg.history_path);
    linked_env = from_array_to_list(linked_env, env);
    launch_loop(&linked_env, &history, &shell_arg);
    free_history(history, shell_arg.history_path);
    free(shell_arg.prompt);
    is_free(&linked_env, &shell_arg);
    if (shell_arg.is_exit)
        return shell_arg.exit_value;
    return shell_arg.return_value;
}
