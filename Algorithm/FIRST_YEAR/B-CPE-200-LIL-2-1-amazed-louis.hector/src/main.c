/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** amazed
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "amazed.h"

void init_struct(amazed_t *amazed)
{
    amazed->start_room = -1;
    amazed->final_room = -1;
    amazed->matrix_link = NULL;
    amazed->room_name = NULL;
    amazed->room_link = NULL;
    amazed->rooms = NULL;
}

int set_name_array(amazed_t *amazed)
{
    room_t *current = amazed->rooms;

    amazed->room_name = malloc(sizeof(char *) * (amazed->number_rooms + 1));
    if (!amazed->room_name)
        return 84;
    amazed->room_name[amazed->number_rooms] = NULL;
    for (int i = 0; i < amazed->number_rooms; i++) {
        amazed->room_name[i] = my_strdup(current->name_room);
        if (!amazed->room_name[i])
            return 84;
        current = current->next;
    }
    return 0;
}

int main(int ac, char **av)
{
    amazed_t amazed = {0};

    init_struct(&amazed);
    if (handle_parsing(ac, av, &amazed) == 84)
        return 84;
    if (set_name_array(&amazed) == 84)
        return 84;
    if (handle_algo(&amazed) == 84) {
        mini_printf("There is no valid path from start to exit.\n");
        return 84;
    }
    return 0;
}
