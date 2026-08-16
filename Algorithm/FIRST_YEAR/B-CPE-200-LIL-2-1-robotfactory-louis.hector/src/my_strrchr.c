/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** my_strrchr
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

char *my_strrchr(char *str, char c)
{
    char *str_cpy = malloc(sizeof(char) * my_strlen(str) + 1);
    char *last_occ = NULL;

    str_cpy = my_strcpy(str_cpy, str);
    while (*str_cpy) {
        if (*str_cpy == c)
            last_occ = (char *)str_cpy;
        str_cpy++;
    }
    if (last_occ == NULL)
        return str;
    return last_occ + 1;
}
