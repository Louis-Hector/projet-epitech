/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** parsing.c element in the line
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "amazed.h"

static int count_command_before_robost(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (i > 1) {
            mini_printf("amazed, line 1: A command must be before a room.\n");
            free(tab);
            return 84;
        }
    }
    return 0;
}

static int get_number(char **line, amazed_t *matrix, size_t size)
{
    char **tab = NULL;

    if (getline(line, &size, stdin) != -1) {
        while (*line[0] == '#')
            getline(line, &size, stdin);
        tab = my_str_to_word_array(*line, " ");
        if (count_command_before_robost(tab) == 84)
            return 84;
        matrix->number_robots = my_getnbr(*line);
        if (matrix->number_robots <= 0) {
            free(tab);
            return 84;
        }
    } else
        return 84;
    mini_printf("#number_of_robots\n");
    mini_printf("%d\n", matrix->number_robots);
    mini_printf("#rooms\n");
    free(tab);
    return 0;
}

static int verif_double_name_or_position(room_t *oth, room_t *cur)
{
    while (oth != NULL) {
        if (my_strcmp(cur->position[0], oth->position[0]) == 0
            && my_strcmp(cur->position[1], oth->position[1]) == 0) {
            mini_printf("amazed, line %d: "
                "Double definition of the coordinates.\n", oth->index + 4);
            return 84;
        }
        if (my_strcmp(cur->name_room, oth->name_room) == 0) {
            mini_printf("amazed, line %d: "
                "Double definition of the room name.\n", oth->index + 4);
            return 84;
        }
        oth = oth->next;
    }
    return 0;
}

int check_name_rooms(amazed_t amazed)
{
    room_t *current_room = amazed.rooms;
    room_t *other_room = NULL;

    while (current_room != NULL) {
        other_room = current_room->next;
        if (verif_double_name_or_position(other_room, current_room) == 84)
            return 84;
        current_room = current_room->next;
    }
    return 0;
}

int print_error_parsing(amazed_t amazed)
{
    if (amazed.number_rooms == 0) {
        mini_printf("amazed: You didn't define any rooms.\n");
        return 84;
    }
    if (amazed.start_room == -1) {
        mini_printf("amazed: You didn't define any start room.\n");
        return 84;
    }
    if (amazed.final_room == -1) {
        mini_printf("amazed: You didn't define any end room.\n");
        return 84;
    }
    return 0;
}

static int handle_room_link(int index, char **tab
    , amazed_t *amazed, int *value)
{
    if (index == 0) {
        amazed->number_rooms += 1;
        if (recup_room(tab, value, amazed) == 84
            || check_name_rooms(*amazed) == 84)
            return 84;
    } else {
        amazed->number_links += 1;
        if (print_error_parsing(*amazed) == 84
            || recup_link(&amazed->room_link, tab, amazed) == 84)
                return 84;
    }
    return 0;
}

int parsing_and_recup_data(char *line, amazed_t *amazed, int *value)
{
    char **tab = NULL;
    int index = 0;

    tab = my_str_to_word_array(line, " ");
    if (tab == NULL)
        return 84;
    if (tab[0] == NULL) {
        mini_printf("Please remove empty lines.\n");
        return 84;
    }
    if (line[0] == '#')
        return recup_start_and_end_room(line);
    for (int i = 0; tab[0][i] != '\0'; i++)
        if (tab[0][i] == '-')
            index = 1;
    if (handle_room_link(index, tab, amazed, value) == 84)
        return 84;
    mini_printf("%s\n", line);
    return 0;
}

int handle_parsing(int ac, char **av, amazed_t *amazed)
{
    size_t size = 0;
    char *line = NULL;
    int value = 0;

    if (ac != 1 || av[0] == NULL || get_number(&line, amazed, size))
        return 84;
    while (getline(&line, &size, stdin) != -1) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        value = parsing_and_recup_data(line, amazed, &value);
        if (value == 84)
            return 84;
    }
    if (check_link(amazed) == 84)
        return 84;
    line[strlen(line)] = '\0';
    get_matrix(amazed);
    return 0;
}
