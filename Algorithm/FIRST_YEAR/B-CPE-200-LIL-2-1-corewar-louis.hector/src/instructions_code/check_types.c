/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** check_types.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Retrieves the type of an argument from the coding byte.
 *
 * This function extracts the type of an argument (register, direct, or
 * indirect) from the coding byte based on its position. It ensures that
 * the position is valid and returns the corresponding type.
 *
 * @param coding_byte The coding byte containing argument type information.
 * @param pos The position of the argument (0, 1, or 2).
 * @return The type of the argument (T_REG, T_DIR, T_IND), or 0 if invalid.
 */
int get_arg_type(unsigned char coding_byte, int pos)
{
    int code = (coding_byte >> (6 - (pos * 2))) & 0b11;

    if (pos < 0 || pos > 2)
        return 0;
    if (code == 0b01)
        return T_REG;
    if (code == 0b10)
        return T_DIR;
    if (code == 0b11)
        return T_IND;
    return 0;
}

/**
 * @brief Handles indirect arguments and retrieves their values.
 *
 * This function checks if an argument is of type indirect. If so, it
 * calculates the offset and retrieves the corresponding value from the
 * arena. The position is updated accordingly.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @param i The index of the argument to check.
 */
void check_if_indirect(params_values_t *values
    , corewar_t *global, processes_t *process, int i)
{
    int offset = 0;

    if (values->args[i].param == T_IND) {
        offset = recover_direct_value(global, values->position, 2);
        values->args[i].value_direct =
        recover_indirect(global, process->pc, offset, *values);
        values->position += 2;
    }
}

/**
 * @brief Retrieves the value of an indirect argument.
 *
 * This function calculates the address of an indirect argument based on
 * the program counter and the offset. It retrieves the value stored at
 * the calculated address in the arena.
 *
 * @param global Pointer to the corewar global structure.
 * @param pc The program counter of the process.
 * @param decal The offset to calculate the address.
 * @param values The structure containing the parameter values.
 * @return The value of the indirect argument.
 */
int recover_indirect(corewar_t *global
    , int pc, int decal, params_values_t values)
{
    int address = 0;
    int result = 0;

    if (values.modulo_command == 0)
        address = (pc + (decal) % IDX_MOD) % MEM_SIZE;
    else
        address = (pc + (decal)) % MEM_SIZE;
    result = (global->arena[address % MEM_SIZE] << 24)
        | (global->arena[(address + 1) % MEM_SIZE] << 16)
        | (global->arena[(address + 2) % MEM_SIZE] << 8)
        | (global->arena[(address + 3) % MEM_SIZE]);
    return result;
}

/**
 * @brief Checks the type of an argument and retrieves its value.
 *
 * This function validates the type of an argument (register, direct, or
 * indirect) and retrieves its value. It updates the position in the arena
 * and ensures that the argument is valid.
 *
 * @param values Pointer to the structure containing the parameter values.
 * @param global Pointer to the corewar global structure.
 * @param process Pointer to the current process structure.
 * @param i The index of the argument to check.
 * @return 0 on success, 1 if the argument is invalid.
 */
int check_type(params_values_t *values
    , corewar_t *global, processes_t *process, int i)
{
    int size = 0;

    if (values->args[i].param == T_REG) {
        values->args[i].value_regi =
        global->arena[values->position % MEM_SIZE];
        if (values->args[i].value_regi < 0
            || values->args[i].value_regi > REG_NUMBER)
            return 1;
        values->args[i].value_direct =
        process->registre[values->args[i].value_regi - 1];
        values->position += 1;
    }
    if (values->args[i].param == T_DIR) {
        size = recover_dir_size(values->command);
        values->args[i].value_direct = recover_direct_value(global
            , values->position, size);
        values->position += size;
    }
    check_if_indirect(values, global, process, i);
    return 0;
}
