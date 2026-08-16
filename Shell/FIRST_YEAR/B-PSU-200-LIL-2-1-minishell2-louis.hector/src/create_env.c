/*
** EPITECH PROJECT, 2025
** create_env.c
** File description:
** create environnemt with linked list
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"
#include <signal.h>
#include <string.h>
#include "mylinkedlist.h"

void affect_values_to_tab(linked_list_t *current, char **board, int i)
{
    board[i] = malloc(sizeof(char)
        * (my_strlen(current->key) + my_strlen(current->value) + 2));
    if (board[i] == NULL)
        return;
    my_strcpy(board[i], current->key);
    my_strcat(board[i], "=");
    my_strcat(board[i], current->value);
}

char **create_environnement(linked_list_t **list)
{
    int count = 0;
    char **board = NULL;
    linked_list_t *current = *list;
    int i = 0;

    for (; current != NULL; current = current->next)
        count++;
    board = malloc(sizeof(char *) * (count + 1));
    if (board == NULL)
        return NULL;
    current = *list;
    while (current != NULL) {
        affect_values_to_tab(current, board, i);
        if (board == NULL)
            return NULL;
        current = current->next;
        i++;
    }
    board[i] = NULL;
    return board;
}
