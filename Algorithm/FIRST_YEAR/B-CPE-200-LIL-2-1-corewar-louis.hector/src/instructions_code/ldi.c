/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** ldi.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Reads a value for the ldi or lldi instruction.
 *
 * This function calculates the offset based on the sum of the first two
 * arguments and retrieves the value from the arena. If the instruction
 * is lldi, the offset is not restricted by IDX_MOD.
 *
 * @param values The structure containing the parameter values.
 * @param process Pointer to the current process structure.
 * @param global Pointer to the corewar global structure.
 * @param is_lldi Boolean indicating if the instruction is lldi.
 * @return The value retrieved from the arena.
 */
int read_value(params_values_t values, processes_t *process,
    corewar_t *global, bool is_lldi)
{
    int value = 0;
    int offset = (values.args[0].value_direct + values.args[1].value_direct);

    if (is_lldi) {
        value = recover_indirect(global, process->pc, offset, values);
        return value;
    }
    value = recover_indirect(global, process->pc, offset % IDX_MOD, values);
    return value;
}

/**
 * @brief Validates and retrieves the values for the ldi instruction.
 *
 * This function checks the argument types for the ldi instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int affect_value_ldi(params_values_t *values
    , corewar_t *global, processes_t *process)
{
    values->position = process->pc + 2;
    if (values->args[0].param == 0 || (values->args[1].param != T_REG &&
        values->args[1].param != T_DIR) || values->args[2].param != T_REG)
        return 1;
    for (int i = 0; i < 3; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    return 0;
}

/**
 * @brief Executes the ldi instruction for a process.
 *
 * This function decodes the ldi instruction, validates the argument types,
 * retrieves their values, and loads the value into the specified register.
 * It also manages the readiness of the process and updates the program
 * counter and carry flag.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_ldi(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[process->pc + 1];
    params_values_t values = {0};
    int value = 0;

    values.command = global->arena[process->pc];
    for (int i = 0; i < 3; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (affect_value_ldi(&values, global, process) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[9].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    value = read_value(values, process, global, false);
    process->registre[values.args[2].value_regi - 1] = value;
    process->pc += 1 + calculate_new_pc(values, 3, 9) % MEM_SIZE;
    change_carry(value, process);
    return 0;
}
