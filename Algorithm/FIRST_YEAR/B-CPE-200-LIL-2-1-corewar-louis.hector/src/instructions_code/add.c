/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** add.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Executes the add operation for a process.
 *
 * This function performs the addition of two register values and stores
 * the result in a third register. It also updates the program counter
 * and the carry flag of the process. The function ensures that the
 * operation is valid by checking the argument types and waiting for the
 * required number of cycles before execution.
 *
 * @param process Pointer to the current process structure.
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int affect_value_add(processes_t *process
    , params_values_t *values, corewar_t *global)
{
    int sum = 0;

    for (int i = 0; i < 3; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[3].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    sum = values->args[0].value_direct + values->args[1].value_direct;
    process->registre[values->args[2].value_regi - 1] = sum;
    process->pc += 1 + calculate_new_pc(*values, 3, 3) % MEM_SIZE;
    change_carry(sum, process);
    return 0;
}

/**
 * @brief Handles the add instruction for a process.
 *
 * This function decodes the add instruction from the arena, validates
 * the argument types, and calls the function to execute the operation.
 * The add instruction adds the values of two registers and stores the
 * result in a third register.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_add(corewar_t *global, processes_t *process)
{
    params_values_t values = {0};
    unsigned char coding_byte = global->arena[process->pc + 1];

    values.modulo_command = 0;
    values.command = global->arena[process->pc];
    values.position = process->pc + 2;
    for (int i = 0; i < 3; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (values.args[0].param != T_REG
        || values.args[1].param != T_REG || values.args[2].param != T_REG)
        return 1;
    return affect_value_add(process, &values, global);
}
