/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** aff.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Retrieves the value stored in a register.
 *
 * This function retrieves the value of a register based on its position
 * in the arena. If the register index is invalid, it returns -1.
 *
 * @param position The position in the arena to read the register index.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return The value of the register, or -1 if the index is invalid.
 */
int recover_registre(int position, corewar_t *global, processes_t *process)
{
    int value_registre = global->arena[position % MEM_SIZE];

    if (value_registre < 0 || value_registre > REG_NUMBER)
        return -1;
    return process->registre[value_registre - 1];
}

/**
 * @brief Executes the aff instruction for a process.
 *
 * This function decodes the aff instruction, retrieves the value from
 * the specified register, and prints it as an ASCII character. It also
 * manages the process's readiness and updates the program counter.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_aff(corewar_t *global, processes_t *process)
{
    int value_asci = 0;
    int position = process->pc + 2;

    value_asci = recover_registre(position, global, process);
    if (value_asci == -1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[15].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    value_asci = value_asci % 256;
    mini_printf("%c\n", value_asci);
    process->pc = + 1 + (process->pc + 2) % MEM_SIZE;
    return 0;
}
