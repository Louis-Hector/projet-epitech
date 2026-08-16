/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** zjmp.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Retrieves a single argument for the zjmp instruction.
 *
 * This function retrieves the direct value of the argument for the zjmp
 * instruction. The value is restricted by IDX_MOD to ensure it is within
 * the valid range.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @return The direct value of the argument, restricted by IDX_MOD.
 */
int take_one_arg(params_values_t *values, corewar_t *global)
{
    return (recover_direct_value(global, values->position,
        recover_dir_size(values->command))) % IDX_MOD;
}

/**
 * @brief Executes the zjmp instruction for a process.
 *
 * This function decodes the zjmp instruction and checks the carry flag
 * of the process. If the carry flag is set to 1, the program counter is
 * updated to the specified offset. Otherwise, the program counter is
 * incremented to the next instruction. The function also manages the
 * readiness of the process.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success.
 */
int make_zjmp(corewar_t *global, processes_t *process)
{
    params_values_t values = {0};
    int value = 0;

    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[8].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    values.command = global->arena[process->pc];
    values.position = process->pc + 1;
    if (process->carry == 1) {
        value = take_one_arg(&values, global) % MEM_SIZE;
        process->pc = (process->pc + value < 0) ? ((process->pc +
        value) % MEM_SIZE) + MEM_SIZE : (process->pc + value) % MEM_SIZE;
    } else
        process->pc += calculate_new_pc(values, 1, 8) % MEM_SIZE;
    return 0;
}
