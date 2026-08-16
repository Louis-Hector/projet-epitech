/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** flags.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Changes the program number for a champion.
 *
 * This function validates and assigns a program number to a champion
 * based on the provided argument. It ensures that the argument is a
 * valid number.
 *
 * @param av Array of arguments.
 * @param player Array of player structures.
 * @param i Index of the current argument.
 * @param actual_champion Index of the current champion.
 * @return 0 on success, 84 if the argument is invalid.
 */
int change_prog_number(char **av, player_t player[4]
    , int i, int actual_champion)
{
    for (int j = 0; av[i + 1][j] != '\0'; j++)
        if (av[i + 1][j] < '0' || av[i + 1][j] > '9')
            return 84;
    player[actual_champion].number = my_getnbr(av[i + 1]);
    return 0;
}

/**
 * @brief Changes the load address for a champion.
 *
 * This function validates and assigns a load address to a champion
 * based on the provided argument. It ensures that the argument is a
 * valid number.
 *
 * @param av Array of arguments.
 * @param player Array of player structures.
 * @param i Index of the current argument.
 * @param actual_champion Index of the current champion.
 * @return 0 on success, 84 if the argument is invalid.
 */
int change_load_adress(char **av, player_t player[4]
    , int i, int actual_champion)
{
    for (int j = 0; av[i + 1][j] != '\0'; j++)
        if (av[i + 1][j] < '0' || av[i + 1][j] > '9')
            return 84;
    player[actual_champion].load_address = my_getnbr(av[i + 1]);
    return 0;
}

/**
 * @brief Verifies if a file has the .cor extension.
 *
 * This function checks if the provided file name has the correct .cor
 * extension, indicating that it is a valid Corewar binary file.
 *
 * @param av Array of arguments.
 * @param i Index of the current argument.
 * @return 0 if the file is valid, 1 otherwise.
 */
int verif_cor(char **av, int i)
{
    int len = my_strlen(av[i]);

    if (len < 4 || my_strcmp(av[i] + len - 4, ".cor") != 0)
        return 1;
    return 0;
}

static void assign_missing_addresses(player_t player[4], int count)
{
    int step = MEM_SIZE / count;

    for (int i = 0; i < count; i++) {
        if (player[i].load_address == -1)
            player[i].load_address = i * step;
    }
    return;
}

static void assign_missing_numbers(player_t player[4], int count)
{
    int number[5] = {0};

    for (int i = 0; i < count; i++) {
        if (player[i].number >= 1)
            number[i] = 1;
    }
    for (int i = 0; i < 4; i++) {
        if (number[i] == 0)
            player[i].number = i;
    }
}

/**
 * @brief Parses and assigns load addresses and program numbers.
 *
 * This function processes the arguments to assign load addresses and
 * program numbers to the champions. It also verifies the validity of
 * the provided arguments.
 *
 * @param av Array of arguments.
 * @param player Array of player structures.
 * @param ac Number of arguments.
 * @param pars Pointer to the parsing position structure.
 * @return 0 on success, 84 if an error occurs.
 */
int recup_load_and_number(char **av, player_t player[4]
    , int ac, parsing_position_t *pars)
{
    player[pars->pos].load_address = -1;
    if (my_strcmp(av[pars->pos], "-a") == 0) {
        if (pars->pos + 1 >= ac || change_load_adress(av, player, pars->pos
            , pars->actual_champion) == 84) {
            mini_printf("INIT: header error\n");
            return 84;
        }
    }
    if (my_strcmp(av[pars->pos], "-n") == 0) {
        if (pars->pos + 1 >= ac || change_prog_number(av, player, pars->pos
            , pars->actual_champion) == 84) {
            mini_printf("INIT: header error\n");
            return 84;
        }
    }
    if (verif_cor(av, pars->pos) == 0) {
        player[pars->actual_champion].path_file = av[pars->pos];
        pars->actual_champion += 1;
    }
    return 0;
}

static int change_number_cycle(char **av, parsing_position_t *pars
    , corewar_t *global)
{
    for (int j = 0; av[pars->pos + 1][j] != '\0'; j++)
        if (av[pars->pos + 1][j] < '0' || av[pars->pos + 1][j] > '9')
            return 84;
    global->nbr_cycle = my_getnbr(av[pars->pos + 1]);
    pars->flag_dump_detected = 1;
    return 0;
}

static int recover_cycle(char **av, int ac
    , parsing_position_t *pars, corewar_t *global)
{
    if (my_strcmp(av[pars->pos], "-dump") == 0) {
        if (pars->pos + 1 >= ac)
            return 84;
        if (change_number_cycle(av, pars, global) == 84)
            return 84;
    }
    return 0;
}

static int verif_end_parsing(parsing_position_t pars
    , corewar_t *global, player_t player[4])
{
    if (pars.actual_champion < 2) {
        mini_printf("INIT: Too few warrior\n");
        return 84;
    }
    global->nb_champions = pars.actual_champion;
    assign_missing_numbers(player, pars.actual_champion);
    assign_missing_addresses(player, pars.actual_champion);
    return 0;
}

/**
 * @brief Parses the flags and initializes the players and global data.
 *
 * This function processes the command-line arguments to parse the flags,
 * validate the input, and initialize the player and global structures.
 *
 * @param ac Number of arguments.
 * @param av Array of arguments.
 * @param player Array of player structures.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 84 if an error occurs.
 */
int parsing_flags(int ac, char **av,
    player_t player[4], corewar_t *global)
{
    parsing_position_t pars = {0};

    global->nbr_cycle = -1;
    for (int i = 1; i < ac; i++) {
        pars.pos = i;
        if (pars.actual_champion > 3) {
            mini_printf("INIT: Too many warrior\n");
            return 84;
        }
        if (recover_cycle(av, ac, &pars, global) == 84
            || recup_load_and_number(av, player, ac, &pars) == 84)
            return 84;
    }
    if (verif_end_parsing(pars, global, player) == 84)
        return 84;
    return 0;
}
