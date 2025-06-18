/*
** EPITECH PROJECT, 2024
** option R
** File description:
** recursive
*/

#include <linux/stat.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

void make_ch(char const *str, struct dirent *info, char *c)
{
    if (str == NULL || str[0] == '.') {
        my_strcpy(c, info->d_name);
    } else {
        my_strcpy(c, str);
        my_strcat(c, "/");
        my_strcat(c, info->d_name);
    }
}

void print_many(const char *str, char **files, int count)
{
    if (str != NULL && str[0] != '.') {
        mini_printf("\n%s:\n", str);
    } else {
        mini_printf("\n./:\n");
    }
    for (int i = 0; i < count; i++) {
        mini_printf("%s ", files[i]);
    }
    mini_printf("\n");
}

int check_directory(char **files, int *count, struct dirent *info, char *c)
{
    struct stat sb;

    lstat(c, &sb);
    if (S_ISDIR(sb.st_mode)) {
        files[*count] = my_strdup(info->d_name);
        (*count)++;
        return 1;
    } else {
        files[*count] = my_strdup(info->d_name);
        (*count)++;
        return 0;
    }
}

void do_directory(char **files, int *count, struct dirent *info, char *c)
{
    if (check_directory(files, count, info, c)) {
        display_rmaj(c);
    }
}

int display_rmaj(const char *str)
{
    DIR *dirp;
    struct dirent *info;
    char c[1024];
    char *files[1024];
    int count = 0;

    dirp = opendir(str ? str : ".");
    info = readdir(dirp);
    while (info != NULL) {
        if (info->d_name[0] != '.') {
            make_ch(str, info, c);
            do_directory(files, &count, info, c);
        }
        info = readdir(dirp);
    }
    print_many(str, files, count);
    closedir(dirp);
    return 0;
}
