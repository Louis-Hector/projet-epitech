/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** sti.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Validates and retrieves the values for the sti instruction.
 *
 * This function checks the argument types for the sti instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int recup_value_sti(params_values_t *values
    , corewar_t *global, processes_t *process)
{
    values->position = process->pc + 2;
    if (values->args[0].param != T_REG || values->args[1].param == 0
        || (values->args[2].param != T_DIR
        && values->args[2].param != T_REG))
            return 1;
    for (int i = 0; i < 3; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    return 0;
}

/**
 * @brief Stores a value in the arena for the sti instruction.
 *
 * This function calculates the position in the arena based on the sum
 * of the second and third arguments and stores the value from the
 * specified register at that position.
 *
 * @param values The structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 */
void stock_value_i(params_values_t values,
    corewar_t *global, processes_t *process)
{
    int decal = (values.args[1].value_direct
        + values.args[2].value_direct) % IDX_MOD;
    int position = (process->pc + decal) % MEM_SIZE;
    int registre_value = values.args[0].value_direct;

    global->arena[position] = registre_value >> 24;
    global->arena[(position + 1) % MEM_SIZE] = registre_value >> 16;
    global->arena[(position + 2) % MEM_SIZE] = registre_value >> 8;
    global->arena[(position + 3) % MEM_SIZE] = registre_value;
}

/**
 * @brief Executes the sti instruction for a process.
 *
 * This function decodes the sti instruction, validates the argument types,
 * retrieves their values, and stores the value from a register into a
 * memory location in the arena. It also manages the readiness of the
 * process and updates the program counter.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_sti(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[(process->pc + 1) % MEM_SIZE];
    params_values_t values = {0};

    values.modulo_command = 0;
    values.command = global->arena[process->pc];
    for (int i = 0; i < 3; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (recup_value_sti(&values, global, process) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[10].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    stock_value_i(values, global, process);
    process->pc += (1 + calculate_new_pc(values, 3, 10)) % MEM_SIZE;
    return 0;
}
