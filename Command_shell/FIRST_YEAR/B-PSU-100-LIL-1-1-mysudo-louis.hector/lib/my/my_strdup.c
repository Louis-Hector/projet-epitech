/*
** EPITECH PROJECT, 2024
** my_strdup
** File description:
** Write a function that allocates memory and copies the string
*/


#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *chaine = malloc(sizeof(char) * (len + 1));

    my_strcpy(chaine, src);
    return chaine;
}
