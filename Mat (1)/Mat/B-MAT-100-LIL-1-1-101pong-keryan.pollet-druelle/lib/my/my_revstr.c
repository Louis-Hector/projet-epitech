/*
** EPITECH PROJECT, 2024
** my_revst
** File description:
** Write a function that reverses a string.
*/

#include "my.h"

char *my_revstr(char *str)
{
    int i = 0;
    int longeur = my_strlen(str);
    char temp;

    for (i; i < longeur / 2; i++) {
        temp = str[i];
        str[i] = str[longeur - 1 - i];
        str[longeur - 1 - i] = temp;
    }
    return str;
}
