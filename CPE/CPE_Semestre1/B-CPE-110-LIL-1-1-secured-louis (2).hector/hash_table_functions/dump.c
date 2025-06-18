/*
** EPITECH PROJECT, 2025
** dump
** File description:
** display hash table
*/

#include "../libshell/hashtable.h"

void display(tab_t *current)
{
    if (current->cipher_value != 0 && current->path != NULL)
        printf("> %d  -  %s\n", current->cipher_value, current->path);
}

void ht_dump(hashtable_t *ht)
{
    tab_t *current;

    for (int i = 0; i < ht->len; i++) {
        printf("[%i]:\n", i);
        current = ht->tab[i];
        while (current != NULL) {
            display(current);
            current = current->next;
        }
    }
}
