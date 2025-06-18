/*
** EPITECH PROJECT, 2025
** create hashtable
** File description:
** create
*/

#include "../libshell/hashtable.h"

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *new_hashtable = malloc(sizeof(hashtable_t));
    tab_t **tab = malloc(sizeof(tab_t *) * (len + 1));

    if (new_hashtable == NULL || tab == NULL)
        return NULL;
    tab[len] = NULL;
    new_hashtable->len = len;
    for (int i = 0; i < len; i++) {
        tab[i] = malloc(sizeof(tab_t));
        if (tab[i] == NULL)
            return NULL;
        tab[i]->cipher_value = 0;
        tab[i]->id = 0;
        tab[i]->path = NULL;
        tab[i]->next = NULL;
    }
    new_hashtable->len = len;
    new_hashtable->hash = hash;
    new_hashtable->tab = tab;
    return new_hashtable;
}
