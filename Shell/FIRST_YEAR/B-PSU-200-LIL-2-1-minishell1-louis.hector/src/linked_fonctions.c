/*
** EPITECH PROJECT, 2025
** linked_fonctions.c
** File description:
** createlinked list fonctions
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"


static linked_list_t *affect_node(char *line, char **env
    , linked_list_t *node, int i)
{
    char *cpy_ev = my_strdup(env[i]);

    line = (strtok(cpy_ev, "="));
    if (line == NULL)
        node->key = my_strdup("");
    else
        node->key = my_strdup(line);
    line = (strtok(NULL, "\n"));
    if (line == NULL)
        node->value = my_strdup("");
    else
        node->value = my_strdup(line);
    node->next = NULL;
    free(cpy_ev);
    return node;
}

linked_list_t *add_linked_list(linked_list_t *list, char **env)
{
    linked_list_t *node = NULL;
    linked_list_t *last_node = NULL;
    char *line = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        node = malloc(sizeof(linked_list_t));
        if (node == NULL)
            return NULL;
        node->key = NULL;
        node->value = NULL;
        if (affect_node(line, env, node, i) == NULL)
            return NULL;
        if (list == NULL)
            list = node;
        else
            last_node->next = node;
        last_node = node;
    }
    return list;
}

int make_env(linked_list_t **list, char **tab)
{
    linked_list_t *current = *list;
    int count = 0;

    for (int i = 0; tab[i] != NULL; i++)
        count++;
    if (count > 1) {
        mini_printf("env: %s: No such file or directory\n", tab[1]);
        return 1;
    }
    while (current != NULL) {
        mini_printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return 0;
}

void free_linked_list(linked_list_t **list)
{
    linked_list_t *current = *list;
    linked_list_t *previous = NULL;

    while (current != NULL) {
        previous = current;
        current = current->next;
        if (previous->key != NULL)
            free(previous->key);
        if (previous->value != NULL)
            free(previous->value);
        free(previous);
    }
}
