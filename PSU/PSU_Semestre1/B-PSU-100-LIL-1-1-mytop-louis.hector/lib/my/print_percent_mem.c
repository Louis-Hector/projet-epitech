/*
** EPITECH PROJECT, 2024
** print_percent_mem.c
** File description:
** percentage of mem
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>
#include <linux/stat.h>
#include <sys/stat.h>


void find_percentage_mem(int *i, int vmRss)
{
    int fd = 0;
    char buffer[256] = {0};
    int total_mem = 0;
    double percentage;

    fd = open("/proc/meminfo", O_RDONLY);
    if (fd < 0)
        return;
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[40 - 1] = '\0';
    if (sscanf(buffer, "MemTotal:       %d kB", &total_mem) != 1)
        return;
    close(fd);
    percentage = (double)(vmRss) / total_mem * 100;
    mvprintw(*i, 57, "%.1f", percentage);
}
