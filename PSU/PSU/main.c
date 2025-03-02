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
#include "include/mystruct.h"

static int my_exec(char *command, char *fichier)
{
    printf("\n");
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



int main(int ac, char **av)
{
    uid_t uid = getuid();
    char *name = getname(uid);
    int a = 0;
    char *shadow_hash = malloc(sizeof(char) * 100);
    int return_value = check_arg(ac, av);

    if (return_value >= 0)
        return return_value;
    if (my_strcmp(name, "root") == 0)
        return my_exec(av[1], av[2]);
    if (check_sudoers(name) == 84)
        return 84;
    shadow_hash = cat_shadow(shadow_hash, name);
    if (shadow_hash == NULL)
        return 84;
    if (check_password(shadow_hash, name) == 0) {
        check_av(ac, av, &a);
        return my_exec(av[a + 1], av[a + 2]);
    }
    return 84;
}
