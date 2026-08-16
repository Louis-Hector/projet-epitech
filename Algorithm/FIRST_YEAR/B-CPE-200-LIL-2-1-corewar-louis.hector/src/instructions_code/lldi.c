/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** lldi.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Validates and retrieves the values for the lldi instruction.
 *
 * This function checks the argument types for the lldi instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int affect_value_lldi(params_values_t *values
    , corewar_t *global, processes_t *process)
{
    values->modulo_command = 1;
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
 * @brief Executes the lldi instruction for a process.
 *
 * This function decodes the lldi instruction, validates the argument types,
 * retrieves their values, and loads the value into the specified register.
 * Unlike the ldi instruction, the lldi instruction does not restrict the
 * offset by IDX_MOD. It also manages the readiness of the process and
 * updates the program counter and carry flag.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_lldi(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[process->pc + 1];
    params_values_t values = {0};
    int value = 0;

    values.command = global->arena[process->pc];
    for (int i = 0; i < 3; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (affect_value_lldi(&values, global, process) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[13].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    value = read_value(values, process, global, true);
    process->registre[values.args[2].value_regi - 1] = value;
    process->pc += 1 + calculate_new_pc(values, 3, 13) % MEM_SIZE;
    change_carry(value, process);
    return 0;
}
