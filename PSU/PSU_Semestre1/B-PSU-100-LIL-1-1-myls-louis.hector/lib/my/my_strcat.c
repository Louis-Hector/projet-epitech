/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** Fonction my_strcat
*/

#include <stdio.h>

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    for (j; src[j] != '\0'; j++) {
        dest[i + j] = src[j];
    }
    dest[i + j] = '\0';
    return dest;
}
