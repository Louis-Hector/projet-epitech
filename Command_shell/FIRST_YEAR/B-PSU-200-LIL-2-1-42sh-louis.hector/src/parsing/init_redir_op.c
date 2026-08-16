/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** init_redir_op
*/

#include "shell.h"

/**
 * @brief Initialize the operator field in the command structure.
 *
 * This function examines the first element of the array to determine
 * the type of logical or sequential operator ('||', '|', '&&', ';') and
 * updates the corresponding field in the 'command_t' structure.
 *
 * @param new Pointer to the command structure.
 * @param array Array of strings containing the command and operator.
 */
void init_operator(command_t *new, char **array)
{
    if (strncmp(array[0], "||", 2) == 0) {
        new->op = OR;
        return;
    }
    if (strncmp(array[0], "|", 1) == 0)
        new->op = PIPE;
    if (strncmp(array[0], "&&", 2) == 0)
        new->op = AND;
    if (strncmp(array[0], ";", 1) == 0)
        new->op = SEPARATOR;
}

/**
 * @brief Initialize the redirection type in the command structure.
 *
 * This function detects redirection operators ('>', '>>', '<', '<<') in the
 * command string and sets the corresponding field in the 'command_t' structure
 *
 * @param new Pointer to the command structure.
 * @param full_command The command string to analyze.
 * @param i Index of the current character in the command string.
 * @return Returns 1 if a redirection operator is identified, 0 otherwise.
 */
int init_redir(command_t *new, char *full_command, int i)
{
    if (full_command[i] == '>' && full_command[i + 1] == '>') {
        new->redir = R_DOUBLE_REDI;
        return 1;
    }
    if (full_command[i] == '>') {
        new->redir = R_SIMPLE_REDI;
        return 1;
    }
    if (full_command[i] == '<' && full_command[i + 1] == '<') {
        new->redir = L_DOUBLE_REDI;
        return 1;
    }
    if (full_command[i] == '<') {
        new->redir = L_SIMPLE_REDI;
        return 1;
    }
    return 0;
}

/**
 * @brief Populate the command structure with information from the input.
 *
 * This function extracts the relevant part of the input command string,
 * processes redirection operators and logical/sequential operators,
 * and updates the 'command_t' structure.
 *
 * @param new Pointer to the command structure.
 * @param input The input command string.
 * @param index Start index for parsing the input string.
 * @param end End index for parsing the input string.
 */
void add_infos(command_t *new, char *input, int index, int end)
{
    char *full_command = malloc(sizeof(char) * (end - index + 1));
    char **array = my_str_to_word_array(input + end, " \t");

    if (!full_command) {
        free_array(array);
        return;
    }
    for (int i = 0; i < (end - index); i++)
        full_command[i] = input[index + i];
    full_command[end - index] = '\0';
    handle_redir(new, full_command);
    init_operator(new, array);
    for (int i = 0; full_command[i] != '\0'; i++) {
        if (init_redir(new, full_command, i) == 1)
            break;
    }
    free(full_command);
    free_array(array);
}
