/*
** EPITECH PROJECT, 2024
** exo bootstrap
** File description:
** k
*/

/*
** EPITECH PROJECT, 2024
** exo bootstrap
** File description:
** k
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <linux/stat.h>
#include <fcntl.h>
#include "my.h"
#include <dirent.h>
#include "myliste.h"

static void make_condition(char const *flag, char const *str, int a, int i)
{
    if (list[a].flags == flag[i]) {
        list[a].function(str);
    }
}

static void check_sanitor_error(char const *flag, char const *str,
    int a, int *flag_found)
{
    if (list[a].flags == flag[1])
        *flag_found = 1;
}

int find_the_options(char const *flag, char const *str)
{
    int flag_found = 0;
    int i = 1;

    if (flag[0] == '-') {
        for (int a = 0; list[a].function != NULL; a++) {
            make_condition(flag, str, a, i);
            check_sanitor_error(flag, str, a, &flag_found);
        }
        if (!flag_found)
            exit(84);
        return 0;
    }
    return 1;
}

int check_err(char const *str, DIR *dirp)
{
    if (dirp == NULL) {
        mini_printf("ls: cannot access '%s' : ", str);
        perror("");
        exit(84);
    }
    return 0;
}

int my_ls(char const *str, char *flags)
{
    DIR *dirp;
    struct dirent *info;

    if (flags != NULL)
        if (find_the_options(flags, str) == 0)
            return 0;
    dirp = opendir(str ? str : ".");
    if (check_err(str, dirp) != 0)
        return 84;
    info = readdir(dirp);
    while (info != NULL) {
        if ((flags == NULL && info->d_name[0] != '.'))
            mini_printf("%s ", info->d_name);
        info = readdir(dirp);
    }
    closedir(dirp);
    my_putchar('\n');
    return 0;
}

static void make_test(int ac, int i)
{
    if (i < ac - 1)
        my_putchar('\n');
}

static void print_flags(char *flags, char **av, int ac, int *i)
{
    if (av[*i][0] != '-') {
        mini_printf("%s:\n", av[*i]);
        my_ls(av[*i], flags);
        make_test(ac, *i);
    }
}

static void display_condition(int ac, char **av, char *flags, int i)
{
    if (ac > 3 && flags != NULL || ac >= 3 && flags == NULL) {
        while (i < ac) {
            print_flags(flags, av, ac, &i);
            i++;
        }
    } else if ((ac == 2 && flags != NULL)
        || (ac == 3 && flags != NULL && av[2][0] == '.'))
        my_ls(".", flags);
    else
        my_ls(av[i], flags);
}

int main(int ac, char **av)
{
    int i = 1;
    char *flags = NULL;

    if (ac == 1 || (ac == 2 && av[1][0] == '.')) {
        my_ls(".", NULL);
    } else {
        if (av[1][0] == '-') {
            flags = av[1];
            i++;
        }
        display_condition(ac, av, flags, i);
    }
    return 0;
}
