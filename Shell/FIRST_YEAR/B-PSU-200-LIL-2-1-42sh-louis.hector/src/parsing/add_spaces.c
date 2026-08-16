/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** add_spaces
*/

#include "shell.h"

/**
 * @brief Count the number of redirections in the command.
 *
 * This function analyzes the given command string and counts the number of
 * redirection operators ('>', '>>', '<', '<<').
 *
 * @param full_command The command to analyze.
 * @param len Pointer to an integer to store the length of the command.
 * @param nb_redir Pointer to an integer to store the number of redirections.
 * @return Always returns 0.
 */
int count_nb_redir(char *full_command, int *len, int *nb_redir)
{
    for (; full_command[*len] != '\0'; *len += 1) {
        if ((full_command[*len] == '>' && full_command[*len + 1] == '>')
            || (full_command[*len] == '<' && full_command[*len + 1] == '<')) {
            *len += 1;
            *nb_redir += 1;
            continue;
        }
        if ((full_command[*len] == '>' && full_command[*len + 1] != '>')
            || (full_command[*len] == '<' && full_command[*len + 1] != '<')) {
            *nb_redir += 1;
            continue;
            }
    }
    return 0;
}

/**
 * @brief Handle double redirection operators and add spaces around them.
 *
 * This function processes double redirection operators ('>>' and '<<')
 * in the command string and adds spaces around them in the new command.
 *
 * @param full_command The original command string.
 * @param new_command The modified command string with spaces.
 * @param i Pointer to the current index in the original command.
 * @param j Pointer to the current index in the new command.
 * @return Returns 1 if a double redirection is processed, 0 otherwise.
 */
int double_redir(char *full_command, char *new_command, int *i, int *j)
{
    if ((full_command[*i] == '>' && full_command[*i + 1] == '>')
        || (full_command[*i] == '<' && full_command[*i + 1] == '<')) {
        new_command[*j] = ' ';
        *j += 1;
        new_command[*j] = full_command[*i];
        *j += 1;
        *i += 1;
        new_command[*j] = full_command[*i];
        *j += 1;
        new_command[*j] = ' ';
        *j += 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Handle simple redirection operators and add spaces around them.
 *
 * This function processes single redirection operators ('>' and '<')
 * in the command string and adds spaces around them in the new command.
 *
 * @param full_command The original command string.
 * @param new_command The modified command string with spaces.
 * @param i Pointer to the current index in the original command.
 * @param j Pointer to the current index in the new command.
 * @return Returns 1 if a simple redirection is processed, 0 otherwise.
 */
int simple_redir(char *full_command, char *new_command, int *i, int *j)
{
    if ((full_command[*i] == '>' && full_command[*i + 1] != '>')
        || (full_command[*i] == '<' && full_command[*i + 1] != '<')) {
        new_command[*j] = ' ';
        *j += 1;
        new_command[*j] = full_command[*i];
        *j += 1;
        new_command[*j] = ' ';
        *j += 1;
        return 1;
    }
    return 0;
}

/**
 * @brief Add spaces around redirection operators in a command string.
 *
 * This function analyzes a given command string, detects redirection operators
 * ('>', '>>', '<', '<<'), and creates a new command string with spaces added
 * around the operators.
 *
 * @param full_command The original command string.
 * @return A newly allocated string with spaces around redirection
 * operators, or NULL if memory allocation fails.
 */
char *put_space(char *full_command)
{
    char *new_command = NULL;
    int j = 0;
    int len = 0;
    int nb_redir = 0;

    if (full_command == NULL)
        return NULL;
    count_nb_redir(full_command, &len, &nb_redir);
    new_command = malloc(sizeof(char) * (len + (nb_redir * 2) + 1));
    if (!new_command)
        return NULL;
    for (int i = 0; i < len; i++) {
        if ((double_redir(full_command, new_command, &i, &j))
        || (simple_redir(full_command, new_command, &i, &j)))
            continue;
        new_command[j] = full_command[i];
        j++;
    }
    new_command[j] = '\0';
    return new_command;
}
