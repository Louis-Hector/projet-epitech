/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** or.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Executes the OR operation for a process.
 *
 * This function performs a bitwise OR operation between two values and
 * stores the result in a specified register. It also updates the program
 * counter and the carry flag of the process. The function ensures that
 * the operation is valid by checking the argument types and waiting for
 * the required number of cycles before execution.
 *
 * @param process Pointer to the current process structure.
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int affect_value_or(processes_t *process
    , params_values_t *values, corewar_t *global)
{
    int result = 0;

    for (int i = 0; i < 3; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[6].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    result = values->args[0].value_direct | values->args[1].value_direct;
    process->registre[values->args[2].value_regi] = result;
    change_carry(result, process);
    process->pc += 1 + calculate_new_pc(*values, 3, 6) % MEM_SIZE;
    return 0;
}

/**
 * @brief Handles the OR instruction for a process.
 *
 * This function decodes the OR instruction from the arena, validates
 * the argument types, and calls the function to execute the operation.
 * The OR instruction performs a bitwise OR between two values and stores
 * the result in a register.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_or(corewar_t *global, processes_t *process)
{
    unsigned char coding_byte = global->arena[process->pc + 1];
    params_values_t values = {0};

    values.modulo_command = 0;
    values.command = global->arena[process->pc];
    for (int i = 0; i < 3; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (values.args[2].param != T_REG
        || values.args[0].param == 0 || values.args[1].param == 0)
        return 1;
    values.position = process->pc + 2;
    return affect_value_or(process, &values, global);
}
