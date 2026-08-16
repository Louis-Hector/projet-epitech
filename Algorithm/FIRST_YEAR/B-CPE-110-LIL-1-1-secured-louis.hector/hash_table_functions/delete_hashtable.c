/*
** EPITECH PROJECT, 2025
** delete hashtable
** File description:
** delete
*/

#include "../libshell/hashtable.h"

void delete_hashtable(hashtable_t *ht)
{
    tab_t *current = NULL;
    tab_t *to_delete = NULL;

    for (int i = 0; i < ht->len; i++) {
        current = ht->tab[i];
        while (current != NULL) {
            to_delete = current;
            current = current->next;
            free(to_delete);
        }
    }
    free(ht->tab);
    free(ht);
}
