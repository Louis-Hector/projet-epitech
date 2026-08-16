/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** check_winner.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Checks if a process should be removed due to inactivity.
 *
 * This function verifies if a process has exceeded the allowed number
 * of cycles without a live signal. If so, it removes the process from
 * the process list.
 *
 * @param global Pointer to the corewar global structure.
 * @param proc_current Pointer to the current process being checked.
 * @param prev Pointer to the previous process in the list.
 * @param next Pointer to the next process in the list.
 */
void check_delta(corewar_t *global, processes_t *proc_current
    , processes_t *prev, processes_t *next)
{
    if ((global->current_cycle - proc_current->live_cycle)
    >= global->cycle_to_die) {
        if (prev == NULL)
            global->process_list = next;
        else
            prev->next = next;
    } else
        prev = proc_current;
    return;
}

/**
 * @brief Prints the winner of the Corewar game.
 *
 * This function displays the winner of the game based on the last
 * process to send a live signal. If no valid winner exists, it prints
 * an empty message.
 *
 * @param global Pointer to the corewar global structure.
 */
void print_winner(corewar_t *global)
{
    if (global->last_alive >= 0 && global->last_alive < global->nb_champions) {
        mini_printf("The player %d(%s) has won\n",
        global->player[global->last_alive].number,
        global->player[global->last_alive].name);
    }
    return;
}

/**
 * @brief Manages the elimination of inactive processes.
 *
 * This function iterates through the process list and removes processes
 * that have not sent a live signal within the allowed number of cycles.
 * It also adjusts the cycle-to-die value if the number of live signals
 * exceeds the threshold.
 *
 * @param global Pointer to the corewar global structure.
 */
void check_hunger_games(corewar_t *global)
{
    processes_t *prev = NULL;
    processes_t *next;
    processes_t *proc_current = global->process_list;

    if (global->number_live >= NBR_LIVE) {
        global->cycle_to_die = global->cycle_to_die - CYCLE_DELTA;
        global->number_live = 0;
    }
    while (proc_current != NULL) {
        next = proc_current->next;
        check_delta(global, proc_current, prev, next);
        proc_current = next;
    }
}
