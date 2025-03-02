/*
** EPITECH PROJECT, 2024
** print_ltime.c
** File description:
** the lowersection for the time
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>


void make_time(int uptime, int stime, int *i)
{
    int total_time = uptime + stime;
    int second = total_time / 100;
    int millisecond = total_time % 100;
    int minute = second / 60;

    second = second % 60;
    mvprintw(*i, 63, "%d:%02d.%02d", minute, second, millisecond);
}
