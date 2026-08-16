/*
** EPITECH PROJECT, 2024
** option a
** File description:
** all
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int display_a(char const *str)
{
    DIR *dirp;
    struct dirent *info;

    if (str == NULL || str[0] == '.')
        dirp = opendir(".");
    else
        dirp = opendir(str);
    if (dirp == NULL) {
        mini_printf("ls: cannot access '%s' : ", str);
        perror("");
        exit(84);
    }
    info = readdir(dirp);
    while (info != NULL) {
        mini_printf("%s ", info->d_name);
        info = readdir(dirp);
    }
    closedir(dirp);
    mini_printf("\n");
    return 0;
}
