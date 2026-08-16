/*
** EPITECH PROJECT, 2025
** error_handling
** File description:
** check header
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "op.h"

void format_line(char *line)
{
    if (line[my_strlen(line) - 1] == '\n')
        line[my_strlen(line) - 1] = '\0';
    line = check_comment(line);
}

void free_tab(char **args)
{
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

void count_number(int *number_guillemets, char **input, int i)
{
    for (int j = 0; input[i][j] != '\0'; j++) {
        if (input[i][j] == '"')
            (*number_guillemets)++;
    }
    return;
}

static int count_number_args(char *line, int *i, int *count)
{
    if (line[*i] == ' ') {
        (*count)++;
        while (line[*i] == ' ')
            (*i)++;
    }
    if (line[*i] == '"') {
        (*i)++;
        while (*i < my_strlen(line) && line[*i] != '"')
            (*i)++;
        (*i)++;
        while (*i < my_strlen(line) && line[*i] == ' ')
            (*i)++;
        if (line[*i] != ' ' && line[*i] != '\0')
            return 1;
    }
    return 0;
}

int check_header(char **input, char *line)
{
    int count = 1;
    int number_guillemets = 0;
    int i = 0;

    if (my_strcmp(input[0], ".name") != 0
        && my_strcmp(input[0], ".comment") != 0)
        return 84;
    while (line[i] == ' ')
        i++;
    for (; line[i] != '\0'; i++)
        if (count_number_args(line, &i, &count) == 1)
            return 84;
    if (count != 2)
        return 84;
    for (int i = 0; input[i] != NULL; i++)
        count_number(&number_guillemets, input, i);
    if (number_guillemets != 2)
        return 84;
    return 0;
}

char *check_comment(char *line)
{
    char *buffer = line;
    int i = 0;

    for (; line[i] != '\0'; i++) {
        if (line[i] == '#') {
            buffer = my_strtok(line, '#');
            break;
        }
    }
    if (i > 0 && buffer[i - 1] == ' ')
        buffer[i - 1] = '\0';
    return buffer;
}
