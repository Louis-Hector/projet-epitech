/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** algorithm
*/

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "amazed.h"
#include "my.h"

int find_min_dist(int *dist, bool *is_check, amazed_t *amazed)
{
    int min = INT_MAX;
    int min_index = 0;

    for (int i = 0; i < amazed->number_rooms; i++) {
        if (!is_check[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

static void check_shorter(distance_t distance,
    int **dist, int **parent, amazed_t *amazed)
{
    if ((*dist)[distance.i] + 1 < (*dist)[distance.j]) {
        (*dist)[distance.j] = (*dist)[distance.i]
            + amazed->matrix_link[distance.i][distance.j];
        (*parent)[distance.j] = distance.i;
    }
}

static void update_distances(int **dist, int **parent,
    bool **is_check, amazed_t *amazed)
{
    int i = find_min_dist(*dist, *is_check, amazed);
    distance_t distance = {0};

    distance.i = i;
    (*is_check)[i] = true;
    for (int j = 0; j < amazed->number_rooms; j++) {
        distance.j = j;
        if (!(*is_check)[j] && (amazed->matrix_link)[i][j] != 0
            && (*dist)[i] != INT_MAX)
            check_shorter(distance, dist, parent, amazed);
    }
}

static int *get_clean_parent(int *parent, amazed_t *amazed)
{
    int *clean_parent = malloc(sizeof(int) * (amazed->number_rooms + 1));
    int tmp = amazed->final_room;

    for (int i = 0; i < amazed->number_rooms; i++)
        clean_parent[i] = -1;
    for (; tmp != -1; tmp = parent[tmp]) {
        clean_parent[tmp] = parent[tmp];
    }
    return clean_parent;
}

static int *get_path(int *parent, amazed_t *amazed)
{
    int *path = malloc(sizeof(int) * (amazed->number_rooms + 1));
    int *clean_parent = get_clean_parent(parent, amazed);

    for (int i = 0; i < amazed->number_rooms; i++)
        path[i] = -1;
    for (int i = 0; i < amazed->number_rooms; i++)
        if (clean_parent[i] != -1)
            path[clean_parent[i]] = i;
    return path;
}

static int *set_path(int *parent, amazed_t *amazed)
{
    return get_path(parent, amazed);
}

static int dijkstra(amazed_t *amazed, int robot)
{
    int *dist = malloc(sizeof(int) * amazed->number_rooms);
    bool *is_check = malloc(sizeof(bool) * amazed->number_rooms);
    int *parent = malloc(sizeof(int) * amazed->number_rooms);

    for (int i = 0; i < amazed->number_rooms; i++) {
        dist[i] = INT_MAX;
        is_check[i] = false;
        parent[i] = -1;
    }
    dist[amazed->start_room] = 0;
    for (int i = 0; i < amazed->number_rooms - 1; i++)
        update_distances(&dist, &parent, &is_check, amazed);
    amazed->robots[robot] = set_path(parent, amazed);
    if (amazed->robots[robot][amazed->start_room] == -1)
        return 84;
    amazed->matrix_link[amazed->start_room]
        [amazed->robots[robot][amazed->start_room]] += 1;
    amazed->matrix_link[amazed->robots[robot][amazed->start_room]]
        [amazed->start_room] += 1;
    return 0;
}

int handle_algo(amazed_t *amazed)
{
    amazed->robots = malloc(sizeof(int *) * (amazed->number_robots + 1));
    for (int i = 0; i < amazed->number_robots; i++)
        if (dijkstra(amazed, i) == 84)
            return 84;
    mini_printf("#moves\n");
    simulate_moves(amazed);
    return 0;
}
