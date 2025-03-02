/*
** EPITECH PROJECT, 2025
** main sudo
** File description:
** main
*/

#include "include/my.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <termio.h>
#include <crypt.h>
#include <grp.h>
#include "include/mystruct.h"

int my_exec(char *command, char *fichier, char *name)
{
    if (strcmp(name, "root") != 0)
        printf("\n");
    setuid(0);
    setgid(0);
    setgroups(0, NULL);
    if (execlp(command, command, fichier, (char *)NULL) != 0)
        return 84;
    return 0;
}

char *affect_table(FILE *fd, uid_t uid, char *username)
{
    size_t len = 0;
    uid_t user_uid;
    char **tab = NULL;
    char *line = NULL;

    while (getline(&line, &len, fd) != -1) {
        tab = my_str_to_word_array(line, ':');
        if (tab == NULL)
            return NULL;
        user_uid = atoi(tab[2]);
        if (user_uid == uid)
            username = tab[0];
    }
    free(line);
    return username;
}

char *getname(uid_t uid)
{
    FILE *fd;
    char *username = NULL;
    char *line = NULL;

    fd = fopen("/etc/passwd", "r");
    if (fd == NULL)
        return NULL;
    username = affect_table(fd, uid, username);
    fclose(fd);
    return username;
}

int check_arg(int ac, char **av)
{
    if (ac < 2) {
        printf("usage: ./my_sudo -h\nusage: "
        "./my_sudo [-ugEs] [command [args ...]]\n");
        return 84;
    }
    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        printf("usage: ./my_sudo -h\nusage: "
        "./my_sudo [-ugEs] [command [args ...]]\n");
        return 0;
    }
    return -1;
}

static int check_av(int ac, char **av, int *a) 
{
    uid_t uid = -1;
    gid_t gid = -1;

    for (int i = 1; i < ac; i++) {
        if (my_strcmp(av[i], "-u") == 0 && i + 1 < ac) {
            get_flag_u(av[i + 1], &uid, &gid);
            setgroups(1, &gid);
            setgid(gid);
            setuid(uid);
            *(a) += 2;
            i++;
        } else if (my_strcmp(av[i], "-g") == 0 && i + 1 < ac) {
            gid = check_group(av[i + 1]);
            setgid(gid);
            *(a) += 2;
            i++;
        }
    }
    return 0;
}


int main(int ac, char **av)
{
    char *name = getname(getuid());
    char *shadow_hash = malloc(sizeof(char) * 100);
    int return_value = check_arg(ac, av);
    int a = 0;

    if (ac > 1 && geteuid() != 0) {
        printf("Permission Denied\n");
        return 84;
    }
    if (shadow_hash == NULL)
        return 84;
    if (return_value >= 0)
        return return_value;
    if (my_strcmp(name, "root") == 0)
        return my_exec(av[1], av[2], name);
    if (check_sudoers(name) == 84)
        return 84;
    shadow_hash = cat_shadow(shadow_hash, name);
    if (check_password(shadow_hash, name) == 0) {
        if (check_av(ac, av, &a) == 84)
            return 84;
        return my_exec(av[a + 1], av[a + 2], name);
    }
    return 84;
}
