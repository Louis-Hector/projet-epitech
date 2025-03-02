/*
** EPITECH PROJECT, 2024
** my_str_to_word
** File description:
** Write a function that splits a string into words
*/

#include "my.h"
#include <stdlib.h>
#include <stdio.h>

#include <stdlib.h>


int count_word(char const *str)
{
    int nb_mot = 0;
    int i = 0;
    int len = my_strlen(str);

    while (i < len) {
        while (i < len && (str[i] < 'A' || str[i] > 'Z')
            && (str[i] < 'a' || str[i] > 'z')
            && (str[i] < '0' || str[i] > '9')) {
            i++;
        }
        if (i < len) {
            nb_mot++;
        }
        while (i < len && ((str[i] >= 'A' && str[i] <= 'Z')
            || (str[i] >= 'a' && str[i] <= 'z')
            || (str[i] >= '0' && str[i] <= '9'))) {
            i++;
        }
    }
    return nb_mot;
}

void count_char(char const *str, int *i, char **tab, int word)
{
    int start = *i;
    int longeur = 0;
    char *mot;

    while ((str[*i] >= 'A' && str[*i] <= 'Z')
        || (str[*i] >= 'a' && str[*i] <= 'z')
        || (str[*i] >= '0' && str[*i] <= '9')) {
        (*i)++;
    }
    longeur = *i - start;
    mot = malloc(sizeof(char) * (longeur + 1));
    for (int k = 0; k < longeur; k++) {
        mot[k] = str[start + k];
    }
    mot[longeur] = '\0';
    tab[word] = mot;
}

char **my_str_to_word_array(char const *str)
{
    int i = 0;
    int word = 0;
    int len = my_strlen(str);
    char **tab = malloc(sizeof(char *) * (count_word(str) + 1));

    while (i < len) {
        while (i < len && (str[i] < 'A' || str[i] > 'Z')
            && (str[i] < 'a' || str[i] > 'z')
            && (str[i] < '0' || str[i] > '9')) {
            i++;
        }
        if (i < len) {
            count_char(str, &i, tab, word);
            word++;
        }
    }
    tab[word] = NULL;
    return tab;
}
