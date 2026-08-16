/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** create_matrix.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "amazed.h"

int **create_empty_matrix(int room_number)
{
    int **empty_matrix = malloc(sizeof(int *) * room_number);

    if (!empty_matrix)
        return NULL;
    for (int i = 0; i < room_number; i++) {
        empty_matrix[i] = malloc(sizeof(int) * room_number);
        if (!empty_matrix[i])
            return NULL;
        for (int j = 0; j < room_number; j++)
            empty_matrix[i][j] = 0;
    }
    return empty_matrix;
}

int get_index_from_name(room_t *list, const char *name)
{
    while (list) {
        if (my_strcmp(list->name_room, name) == 0)
            return list->index;
        list = list->next;
    }
    return -1;
}

int get_matrix(amazed_t *amazed)
{
    int **matrix = NULL;
    char **linked_room = NULL;
    int idx1 = -1;
    int idx2 = -1;
    link_t *current = amazed->room_link;

    matrix = create_empty_matrix(amazed->number_rooms);
    while (current != NULL) {
        linked_room = my_str_to_word_array(current->link, "-");
        idx1 = get_index_from_name(amazed->rooms, linked_room[0]);
        idx2 = get_index_from_name(amazed->rooms, linked_room[1]);
        if (idx1 != -1 && idx2 != -1) {
            matrix[idx1][idx2] = 1;
            matrix[idx2][idx1] = 1;
        }
        current = current->next;
    }
    amazed->matrix_link = matrix;
    return 0;
}
