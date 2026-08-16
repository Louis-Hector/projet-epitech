/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** process_parsing.c
*/

#include "shell.h"

/**
 * @brief Count the number of pipes ('|') in a given input string.
 *
 * This function iterates through the input string and counts the occurrences
 * of the pipe character ('|'). If the count exceeds 100, it returns 84 to
 * indicate an error.
 *
 * @param input The input string to be checked.
 * @return The count of pipes, or 84 if the count exceeds 100.
 */
int count_pipes(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '|')
            count++;
        if (count > 100)
            return 84;
    }
    return 0;
}

/**
 * @brief Check if the new command is the same as the last command in history.
 *
 * This function compares the new command with the last command stored in the
 * history linked list to determine if they are identical.
 *
 * @param new_command The new command to be compared.
 * @param history A pointer to the head of the history linked list.
 * @return 1 if the commands are the same, 0 otherwise.
 */
static int is_same_command(char *new_command, history_t **history)
{
    history_t *current = *history;

    if (!current)
        return 0;
    while (current->next) {
        current = current->next;
    }
    if (strcmp(current->command, new_command) == 0)
        return 1;
    if (strlen(new_command) < 1)
        return 1;
    return 0;
}

/**
 * @brief Prepare the environment and update the history with the new command.
 *
 * This function initializes the environment, retrieves the command's
 * timestamp and adds the command to the history list if it is not a duplicate.
 *
 * @param shell_arg A pointer to the shell structure to be updated.
 * @param history A pointer to the history linked list.
 * @param env A pointer to the environment structure.
 * @param time_str A pointer to store the timestamp of the command.
 * @return 1 on success, 0 on failure.
 */
static int prepare_environment(shell_t *shell_arg, history_t **history,
    env_t **env, char **time_str)
{
    shell_arg->environement = from_list_to_array(env);
    if (shell_arg->environement == NULL) {
        shell_arg->return_value = 84;
        return 0;
    }
    *time_str = get_time_of_command();
    if (!(*time_str)) {
        free_array(shell_arg->environement);
        shell_arg->return_value = 84;
        return 0;
    }
    if (is_same_command(shell_arg->command, history) == 0) {
        if (add_command_to_list(history, shell_arg->command, *time_str,
            get_size_of_history_list(history)) == 1) {
            free(*time_str);
            free_array(shell_arg->environement);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Handle the user input and execute the appropriate actions.
 *
 * This function prepares the environment, validates the command input,
 * checks for excessive pipes, and frees allocated resources.
 *
 * @param shell_arg A pointer to the shell structure to be updated.
 * @param history A pointer to the history linked list.
 * @param env A pointer to the environment structure.
 * @return 1 on success, 0 on failure.
 */
int handle_input(shell_t *shell_arg, history_t **history, env_t **env)
{
    char *time_str = NULL;

    if (!prepare_environment(shell_arg, history, env, &time_str))
        return 0;
    free(time_str);
    if (count_pipes(shell_arg->command) == 84) {
        shell_arg->return_value = 1;
        free_array(shell_arg->environement);
        return 0;
    }
    free_array(shell_arg->environement);
    return (shell_arg->command != NULL);
}
