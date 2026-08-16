/*
** EPITECH PROJECT, 2025
** sudo
** File description:
** sudo
*/

#include "../include/my.h"
#include "../include/mystruct.h"
#include <string.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>

int check_etc(FILE *fd, char *name, uid_t *uid, gid_t *gid)
{
    size_t len = 0;
    char **tab = NULL;
    char *line = NULL;

    while (getline(&line, &len, fd) != -1) {
        tab = my_str_to_word_array(line, ':');
        if (tab == NULL)
            return -1;
        if (strcmp(tab[0], name) == 0) {
            *uid = atoi(tab[2]);
            *gid = atoi(tab[3]);
            break;
        }
    }
    free(line);
    return 0;
}

int get_flag_u(char *name, uid_t *uid, gid_t *gid)
{
    FILE *fd;

    fd = fopen("/etc/passwd", "r");
    if (fd == NULL)
        return -1;
    check_etc(fd, name, uid, gid);
    fclose(fd);
    return 0;
}

gid_t check_group(char *group)
{
    FILE *fd = fopen("/etc/group", "r");
    size_t size = 0;
    char *line = NULL;
    char name[100];
    gid_t gid = -1;

    if (fd == NULL)
        return -1;
    while (getline(&line, &size, fd) != -1) {
        sscanf(line, "%[^:]", name);
        if (strcmp(name, group) == 0) {
            sscanf(line, "%*[^:]:%*[^:]:%d", &gid);
            break;
        }
    }
    free(line);
    fclose(fd);
    printf("%d", gid);
    return gid;
}
