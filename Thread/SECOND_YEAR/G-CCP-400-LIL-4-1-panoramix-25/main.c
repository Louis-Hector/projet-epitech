/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** main
*/

#include "my.h"

static int check_number(char **av, int i)
{
    for (unsigned long j = 0; j < strlen(av[i]); j++) {
        if (av[i][j] < '0' || av[i][j] > '9') {
            fprintf(stderr, "USAGE: ./panoramix <nb_villagers> "
                "<pot_size> <nb_fights> <nb_refills>\nValues must be >0.\n");
            return 84;
        }
    }
    return 0;
}

static int init_args(int ac, char **av, info_village_t *args)
{
    for (int i = 1; i < ac; i++)
        if (check_number(av, i) == 84)
            return 84;
    args->nb_villagers = atoi(av[1]);
    args->pot_size = atoi(av[2]);
    args->nb_fights = atoi(av[3]);
    args->nb_refills = atoi(av[4]);
    return 0;
}

int main(int ac, char **av)
{
    info_village_t args = {};

    if (ac == 1 || av[1] == NULL) {
        fprintf(stderr, "USAGE: ./panoramix <nb_villagers> "
            "<pot_size> <nb_fights> <nb_refills>\n");
        return 0;
    }
    if (ac != 5)
        return 84;
    if (init_args(ac, av, &args) == 84)
        return 84;
    if (args.nb_villagers == 0 || args.pot_size == 0
        || args.nb_fights == 0 || args.nb_refills == 0) {
        fprintf(stderr, "USAGE: ./panoramix <nb_villagers> "
            "<pot_size> <nb_fights> <nb_refills>\nValues must be >0.\n");
        return 84;
    }
    return launch_panoramix(&args);
}
