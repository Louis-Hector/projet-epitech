/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** globbins.c
*/

#include "shell.h"

/**
 *@file globbins.c
 *@brief Functions for handling globbing in shell commands.
 *
 *This file contains functions to process and expand globbing patterns
 *(e.g., wildcards like `*` and `?`) in shell commands. It uses the `glob`
 *library to match patterns and replace them with the corresponding file paths.
 *
 */

/**
 *@brief Increase the length of the resulting string based on glob results.
*
*This function calculates the total length of the resulting string after
*expanding globbing patterns. It iterates through the matched paths and
*adds their lengths to the total length.
*
*@param length A pointer to the total length to be updated.
*@param glob_result The result of the globbing operation.
*/
static void increase_length(int *length, glob_t glob_result)
{
    for (size_t i = 0; i < glob_result.gl_pathc; i++) {
        *length += strlen(glob_result.gl_pathv[i]);
        if (i < glob_result.gl_pathc - 1)
            (*length)++;
    }
}

/**
 *@brief Get the total length of the expanded globbing result.
*
*This function calculates the length of the resulting string after
*expanding globbing patterns. If no matches are found, it returns the
*length of the original input string.
*
*@param line The input string containing globbing patterns.
*@return The total length of the resulting string.
*/
static int get_globbins_length(char *line)
{
    int length = 0;
    glob_t glob_result = {0};

    if (glob(line, 0, NULL, &glob_result) == 0) {
        increase_length(&length, glob_result);
        globfree(&glob_result);
    } else {
        length = strlen(line);
    }
    return length;
}

/**
  *@brief Concatenate globbing results into a single string.
  *
  *This function takes the results of a globbing operation and concatenates
  *the matched paths into a single string, separated by spaces.
  *
  *@param new_line The string where the concatenated result will be stored.
  *@param glob_result The result of the globbing operation.
*/
static void concatenate_globbins(char *new_line, glob_t glob_result)
{
    for (size_t i = 0; i < glob_result.gl_pathc; i++) {
        strcat(new_line, glob_result.gl_pathv[i]);
        if (i < glob_result.gl_pathc - 1)
            strcat(new_line, " ");
    }
}

/**
 *@brief Replace globbing patterns in a line with their expanded results.
*
*This function processes a line containing globbing patterns, expands
*them using the `glob` library, and returns a new string with the expanded
*results. If no matches are found, the original line is returned.
*
*@param line The input string containing globbing patterns.
*@return A newly allocated string with the expanded results, or NULL if
*memory allocation fails.
*/
char *change_globbins_in_line(char *line)
{
    int length = get_globbins_length(line);
    glob_t glob_result = {0};
    char *new_line = malloc(length + 1);

    if (!new_line)
        return NULL;
    new_line[0] = '\0';
    if (glob(line, 0, NULL, &glob_result) == 0) {
            concatenate_globbins(new_line, glob_result);
            globfree(&glob_result);
    } else {
        strcpy(new_line, line);
    }
    return new_line;
}

char *from_array_to_line(char **args)
{
    int total_len = 0;
    int i = 0;
    char *line = NULL;

    while (args[i]) {
        total_len += strlen(args[i]) + 1;
        i++;
    }
    line = malloc(sizeof(char) * total_len);
    if (!line)
        return NULL;
    line[0] = '\0';
    for (i = 0; args[i]; i++) {
        strcat(line, args[i]);
        if (args[i + 1])
            strcat(line, " ");
    }
    return line;
}

int reformate_args(command_t *commands)
{
    char *new_line = from_array_to_line(commands->args);
    char **new_args = my_str_to_word_array(new_line, " ");

    free_array(commands->args);
    free(new_line);
    commands->args = new_args;
    if (commands->args == NULL)
        return 84;
    return 0;
}

static int check_no_match(command_t *commands, shell_t *shell
    , char *globbings, int i)
{
    if (strcmp(globbings, commands->args[i]) == 0) {
        shell->return_value = 1;
        free(globbings);
        dprintf(2, "%s: No match.\n", commands->args[0]);
        return 1;
    }
    return 0;
}

int check_globbins(command_t *commands, shell_t *shell)
{
    char *globbings = NULL;

    for (int i = 1; commands->args[i] != NULL; i++) {
        if (!(strchr(commands->args[i], '*')
        || strchr(commands->args[i], '?')
        || strchr(commands->args[i], '[')))
            continue;
        globbings = change_globbins_in_line(commands->args[i]);
        if (check_no_match(commands, shell, globbings, i) == 1)
            return 1;
        free(commands->args[i]);
        commands->args[i] = strdup(globbings);
        if (reformate_args(commands) == 84) {
            free(globbings);
            return 84;
        }
        free(globbings);
    }
    return 0;
}
