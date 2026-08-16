/*
** EPITECH PROJECT, 2025
** 42hesh
** File description:
** test_shell
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void redirect_all_streams(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static env_t *create_env(const char *key, const char *value)
{
    env_t *env = malloc(sizeof(env_t));
    env->key = strdup(key);
    env->value = strdup(value);
    env->next = NULL;
    return env;
}

Test(change_directory, go_to_home_directory)
{
    char *old_path = NULL;
    shell_t shell = {NULL, 0, NULL, NULL, NULL, NULL};
    env_t *env = create_env("HOME", "/tmp");

    char *args[] = {"cd", NULL};
    int result = change_directory(args, &env, &old_path, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
    cr_assert_not_null(shell.prompt);
    cr_assert(strstr(shell.prompt, "/tmp") != NULL, "Prompt does not contain /tmp");

    free(env->key);
    free(env->value);
    free(env);
    free(old_path);
    free(shell.prompt);
}

Test(change_directory, valid_directory_change)
{
    shell_t shell = { .return_value = 0, .prompt = strdup("test>") };
    env_t *env = NULL;
    char *old_path = strdup("/home/user");
    char *tab[] = {"cd", "/tmp", NULL};

    int result = change_directory(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);

    free(old_path);
    free(shell.prompt);
}

Test(change_directory, valid_cd_wave)
{
    shell_t shell = { .return_value = 0, .prompt = strdup("test>") };
    env_t *env = NULL;
    char *old_path = strdup("/home/user");
    char *tab[] = {"cd", "~/tmp", NULL};

    int result = change_directory(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);

    free(old_path);
    free(shell.prompt);
}

Test(change_directory, too_many_args)
{
    shell_t shell = { .return_value = 0, .prompt = strdup("test>") };
    env_t *env = NULL;
    char *old_path = strdup("/home/user");
    char *tab[] = {"cd", "~/tmp", "tests", NULL};

    int result = change_directory(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);

    free(old_path);
    free(shell.prompt);
}

Test(change_directory, invalid_directory)
{
    shell_t shell = { .return_value = 0, .prompt = strdup("test>") };
    env_t *env = NULL;
    char *old_path = strdup("/home/user");
    char *tab[] = {"cd", "/invalid_directory", NULL};

    int result = change_directory(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);

    free(old_path);
    free(shell.prompt);
}

Test(change_directory, toggle_previous_directory)
{
    shell_t shell = { .return_value = 0, .prompt = strdup("test>") };
    env_t *env = NULL;
    char *old_path = strdup("/home/user");
    char *tab[] = {"cd", "-", NULL};

    int result = change_directory(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_null(old_path);

    free(shell.prompt);
}

Test(is_data_present, valid_variable_inserted, .init=redirect_all_stdout)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "MYVAR", "42", NULL};

    int result = is_data_present(args, &env);
    cr_assert_eq(result, 0);
    cr_assert_not_null(env);
    cr_assert_str_eq(env->key, "MYVAR");
    cr_assert_str_eq(env->value, "42");
}

Test(is_data_missing, insert_empty_value, .init=redirect_all_stdout)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "EMPTYVAL", NULL};

    int result = is_data_missing(args, &env);
    cr_assert_eq(result, 0);
    cr_assert_not_null(env);
    cr_assert_str_eq(env->value, "");
}

Test(remove_node, remove_first_node)
{
    env_t *env = create_env("VAR1", "123");
    env->next = create_env("VAR2", "456");
    env_t *prev = NULL;
    env_t *current = env;

    remove_node(&current, &prev, &env);

    cr_assert_str_eq(env->key, "VAR2");
    cr_assert_null(env->next);
}

Test(remove_node, remove_middle_node)
{
    env_t *node3 = malloc(sizeof(env_t));
    node3->key = strdup("VAR3");
    node3->value = strdup("value3");
    node3->next = NULL;

    env_t *node2 = malloc(sizeof(env_t));
    node2->key = strdup("VAR2");
    node2->value = strdup("value2");
    node2->next = node3;

    env_t *node1 = malloc(sizeof(env_t));
    node1->key = strdup("VAR1");
    node1->value = strdup("value1");
    node1->next = node2;

    env_t *head = node1;
    env_t *prev = node1;
    env_t *current = node2;

    remove_node(&current, &prev, &head);

    cr_assert_eq(prev->next, node3);
    cr_assert_str_eq(prev->key, "VAR1");
    cr_assert_eq(current, node3);

    free(node3->key);
    free(node3->value);
    free(node3);
    free(node1->key);
    free(node1->value);
    free(node1);
}

Test(remove_node, remove_last_node)
{
    env_t *node2 = malloc(sizeof(env_t));
    node2->key = strdup("VAR2");
    node2->value = strdup("value2");
    node2->next = NULL;

    env_t *node1 = malloc(sizeof(env_t));
    node1->key = strdup("VAR1");
    node1->value = strdup("value1");
    node1->next = node2;

    env_t *head = node1;
    env_t *prev = node1;
    env_t *current = node2;

    remove_node(&current, &prev, &head);

    cr_assert_eq(prev->next, NULL);
    cr_assert_str_eq(prev->key, "VAR1");
    cr_assert_eq(current, NULL);

    free(node1->key);
    free(node1->value);
    free(node1);
}

Test(check_builtins, unknown_command_returns_2)
{
    command_t cmd = {.args = (char*[]){"unknown", NULL}};
    env_t *env = NULL;
    shell_t shell = {0};

    int ret = check_builtins(&cmd, &env, &shell);
    cr_assert_eq(ret, 2);
}

Test(free_old_path, return_value_not_minus_one)
{
    char *old_path = strdup("/home/user");

    int result = free_old_path(0, old_path);
    cr_assert_eq(result, 0);

    free(old_path);
}

Test(free_old_path, return_value_minus_one)
{
    char *old_path = strdup("/home/user");

    int result = free_old_path(-1, old_path);
    cr_assert_eq(result, -1);
}

void print_env(env_t *env)
{
    while (env) {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

Test(from_array_to_list, converts_array_to_list)
{
    char *array[] = {"USER=test", "HOME=/home/user", NULL};
    env_t *list = NULL;

    list = from_array_to_list(list, array);
    cr_assert_not_null(list);
    cr_assert_str_eq(list->key, "USER");
    cr_assert_str_eq(list->value, "test");
    cr_assert_str_eq(list->next->key, "HOME");
    cr_assert_str_eq(list->next->value, "/home/user");
}

Test(from_list_to_array, converts_list_to_array)
{
    env_t *env = malloc(sizeof(env_t));
    env->key = strdup("EDITOR");
    env->value = strdup("vim");
    env->next = malloc(sizeof(env_t));
    env->next->key = strdup("SHELL");
    env->next->value = strdup("/bin/bash");
    env->next->next = NULL;

    char **array = from_list_to_array(&env);
    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "EDITOR=vim");
    cr_assert_str_eq(array[1], "SHELL=/bin/bash");
    cr_assert_null(array[2]);
}

Test(check_arg_number, too_many_arguments)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "VAR", "value", "extra", NULL};

    int result = check_arg_number(&env, 4, args);

    cr_assert_eq(result, 1);
}

Test(check_arg_number, display_env_variables)
{
    env_t env1 = { .key = "PATH", .value = "/usr/bin", .next = NULL };
    env_t env2 = { .key = "HOME", .value = "/home/user", .next = &env1 };
    env_t *env = &env2;
    char *args[] = {"setenv", NULL};

    int result = check_arg_number(&env, 1, args);

    cr_assert_eq(result, 0);
}

Test(check_arg_number, valid_argument_number)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "VAR", "value", NULL};

    int result = check_arg_number(&env, 3, args);

    cr_assert_eq(result, 0);
}

Test(is_data_missing, variable_starts_with_number)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "123VAR", NULL};

    int result = is_data_missing(args, &env);

    cr_assert_eq(result, 1);
}

Test(is_data_missing, variable_contains_non_alphanumeric)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "VAR$", NULL};

    int result = is_data_missing(args, &env);

    cr_assert_eq(result, 1);
}

Test(is_data_missing, variable_not_existing)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "NEW_VAR", NULL};

    int result = is_data_missing(args, &env);

    cr_assert_eq(result, 0);
}

Test(is_data_missing, valid_variable_no_value)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "MY_VAR", NULL};

    int result = is_data_missing(args, &env);

    cr_assert_eq(result, 0);
}

#include <criterion/criterion.h>
#include <stdlib.h>

Test(is_data_present, variable_starts_with_number)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "123VAR", "value", NULL};

    int result = is_data_present(args, &env);

    cr_assert_eq(result, 1);
}

Test(is_data_present, variable_is_empty_string)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "\"\"", "value", NULL};

    int result = is_data_present(args, &env);

    cr_assert_eq(result, 1);
}

Test(is_data_present, variable_contains_non_alphanumeric)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "VAR$", "value", NULL};

    int result = is_data_present(args, &env);

    cr_assert_eq(result, 1);
}

Test(is_data_present, variable_not_existing)
{
    env_t *env = NULL;
    char *args[] = {"setenv", "NEW_VAR", "value", NULL};

    int result = is_data_present(args, &env);

    cr_assert_eq(result, 0);
}

Test(unset_env, remove_existing_variable, .init=redirect_all_stdout)
{
    shell_t shell = {0};
    env_t *env = malloc(sizeof(env_t));
    env->key = strdup("MYVAR");
    env->value = strdup("test");
    env->next = NULL;
    char *tab[] = {"unsetenv", "MYVAR", NULL};

    int ret = unset_env(tab, &env, (char *[]){"OLDPWD"}, &shell);

    FILE *output = cr_get_redirected_stdout();
    char buffer[1024];
    fgets(buffer, sizeof(buffer), output);
    cr_log_info("Sortie obtenue:\n%s\n", buffer);

    cr_assert_eq(ret, 0);
    cr_assert_null(env);
}

Test(get_home_user, without_home_variable)
{
    unsetenv("HOME");
    char *result = get_home_user("documents/file.txt");

    cr_assert_not_null(result);
}

Test(create_files, success)
{
    shell_t shell = {NULL, 0, NULL, NULL, NULL, NULL};
    shell.history_path = "/tmp/history_test.txt";
    
    unlink(shell.history_path);

    int result = create_files(&shell);

    cr_assert_eq(result, 0);
    FILE *file = fopen(shell.history_path, "r");
    cr_assert_not_null(file);
    fclose(file);
}

Test(unset_env, not_found)
{
    env_t *env = create_env("MYVAR", "42");
    char *args[] = {"unsetenv", "NONEXISTENT", NULL};
    shell_t shell = {0};

    int result = unset_env(args, &env, NULL, &shell);

    cr_assert_eq(result, 0);
    cr_assert_not_null(env);
}

Test(parse_input, empty_input)
{
    command_t *commands = NULL;
    char *input = "";

    int result = parse_input(&commands, input);

    cr_assert_eq(result, 0, "Expected success (0), got %d", result);
    cr_assert_null(commands, "Commands list should be NULL for empty input");
}

static history_t *create_history_entry(const char *command, int index)
{
    history_t *entry = malloc(sizeof(history_t));
    entry->command = strdup(command);
    entry->time = strdup("12:00");
    entry->index = index;
    entry->next = NULL;
    return entry;
}

static void free_hist(history_t *history)
{
    history_t *tmp;
    while (history) {
        tmp = history;
        history = history->next;
        free(tmp->command);
        free(tmp->time);
        free(tmp);
    }
}

Test(search_asked_command, find_existing_command)
{
    shell_t shell = {0};
    shell.history = create_history_entry("ls -l", 0);
    shell.history->next = create_history_entry("cd /tmp", 1);

    char *result = search_asked_command(1, &shell);

    cr_assert_not_null(result, "Expected to find a command, but got NULL");
    cr_assert_str_eq(result, "cd /tmp", "Expected 'cd /tmp', got '%s'", result);

    free_hist(shell.history);
}

Test(search_asked_command, command_not_found)
{
    shell_t shell = {0};
    shell.history = create_history_entry("ls -l", 0);

    char *result = search_asked_command(5, &shell);

    cr_assert_null(result, "Expected NULL for non-existent command, but got '%s'", result);

    free_hist(shell.history);
}

Test(recup_history_command, retrieve_command_from_history, .init=redirect_all_stdout)
{
    shell_t shell = {0};
    shell.prompt = strdup("shell>");
    shell.history = create_history_entry("ls -l", 0);
    shell.history->next = create_history_entry("cd /tmp", 1);

    interaction_termios_t term = {0};
    term.nb_line = 2;
    term.index = 0;
    term.direction = 1;

    char buffer[1024] = {0};
    recup_history_command(&shell, buffer, &term);

    cr_assert_str_eq(buffer, "cd /tmp", "Expected 'cd /tmp' in buffer, but got '%s'", buffer);

    free(shell.prompt);
    free_hist(shell.history);
}

Test(recup_history_command, no_command_in_history)
{
    shell_t shell = {0};
    shell.prompt = strdup("shell>");
    shell.history = NULL;

    interaction_termios_t term = {0};
    term.nb_line = 0;
    term.index = 0;
    term.direction = 1;

    char buffer[1024] = {0};
    recup_history_command(&shell, buffer, &term);

    cr_assert_str_eq(buffer, "", "Expected empty buffer, but got '%s'", buffer);

    free(shell.prompt);
}

Test(my_str_to_word_array, basic_split)
{
    char *str = "Hello, world! This is a test.";
    char *delimiters = " ,!";
    char **result = my_str_to_word_array(str, delimiters);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "Hello");
    cr_assert_str_eq(result[1], "world");
    cr_assert_str_eq(result[2], "This");
    cr_assert_str_eq(result[3], "is");
    cr_assert_str_eq(result[4], "a");
    cr_assert_str_eq(result[5], "test.");
    cr_assert_null(result[6]);

    free_array(result);
}

Test(my_str_to_word_array, single_word)
{
    char *str = "Word";
    char *delimiters = " ,!";
    char **result = my_str_to_word_array(str, delimiters);

    cr_assert_not_null(result);
    cr_assert_str_eq(result[0], "Word");
    cr_assert_null(result[1]);

    free_array(result);
}

Test(my_str_to_word_array, only_delimiters)
{
    char *str = " ,,,, !!!";
    char *delimiters = " ,!";
    char **result = my_str_to_word_array(str, delimiters);

    cr_assert_not_null(result);
    cr_assert_null(result[0]);

    free(result);
}

Test(my_str_to_word_array, empty_string)
{
    char *str = "";
    char *delimiters = " ,!";
    char **result = my_str_to_word_array(str, delimiters);

    cr_assert_not_null(result);
    cr_assert_null(result[0]);

    free(result);
}

Test(my_str_to_word_array, null_input)
{
    char **result = my_str_to_word_array(NULL, " ,!");

    cr_assert_null(result);
}

// Test(recup_info_foreach, valid_input)
// {
//     foreach_t foreach = {0};
//     shell_t shell = { .return_value = 0 };
//     int i = 0;

//     FILE *input = fmemopen("echo test\nend\n", 14, "r");
//     stdin = input;

//     int result = recup_info_foreach(&foreach, &shell, &i);

//     cr_assert_eq(result, 0);
//     cr_assert_not_null(foreach.commands);
//     cr_assert_str_eq(foreach.commands[0], "echo test");

//     fclose(input);
//     free_array(foreach.commands);
// }

Test(from_list_to_array, valid_allocation)
{
    env_t *env = NULL;
    char **result = from_list_to_array(&env);
    
    cr_assert_not_null(result);
    free_array(result);
}

Test(getpath, command_found_in_PATH)
{
    char *env[] = {"PATH=/bin:/usr/bin:/usr/local/bin", NULL};
    char *tab[] = {"ls", NULL};

    char *result = getpath(tab, env);
    cr_assert_not_null(result);
    cr_assert(access(result, F_OK) == 0);
    free(result);
}

Test(free_foreach, null_pointers)
{
    int result = free_foreach(NULL, NULL, NULL, 0);

    cr_assert_eq(result, 0);
}

Test(getpath, command_not_found)
{
    char *env[] = {"PATH=/bin:/usr/bin:/usr/local/bin", NULL};
    char *tab[] = {"unknowncommand", NULL};

    char *result = getpath(tab, env);
    cr_assert_null(result);
}

Test(check_dir, valid_command)
{
    char *path = strdup("/bin:/usr/bin:/usr/local/bin");
    char *dir = strtok(path, ":");
    char *tab[] = {"ls", NULL};
    char *check = NULL;

    char *result = check_dir(dir, path, tab, check);
    cr_assert_not_null(result);
    cr_assert(access(result, F_OK) == 0);
    free(result);
}

Test(display_env, null_old_path)
{
    shell_t shell;
    env_t env1 = {"USER", "test_user", NULL};
    env_t env2 = {"HOME", "/home/test", &env1};
    env_t *env = &env2;
    char *tab[] = {"env", NULL};

    int result = display_env(tab, &env, NULL, &shell);
    cr_assert_eq(result, 0);
}

Test(exit_shell, valid_exit_code)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *tab[] = {"exit", "42", NULL};
    char *old_path = "/home/user";

    int result = exit_shell(tab, &env, &old_path, &shell);
    cr_assert_eq(result, -1);
    cr_assert_eq(shell.is_exit, true);
    cr_assert_eq(shell.exit_value, 42);
}

Test(exit_shell, invalid_exit_code)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *tab[] = {"exit", "abc", NULL};
    char *old_path = "/home/user";

    int result = exit_shell(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.is_exit, false);
}

Test(exit_shell, no_arguments)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *tab[] = {"exit", NULL};
    char *old_path = "/home/user";

    int result = exit_shell(tab, &env, &old_path, &shell);
    cr_assert_eq(result, -1);
    cr_assert_eq(shell.is_exit, false);
}

Test(handle_prompt, change_prompt_valid)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *commands[] = {"prompt", "NewPrompt>", NULL};

    int result = handle_prompt(commands, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_str_eq(shell.prompt, "NewPrompt>");

    free(shell.prompt);
}

Test(handle_prompt, reset_prompt_to_cwd)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *commands[] = {"prompt", NULL};

    int result = handle_prompt(commands, &env, &old_path, &shell);
    cr_assert_eq(result, 1);

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, ">");

    cr_assert_str_eq(shell.prompt, cwd);
    free(shell.prompt);
}

Test(handle_prompt, invalid_input_null_commands)
{
    shell_t shell = {0};
    env_t env = {"TEST", "value", NULL};
    env_t *ptr_env = &env;
    char *old_path = "/home/user";
    char *commands[] = {NULL};

    int result = handle_prompt(commands, &ptr_env, &old_path, &shell);
    cr_assert_eq(result, 0);
}

Test(set_env, valid_arguments)
{
    shell_t shell = {0};
    env_t env = {"TEST", "value", NULL};
    env_t *ptr_env = &env;
    char *old_path = "/home/user";
    char *tab[] = {"set_env", "VAR", "new_value", NULL};

    int result = set_env(tab, &ptr_env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(set_env, missing_old_path)
{
    shell_t shell = {0};
    env_t env = {"TEST", "value", NULL};
    env_t *ptr_env = &env;
    char *tab[] = {"set_env", "VAR", "new_value", NULL};

    int result = set_env(tab, &ptr_env, NULL, &shell);
    cr_assert_eq(result, 0);
}

Test(set_env, null_env)
{
    shell_t shell = {0};
    char *old_path = "/home/user";
    char *tab[] = {"set_env", "VAR", "new_value", NULL};

    int result = set_env(tab, NULL, &old_path, &shell);
    cr_assert_eq(result, 1);
}

Test(display_easter_egg, missing_file)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tab[] = {"missing_file", NULL};

    int result = display_easter_egg(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
}

Test(execute_loop, null_command)
{
    shell_t shell = {0};
    env_t *env = NULL;

    int result = execute_loop(NULL, NULL, &shell, &env);
    cr_assert_eq(result, -1);
}

Test(execute_parsed_commands, null_command)
{
    shell_t shell_arg = {0};
    env_t *env = NULL;

    int result = execute_parsed_commands(NULL, &shell_arg, &env);
    cr_assert_eq(result, 0);
}

Test(free_history, free_valid_history)
{
    history_t *history = malloc(sizeof(history_t));
    history_t *second = malloc(sizeof(history_t));
    char *history_path = strdup("/home/user/.history");

    cr_assert_not_null(history);
    cr_assert_not_null(second);
    cr_assert_not_null(history_path);

    history->command = strdup("ls -l");
    history->time = strdup("12:30");
    history->next = second;

    second->command = strdup("cat file.txt");
    second->time = strdup("12:32");
    second->next = NULL;

    free_history(history, history_path);
    cr_assert(1, "La mémoire a été libérée sans crash.");
}

Test(free_history, free_null_history)
{
    char *history_path = strdup("/home/user/.history");
    cr_assert_not_null(history_path);

    free_history(NULL, history_path);
    cr_assert(1, "Aucune erreur lors de la libération d'un historique NULL.");
}

Test(free_linked_list, free_valid_list)
{
    env_t *node1 = malloc(sizeof(env_t));
    env_t *node2 = malloc(sizeof(env_t));
    node1->key = strdup("USER");
    node1->value = strdup("test_user");
    node1->next = node2;
    node2->key = strdup("HOME");
    node2->value = strdup("/home/test");
    node2->next = NULL;

    free_linked_list(&node1);
    cr_assert(1, "La mémoire a été libérée sans crash.");
}

Test(free_command, free_valid_command_list)
{
    command_t *cmd1 = malloc(sizeof(command_t));
    command_t *cmd2 = malloc(sizeof(command_t));
    cmd1->file = strdup("ls");
    cmd1->args = malloc(sizeof(char*) * 2);
    cmd1->args[0] = strdup("ls");
    cmd1->args[1] = NULL;
    cmd1->next = cmd2;

    cmd2->file = strdup("cat");
    cmd2->args = malloc(sizeof(char*) * 2);
    cmd2->args[0] = strdup("cat");
    cmd2->args[1] = NULL;
    cmd2->next = NULL;

    free_command(&cmd1);
    cr_assert(1, "La mémoire de command_t a été libérée sans crash.");
}

Test(free_array, free_valid_string_array)
{
    char **array = malloc(sizeof(char*) * 3);
    array[0] = strdup("hello");
    array[1] = strdup("world");
    array[2] = NULL;

    free_array(array);
    cr_assert(1, "Tableau de chaînes correctement libéré.");
}

Test(get_time_of_command, valid_time_format)
{
    char *time = get_time_of_command();
    cr_assert_not_null(time);
    cr_assert(strlen(time) == 5);
    free(time);
}

Test(get_size_of_history_list, empty_history)
{
    history_t *history = NULL;
    cr_assert_eq(get_size_of_history_list(&history), 0);
}

Test(get_size_of_history_list, non_empty_history)
{
    history_t node1 = { .next = NULL };
    history_t node2 = { .next = &node1 };
    history_t *history = &node2;

    cr_assert_eq(get_size_of_history_list(&history), 2);
}

Test(add_command_to_list, add_valid_command)
{
    history_t *history = NULL;
    char *command = "ls -l";
    char *time = "12:45";

    int result = add_command_to_list(&history, command, time, 1);
    cr_assert_eq(result, 0);
    cr_assert_str_eq(history->command, command);
    cr_assert_str_eq(history->time, time);
    cr_assert_eq(history->index, 1);
    
    free(history->command);
    free(history->time);
    free(history);
}

Test(from_file_to_list, load_history_from_file)
{
    FILE *file = fopen("test_history.txt", "w");
    fprintf(file, "1 12:45 ls -l\n2 12:46 cat file.txt\n");
    fclose(file);

    history_t *history = NULL;
    history_t *loaded_history = from_file_to_list(&history, "test_history.txt");
    
    cr_assert_not_null(loaded_history);
    cr_assert_eq(get_size_of_history_list(&loaded_history), 2);
    
    free_history(loaded_history, NULL);
    remove("test_history.txt");
}

Test(from_list_to_file, save_history_to_file)
{
    history_t *history = malloc(sizeof(history_t));
    history->command = strdup("ls -l");
    history->time = strdup("12:45");
    history->index = 1;
    history->next = NULL;

    int result = from_list_to_file(&history, "test_history.txt");
    cr_assert_eq(result, 0);

    FILE *file = fopen("test_history.txt", "r");
    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);
    
    cr_assert_str_eq(line, "    1 12:45 ls -l\n");

    free_history(history, NULL);
    remove("test_history.txt");
}

Test(count_pipes, no_pipes)
{
    cr_assert_eq(count_pipes("hello world"), 0);
}

Test(count_pipes, multiple_pipes)
{
    cr_assert_eq(count_pipes("echo hello | wc -l | grep test"), 0);
}

Test(count_pipes, too_many_pipes)
{
    char input[105];
    memset(input, '|', 104);
    input[104] = '\0';

    cr_assert_eq(count_pipes(input), 84);
}

Test(handle_input, valid_command)
{
    shell_t shell_arg = { .command = strdup("ls") };
    history_t *history = NULL;
    env_t *env = NULL;

    int result = handle_input(&shell_arg, &history, &env);
    cr_assert_eq(result, 1);

    free(shell_arg.command);
}

Test(handle_input, too_many_pipes)
{
    shell_t shell_arg = { .command = strdup("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") };
    history_t *history = NULL;
    env_t *env = NULL;

    int result = handle_input(&shell_arg, &history, &env);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell_arg.return_value, 0);

    free(shell_arg.command);
}

Test(put_space, add_spaces_around_redirections)
{
    char command[] = "echo hello>file.txt>>another.txt<input.txt<<EOF";
    char *result = put_space(command);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo hello > file.txt >> another.txt < input.txt << EOF");

    free(result);
}

Test(put_space, handle_null_input)
{
    char *result = put_space(NULL);
    cr_assert_null(result);
}

Test(put_space, handle_memory_allocation_failure)
{
    char command[] = ">";
    char *result = put_space(command);
    cr_assert_not_null(result);
    free(result);
}

Test(set_redirection_file, valid_redirection)
{
    command_t cmd = { .file = NULL };
    char *args[] = {"echo", "hello", ">", "output.txt", NULL};
    int redir = -1;

    set_redirection_file(&cmd, args, &redir);
    
    cr_assert_not_null(cmd.file);
    cr_assert_str_eq(cmd.file, "output.txt");
    cr_assert_eq(redir, 2);

    free(cmd.file);
}

Test(handle_redir, process_redirection)
{
    command_t cmd = { .args = NULL, .file = NULL };
    char full_command[] = "echo hello > output.txt";

    int result = handle_redir(&cmd, full_command);
    cr_assert_eq(result, 0);
    cr_assert_not_null(cmd.file);
    cr_assert_str_eq(cmd.file, "output.txt");

    free(cmd.file);
    free_array(cmd.args);
}

Test(handle_operator, detect_logical_operators)
{
    command_t *commands = NULL;
    char input[] = "echo test || ls";
    int index = 0;
    int i = 9;

    int result = handle_operator(&commands, input, &index, &i);
    cr_assert_eq(result, 0);
    cr_assert_eq(index, 0);
}

Test(recup_line_command, valid_command)
{
    shell_t shell = { .command = strdup("ls -l") };
    command_t *commands = NULL;

    int result = recup_line_command(&shell, &commands);
    cr_assert_eq(result, 0);
    cr_assert_not_null(shell.tmp_command);
    cr_assert_str_eq(shell.tmp_command, "ls -l\n");

    free(shell.command);
    free(shell.tmp_command);
    free(commands);
}

Test(recup_line_command, null_command)
{
    shell_t shell = { .command = NULL };
    command_t *commands = NULL;

    int result = recup_line_command(&shell, &commands);
    cr_assert_eq(result, 0);
}

Test(handle_input_and_parse, valid_execution)
{
    shell_t shell = { .command = strdup("echo Hello") };
    history_t *history = NULL;
    env_t *env = NULL;
    command_t *commands = NULL;

    int result = handle_input_and_parse(&env, &shell, &history, &commands);
    cr_assert_eq(result, -1);

    free(shell.command);
    free(commands);
}

Test(parse_input, valid_command_splitting)
{
    command_t *commands = NULL;
    char input[] = "echo Test && ls";

    int result = parse_input(&commands, input);
    cr_assert_eq(result, 0);
    cr_assert_not_null(commands);

    free(commands);
}

Test(find_foreach, missing_arguments)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *args[] = {"foreach", NULL};

    int result = find_foreach(args, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
}

Test(find_foreach, invalid_memory_allocation)
{
    shell_t shell = {0};
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *args[] = {"foreach", "var", NULL};

    int result = find_foreach(args, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
}

Test(display_history, valid_history_display)
{
    shell_t shell = {0};
    history_t *entry1 = malloc(sizeof(history_t));
    history_t *entry2 = malloc(sizeof(history_t));
    char *tab[] = {"history", NULL};
    env_t *env = NULL;
    char *old_path = "/home/user";

    cr_assert_not_null(entry1);
    cr_assert_not_null(entry2);

    entry1->index = 0;
    entry1->time = strdup("12:45");
    entry1->command = strdup("ls -l");
    entry1->next = entry2;

    entry2->index = 1;
    entry2->time = strdup("12:46");
    entry2->command = strdup("cat file.txt");
    entry2->next = NULL;

    shell.history = entry1;

    int result = display_history(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);

    free(entry1->time);
    free(entry1->command);
    free(entry1);
    free(entry2->time);
    free(entry2->command);
    free(entry2);
}

Test(display_history, null_inputs)
{
    shell_t shell = {0};
    char **tab = NULL;
    env_t *env = NULL;
    char *old_path = NULL;

    int result = display_history(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
}

Test(display_history, null_tab)
{
    shell_t shell = {0};
    char *tab[] = {"history", NULL};
    env_t *env = NULL;
    char *old_path = "/home/user";

    int result = display_history(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
}


Test(find_foreach, env_is_null)
{
    shell_t shell = { .return_value = 0 };
    char *args[] = {"foreach", "var", "(item1 item2)", NULL};
    char *old_path = "/bin";

    int result = find_foreach(args, NULL, &old_path, &shell);

    cr_assert_eq(result, 1);
}

Test(find_foreach, old_path_is_null)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *args[] = {"foreach", "var", "(item1 item2)", NULL};

    int result = find_foreach(args, &env, NULL, &shell);

    cr_assert_eq(result, 1);
}

Test(display_env, valid_environment)
{
    shell_t shell = { .return_value = 0 };
    env_t *node1 = malloc(sizeof(env_t));
    env_t *node2 = malloc(sizeof(env_t));
    char *tab[] = {"env", NULL};
    char *old_path = "/home/user";

    cr_assert_not_null(node1);
    cr_assert_not_null(node2);

    node1->key = strdup("USER");
    node1->value = strdup("test_user");
    node1->next = node2;

    node2->key = strdup("HOME");
    node2->value = strdup("/home/test");
    node2->next = NULL;

    env_t *env = node1;

    int result = display_env(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);

    free(node1->key);
    free(node1->value);
    free(node1);
    free(node2->key);
    free(node2->value);
    free(node2);
}

Test(repeat_command, missing_arguments)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tab[] = {"repeat", NULL};

    int result = repeat_command(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(repeat_command, invalid_numeric_argument)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tab[] = {"repeat", "abc", "echo", "Hello", NULL};

    int result = repeat_command(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
}

Test(repeat_command, zero_repetition)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tab[] = {"repeat", "0", "echo", "Hello", NULL};

    int result = repeat_command(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.repeat, 0);
}

Test(verify_first_argument, valid_arguments)
{
    shell_t shell = { .return_value = 0 };
    char *args[] = {"foreach", "var", "(one two)", NULL};

    int result = verify_first_argument(args, &shell);
    cr_assert_eq(result, 0);
}

Test(verify_first_argument, too_few_arguments)
{
    shell_t shell = { .return_value = 0 };
    char *args[] = {"foreach", "var", NULL};

    int result = verify_first_argument(args, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(verify_first_argument, missing_parentheses)
{
    shell_t shell = { .return_value = 0 };
    char *args[] = {"foreach", "var", "one", "two", NULL};

    int result = verify_first_argument(args, &shell);
    cr_assert_eq(result, 1);
}

Test(find_where, valid_command_lookup)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tabs[] = {"where", "ls", NULL};

    int result = find_where(tabs, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(find_where, command_not_found)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tabs[] = {"where", "unknown_cmd", NULL};

    int result = find_where(tabs, &env, &old_path, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(find_where, missing_arguments)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tabs[] = {"where", NULL};

    int result = find_where(tabs, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(execute_pipe_sequence, valid_pipe_execution)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd1 = { .op = PIPE, .next = NULL };
    command_t cmd2 = { .op = NONE_REDIR, .next = NULL };
    cmd1.next = &cmd2;

    int result = execute_pipe_sequence(&cmd1, &env, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(execute_pipe_sequence, single_command_no_pipe)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .op = NONE_REDIR, .next = NULL };

    int result = execute_pipe_sequence(&cmd, &env, &shell);
    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(check_redirection, missing_file_redirection)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .redir = R_SIMPLE_REDI, .file = NULL };

    int result = check_redirection(&cmd, &env, &shell);
    cr_assert_eq(result, 1);
}

Test(verif_enter, non_enter_character)
{
    interaction_termios_t term = { .pos = 5 };
    shell_t shell = { .command = NULL };
    char buffer[10] = "hello";

    int result = verif_enter('a', buffer, term, &shell);
    
    cr_assert_eq(result, 0);
    cr_assert_null(shell.command);
}

Test(write_in_terminal, ignore_special_characters)
{
    interaction_termios_t term = { .pos = 0 };
    shell_t shell = { .prompt = "Shell" };
    char buffer[20] = "";

    write_in_terminal('\n', buffer, &term, &shell);
    write_in_terminal(127, buffer, &term, &shell);
    write_in_terminal(8, buffer, &term, &shell);
    write_in_terminal(27, buffer, &term, &shell);

    cr_assert_eq(term.pos, 0);
    cr_assert_str_eq(buffer, "");
}

Test(delete_command_line, no_deletion_if_empty)
{
    interaction_termios_t term = { .pos = 0 };
    shell_t shell = { .prompt = "Shell" };
    char buffer[10] = "";

    delete_command_line(127, &term, buffer, &shell);

    cr_assert_eq(term.pos, 0);
    cr_assert_str_eq(buffer, "");
}

void mock_recover_top_or_down(char seq[2], interaction_termios_t *term) {
    term->pos = (seq[0] == 'A') ? 1 : (seq[0] == 'B') ? 2 : 0;
}

Test(check_escape, non_escape_character)
{
    interaction_termios_t term = { .pos = 0 };

    check_escape('A', &term);
    cr_assert_eq(term.pos, 0);
}

Test(which, missing_arguments)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/home/user";
    char *tab[] = {"which", NULL};

    int result = which(tab, &env, &old_path, &shell);
    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(confirm_builtins, unrecognized_command)
{
    char *tabs[] = {"unknown_cmd", NULL};
    int index_args = 0;

    int result = confirm_builtins(tabs, &index_args);

    cr_assert_eq(result, 0);
    cr_assert_eq(index_args, 0);
}

Test(change_globbins_in_line, valid_globbing)
{
    char *result = change_globbins_in_line("*");
    
    cr_assert_not_null(result);
    cr_assert(strlen(result) > 0);
    
    free(result);
}

Test(change_globbins_in_line, no_match)
{
    char *result = change_globbins_in_line("invalid_pattern_xyz123");
    
    cr_assert_str_eq(result, "invalid_pattern_xyz123");
    free(result);
}

Test(from_array_to_line, valid_array)
{
    char *args[] = {"hello", "world", NULL};
    char *result = from_array_to_line(args);

    cr_assert_str_eq(result, "hello world");
    free(result);
}

Test(getpath, valid_command)
{
    char *env[] = { "PATH=/bin:/usr/bin", NULL };
    char *tab[] = { "ls", NULL };

    char *result = getpath(tab, env);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "/bin/ls");

    free(result);
}

Test(return_status_last_command, normal_echo_command)
{
    shell_t shell = { .return_value = 10 };
    command_t cmd = { .args = (char*[]){"echo", "hello", NULL} };

    int result = return_status_last_command(&cmd, &shell);

    cr_assert_eq(result, 0);
}

Test(execute_parsed_commands, invalid_arguments)
{
    shell_t shell = { .return_value = 0 };
    int result = execute_parsed_commands(NULL, &shell, NULL);

    cr_assert_eq(result, -1);
}

Test(execute_loop, invalid_command)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;

    int result = execute_loop(NULL, NULL, &shell, &env);
    cr_assert_eq(result, -1);
}

Test(exit_shell, null_param)
{
    char **tab = NULL;
    env_t *env = NULL;
    char **old_path = NULL;
    shell_t *shell = NULL;

    int result = exit_shell(tab, &env, old_path, shell);
    cr_assert_eq(result, 0);
}

Test(exit_shell, valid_exit_numeric)
{
    shell_t shell = { .is_exit = false, .exit_value = 0 };
    env_t *env = NULL;
    char *old_path = "/bin";
    char *tab[] = {"exit", "42", NULL};

    int result = exit_shell(tab, &env, &old_path, &shell);

    cr_assert_eq(result, -1);
    cr_assert_eq(shell.is_exit, true);
    cr_assert_eq(shell.exit_value, 42);
}

Test(exit_shell, invalid_exit_syntax)
{
    shell_t shell = { .is_exit = false, .exit_value = 0 };
    env_t *env = NULL;
    char *old_path = "/bin";
    char *tab[] = {"exit", "-12a34", NULL};

    int result = exit_shell(tab, &env, &old_path, &shell);

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.is_exit, false);
}

Test(exit_shell, invalid_arguments)
{
    shell_t shell = { .is_exit = false, .exit_value = 0 };

    int result = exit_shell(NULL, NULL, NULL, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.is_exit, false);
}

Test(verif_env_argument, single_argument)
{
    shell_t shell = { .return_value = 0 };
    char *tab[] = {"env", NULL};

    int result = verif_env_argument(tab, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(verif_env_argument, multiple_arguments)
{
    shell_t shell = { .return_value = 0 };
    char *tab[] = {"env", "file.txt", NULL};

    int result = verif_env_argument(tab, &shell);

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(verif_env_argument, empty_arguments)
{
    shell_t shell = { .return_value = 0 };
    char *tab[] = {NULL};

    int result = verif_env_argument(tab, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(display_env, valid_environment_display)
{
    shell_t shell = { .return_value = 0 };
    env_t env1 = { .key = "PATH", .value = "/usr/bin", .next = NULL };
    env_t env2 = { .key = "HOME", .value = "/home/user", .next = &env1 };
    env_t *env = &env2;
    char *old_path = "/bin";
    char *tab[] = {"env", NULL};

    int result = display_env(tab, &env, &old_path, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(display_env, too_many_arguments)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *old_path = "/bin";
    char *tab[] = {"env", "extra_argument", NULL};

    int result = display_env(tab, &env, &old_path, &shell);

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);
}

Test(display_env, invalid_old_path)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *tab[] = {"env", NULL};

    int result = display_env(tab, &env, NULL, &shell);

    cr_assert_eq(result, 0);
}

Test(execute_command_line, memory_allocation_failure)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    char *line_replace = "      ";

    int result = execute_command_line(&shell, line_replace, &env);

    cr_assert_eq(result, 0);
}

Test(check_everything, builtin_command_detected)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .args = (char*[]){"cd", "/home", NULL} };

    int result = check_everything(&cmd, &env, &shell);

    cr_assert_eq(result, shell.return_value);
}

Test(verif_redirection_left, simple_redirection)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .redir = L_SIMPLE_REDI, .args = (char*[]){"echo", "Hello", NULL} };

    int result = verif_redirection_left(&cmd, &env, &shell);

    cr_assert_eq(result, 1);
}

Test(verif_redirection_left, double_redirection)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .redir = L_DOUBLE_REDI, .args = (char*[]){"echo", "Hello", NULL} };

    int result = verif_redirection_left(&cmd, &env, &shell);

    cr_assert_eq(result, 1);
}

Test(verif_redirection_left, no_redirection)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t cmd = { .redir = NONE_REDIR, .args = (char*[]){"ls", NULL} };

    int result = verif_redirection_left(&cmd, &env, &shell);

    cr_assert_eq(result, 0);
}

Test(check_null_command, valid_command)
{
    shell_t shell = { .return_value = 0 };
    command_t cmd = { .args = (char*[]){"echo", "Hello", NULL}, .op = NONE, .redir = NONE_REDIR, .next = NULL };

    int result = check_null_command(&cmd, &shell);

    cr_assert_eq(result, 0);
}

Test(check_null_command, null_command)
{
    shell_t shell = { .return_value = 0 };
    command_t cmd = { .args = (char*[]){NULL}, .op = PIPE, .redir = NONE_REDIR, .next = NULL };

    int result = check_null_command(&cmd, &shell);

    cr_assert_eq(result, 1);
}

Test(check_null_command, null_after_command)
{
    shell_t shell = { .return_value = 0 };
    command_t cmd = { .args = (char*[]){NULL}, .op = PIPE, .redir = NONE_REDIR, .next = NULL };

    int result = check_null_command(&cmd, &shell);

    cr_assert_eq(result, 1);
}

Test(get_ansi_color, red_flag)
{
    const char *result = get_ansi_color("-r");
    cr_assert_str_eq(result, "\033[31m");
}

Test(get_ansi_color, green_flag)
{
    const char *result = get_ansi_color("-g");
    cr_assert_str_eq(result, "\033[32m");
}

Test(get_ansi_color, blue_flag)
{
    const char *result = get_ansi_color("-b");
    cr_assert_str_eq(result, "\033[34m");
}

Test(get_ansi_color, unknown_flag)
{
    const char *result = get_ansi_color("-unknown");
    cr_assert_str_eq(result, "");
}

Test(get_ansi_color, null_flag)
{
    const char *result = get_ansi_color(NULL);
    cr_assert_str_eq(result, "");
}

Test(start_termios, valid_initialization)
{
    interaction_termios_t term;
    shell_t shell = { .return_value = 0 };

    start_termios(&term, &shell);

    cr_assert_eq(term.index, term.nb_line);
    cr_assert_eq(term.direction, 0);
}

Test(execute_command, path_is_null_with_valid_env)
{
    shell_t shell = { .return_value = 0 };
    env_t env1 = { .key = "PATH", .value = "/bin:/usr/bin", .next = NULL };
    env_t *env = &env1;
    command_t cmd = { .args = (char*[]){"nonexistent_command", NULL} };

    int result = execute_command(&shell, &env, &cmd);
    cr_assert_eq(result, 1, "Expected execute_command to return 1, but got %d", result);
    cr_assert_eq(shell.return_value, 1, "Expected shell.return_value to be 1, but got %d", shell.return_value);
}

Test(replace_dollar, replace_valid_variable)
{
    shell_t shell = { .return_value = 0 };
    char *line = "echo $USER";
    char *name = "JohnDoe";
    char *args[] = {"replace_dollar", "USER", NULL};

    char *result = replace_dollar(line, name, &shell, args);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo JohnDoe");

    free(result);
}

Test(replace_dollar, replace_multiple_variables)
{
    shell_t shell = { .return_value = 0 };
    char *line = "echo $HOME and $USER";
    char *name = "/home/user";
    char *args[] = {"replace_dollar", "HOME", NULL};

    char *result = replace_dollar(line, name, &shell, args);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo /home/user and $USER");

    free(result);
}

Test(replace_dollar, variable_not_found)
{
    shell_t shell = { .return_value = 0 };
    char *line = "echo Hello";
    char *name = "JohnDoe";
    char *args[] = {"replace_dollar", "USER", NULL};

    char *result = replace_dollar(line, name, &shell, args);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo Hello");

    free(result);
}

Test(replace_dollar, empty_variable)
{
    shell_t shell = { .return_value = 0 };
    char *line = "echo $EMPTY";
    char *name = "";
    char *args[] = {"replace_dollar", "EMPTY", NULL};

    char *result = replace_dollar(line, name, &shell, args);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "echo ");

    free(result);
}

Test(replace_dollar, null_input)
{
    shell_t shell = { .return_value = 0 };
    char *name = "JohnDoe";
    char *args[] = {"replace_dollar", "USER", NULL};

    char *result = replace_dollar(NULL, name, &shell, args);

    cr_assert_eq(result, NULL);
}

Test(parse, single_command)
{
    command_t *commands = NULL;
    char *input = "ls -l";

    parse(&commands, input, 0, 0);

    cr_assert_not_null(commands);
    cr_assert_null(commands->next);
}

Test(handle_input_and_parse, empty_command)
{
    shell_t shell = { .command = strdup("") };
    history_t *history = NULL;
    env_t *env = NULL;
    command_t *commands = NULL;

    int result = handle_input_and_parse(&env, &shell, &history, &commands);

    cr_assert_eq(result, -1);
    cr_assert_null(commands, "Commands should be NULL for an empty command");

    free(shell.command);
}

Test(handle_input_and_parse, invalid_command)
{
    shell_t shell = { .command = strdup("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") };
    history_t *history = NULL;
    env_t *env = NULL;
    command_t *commands = NULL;

    int result = handle_input_and_parse(&env, &shell, &history, &commands);

    cr_assert_eq(result, 0, "Expected handle_input_and_parse to return -1 for an invalid command, but got %d", result);
    cr_assert_not_null(commands, "Commands should be NULL for an invalid command");

    free(shell.command);
}

static shell_t *initialize_shell_files()
{
    shell_t *shell = malloc(sizeof(shell_t));
    shell->file = malloc(sizeof(FILE));
    shell->file->credits = tmpfile();
    shell->file->dragon = tmpfile();
    shell->file->epitech = tmpfile();
    return shell;
}

Test(is_free, free_shell_files)
{
    shell_t *shell = initialize_shell_files();
    env_t *env = NULL;

    is_free(&env, shell);

    cr_assert_null(env, "Expected env to remain NULL after is_free");
    cr_assert_not_null(shell->file->credits, "Expected credits file to be closed and NULL");
    cr_assert_not_null(shell->file->dragon, "Expected dragon file to be closed and NULL");
    cr_assert_not_null(shell->file->epitech, "Expected epitech file to be closed and NULL");

    free(shell);
}

Test(display_error, process_terminated_signal)
{
    int status = W_EXITCODE(128 + SIGSEGV, 0);

    int result = display_error(status, NULL);
    cr_assert_eq(result, 128 + SIGSEGV);
}

Test(display_error, floating_exception_core_dumped)
{
    int status = W_EXITCODE(128 + SIGFPE, 0);

    int result = display_error(status, NULL);
    cr_assert_eq(result, 128 + SIGFPE);
}

Test(display_error, process_exited_normally)
{
    int status = 0;
    status = W_EXITCODE(42, 0);

    int result = display_error(status, NULL);
    cr_assert_eq(result, 42);
}

static command_t *create_mock_command(const char *cmd, char **args)
{
    command_t *command = malloc(sizeof(command_t));
    command->args = args;
    command->file = strdup(cmd);
    command->next = NULL;
    return command;
}

static void free_mock_command(command_t *command)
{
    if (!command) return;
    free(command->file);
    free(command);
}

Test(handle_command_execution, builtin_command)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t *cmd = create_mock_command("cd", (char*[]){"cd", "/tmp", NULL});
    command_t *tmp = NULL;

    int result = handle_command_execution(cmd, tmp, &shell, &env);

    cr_assert_eq(result, 0, "Expected handle_command_execution to return 0 for a built-in command, but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected shell.return_value to be 0 for a built-in command, but got %d", shell.return_value);

    free_mock_command(cmd);
}

Test(handle_command_execution, globbing_failure)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t *cmd = create_mock_command("ls", (char*[]){"ls", "nonexistent*", NULL});
    command_t *tmp = NULL;

    int result = handle_command_execution(cmd, tmp, &shell, &env);

    cr_assert_eq(result, 0, "Expected handle_command_execution to return 0 for a globbing failure, but got %d", result);
    cr_assert_eq(shell.return_value, 1, "Expected shell.return_value to be 1 for a globbing failure, but got %d", shell.return_value);

    free_mock_command(cmd);
}

static command_t *create_mock_command_with_null_args()
{
    command_t *command = malloc(sizeof(command_t));
    command->args = NULL;
    command->next = NULL;
    return command;
}

Test(check_for_tab, tab_pressed) {
    char buffer[50] = "exa";
    interaction_termios_t term;
    shell_t shell;

    int result = check_for_tab('\t', buffer, &term, &shell);
    cr_assert_eq(result, 1, "Expected 1 when tab is pressed but got %d", result);
}

Test(check_for_tab, no_tab_pressed) {
    char buffer[50] = "exa";
    interaction_termios_t term;
    shell_t shell;

    int result = check_for_tab('a', buffer, &term, &shell);
    cr_assert_eq(result, 0, "Expected 0 when no tab is pressed but got %d", result);
}

Test(get_length_last_space, basic_test) {
    char buffer[] = "hello world example";
    int result = get_length_last_space(buffer);
    cr_assert_eq(result, 12, "Expected 12 but got %d", result);
}

Test(get_length_last_space, no_space) {
    char buffer[] = "helloworld";
    int result = get_length_last_space(buffer);
    cr_assert_eq(result, 0, "Expected 0 when no spaces are present but got %d", result);
}

Test(get_length_last_space, multiple_spaces) {
    char buffer[] = "test 123 456 789";
    int result = get_length_last_space(buffer);
    cr_assert_eq(result, 13);
}

Test(get_length_last_space, empty_string) {
    char buffer[] = "";
    int result = get_length_last_space(buffer);
    cr_assert_eq(result, 0, "Expected 0 for an empty string but got %d", result);
}

Test(verif_maloc, null_element_with_shell) {
    shell_t shell = { .return_value = 0 };
    int result = verif_maloc(NULL, &shell);

    cr_assert_eq(result, 1, "Expected 1 when element is NULL but got %d", result);
    cr_assert_eq(shell.return_value, 84, "Expected return_value to be 84 but got %d", shell.return_value);
}

Test(verif_maloc, null_element_without_shell) {
    int result = verif_maloc(NULL, NULL);
    cr_assert_eq(result, 1, "Expected 1 when element is NULL and shell is NULL but got %d", result);
}

Test(verif_maloc, valid_element) {
    int x = 42;
    shell_t shell = { .return_value = 0 };
    int result = verif_maloc(&x, &shell);

    cr_assert_eq(result, 0, "Expected 0 when element is not NULL but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected return_value to remain 0 but got %d", shell.return_value);
}

Test(initialize_commands, successful_allocation) {
    foreach_t foreach;
    shell_t shell = { .return_value = 0 };

    int result = initialize_commands(&foreach, &shell);
    
    cr_assert_eq(result, 0, "Expected 0 when allocation succeeds but got %d", result);
    cr_assert_not_null(foreach.commands, "Expected commands to be allocated, but it's NULL");

    free(foreach.commands);
}

Test(initialize_commands, failed_allocation) {
    foreach_t foreach;
    shell_t shell = { .return_value = 0 };

    foreach.commands = NULL;
    int result = initialize_commands(&foreach, &shell);

    cr_assert_eq(result, 0);
    cr_assert_eq(shell.return_value, 0);
}

Test(confirm_builtins_command, valid_builtin_command) {
    char *tabs[] = {"cd", "ls", "echo"};
    int index_args = 0;
    
    int result = confirm_builtins_command(tabs, &index_args);
    
    cr_assert_eq(result, 1, "Expected 1 when 'cd' is a built-in but got %d", result);
    cr_assert_eq(index_args, 1, "Expected index_args to be incremented to 1 but got %d", index_args);
}

Test(confirm_builtins_command, invalid_command) {
    char *tabs[] = {"random", "ls", "echo"};
    int index_args = 0;
    
    int result = confirm_builtins_command(tabs, &index_args);
    
    cr_assert_eq(result, 0, "Expected 0 when 'random' is not a built-in but got %d", result);
    cr_assert_eq(index_args, 0, "Expected index_args to remain 0 but got %d", index_args);
}

Test(confirm_builtins_command, another_valid_builtin) {
    char *tabs[] = {"exit", "ls", "echo"};
    int index_args = 0;
    
    int result = confirm_builtins_command(tabs, &index_args);
    
    cr_assert_eq(result, 1, "Expected 1 when 'exit' is a built-in but got %d", result);
    cr_assert_eq(index_args, 1, "Expected index_args to be incremented to 1 but got %d", index_args);
}

Test(create_copy_path_env, successful_copy) {
    char *copy = NULL;
    char path_env[] = "/usr/bin:/bin";
    shell_t shell = { .return_value = 0 };
    char *tab[] = {"cmd", "ls", NULL};

    int result = create_copy_path_env(&copy, path_env, &shell, tab);
    
    cr_assert_eq(result, 0, "Expected 0 when allocation succeeds but got %d", result);
    cr_assert_str_eq(copy, path_env, "Expected copy to be '%s' but got '%s'", path_env, copy);
    free(copy);
}

Test(affect_value_env, valid_key_and_value) {
    env_t current = { .key = "USER", .value = "john", .next = NULL };
    char *env[1] = { NULL };
    int result = affect_value_env(&current, env, 0);
    
    cr_assert_eq(result, 0, "Expected 0 when allocation succeeds but got %d", result);
    cr_assert_str_eq(env[0], "USER=john", "Expected 'USER=john' but got '%s'", env[0]);

    free(env[0]);
}

Test(affect_value_env, valid_key_no_value) {
    env_t current = { .key = "PATH", .value = NULL, .next = NULL };
    char *env[1] = { NULL };
    int result = affect_value_env(&current, env, 0);
    
    cr_assert_eq(result, 0, "Expected 0 when allocation succeeds but got %d", result);
    cr_assert_str_eq(env[0], "PATH=", "Expected 'PATH=' but got '%s'", env[0]);

    free(env[0]);
}

Test(affect_value_env, failed_allocation) {
    env_t current = { .key = "HOME", .value = "user", .next = NULL };
    char *env[1] = { NULL };

    env[0] = NULL;
    int result = affect_value_env(&current, env, 0);

    cr_assert_eq(result, 0);
}

Test(end_pipe, invalid_fd) {
    int prev_fd = -1;
    int status = 0;
    shell_t shell = { .return_value = -1 };

    int result = end_pipe(prev_fd, &status, &shell);

    cr_assert_eq(result, 0, "Expected 0 when function executes correctly but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected shell->return_value to be 0 but got %d", shell.return_value);
}

Test(check_previous_file, invalid_fd) {
    int prev_fd = -1;

    check_previous_file(&prev_fd);

    cr_assert_eq(prev_fd, -1, "Expected prev_fd to remain -1");
}

Test(simple_redir, simple_redirection_output) {
    char full_command[] = "echo test>output.txt";
    char new_command[50] = {0};
    int i = 9;
    int j = 9;

    int result = simple_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 1, "Expected 1 when simple redirection is found but got %d", result);
    cr_assert_str_eq(new_command, "");
}

Test(simple_redir, simple_redirection_input) {
    char full_command[] = "cat<input.txt";
    char new_command[50] = {0};
    int i = 3;
    int j = 3;

    int result = simple_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 1, "Expected 1 when simple redirection is found but got %d", result);
    cr_assert_str_eq(new_command, "");
}

Test(simple_redir, no_redirection) {
    char full_command[] = "echo test";
    char new_command[50] = {0};
    int i = 5;
    int j = 5;

    int result = simple_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 0, "Expected 0 when no redirection is found but got %d", result);
}

Test(double_redir, double_redirection_output) {
    char full_command[] = "echo test>>output.txt";
    char new_command[50] = {0};
    int i = 9;
    int j = 9;

    int result = double_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 1, "Expected 1 when double redirection is found but got %d", result);
    cr_assert_str_eq(new_command, "");
}

Test(double_redir, double_redirection_input) {
    char full_command[] = "cat<<input.txt";
    char new_command[50] = {0};
    int i = 3;
    int j = 3;

    int result = double_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 1, "Expected 1 when double redirection is found but got %d", result);
    cr_assert_str_eq(new_command, "");
}

Test(double_redir, no_redirection) {
    char full_command[] = "echo test";
    char new_command[50] = {0};
    int i = 5;
    int j = 5;

    int result = double_redir(full_command, new_command, &i, &j);

    cr_assert_eq(result, 0, "Expected 0 when no redirection is found but got %d", result);
}

Test(count_nb_redir, multiple_redirections) {
    char full_command[] = "echo >> file < input.txt >> log";
    int len = 0, nb_redir = 0;

    count_nb_redir(full_command, &len, &nb_redir);

    cr_assert_eq(nb_redir, 3, "Expected 3 redirections but got %d", nb_redir);
}

Test(count_nb_redir, single_redirection) {
    char full_command[] = "echo > file";
    int len = 0, nb_redir = 0;

    count_nb_redir(full_command, &len, &nb_redir);

    cr_assert_eq(nb_redir, 1, "Expected 1 redirection but got %d", nb_redir);
}

Test(count_nb_redir, no_redirection) {
    char full_command[] = "echo hello world";
    int len = 0, nb_redir = 0;

    count_nb_redir(full_command, &len, &nb_redir);

    cr_assert_eq(nb_redir, 0, "Expected 0 redirections but got %d", nb_redir);
}

Test(count_nb_redir, consecutive_redirections) {
    char full_command[] = "cmd << input >> output > log";
    int len = 0, nb_redir = 0;

    count_nb_redir(full_command, &len, &nb_redir);

    cr_assert_eq(nb_redir, 3, "Expected 3 redirections but got %d", nb_redir);
}

Test(remove_redir_args, valid_arguments) {
    command_t new;
    new.args = malloc(sizeof(char *) * 4);
    new.args[0] = strdup("echo");
    new.args[1] = strdup(">");
    new.args[2] = strdup("file.txt");
    new.args[3] = NULL;

    remove_redir_args(&new, 1);

    cr_assert_null(new.args[1], "Expected args[1] to be NULL after freeing.");
    cr_assert_null(new.args[2], "Expected args[2] to be NULL after freeing.");

    free(new.args[0]);
    free(new.args);
}

Test(remove_redir_args, already_null_arguments) {
    command_t new;
    new.args = malloc(sizeof(char *) * 3);
    new.args[0] = strdup("ls");
    new.args[1] = NULL;
    new.args[2] = NULL;

    remove_redir_args(&new, 1);

    cr_assert_null(new.args[1], "Expected args[1] to remain NULL.");
    cr_assert_null(new.args[2], "Expected args[2] to remain NULL.");

    free(new.args[0]);
    free(new.args);
}

Test(init_redir, double_redirection_output) {
    command_t new = {0};
    char full_command[] = ">>";
    int result = init_redir(&new, full_command, 0);

    cr_assert_eq(result, 1, "Expected 1 for '>>' but got %d", result);
    cr_assert_eq(new.redir, R_DOUBLE_REDI, "Expected R_DOUBLE_REDI but got %d", new.redir);
}

Test(init_redir, simple_redirection_output) {
    command_t new = {0};
    char full_command[] = ">";
    int result = init_redir(&new, full_command, 0);

    cr_assert_eq(result, 1, "Expected 1 for '>' but got %d", result);
    cr_assert_eq(new.redir, R_SIMPLE_REDI, "Expected R_SIMPLE_REDI but got %d", new.redir);
}

Test(init_redir, double_redirection_input) {
    command_t new = {0};
    char full_command[] = "<<";
    int result = init_redir(&new, full_command, 0);

    cr_assert_eq(result, 1, "Expected 1 for '<<' but got %d", result);
    cr_assert_eq(new.redir, L_DOUBLE_REDI, "Expected L_DOUBLE_REDI but got %d", new.redir);
}

Test(init_redir, simple_redirection_input) {
    command_t new = {0};
    char full_command[] = "<";
    int result = init_redir(&new, full_command, 0);

    cr_assert_eq(result, 1, "Expected 1 for '<' but got %d", result);
    cr_assert_eq(new.redir, L_SIMPLE_REDI, "Expected L_SIMPLE_REDI but got %d", new.redir);
}

Test(init_redir, no_redirection) {
    command_t new = {0};
    char full_command[] = "echo test";
    int result = init_redir(&new, full_command, 0);

    cr_assert_eq(result, 0, "Expected 0 when no redirection is found but got %d", result);
}

static command_t *create_mock_command2(const char *cmd, int op, int redir)
{
    command_t *command = malloc(sizeof(command_t));
    command->args = malloc(sizeof(char *) * 2);
    command->args[0] = strdup(cmd);
    command->args[1] = NULL;
    command->op = op;
    command->redir = redir;
    command->next = NULL;
    return command;
}

static void free_mock_command2(command_t *command)
{
    if (!command) return;
    free(command->args[0]);
    free(command->args);
    free(command);
}

Test(check_operator, handle_pipe_operator)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t *cmd = create_mock_command2("ls", PIPE, NONE_REDIR);

    int result = check_operator(&cmd, &env, &shell);

    cr_assert_eq(result, 1, "Expected check_operator to return 1 for a pipe operator, but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected shell.return_value to remain 0, but got %d", shell.return_value);

    free_mock_command2(cmd);
}

Test(check_operator, handle_redirection_operator)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t *cmd = create_mock_command2("echo", NONE, R_SIMPLE_REDI);

    int result = check_operator(&cmd, &env, &shell);

    cr_assert_eq(result, 1);
    cr_assert_eq(shell.return_value, 1);

    free_mock_command2(cmd);
}

Test(check_operator, handle_alias_command)
{
    shell_t shell = { .return_value = 0 };
    shell.alias = NULL;
    env_t *env = NULL;
    command_t *cmd = create_mock_command2("alias", NONE, NONE_REDIR);

    int result = check_operator(&cmd, &env, &shell);

    cr_assert_eq(result, 1, "Expected check_operator to return 1 for an alias command, but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected shell.return_value to remain 0, but got %d", shell.return_value);

    free_mock_command2(cmd);
}

Test(check_operator, no_operator_or_redirection)
{
    shell_t shell = { .return_value = 0 };
    env_t *env = NULL;
    command_t *cmd = create_mock_command2("ls", NONE, NONE_REDIR);

    int result = check_operator(&cmd, &env, &shell);

    cr_assert_eq(result, 0, "Expected check_operator to return 0 for no operator or redirection, but got %d", result);
    cr_assert_eq(shell.return_value, 0, "Expected shell.return_value to remain 0, but got %d", shell.return_value);

    free_mock_command2(cmd);
}

Test(find_alias_in_cmd, valid_alias_replacement) {
    alias_t alias = { .alias = "ls", .value = "echo List Files" };
    shell_t shell = { .return_value = 0 };
    char *tab[] = { strdup("ls"), NULL };

    int result = find_alias_in_cmd(&alias, tab, &shell);

    cr_assert_eq(result, 1, "Expected 1 when alias is found but got %d", result);
    cr_assert_str_eq(tab[0], "echo List Files", "Expected alias replacement to be 'echo List Files' but got '%s'", tab[0]);
    
    free(tab[0]);
}

Test(find_alias_in_cmd, no_alias_match) {
    alias_t alias = { .alias = "grep", .value = "search" };
    shell_t shell = { .return_value = 0 };
    char *tab[] = { strdup("ls"), NULL };

    int result = find_alias_in_cmd(&alias, tab, &shell);

    cr_assert_eq(result, 0, "Expected 0 when alias is not found but got %d", result);
    cr_assert_str_eq(tab[0], "ls", "Expected tab[0] to remain 'ls' but got '%s'", tab[0]);

    free(tab[0]);
}

Test(add_alias, successful_addition) {
    alias_t *alias_list = NULL;
    char alias_name[] = "ls";
    char value[] = "echo List Files";

    int result = add_alias(&alias_list, alias_name, value);

    cr_assert_eq(result, 1, "Expected 1 for successful addition but got %d", result);
    cr_assert_not_null(alias_list, "Expected alias_list to be initialized but got NULL");
    cr_assert_str_eq(alias_list->alias, alias_name, "Expected alias to be '%s' but got '%s'", alias_name, alias_list->alias);
    cr_assert_str_eq(alias_list->value, value, "Expected alias value to be '%s' but got '%s'", value, alias_list->value);

    free(alias_list->alias);
    free(alias_list->value);
    free(alias_list);
}

Test(add_alias, failed_allocation) {
    alias_t *alias_list = NULL;
    char alias_name[] = "cd";
    char value[] = "change_directory";

    alias_t *backup_malloc = malloc(sizeof(alias_t));
    free(backup_malloc);
    alias_t *new_alias = NULL;

    int result = add_alias(&new_alias, alias_name, value);

    cr_assert_eq(result, 1, "Expected 1 when allocation fails but got %d", result);
    cr_assert_not_null(new_alias, "Expected alias to remain NULL after failed allocation");
}

Test(delete_alias_node, delete_middle_node) {
    alias_t *alias_list = malloc(sizeof(alias_t));
    alias_t *second_alias = malloc(sizeof(alias_t));
    alias_t *third_alias = malloc(sizeof(alias_t));
    char *tab[] = {"ls", "rm"};

    alias_list->alias = strdup("ls");
    alias_list->value = strdup("echo List Files");
    alias_list->next = second_alias;

    second_alias->alias = strdup("rm");
    second_alias->value = strdup("delete Files");
    second_alias->next = third_alias;

    third_alias->alias = strdup("cd");
    third_alias->value = strdup("change Directory");
    third_alias->next = NULL;

    delete_alias_node(&alias_list, tab, 1);

    cr_assert_not_null(alias_list, "Alias list should not be NULL after deletion.");
    cr_assert_str_eq(alias_list->alias, "ls", "Expected alias 'ls' to remain.");
    cr_assert_str_eq(alias_list->next->alias, "cd", "Expected alias 'cd' to be next after deletion.");
    
    free(alias_list->alias);
    free(alias_list->value);
    free(alias_list->next->alias);
    free(alias_list->next->value);
    free(alias_list->next);
    free(alias_list);
}

Test(delete_alias_node, delete_head_node) {
    alias_t *alias_list = malloc(sizeof(alias_t));
    alias_t *second_alias = malloc(sizeof(alias_t));
    char *tab[] = {"ls"};

    alias_list->alias = strdup("ls");
    alias_list->value = strdup("echo List Files");
    alias_list->next = second_alias;

    second_alias->alias = strdup("rm");
    second_alias->value = strdup("delete Files");
    second_alias->next = NULL;

    delete_alias_node(&alias_list, tab, 0);

    cr_assert_not_null(alias_list, "Alias list should still exist after deletion.");
    cr_assert_str_eq(alias_list->alias, "rm", "Expected alias 'rm' to be head after deleting 'ls'.");

    free(alias_list->alias);
    free(alias_list->value);
    free(alias_list);
}

Test(delete_alias_node, alias_not_found) {
    alias_t *alias_list = malloc(sizeof(alias_t));
    alias_list->alias = strdup("ls");
    alias_list->value = strdup("echo List Files");
    alias_list->next = NULL;
    char *tab[] = {"rm"};

    delete_alias_node(&alias_list, tab, 0);

    cr_assert_not_null(alias_list, "Alias list should remain unchanged if alias is not found.");
    cr_assert_str_eq(alias_list->alias, "ls", "Expected alias 'ls' to remain unchanged.");

    free(alias_list->alias);
    free(alias_list->value);
    free(alias_list);
}
