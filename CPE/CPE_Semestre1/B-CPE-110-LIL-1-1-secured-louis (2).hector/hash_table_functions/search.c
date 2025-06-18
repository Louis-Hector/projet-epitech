/*
** EPITECH PROJECT, 2025
** search
** File description:
** search in table
*/

#include "../libshell/hashtable.h"

char *browse_file(tab_t *current, int hash_value)
{
    while (current != NULL) {
        if (current->cipher_value == hash_value)
            return current->path;
        current = current->next;
    }
    return NULL;
}

char *ht_search(hashtable_t *ht, char *key)
{
    int hash_value = ht->hash(key, ht->len);
    tab_t *current = NULL;
    char *value = NULL;

    for (int i = 0; i < ht->len; i++) {
        current = ht->tab[i];
        value = browse_file(current, hash_value);
        if (value != NULL)
            return value;
    }
    return NULL;
}
