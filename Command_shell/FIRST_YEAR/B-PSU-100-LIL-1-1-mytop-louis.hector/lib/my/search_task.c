/*
** EPITECH PROJECT, 2024
** search_task.c
** File description:
** the header for top with task
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>
#include <dirent.h>
#include <string.h>
#include "../../include/mystruct.h"

void make_path(const char *str, struct dirent *info, char *c)
{
    if (str == NULL || str[0] == '.') {
        my_strcpy(c, info->d_name);
    } else {
        my_strcpy(c, str);
        my_strcat(c, "/");
        my_strcat(c, info->d_name);
        my_strcat(c, "/stat");
    }
}

static void read_stat(const char *path, char *buff)
{
    int fd = open(path, O_RDONLY);

    if (fd != -1) {
        read(fd, buff, 2000 - 1);
        buff[2000 - 1] = '\0';
        close(fd);
    }
}

void analyze_process_state(char *buff, ProcessStats_t *stats)
{
    for (int j = 0; j < my_strlen(buff); j++) {
        if (buff[j] == 'R' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->R++;
        if (buff[j] == 'D' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->D++;
        if (buff[j] == 'S' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->S++;
        if (buff[j] == 'Z' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->Z++;
        if (buff[j] == 'T' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->T++;
        if (buff[j] == 'I' && buff[j + 1] == ' '
            && buff[j - 1] == ' ')
            stats->I++;
    }
}

void display_results(ProcessStats_t *stats)
{
    int total = stats->D + stats->I + stats->R
        + stats->S + stats->T + stats->Z;

    mvprintw(1, 0, "Tasks: %d total,   %d running,"
        , total, stats->R);
    mvprintw(1, 34, "%d sleeping,   %d stopped,   %d zombie"
        , stats->S + stats->D + stats->I, stats->T, stats->Z);
}

void process_dir(DIR *dirp, ProcessStats_t *stats)
{
    struct dirent *infos;
    char buff[2000] = {0};
    char path[1024] = {0};

    infos = readdir(dirp);
    while (infos != NULL) {
        if (strcmp(infos->d_name, ".") == 0
            || strcmp(infos->d_name, "..") == 0) {
            infos = readdir(dirp);
            continue;
        }
        if (my_getnbr(infos->d_name) != 0) {
            make_path("/proc", infos, path);
            read_stat(path, buff);
            analyze_process_state(buff, stats);
        }
        infos = readdir(dirp);
    }
}

int my_task(void)
{
    DIR *dirp = opendir("/proc/");
    ProcessStats_t stats = {0, 0, 0, 0, 0, 0};

    if (dirp == NULL)
        return 84;
    process_dir(dirp, &stats);
    display_results(&stats);
    closedir(dirp);
    return 0;
}
