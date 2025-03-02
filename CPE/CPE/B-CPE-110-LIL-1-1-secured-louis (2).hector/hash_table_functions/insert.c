/*
** EPITECH PROJECT, 2025
** insert
** File description:
** insert data in table
*/

#include "../libshell/hashtable.h"

int browse_list(tab_t **list, tab_t *new_node)
{
    tab_t *current = *list;

    while (current != NULL) {
        if (current->cipher_value == new_node->cipher_value) {
            current->path = new_node->path;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    tab_t *new_node = malloc(sizeof(tab_t));
    tab_t **list = NULL;

    if (new_node == NULL || key == NULL || value == NULL || ht == NULL)
        return 84;
    new_node->cipher_value = ht->hash(key, ht->len);
    new_node->id = new_node->cipher_value % ht->len;
    new_node->path = value;
    new_node->next = NULL;
    list = &ht->tab[new_node->id];
    if (browse_list(list, new_node) == 1)
        return 0;
    new_node->next = *list;
    *list = new_node;
    return 0;
}
