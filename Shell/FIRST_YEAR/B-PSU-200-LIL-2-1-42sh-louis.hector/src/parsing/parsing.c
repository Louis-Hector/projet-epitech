/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** parsing.c
*/

#include "shell.h"

/**
 * @brief Recovers the command line from the shell structure and parses it.
 *
 * This function allocates memory for a temporary command string,
 * copies the command from the shell structure, appends a newline character,
 * and then parses the input to create a new command structure.
 *
 * @param shell_arg Pointer to the shell structure containing the command.
 * @param commands Pointer to the pointer of the head of the command list.
 * @return Returns 0 on success, or -1 if memory allocation or parsing fails.
 */
int recup_line_command(shell_t *shell_arg, command_t **commands)
{
    if (shell_arg->command == NULL)
        return 0;
    shell_arg->tmp_command = malloc(sizeof(char)
    * (strlen(shell_arg->command) + 2));
    if (shell_arg->tmp_command == NULL)
        return -1;
    strcpy(shell_arg->tmp_command, shell_arg->command);
    shell_arg->tmp_command[strlen(shell_arg->command)] = '\n';
    shell_arg->tmp_command[strlen(shell_arg->command) + 1] = '\0';
    if (parse_input(commands, shell_arg->tmp_command) == -1) {
        free(shell_arg->tmp_command);
        return -1;
    }
    return 0;
}

/**
 * @brief Handles input from the user and parses it into commands.
 *
 * This function reads user input, updates the history,
 * and parses the input into a list of commands.
 *
 * @param env Pointer to the environment variables.
 * @param shell_arg Pointer to the shell structure.
 * @param history Pointer to the history linked list.
 * @param commands Pointer to the pointer of the head of the command list.
 * @return Returns 0 on success, or -1 if an error occurs.
 */
int handle_input_and_parse(env_t **env,
    shell_t *shell_arg, history_t **history, command_t **commands)
{
    int status = 0;

    if (handle_input(shell_arg, history, env)) {
        if (from_list_to_file(history, shell_arg->history_path) == 84)
            return -1;
    }
    status = recup_line_command(shell_arg, commands);
    if (status == -1)
        return -1;
    if (status)
        return 1;
    return 0;
}

/**
 * @brief Parse a segment of the input and add a new command to the list.
 *
 * This function creates a new command structure, initializes its fields,
 * fills it with information from the input string segment, and appends it
 * to the list of commands. If the 'commands' list is empty, it initializes it.
 *
 * @param commands Pointer to the pointer of the head of the command list.
 * @param input The input string containing the command to be parsed.
 * @param index The starting index of the command segment in the input string.
 * @param i The ending index of the command segment in the input string.
 * @return Returns 0 on success, or 84 if memory allocation fails.
 */
int parse(command_t **commands, char *input, int index, int i)
{
    command_t *new = malloc(sizeof(command_t));
    command_t *tmp = *commands;

    if (!new)
        return 84;
    new->file = NULL;
    new->args = NULL;
    new->next = NULL;
    new->redir = NONE_REDIR;
    new->op = NONE;
    add_infos(new, input, index, i);
    if (*commands == NULL) {
        *commands = new;
        return 0;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return 0;
}

/**
 * @brief Parse the entire input string into a list of commands.
 *
 * This function iterates through the input string, identifies operators (e.g.,
 * '|', ';', '&&', '||', newline) using 'handle_operator', and splits the input
 * into separate commands. Each command is processed and added to the list.
 *
 * @param commands Pointer to the pointer of the head of the command list.
 * @param input The input string containing all commands to be parsed.
 * @return Returns 0 on success, or -1 if an error occurs during parsing.
 */
int parse_input(command_t **commands, char *input)
{
    int index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (handle_operator(commands, input, &index, &i) == -1)
            return -1;
    }
    return 0;
}
