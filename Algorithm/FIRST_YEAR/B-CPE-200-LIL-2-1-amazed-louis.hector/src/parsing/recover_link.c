/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** revover_link.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "amazed.h"


int check_link(amazed_t *amazed)
{
    if (amazed->number_links == 0) {
        mini_printf("amazed: Please define the tubes after the rooms.\n");
        return 84;
    }
    return 0;
}

int error_recup_link(amazed_t *amazed, char **tab, link_t *node)
{
    room_t *current = amazed->rooms;
    char **link = NULL;
    int error1 = -1;
    int error2 = -1;

    while (current != NULL) {
        link = my_str_to_word_array(tab[0], "-");
        if (link == NULL)
            return 84;
        if (my_strcmp(link[0], current->name_room) == 0)
            error1 = 1;
        if (my_strcmp(link[1], current->name_room) == 0)
            error2 = 1;
        current = current->next;
    }
    if (error1 == -1 || error2 == -1)
        return 84;
    node->link = my_strdup(tab[0]);
    node->next = NULL;
    return 0;
}

int recup_link(link_t **room_link, char **tab, amazed_t *amazed)
{
    link_t *node = malloc(sizeof(link_t));
    link_t *last_node = NULL;
    static int tunnel = 0;

    if (tunnel == 0) {
        mini_printf("#tunnels\n");
        tunnel++;
    }
    if (error_recup_link(amazed, tab, node) == 84)
        return 84;
    if (*room_link == NULL)
        *room_link = node;
    else {
        last_node = *room_link;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = node;
    }
    return 0;
}
