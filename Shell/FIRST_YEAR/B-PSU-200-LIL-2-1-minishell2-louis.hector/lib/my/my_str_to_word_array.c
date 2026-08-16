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

void count_char(char const *str, int *i, char **tab, int word)
{
    int start = *i;
    int longeur = 0;
    char *mot;

    while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\0')
        (*i)++;
    longeur = *i - start;
    mot = malloc(sizeof(char) * (longeur + 1));
    if (mot == NULL)
        return;
    for (int k = 0; k < longeur; k++)
        mot[k] = str[start + k];
    mot[longeur] = '\0';
    tab[word] = mot;
}

int count_word(char const *str)
{
    int nb_mot = 0;
    int i = 0;
    int len = my_strlen(str);

    while (i < len) {
        while (i < len && ((str[i] == ' ' || str[i] == '\t')))
            i++;
        if (i < len)
            nb_mot++;
        while (i < len && ((str[i] != ' ' && str[i] != '\t')))
            i++;
    }
    return nb_mot;
}

char **my_str_to_word_array(char const *str)
{
    int i = 0;
    int word = 0;
    int len = my_strlen(str);
    char **tab = malloc(sizeof(char *) * (count_word(str) + 1));

    if (tab == NULL)
        return NULL;
    while (i < len) {
        while (i < len && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (i < len) {
            count_char(str, &i, tab, word);
            word++;
        }
    }
    tab[word] = NULL;
    return tab;
}
