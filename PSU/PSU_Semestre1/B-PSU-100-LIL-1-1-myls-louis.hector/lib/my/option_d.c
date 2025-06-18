/*
** EPITECH PROJECT, 2024
** option d
** File description:
** directory
*/

#include <linux/stat.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int display_d(char const *str)
{
    if (str == NULL || str[0] == '.') {
        str = ".";
    }
    mini_printf("%s ", str);
    return 0;
}
