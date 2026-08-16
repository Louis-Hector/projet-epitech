/*
** EPITECH PROJECT, 2024
** my_pustr
** File description:
** tab
*/

#include "my.h"

int my_putstr(char const *str)
{
    char const *i = str;

    while (*i != '\0') {
        my_putchar(*i);
        i++;
    }
    return 0;
}
