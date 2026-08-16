/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** st.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Validates and retrieves the values for the st instruction.
 *
 * This function checks the argument types for the st instruction and
 * retrieves their values. It ensures that the arguments are valid and
 * updates the position in the arena accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the arguments are invalid.
 */
int affect_value_st(params_values_t *values
    , corewar_t *global, processes_t *process)
{
    if (values->args[0].param != T_REG
        || (values->args[1].param != T_IND
        && values->args[1].param != T_REG))
        return 1;
    for (int i = 0; i < 2; i++) {
        if (check_type(values, global, process, i) == 1)
            return 1;
    }
    return 0;
}

/**
 * @brief Stores a value in the arena or a register.
 *
 * This function stores the value from a register into either another
 * register or a memory location in the arena, depending on the argument
 * type. The position in the arena is calculated using the offset.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @param values The structure containing the parameter values.
 */
void stock_value(corewar_t *global
    , processes_t *process, params_values_t values)
{
    int decal = (values.args[1].value_direct) % IDX_MOD;
    int position = (process->pc + decal) % MEM_SIZE;
    int value_stock = values.args[0].value_direct;

    global->arena[position % MEM_SIZE] = value_stock >> 24;
    global->arena[(position + 1) % MEM_SIZE] = value_stock >> 16;
    global->arena[(position + 2) % MEM_SIZE] = value_stock >> 8;
    global->arena[(position + 3) % MEM_SIZE] = value_stock;
    return;
}

/**
 * @brief Executes the st instruction for a process.
 *
 * This function decodes the st instruction, validates the argument types,
 * retrieves their values, and stores the value from a register into
 * another register or memory location. It also manages the readiness of
 * the process and updates the program counter.
 *
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @return 0 on success, 1 if the operation is invalid.
 */
int make_st(corewar_t *global, processes_t *process)
{
    params_values_t values = {0};
    unsigned char coding_byte = global->arena[process->pc + 1];

    values.modulo_command = 0;
    values.position += process->pc + 2;
    values.command = global->arena[process->pc];
    for (int i = 0; i < 2; i++)
        values.args[i].param = get_arg_type(coding_byte, i);
    if (affect_value_st(&values, global, process) == 1)
        return 1;
    if (!process->is_ready) {
        process->is_ready = true;
        process->wait = op_tab[2].nbr_cycles;
        return 0;
    }
    process->is_ready = false;
    stock_value(global, process, values);
    process->pc += 1 + calculate_new_pc(values, 2, 2);
    return 0;
}
