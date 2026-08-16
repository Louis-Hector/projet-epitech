/*
** EPITECH PROJECT, 2024
** mini_printf.c
** File description:
** Fonction who print a mini_printf
*/

#include "my.h"

int is_digit(char *line)
{
    for (int i = 0; line[i] != '\0'; i++)
        if (line[i] < '0' || line[i] > '9')
            return 84;
    return 0;
}
