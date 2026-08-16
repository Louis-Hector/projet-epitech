/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** handle_redir_op
*/

#include "shell.h"

/**
 * @brief Free arguments related to redirection from a command.
 *
 * This function releases the memory allocated for arguments
 * related to redirection (e.g., file paths) and sets them to NULL.
 *
 * @param new Pointer to the command structure.
 * @param i Index of the redirection argument to be removed.
 */
void remove_redir_args(command_t *new, int i)
{
    if (new->args[i]) {
        free(new->args[i]);
        new->args[i] = NULL;
    }
    if (new->args[i + 1]) {
        free(new->args[i + 1]);
        new->args[i + 1] = NULL;
    }
}

/**
 * @brief Update the redirection file and store its path.
 *
 * This function updates the redirection file path in the given command
 * structure and assigns the index of the redirection operator.
 *
 * @param new Pointer to the command structure.
 * @param args Array containing the redirection operator and file path.
 * @param i Index of the redirection operator.
 * @param redir Pointer to store the index of the redirection operator.
 */
static void update_redirection(command_t *new, char **args, int i, int *redir)
{
    if (new->file)
        free(new->file);
    if (args[i + 1] == NULL) {
        new->file = NULL;
        return;
    }
    new->file = strdup(args[i + 1]);
    *redir = i;
}

/**
 * @brief Set the file path for the redirection operator.
 *
 * This function iterates through the arguments array to find redirection
 * operators, and updates the redirection file path using 'update_redirection'.
 *
 * @param new Pointer to the command structure.
 * @param args Array of arguments containing potential redirection operators.
 * @param redir Pointer to store the index of the redirection operator.
 */
void set_redirection_file(command_t *new, char **args, int *redir)
{
    for (int i = 0; args[i] != NULL; i++) {
        if (!(strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0 ||
            strcmp(args[i], "<") == 0 || strcmp(args[i], "<<") == 0))
            continue;
        update_redirection(new, args, i, redir);
    }
}

/**
 * @brief Handle redirections in a command string.
 *
 * This function processes the redirection operators in a full command string,
 * updates the redirection file path, and removes related arguments.
 *
 * @param new Pointer to the command structure.
 * @param full_command The command string to process.
 * @return Always returns 0.
 */
int handle_redir(command_t *new, char *full_command)
{
    int redir = -1;
    char *new_command = put_space(full_command);

    new->args = my_str_to_word_array(new_command, " \t");
    free(new_command);
    set_redirection_file(new, new->args, &redir);
    if (redir != -1)
        remove_redir_args(new, redir);
    return 0;
}

/**
 * @brief Handle logical and sequential operators in a command string.
 *
 * This function processes operators such as '||', '&&', '|', ';', and newline,
 * splitting the commands accordingly and updating indices.
 *
 * @param commands Pointer to an array of command structures.
 * @param input The input command string.
 * @param index Pointer to the start index for parsing.
 * @param i Pointer to the current index in the input string.
 * @return Returns -1 if an error occurs, otherwise returns 0.
 */
int handle_operator(command_t **commands,
    char *input, int *index, int *i)
{
    if ((input[*i] == '|' && input[*i + 1] == '|') ||
        (input[*i] == '&' && input[*i + 1] == '&')) {
        if (parse(commands, input, *index, *i) == 84)
            return -1;
        *index = *i + 2;
        *i += 1;
        return 0;
    }
    if (input[*i] == ';' || input[*i] == '|' || input[*i] == '\n') {
        if (parse(commands, input, *index, *i) == 84)
            return -1;
        *index = *i + 1;
    }
    return 0;
}
