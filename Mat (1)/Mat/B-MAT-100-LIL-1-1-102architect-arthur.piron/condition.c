/*
** EPITECH PROJECT, 2024
** math
** File description:
** conditon
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_flag(const char *arg)
{
    return arg[0] == '-' && isalpha(arg[1]) && arg[2] == '\0';
}

int make_i(int ac, char **av, int *i)
{
    if (*i + 1 >= ac || (is_flag(av[*i + 1]) && !isdigit(av[*i + 1][1])))
        return 84;
    *i += 1;
    return 0;
}

int check(int ac, char **av, int *i)
{
    if ((strcmp(av[*i], "-t") == 0 || strcmp(av[*i], "-z") == 0)) {
        if (*i + 2 >= ac || is_flag(av[*i + 1]) || is_flag(av[*i + 2]))
            return 84;
        *i += 2;
        return 0;
    }
    if ((strcmp(av[*i], "-r") == 0 || strcmp(av[*i], "-s") == 0)) {
        if (make_i(ac, av, i) == 84)
            return 84;
        return 0;
    }
    return 84;
}

int test_condition(char **av, int ac)
{
    double x = atof(av[1]);
    double y = atof(av[2]);

    for (int i = 3; i < ac; i++) {
        if (check(ac, av, &i) == 84)
            return 84;
    }
    return 0;
}
