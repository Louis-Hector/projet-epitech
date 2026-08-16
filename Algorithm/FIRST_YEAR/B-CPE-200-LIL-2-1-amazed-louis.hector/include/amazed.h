/*
** EPITECH PROJECT, 2024
** amazed.h
** File description:
** .h for amazed
*/

#ifndef MY_AMA
    #define MY_AMA
    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <stdint.h>

typedef struct room_s {
    char *name_room;
    int index;
    char *position[2];
    char *link_between_room;
    struct room_s *next;
} room_t;

typedef struct link_s {
    char *link;
    struct link_s *next;
} link_t;

typedef struct amazed_s {
    int number_robots;
    int start_room;
    int final_room;
    int number_rooms;
    int number_links;
    int **matrix_link;
    char **room_name;
    link_t *room_link;
    room_t *rooms;
    int **robots;
} amazed_t;

typedef struct {
    int id;
    int *path;
    int path_len;
    int pos;
    int finished;
} robot_state_t;

typedef struct {
    robot_state_t *states;
    int *occupied;
    int robots_moving;
    int first;
} movement_t;

typedef struct distance_s {
    int i;
    int j;
} distance_t;


int handle_parsing(int ac, char **av, amazed_t *amazed);
int get_matrix(amazed_t *amazed);
void display_matrix(int **matrix, int room_number);
int recup_start_and_end_room(char *line);
int recup_room(char **tab, int *value, amazed_t *amazed);
int handle_algo(amazed_t *amazed);
int recup_link(link_t **room_link, char **tab, amazed_t *amazed);
int check_link(amazed_t *amazed);
void simulate_moves(amazed_t *amazed);

#endif
