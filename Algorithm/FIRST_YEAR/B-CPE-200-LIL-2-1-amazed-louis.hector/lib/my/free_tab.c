/*
** EPITECH PROJECT, 2025
** free tab
** File description:
** free an array
*/

#include <stdlib.h>

void free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; i++) {
        free(tab[i]);
    }
    free(tab);
}
