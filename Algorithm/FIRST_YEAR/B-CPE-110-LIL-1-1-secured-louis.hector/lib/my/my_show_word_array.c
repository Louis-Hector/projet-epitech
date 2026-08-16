/*
** EPITECH PROJECT, 2024
** my_show_word
** File description:
** Write a function that displays the content of an array of words.
*/

#include "my.h"
#include <unistd.h>

int my_show_word_array(char *const *tab)
{
    int i = 0;

    while (tab[i] != 0) {
        write(1, tab[i], my_strlen(tab[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}
