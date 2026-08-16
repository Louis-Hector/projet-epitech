/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** fork.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Creates a new process and initializes its state.
 *
 * This function allocates memory for a new process, copies the state of
 * the parent process, and sets the program counter to the specified
 * value. The new process is initialized with the same register values
 * and other attributes as the parent process.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the parent process structure.
 * @param new_pc The program counter for the new process.
 * @return Pointer to the newly created process, or NULL on failure.
 */
processes_t *add_new_process(corewar_t *global
    , processes_t *process, int new_pc)
{
    processes_t *new_process = malloc(sizeof(processes_t));

    if (!new_process || !global)
        return NULL;
    new_process->id_player = process->id_player;
    new_process->carry = process->carry;
    new_process->pc = new_pc;
    new_process->live_cycle = global->current_cycle;
    new_process->is_ready = false;
    new_process->wait = 0;
    for (int i = 0; i < REG_NUMBER; i++)
        new_process->registre[i] = process->registre[i];
    new_process->registre[0] = process->id_player;
    new_process->next = NULL;
    return new_process;
}

/**
 * @brief Executes the fork instruction for a process.
 *
 * This function decodes the fork instruction, calculates the new program
 * counter for the child process, and creates a new process. The child
 * process is added to the end of the process list. The function also
 * manages the readiness of the parent process and updates its program
 * counter.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, or 1 if the operation is invalid.
 */
int make_fork(corewar_t *global, processes_t *process)
{
    params_values_t values = {0};
    int new_pc = 0;
    int position = 0;
    processes_t *tmp = process;

    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[11].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    values.command = global->arena[process->pc];
    values.position = process->pc + 1;
    position = recover_direct_value(global, values.position, 2) % IDX_MOD;
    new_pc = (process->pc + position < 0) ? ((process->pc +
    position) % MEM_SIZE) + MEM_SIZE : (process->pc + position) % MEM_SIZE;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = add_new_process(global, process, new_pc);
    process->pc += 3;
    return 0;
}
