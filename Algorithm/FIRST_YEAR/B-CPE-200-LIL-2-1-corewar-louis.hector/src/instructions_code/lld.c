/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** lld.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Validates and retrieves the values for the lld instruction.
 *
 * This function checks the argument types for the lld instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param process Pointer to the current process structure.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int affect_value_lld(params_values_t *values
    , processes_t *process, corewar_t *global)
{
    values->position = process->pc + 2;
    if ((values->args[0].param != T_DIR
        && values->args[0].param != T_IND)
        || values->args[1].param != T_REG)
        return 1;
    for (int i = 0; i < 2; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    return 0;
}

/**
 * @brief Executes the lld instruction for a process.
 *
 * This function decodes the lld instruction, validates the argument types,
 * retrieves their values, and loads the value into the specified register.
 * Unlike the ld instruction, the lld instruction does not restrict the
 * offset by IDX_MOD. It also manages the readiness of the process and
 * updates the program counter and carry flag.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_lld(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[process->pc + 1];
    params_values_t values = {0};

    values.modulo_command = 1;
    values.command = global->arena[process->pc];
    for (int i = 0; i < 2; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (affect_value_lld(&values, process, global) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[12].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    process->registre[values.args[1].value_regi - 1]
    = values.args[0].value_direct;
    change_carry(values.args[0].value_direct, process);
    process->pc += 1 + calculate_new_pc(values, 2, 12);
    return 0;
}
