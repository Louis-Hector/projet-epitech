/*
** EPITECH PROJECT, 2025
** B-CPE-110 : struct.h
** File description:
** struct for the projet sudo
*/

#ifndef STRUCT_H
    #define STRUCT_H

char *cat_shadow(char *shadow_hash, char *name);
int check_password(char *shadow_hash, char *name);
int check_sudoers(char *name);
int get_flag_u(char *name, uid_t *uid, gid_t *gid);
gid_t check_group(char *group);

#endif
