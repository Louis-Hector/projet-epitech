/*
** EPITECH PROJECT, 2024
** print_information.c
** File description:
** name command...
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>
#include <string.h>

char **make_the_tab(char *buffer)
{
    char **tab = malloc(sizeof(char *) * 26);
    int index = 0;
    int j = 0;

    for (int i = 0; i < 26; i++) {
        tab[i] = malloc(sizeof(char) * (40 + 1));
        j = 0;
        while (buffer[index] != '\n' && buffer[index] != '\0' && j < 40) {
            tab[i][j] = buffer[index];
            index++;
            j++;
        }
        tab[i][j] = '\0';
        if (buffer[index] == '\n')
            index++;
    }
    return tab;
}

void make_status(const char *str, struct dirent *info, char *c)
{
    if (str == NULL || str[0] == '.') {
        my_strcpy(c, info->d_name);
    } else {
        my_strcpy(c, str);
        my_strcat(c, "/");
        my_strcat(c, info->d_name);
        my_strcat(c, "/status");
    }
}

void verif_vm(char **tab, int *i)
{
    int memory = 0;
    int vmRss = 0;
    int Rssfile = 0;

    if (tab[18] && strncmp(tab[18], "VmSize:", 7) == 0)
        memory = my_getnbr(tab[18] + 7);
    mvprintw(*i, 28, "%d", memory);
    if (tab[22] && strncmp(tab[22], "VmRSS:", 6) == 0)
        vmRss = my_getnbr(tab[22] + 6);
    mvprintw(*i, 35, "%d", vmRss);
    find_percentage_mem(i, vmRss);
    if (tab[24] && strncmp(tab[24], "RssFile:", 8) == 0)
        Rssfile = my_getnbr(tab[24] + 8);
    mvprintw(*i, 42, "%d", Rssfile);
    (*i)++;
}

void print_name(char *buffer, int *i, struct dirent *infos, char *path)
{
    int a = 0;
    char name[1000] = {0};
    int fd = 0;
    char **tab;

    if (my_getnbr(infos->d_name) != 0) {
        make_status("/proc", infos, path);
        fd = open(path, O_RDONLY);
        read(fd, buffer, 2000 - 1);
        buffer[2000 - 1] = '\0';
        tab = make_the_tab(buffer);
        for (int j = 6; j < my_strlen(tab[0]); j++) {
                name[a] = tab[0][j];
                a++;
        }
        name[a] = '\0';
        mvprintw(*i, 71, "%s", name);
        verif_vm(tab, i);
        close(fd);
    }
}

void print_virtual_size(void)
{
    DIR *dirp;
    struct dirent *infos;
    char path[1024] = {0};
    char buffer[2000] = {0};
    int i = 7;

    dirp = opendir("/proc/");
    if (dirp == NULL)
        return;
    infos = readdir(dirp);
    while (infos != NULL) {
        if (strcmp(infos->d_name, ".") == 0
            || strcmp(infos->d_name, "..") == 0) {
            infos = readdir(dirp);
            continue;
        }
        print_name(buffer, &i, infos, path);
        infos = readdir(dirp);
    }
    closedir(dirp);
}
