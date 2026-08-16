/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** recover_room.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "amazed.h"

int check_pos(char *arg)
{
    int i = 0;

    if (arg[i] == '-' || arg[i] == '+')
        i++;
    for (; arg[i] != '\0'; i++)
        if (arg[i] < '0' || arg[i] > '9')
            return 1;
    return 0;
}

int check_error_room(char **tab, room_t *node)
{
    int count = 0;

    for (; tab[count] != NULL; count++);
    if (count != 3)
        return 84;
    for (int i = 1; i < 3; i++) {
        if (check_pos(tab[i]))
            return 84;
    }
    node->position[0] = my_strdup(tab[1]);
    node->position[1] = my_strdup(tab[2]);
    return 0;
}

void get_special_room(int *value, amazed_t *matrix, int index)
{
    if (*value == 1)
        matrix->start_room = index;
    if (*value == 2)
        matrix->final_room = index;
    *value = 0;
}

int recup_room(char **tab, int *value, amazed_t *amazed)
{
    room_t *node = malloc(sizeof(room_t));
    room_t *last_node = NULL;
    static int index = 0;

    if (check_error_room(tab, node) == 84)
        return 84;
    node->name_room = my_strdup(tab[0]);
    node->index = index;
    node->next = NULL;
    if (amazed->rooms == NULL) {
        amazed->rooms = node;
    } else {
        last_node = amazed->rooms;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = node;
    }
    get_special_room(value, amazed, index);
    index += 1;
    return 0;
}

static int recup_end_room(char *line)
{
    static int number_room_end = 0;

    if (my_strcmp(line, "##end") == 0) {
        number_room_end++;
        if (number_room_end > 1) {
            mini_printf("Double definition of command ##end.\n");
            return 84;
        }
        mini_printf("##end\n");
        return 2;
    }
    return 0;
}

int recup_start_and_end_room(char *line)
{
    static int number_room_start = 0;

    if (my_strcmp(line, "##start") == 0) {
        number_room_start++;
        if (number_room_start > 1) {
            mini_printf("Double definition of command ##start.\n");
            return 84;
        }
        mini_printf("##start\n");
        return 1;
    }
    return recup_end_room(line);
}
