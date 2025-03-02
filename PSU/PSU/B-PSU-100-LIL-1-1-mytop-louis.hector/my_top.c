/*
** EPITECH PROJECT, 2024
** my_top.c
** File description:
** my_top
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "my.h"
#include <utmp.h>
#include <ctype.h>

void make_the_top(void)
{
    mvprintw(0, 0, "top - ");
    my_time();
    my_getloadavg();
    my_uptime();
    my_task();
    my_cpu();
    my_user();
    my_meminfo();
    my_swapinfo();
    attron(A_STANDOUT);
    mvprintw(6, 0, "    PID USER      PR  NI    VIRT");
    mvprintw(6, 32, "     RES    SHR S  %%CPU  %%MEM");
    mvprintw(6, 60, "     TIME+ COMMAND");
    attroff(A_STANDOUT);
}

int chec_error(char const *str)
{
    int i = 0;
    int count = 0;

    if (str[0] == '-') {
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] == '.') {
            count++;
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
            return 0;
        }
        i++;
    }
    return count <= 1;
}

void attribute_time(int ac, char **av, int i, double *time)
{
    if (chec_error(av[i + 1]) == 0)
        exit(84);
    *time = atof(av[i + 1]);
}

static void attribute_frame(int ac, char **av, int i, int *frame)
{
    if (chec_error(av[i + 1]) == 0)
        exit(84);
    *frame = atoi(av[i + 1]);
}

void continue_the_loop(double time, int frame)
{
    int ch = 0;
    int j = 0;
    int x = 0, y = 0;
    int max_y = 0;
    int max_x = 0;

    initscr();
    keypad(stdscr, TRUE);
    curs_set(1);
    noecho();
    timeout(time * 1000);
    getmaxyx(stdscr, max_y, max_x);
    while (ch != 'q' && j != frame) {
        make_the_top();
        make_lsection();
        check_process_pid();
        print_virtual_size();
        move(y, x);
        if (ch == KEY_DOWN && y < max_y - 1)
            y++;
        if (ch == KEY_UP && y > 0)
            y--;
        ch = getch();
        refresh();
        j++;
    }
    endwin();
}

int main(int ac, char **av)
{
    double time = 3.0;
    int frame = 0;

    if (ac > 5)
        exit(84);
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-d") == 0 && i + 1 < ac) {
            attribute_time(ac, av, i, &time);
            i++;
        }
        if (strcmp(av[i], "-n") == 0 && i + 1 < ac) {
            attribute_frame(ac, av, i, &frame);
            i++;
        }
    }
    if (frame == 0)
        frame = -1;
    continue_the_loop(time, frame);
    return 0;
}
