/*
** EPITECH PROJECT, 2024
** make_header.c
** File description:
** the header for top
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>

static char **check_tab(char **tab, int i, int j)
{
    if (!tab[i]) {
        for (int j = 0; j < i; j++)
            free(tab[j]);
        free(tab);
        return NULL;
    }
    return tab;
}

char **make_the_str(char *buffer)
{
    int index = 0;
    char **tab = malloc(sizeof(char *) * 26);
    int j = 0;

    for (int i = 0; i < 26; i++) {
        tab[i] = malloc(sizeof(char) * (28 + 1));
        if (check_tab(tab, i, j) == NULL)
            return NULL;
        j = 0;
        while (buffer[index] != '\n' && buffer[index] != '\0' && j < 28) {
            tab[i][j] = buffer[index];
            index++;
            j++;
        }
        tab[i][j] = '\0';
        if (buffer[index] == '\n') {
            index++;
        }
    }
    return tab;
}

void print_meminfo(char *buffer, char **mem)
{
    int memSr;
    int memTotal = 0;
    int memFree = 0;
    int memA = 0;
    int memBu = 0;
    int memC = 0;

    memSr = my_getnbr(mem[25]);
    memBu = my_getnbr(mem[3]);
    memC = my_getnbr(mem[4]);
    sscanf(buffer,
        "MemTotal: %d kB\n MemFree: %d kB\n MemAvailable: %d kB\n",
        &memTotal, &memFree, &memA);
    mvprintw(3, 0, "MiB Mem : %.1f total,", (double)memTotal / 1024);
    mvprintw(3, 25, "   %.1f free,", (double)memFree / 1024);
    mvprintw(3, 40, "   %.1f used,", (double)(memTotal - memA) / 1024.0);
    mvprintw(3, 55, "   %.1f buff/cache"
        , (double)(memBu + memC + memSr) / 1024);
    refresh();
}

int my_meminfo(void)
{
    int fd;
    char buffer[2000] = {0};
    char **mem;

    fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1)
        return -1;
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    mem = make_the_str(buffer);
    print_meminfo(buffer, mem);
    close(fd);
    for (int i = 0; i < 26; i++)
        free(mem[i]);
    free(mem);
}

void print_swapinfo(char **tab)
{
    int swapTotal = 0;
    int swapfree = 0;
    int swapAvailable = 0;

    swapTotal = my_getnbr(tab[14]);
    swapfree = my_getnbr(tab[15]);
    swapAvailable = my_getnbr(tab[2]);
    mvprintw(4, 0, "MiB Swap: %.1f  total,", (double)swapTotal / 1024);
    mvprintw(4, 28, "%.1f free,", (double)swapfree / 1024);
    mvprintw(4, 46, "%.1f used.", (double)(swapTotal - swapfree) / 1024);
    mvprintw(4, 63, "%.1f avail Mem", (double)(swapAvailable) / 1024);
    refresh();
}

int my_swapinfo(void)
{
    int fd;
    char buffer[2000] = {0};
    char **tab;

    fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1)
        return -1;
    read(fd, buffer, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    tab = make_the_str(buffer);
    print_swapinfo(tab);
    close(fd);
    for (int i = 0; i < 26; i++)
        free(tab[i]);
    free(tab);
    return 0;
}
