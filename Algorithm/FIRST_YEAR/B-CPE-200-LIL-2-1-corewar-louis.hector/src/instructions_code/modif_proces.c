/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** modif_proces_actual.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Retrieves the size of a direct argument for a command.
 *
 * This function determines the size of a direct argument (T_DIR) based
 * on the command. Some commands use a 2-byte direct argument, while
 * others use a 4-byte direct argument.
 *
 * @param command The command code to check.
 * @return The size of the direct argument (2 or 4 bytes).
 */
int recover_dir_size(int command)
{
    if (command == 8 || command == 9 || command == 10
        || command == 11 || command == 13 || command == 14)
        return 2;
    return 4;
}

/**
 * @brief Calculates the new program counter for a process.
 *
 * This function calculates the number of bytes to move the program
 * counter forward based on the argument types and the command. It
 * ensures that the program counter is updated correctly after an
 * instruction is executed.
 *
 * @param values The structure containing the parameter values.
 * @param number_args The number of arguments for the instruction.
 * @param command The command code being executed.
 * @return The number of bytes to move the program counter forward.
 */
int calculate_new_pc(params_values_t values, int number_args, int command)
{
    int number_for_pc = 1;

    for (int i = 0; i < number_args; i++) {
        if (values.args[i].param == T_REG)
            number_for_pc += 1;
        if (values.args[i].param == T_DIR)
            number_for_pc += recover_dir_size(command);
        if (values.args[i].param == T_IND)
            number_for_pc += 2;
    }
    return number_for_pc;
}

/**
 * @brief Updates the carry flag for a process.
 *
 * This function sets the carry flag of a process based on the value of
 * the data. If the data is 0, the carry flag is set to 1. Otherwise, it
 * is set to 0.
 *
 * @param data The value to check.
 * @param proces Pointer to the current process structure.
 */
void change_carry(int data, processes_t *proces)
{
    if (data == 0)
        proces->carry = 1;
    else
        proces->carry = 0;
}

/**
 * @brief Retrieves a direct value from the arena.
 *
 * This function reads a direct value (T_DIR) from the arena at the
 * specified position. The size of the value can be either 2 bytes or
 * 4 bytes, depending on the instruction.
 *
 * @param global Pointer to the corewar global structure.
 * @param position The position in the arena to read from.
 * @param size The size of the value to retrieve (2 or 4 bytes).
 * @return The retrieved direct value.
 */
int recover_direct_value(corewar_t *global, int position, int size)
{
    unsigned char high;
    unsigned char low;
    short result = 0;
    int value = 0;

    if (size == 2) {
        high = global->arena[position % MEM_SIZE];
        low = global->arena[(position + 1) % MEM_SIZE];
        result = (high << 8) | low;
        return (int)result;
    }
    if (size == 4) {
        value = (global->arena[position % MEM_SIZE] << 24)
            | (global->arena[(position + 1) % MEM_SIZE] << 16)
            | (global->arena[(position + 2) % MEM_SIZE] << 8)
            | global->arena[(position + 3) % MEM_SIZE];
        return value;
    }
    return 0;
}
