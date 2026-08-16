/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** ld.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Validates and retrieves the values for the ld instruction.
 *
 * This function checks the argument types for the ld instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param process Pointer to the current process structure.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int affect_value_ld(params_values_t *values
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
 * @brief Updates the carry flag and program counter for the ld instruction.
 *
 * This function updates the carry flag based on the value loaded into
 * the register and increments the program counter to the next instruction.
 *
 * @param proc Pointer to the current process structure.
 * @param values Pointer to the structure containing the parameter values.
 */
void print_register_change(processes_t *proc,
    params_values_t *values)
{
    change_carry(values->args[0].value_direct, proc);
    proc->pc += (1 + calculate_new_pc(*values, 2, 1)) % MEM_SIZE;
}

/**
 * @brief Executes the ld instruction for a process.
 *
 * This function decodes the ld instruction, validates the argument types,
 * retrieves their values, and loads the value into the specified register.
 * It also manages the readiness of the process and updates the program
 * counter and carry flag.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_ld(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[process->pc + 1];
    params_values_t values = {0};

    values.modulo_command = 0;
    values.command = global->arena[process->pc];
    for (int i = 0; i < 2; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (affect_value_ld(&values, process, global) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[1].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    process->registre[values.args[1].value_regi - 1]
    = values.args[0].value_direct;
    print_register_change(process, &values);
    return 0;
}
