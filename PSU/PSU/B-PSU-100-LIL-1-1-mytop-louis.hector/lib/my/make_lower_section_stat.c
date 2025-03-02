/*
** EPITECH PROJECT, 2024
** make_lower_section.c
** File description:
** pid,nice,status...
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <pwd.h>

static void make_c(const char *str, struct dirent *info, char *c)
{
    if (str == NULL || str[0] == '.') {
        my_strcpy(c, info->d_name);
    } else {
        my_strcpy(c, str);
        my_strcat(c, "/");
        my_strcat(c, info->d_name);
    }
}

static void verif_priority(int priority, int status, int *i, int nice)
{
    if (priority == -100)
        mvprintw(*i, 18, "rt");
    else
        mvprintw(*i, 18, "%d", priority);
    mvprintw(*i, 22, "%d", nice);
    mvprintw(*i, 47, "%c", status);
    mvprintw(*i, 51, "0.0");
}

void check_directory(struct dirent *infos, char *path, char *buffer, int *i)
{
    int priority = 0;
    int status = 0;
    int fd = 0;
    int uptime = 0;
    int stime = 0;
    int nice = 0;

    if (my_getnbr(infos->d_name) != 0) {
        make_path("/proc", infos, path);
        fd = open(path, O_RDONLY);
        read(fd, buffer, 2000 - 1);
        buffer[2000 - 1] = '\0';
        sscanf(buffer, "%*d %*s %lc %*d %*d %*d %*d %*d %*d %*d %*d "
            "%*d %*d %d %d %*d %*d %d %d %*d %*d %*d %*d"
            , &status, &uptime, &stime, &priority, &nice);
        make_time(uptime, stime, i);
        verif_priority(priority, status, i, nice);
        (*i)++;
        close(fd);
    }
}

void make_lsection(void)
{
    DIR *dirp;
    struct dirent *infos;
    char path[1024] = {0};
    int i = 7;
    char buffer[100] = {0};

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
        check_directory(infos, path, buffer, &i);
        infos = readdir(dirp);
    }
    closedir(dirp);
}

void check_condition(struct dirent *infos, struct passwd *pwd, int *i)
{
    if (pwd != NULL) {
        mvprintw(*i, 4, "%s", infos->d_name);
        mvprintw(*i, 9, "%s", pwd->pw_name);
        (*i)++;
    } else {
        mvprintw(*i, 5, "%s", infos->d_name);
        mvwprintw(stdscr, (*i)++, 10, "Unknown User");
        }
}

void print_pid(struct dirent *infos, char *path, int *i)
{
    struct stat sb;
    struct passwd *pwd;

    if (my_getnbr(infos->d_name) != 0) {
        make_c("/proc", infos, path);
        if (lstat(path, &sb) == 0) {
            pwd = getpwuid(sb.st_uid);
            check_condition(infos, pwd, i);
        }
    }
}

void check_process_pid(void)
{
    DIR *dirp;
    struct dirent *infos;
    char path[1024] = {0};
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
        print_pid(infos, path, &i);
        infos = readdir(dirp);
    }
    closedir(dirp);
}
