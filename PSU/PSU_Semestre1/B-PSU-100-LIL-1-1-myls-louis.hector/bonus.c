/*
** EPITECH PROJECT, 2024
** bonus
** File description:
** sort alpha
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

void check_maj(char *str1, char *str2, int len1, int len2)
{
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] >= 'A' && str1[i] <= 'Z')
            str1[i] = str1[i] + 32;
    }
    for (int j = 0; str2[j] != '\0'; j++) {
        if (str2[j] >= 'A' && str2[j] <= 'Z')
            str2[j] = str2[j] + 32;
    }
}

int display_new_strcmp(const char *s1, const char *s2)
{
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);
    int len = my_strlen(s1);
    char *str1 = my_strdup(s1);
    char *str2 = my_strdup(s2);

    if (len1 > len2)
        len = len1;
    if (len1 < len2)
        len = len2;
    check_maj(str1, str2, len1, len2);
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i] && str1[i] != '.' && str2[i] != '.'
            && str1[i] >= '_' && str2[i] != '_')
            return str1[i] - str2[i];
    }
    return 0;
}

void condition(int j, char **filenames)
{
    char *temp;

    if (display_new_strcmp(filenames[j], filenames[j + 1]) > 0) {
        temp = filenames[j];
        filenames[j] = filenames[j + 1];
        filenames[j + 1] = temp;
    }
}

static void sort_entries_alpha(DIR *dirp, struct dirent *info)
{
    char *filenames[100];
    int longeur = 0;

    info = readdir(dirp);
    while (info != NULL) {
        if (info->d_name[0] != '.') {
            filenames[longeur] = my_strdup(info->d_name);
            longeur++;
        }
        info = readdir(dirp);
    }
    for (int i = 0; i < longeur - 1; i++) {
        for (int j = 0; j < longeur - i - 1; j++)
            condition(j, filenames);
    }
    for (int j = 0; j < longeur; j++)
        mini_printf("%s ", filenames[j]);
    mini_printf("\n");
}

int my_ls(char const *str)
{
    DIR *dirp;
    struct dirent *info;

    if (str == NULL || str[0] == '.')
        dirp = opendir(".");
    else
        dirp = opendir(str);
    sort_entries_alpha(dirp, info);
    closedir(dirp);
    return 0;
}

int main(int ac, char **av)
{
    int i = 1;

    if (ac <= 2)
        my_ls(av[1]);
    else 
        while (av[i] != NULL) {
            mini_printf("%s:\n",av[i]);
            my_ls(av[i]);
            my_putchar('\n');
            i++;
        }
        return 0;
}