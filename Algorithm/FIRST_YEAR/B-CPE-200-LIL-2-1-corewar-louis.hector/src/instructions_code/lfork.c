/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** lfork.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Executes the lfork instruction for a process.
 *
 * This function decodes the lfork instruction, calculates the new program
 * counter for the child process, and creates a new process. Unlike the
 * fork instruction, the offset for lfork is not restricted by IDX_MOD.
 * The child process is added to the end of the process list. The function
 * also manages the readiness of the parent process and updates its program
 * counter.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, or 1 if the operation is invalid.
 */
int make_lfork(corewar_t *global, processes_t *process)
{
    params_values_t values = {0};
    int new_pc = 0;
    int position = 0;
    processes_t *tmp = process;

    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[14].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    values.command = global->arena[process->pc];
    values.position = process->pc + 1;
    position = recover_direct_value(global, values.position, 2);
    new_pc = (process->pc + position < 0) ? ((process->pc +
    position) % MEM_SIZE) + MEM_SIZE : (process->pc + position) % MEM_SIZE;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = add_new_process(global, process, new_pc);
    process->pc += 3;
    return 0;
}
