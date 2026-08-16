/*
** EPITECH PROJECT, 2025
** builtin
** File description:
** builtin
*/

#include "shell.h"

#ifndef BUILTIN_H_
    #define BUILTIN_H_

const builtins_t builtins[] = {
    {"env", display_env},
    {"setenv", set_env},
    {"unsetenv", unset_env},
    {"cd", change_directory},
    {"exit", exit_shell},
    {"history", display_history},
    {"prompt", handle_prompt},
    {"dragon", display_easter_egg},
    {"credits", display_easter_egg},
    {"epitech", display_easter_egg},
    {"foreach", find_foreach},
    {"where", find_where},
    {"which", which},
    {"repeat", repeat_command}
};

#endif /* !BUILTIN_H_ */
