/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** free.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Frees all allocated memory for the corewar structures.
 *
 * This function releases all dynamically allocated memory associated with
 * the corewar game, including the arena, player data, and the linked list
 * of processes. It ensures that no memory leaks occur when the program
 * terminates.
 *
 * @param global The corewar global structure containing the arena and
 *               other global data.
 * @param start_process Pointer to the head of the linked list of processes.
 * @param player Array of player structures containing champion data.
 */
void free_struct(corewar_t global, processes_t *start_process,
    player_t player[4])
{
    processes_t *current = start_process;
    processes_t *prev = NULL;

    free(global.arena);
    for (int i = 0; i < global.nb_champions; i++) {
        free(player[i].name);
        free(player[i].comment);
        free(player[i].code);
    }
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
}
