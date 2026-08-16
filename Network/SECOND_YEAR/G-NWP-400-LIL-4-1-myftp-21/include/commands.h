/*
** EPITECH PROJECT, 2026
** SECOND_YEAR
** File description:
** commands
*/

#include "ftp.h"

#ifndef COMMANDS_H_
    #define COMMANDS_H_

const commands_t commands[] = {
    {"USER", do_user},
    {"PASS", do_pass},
    {"QUIT", do_quit},
    {"HELP", do_help},
    {"NOOP", do_nothing},
    {"PASV", do_pasv},
    {"PORT", do_port},
    {"RETR", do_retr},
    {"STOR", do_stor},
    {"LIST", do_list},
    {"CWD", do_cwd},
    {"CDUP", do_cdup},
    {"DELE", do_delete},
    {"PWD", do_pwd}
};


#endif /* !COMMANDS_H_ */
