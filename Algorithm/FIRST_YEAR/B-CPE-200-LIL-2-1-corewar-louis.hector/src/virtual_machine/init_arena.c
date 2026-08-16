/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** create_arena.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Verifies and places a player's code in the arena.
 *
 * This function checks if the player's code can fit into the arena at
 * the specified load address. If the placement is valid, the player's
 * code is copied into the arena. Otherwise, an error is returned.
 *
 * @param i The index of the player to verify.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 84 if the placement is invalid.
 */
int verif_size_arena(int i, corewar_t *global)
{
    int load_address = global->player[i].load_address;
    int size = global->player[i].prog_size;

    if (load_address < 0 || load_address + size > MEM_SIZE) {
        mini_printf("Can't put with this load memory holy shit Laume\n",
            global->player[i].name);
        return 84;
    }
    for (int j = 0; j < size; j++)
        global->arena[load_address + j] = global->player[i].code[j];
    return 0;
}

/**
 * @brief Initializes the arena and places players' codes.
 *
 * This function allocates memory for the arena and initializes it to 0.
 * It then iterates through all players and places their codes into the
 * arena at their respective load addresses. If any placement fails, the
 * function returns an error.
 *
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 84 if an error occurs.
 */
int create_arena_with_player(corewar_t *global)
{
    global->arena = malloc(sizeof(unsigned char) * MEM_SIZE);
    if (global->arena == NULL)
        return 84;
    for (int i = 0; i < MEM_SIZE; i++)
        global->arena[i] = 0;
    for (int i = 0; i < global->nb_champions; i++) {
        if (verif_size_arena(i, global) == 84)
            return 84;
    }
    return 0;
}
