/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** live.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Executes the live instruction for a process.
 *
 * This function decodes the live instruction, retrieves the player number
 * from the arena, and marks the corresponding player as alive. It updates
 * the live cycle of the process and the player, increments the global live
 * counter, and sets the last alive player. If the player number matches
 * a champion, a message is printed to indicate that the player is alive.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success.
 */
int make_live(corewar_t *global, processes_t *process)
{
    int live = recover_direct_value(global, process->pc + 1, 4);

    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[0].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    process->live_cycle = global->current_cycle;
    for (int i = 0; i < global->nb_champions; i++) {
        if (global->player[i].number == live) {
            mini_printf("The player %d(%s) is alive.\n"
                , global->player[i].number, global->player[i].name);
            global->player[i].live_cycle = process->live_cycle;
            global->last_alive = i;
        }
    }
    global->number_live += 1;
    process->pc += 5;
    return 0;
}
