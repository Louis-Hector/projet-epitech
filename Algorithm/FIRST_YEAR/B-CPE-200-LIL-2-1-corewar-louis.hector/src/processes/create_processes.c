/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** create_processes.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Initializes the values of a process node.
 *
 * This function assigns initial values to a process node, including the
 * player ID, program counter, carry flag, registers, and other attributes.
 *
 * @param node Pointer to the process node to initialize.
 * @param i The index of the player associated with the process.
 * @param global The corewar global structure containing player data.
 */
void affect_value_process(processes_t *node, int i, corewar_t global)
{
    node->id_player = i;
    node->carry = 0;
    node->pc = global.player[i].load_address;
    node->live_cycle = 0;
    node->is_ready = false;
    for (int j = 0; j < REG_SIZE; j++)
        node->registre[j] = 0;
    node->registre[0] = global.player[i].number;
    node->wait = 0;
    node->next = NULL;
}

/**
 * @brief Creates and initializes a new process.
 *
 * This function allocates memory for a new process, initializes its
 * values, and adds it to the linked list of processes. If the list is
 * empty, the new process becomes the head of the list.
 *
 * @param instr Pointer to the head of the process list.
 * @param global The corewar global structure containing player data.
 * @param i The index of the player associated with the process.
 * @return 0 on success, 84 if memory allocation fails.
 */
int initialize_process(processes_t **instr, corewar_t global, int i)
{
    processes_t *node = NULL;
    processes_t *last_node = NULL;

    node = malloc(sizeof(processes_t));
    if (node == NULL)
        return 84;
    affect_value_process(node, i, global);
    if (*instr == NULL)
        *instr = node;
    else {
        last_node = *instr;
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = node;
    }
    return 0;
}
