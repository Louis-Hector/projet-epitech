/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** display
*/

#include "amazed.h"
#include "my.h"

static int init_move(movement_t *move, amazed_t *amazed)
{
    move->states = malloc(sizeof(robot_state_t) * amazed->number_robots);
    move->occupied = malloc(sizeof(int) * amazed->number_rooms);
    if (!move->states || !move->occupied)
        return 84;
    move->robots_moving = 1;
    move->first = 1;
    return 0;
}

static void recover_path_for_room(amazed_t *amazed
    , movement_t *move, int i, int index)
{
    int new_room = -1;

    new_room = amazed->start_room;
    index = 0;
    while (new_room != -1) {
        move->states[i].path[index] = new_room;
        index++;
        new_room = amazed->robots[i][new_room];
    }
    move->states[i].path_len = index;
    move->states[i].pos = 0;
    move->states[i].finished = 0;
}

int init_movement(amazed_t *amazed, movement_t *move)
{
    int index = -1;

    if (init_move(move, amazed) == 84)
        return 84;
    for (int i = 0; i < amazed->number_rooms; i++)
        move->occupied[i] = 0;
    for (int i = 0; i < amazed->number_robots; i++) {
        move->states[i].id = i + 1;
        move->states[i].path = malloc(sizeof(int) * amazed->number_rooms);
        if (!move->states[i].path)
            return 84;
        recover_path_for_room(amazed, move, i, index);
    }
    return 0;
}

void free_movement(amazed_t *amazed, movement_t *move)
{
    for (int i = 0; i < amazed->number_robots; i++)
        free(move->states[i].path);
    free(move->states);
    free(move->occupied);
    free(move);
}

void is_move_allowed(amazed_t *amazed, movement_t *move,
    int i, int curr_pos)
{
    int next = move->states[i].path[curr_pos + 1];

    if (next == amazed->final_room || move->occupied[next] == 0) {
        if (move->states[i].path[curr_pos] != amazed->start_room)
            move->occupied[move->states[i].path[curr_pos]] = 0;
        if (next != amazed->final_room)
            move->occupied[next] = 1;
        move->states[i].pos++;
        if (!move->first)
            mini_printf(" ");
        mini_printf("P%d-%s", move->states[i].id, amazed->room_name[next]);
        move->first = 0;
        if (next == amazed->final_room)
            move->states[i].finished = 1;
        move->robots_moving = 1;
    }
}

void browse_each_robot(amazed_t *amazed, movement_t *move)
{
    int curr_pos = -1;

    for (int i = 0; i < amazed->number_robots; i++) {
        if (move->states[i].finished)
            continue;
        curr_pos = move->states[i].pos;
        if (curr_pos + 1 < move->states[i].path_len)
            is_move_allowed(amazed, move, i, curr_pos);
    }
}

void simulate_moves(amazed_t *amazed)
{
    movement_t *move = malloc(sizeof(movement_t));

    if (!move)
        return;
    init_movement(amazed, move);
    while (move->robots_moving) {
        move->robots_moving = 0;
        move->first = 1;
        browse_each_robot(amazed, move);
        if (!move->first)
            mini_printf("\n");
    }
    free_movement(amazed, move);
}
