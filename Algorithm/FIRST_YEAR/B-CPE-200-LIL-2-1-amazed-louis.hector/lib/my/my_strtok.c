/*
** EPITECH PROJECT, 2025
** my_strtok
** File description:
** Fonction my_strtok
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *my_strtok(char *str, const char delim)
{
    static char *next_token = NULL;
    char *token = NULL;

    if (str == NULL)
        str = next_token;
    if (str == NULL)
        return NULL;
    token = str;
    while (*str != delim && *str != '\0')
        str++;
    if (*str == '\0')
        next_token = NULL;
    else {
        *str = '\0';
        next_token = str + 1;
    }
    return token;
}
