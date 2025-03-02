/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** return char** of word of an str
*/

#include "unistd.h"
#include "stdlib.h"

void go_to_next_word(char *str, int *i, char sep)
{
    while (str[*i] != '\0' && str[*i] == sep)
        (*i)++;
}

static void is_word(int *in_word, int *count)
{
    if (!(*in_word)) {
        (*in_word) = 1;
        (*count)++;
    }
}

int count_nb_word(const char *str, char sep)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != sep) {
            is_word(&in_word, &count);
        } else {
            in_word = 0;
        }
    }
    return count;
}

char *insert_word(char *str, int size, int i)
{
    int start = i - size;
    char *word = malloc(sizeof(char) * (size + 1));

    if (word == NULL)
        return NULL;
    for (int j = 0; j < size; j++)
        word[j] = str[start + j];
    word[size] = '\0';
    return word;
}

static void update_variable(int *size, int *slot, int *j, int type)
{
    if (type == 1) {
        (*size) = 0;
        (*slot)++;
    }
    if (type == 2) {
        (*size)++;
        (*j)++;
    }
}

char **fill_tab(char *str, char **tab, char sep)
{
    int size = 0;
    int slot = 0;
    int j = 0;

    go_to_next_word(str, &j, sep);
    while (str[j] != '\0') {
        if (str[j] == sep && size > 0) {
            tab[slot] = insert_word(str, size, j);
            go_to_next_word(str, &j, sep);
            update_variable(&size, &slot, NULL, 1);
        } else
            update_variable(&size, NULL, &j, 2);
    }
    if (size > 0)
        tab[slot] = insert_word(str, size, j);
    return tab;
}

char **my_str_to_word_array(char *str, char sep)
{
    int nb_word = count_nb_word(str, sep);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));

    if (tab == NULL)
        return NULL;
    tab[nb_word] = NULL;
    return fill_tab(str, tab, sep);
}
