/*
** EPITECH PROJECT, 2025
** delete
** File description:
** delete data in table
*/

#include "../libshell/hashtable.h"

int relink_nodes(int hash_value, linked_list_t *lists, hashtable_t *ht, int i)
{
    tab_t *to_delete = NULL;

    if (lists->current->cipher_value == hash_value) {
        to_delete = lists->current;
        if (lists->previous == NULL)
            ht->tab[i] = lists->current->next;
        else
            lists->previous->next = lists->current->next;
        lists->current = lists->current->next;
        free(to_delete);
    } else {
        lists->previous = lists->current;
        lists->current = lists->current->next;
    }
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hash_value = ht->hash(key, ht->len);
    tab_t *current = NULL;
    tab_t *previous = NULL;
    linked_list_t lists = {NULL};

    for (int i = 0; i < ht->len; i++) {
        lists.current = ht->tab[i];
        lists.previous = NULL;
        while (lists.current != NULL)
            relink_nodes(hash_value, &lists, ht, i);
    }
    return 0;
}
