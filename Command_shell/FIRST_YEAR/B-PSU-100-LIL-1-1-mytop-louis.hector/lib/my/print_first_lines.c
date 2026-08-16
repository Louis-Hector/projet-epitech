/*
** EPITECH PROJECT, 2024
** my_top.c
** File description:
** my_top
*/

#include <pwd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <sys/types.h>
#include "my.h"
#include <utmp.h>
#include <ctype.h>


int my_getloadavg(void)
{
    int fd;
    char *buffer;
    float nb1;
    float nb2;
    float nb3;

    fd = open("/proc/loadavg", O_RDONLY);
    buffer = malloc(sizeof(char) * 15);
    read(fd, buffer, 14);
    buffer[14] = '\0';
    sscanf(buffer, "%f %f %f", &nb1, &nb2, &nb3);
    mvprintw(0, 49, "load average: %.2f, %.2f, %.2f", nb1, nb2, nb3);
    refresh();
    free(buffer);
    close(fd);
    return 0;
}

int my_time(void)
{
    int fd;
    char *buffer = malloc(sizeof(char) * 100);
    char *time = malloc(sizeof(char) * (9 + 1));
    int j = 0;

    fd = open("/proc/driver/rtc", O_RDONLY);
    read(fd, buffer, 99);
    buffer[99] = '\0';
    for (int i = 11; i < 19; i++) {
        time[j] = buffer[i];
        j++;
    }
    time[j] = '\0';
    mvprintw(0, 6, time, 10);
    refresh();
    free(buffer);
    free(time);
    close(fd);
    return 0;
}

void check_the_time(double temps_pc)
{
    int days = (int)(temps_pc / 86400);
    int hours = (int)((temps_pc - days * 86400) / 3600);
    int minutes = (int)((temps_pc - days * 86400 - hours * 3600) / 60);

    if (days >= 1 && hours > 0)
        mvprintw(0, 15, "up %d days, %02d:%02d,", days, hours, minutes);
    if (days == 0 && hours == 0)
        mvprintw(0, 15, "up %02d min", minutes);
    if (days == 0 && hours > 0)
        mvprintw(0, 15, "up %02d:%02d", hours, minutes);
    if (days == 1 && hours == 0 && minutes > 0)
        mvprintw(0, 15, "up 1 day, %02d min", minutes);
}

int my_uptime(void)
{
    int fd;
    char *buffer;
    double temps_pc = 0;

    fd = open("/proc/uptime", O_RDONLY);
    buffer = malloc(sizeof(char) * 100);
    read(fd, buffer, 99);
    temps_pc = atof(buffer);
    buffer[99] = '\0';
    check_the_time(temps_pc);
    refresh();
    free(buffer);
    close(fd);
    return 0;
}

int my_user(void)
{
    int fd;
    struct utmp user;
    int number_users = 0;
    int len = 0;

    fd = open("/var/run/utmp", O_RDONLY);
    if (fd < 0) {
        mvprintw(0, 35, "0 user,");
        return 0;
    }
    len = read(fd, &user, sizeof(struct utmp));
    while (len > 0) {
        if (user.ut_type == USER_PROCESS)
            number_users++;
        len = read(fd, &user, sizeof(struct utmp));
    }
    number_users--;
    mvprintw(0, 35, "%d user,", number_users);
    close(fd);
    return 0;
}
