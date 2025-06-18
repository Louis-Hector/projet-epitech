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
#include <termio.h>

char *hide_character(void)
{
    struct termios echo;
    size_t len = 0;
    char *passwd = NULL;

    tcgetattr(fileno(stdin), &echo);
    echo.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &echo);
    getline(&passwd, &len, stdin);
    passwd[strlen(passwd) - 1] = '\0';
    echo.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &echo);
    return passwd;
}

int check_password(char *shadow_hash, char *name)
{
    char *passwd = NULL;
    static int try = 0;

    printf("[my_sudo] password for %s: ", name);
    passwd = hide_character();
    if (my_strcmp(crypt(passwd, shadow_hash), shadow_hash) != 0) {
        if (try >= 2) {
            printf("\nmy_sudo: 3 incorrect password attempts\n");
            return 1;
        }
        printf("\nSorry, try again.\n");
        try++;
        check_password(shadow_hash, name);
    } else
        return 0;
}

int read_file_shadow(char *name, char **shadow_hash)
{
    FILE *fd = fopen("/etc/shadow", "r");
    size_t len = 0;
    char *line = NULL;
    char **tab = NULL;

    if (fd == NULL)
        return 84;
    while (getline(&line, &len, fd) != -1) {
        tab = my_str_to_word_array(line, ':');
        if (my_strcmp(tab[0], name) == 0) {
            (*shadow_hash) = tab[1];
            break;
        }
        for (int i = 0; tab[i] != NULL; i++)
            free(tab[i]);
        free(tab);
    }
    fclose(fd);
    free(line);
    return 0;
}

char *cat_shadow(char *shadow_hash, char *name)
{
    int count = 0;
    int a = 0;

    if (read_file_shadow(name, &shadow_hash) == 84)
        return NULL;
    return shadow_hash;
}
