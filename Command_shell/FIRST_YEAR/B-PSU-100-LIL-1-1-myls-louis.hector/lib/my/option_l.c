/*
** EPITECH PROJECT, 2024
** option l
** File description:
** use a long listing format
*/

#include <string.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

static void make_many_condition(char const *file
    , char *permissions)
{
    struct stat sb;

    lstat(file, &sb);
    if (sb.st_mode & S_IWGRP)
        permissions[5] = 'w';
    if (sb.st_mode & S_IXGRP)
        permissions[6] = 'x';
    if (sb.st_mode & S_IROTH)
        permissions[7] = 'r';
    if (sb.st_mode & S_IWOTH)
        permissions[8] = 'w';
    if (sb.st_mode & S_IXOTH)
        permissions[9] = 'x';
    if (sb.st_mode & S_ISVTX) {
        if (permissions[9] == 'x')
            permissions[9] = 't';
        else
            permissions[9] = 'T';
    }
}

static void display_mode(char const *file)
{
    struct stat sb;
    char permissions[10] = "----------";

    lstat(file, &sb);
    if (S_ISDIR(sb.st_mode))
        permissions[0] = 'd';
    if (sb.st_mode & S_IRUSR)
        permissions[1] = 'r';
    if (sb.st_mode & S_IWUSR)
        permissions[2] = 'w';
    if (sb.st_mode & S_IXUSR)
        permissions[3] = 'x';
    if (sb.st_mode & S_IRGRP)
        permissions[4] = 'r';
    make_many_condition(file, permissions);
    mini_printf("%s ", permissions);
}

void make_c(char const *str, struct dirent *info, char *c)
{
    if (str == NULL || str[0] == '.') {
        my_strcpy(c, info->d_name);
    } else {
        my_strcpy(c, str);
        my_strcat(c, "/");
        my_strcat(c, info->d_name);
    }
}

void print_total_blocks(const char *str)
{
    DIR *dirp;
    struct dirent *info;
    struct stat sb;
    int total = 0;
    char c[1024];

    dirp = opendir(str ? str : ".");
    info = readdir(dirp);
    while (info != NULL) {
        if (info->d_name[0] != '.') {
            make_c(str, info, c);
            lstat(c, &sb);
            total += sb.st_blocks;
        }
        info = readdir(dirp);
    }
    closedir(dirp);
    mini_printf("total %d\n", total / 2);
}

void display_infos(const char *file)
{
    struct stat sb;
    struct passwd *pwd;
    struct group *grp;

    lstat(file, &sb);
    pwd = getpwuid(sb.st_uid);
    grp = getgrgid(sb.st_gid);
    if (grp == NULL) {
        mini_printf("GID %d\n", sb.st_gid);
        return;
    }
    mini_printf("%d ", sb.st_nlink);
    mini_printf("%s ", pwd->pw_name);
    mini_printf("%s ", grp->gr_name);
    mini_printf("%d ", sb.st_size);
}

void display_time(char const *file)
{
    struct stat sb;
    char *c = ctime(&sb.st_ctime);
    char time[12];
    int j = 0;

    lstat(file, &sb);
    for (int i = 4; c[i] != '\0'; i++) {
        if (i < 16) {
        time[j] = c[i];
        j++;
        }
    }
    time[j] = '\0';
    mini_printf("%s ", time);
}

static int check_error(char const *str, DIR *dirp)
{
    if (dirp == NULL) {
        mini_printf("ls: cannot access '%s' : ", str);
        perror("");
        exit(84);
    }
    return 0;
}

static void display(char *c)
{
    display_mode(c);
    display_infos(c);
    display_time(c);
}

int display_l(char const *str)
{
    DIR *dirp;
    struct dirent *info;
    char c[1024];

    dirp = opendir(str ? str : ".");
    if (check_error(str, dirp) != 0)
        return 84;
    info = readdir(dirp);
    print_total_blocks(str);
    while (info != NULL) {
        if (info->d_name[0] != '.') {
            make_c(str, info, c);
            display(c);
            mini_printf("%s\n", info->d_name);
        }
        info = readdir(dirp);
    }
    closedir(dirp);
    return 0;
}
