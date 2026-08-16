/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-keryan.pollet-druelle
** File description:
** 42sh
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #define GREEN "\033[32m"
    #define CYAN  "\033[36m"
    #define RESET "\033[0m"

// Includes
    #include <stdio.h>
    #include <glob.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <signal.h>
    #include <time.h>
    #include <sys/wait.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <limits.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <pwd.h>

// Structures

/**
 * @struct env_s
 * @brief Represents an environment variable as a key-value pair.
 */
typedef struct env_s {
    char *key;                  /** Key of the environment variable */
    char *value;                /** Value of the environment variable */
    struct env_s *next;         /** Pointer to the next variable */
} env_t;

/**
 * @enum redir_type_e
 * @brief Represents types of redirection operators.
 */
typedef enum redir_type_e {
    NONE_REDIR,
    R_SIMPLE_REDI,
    R_DOUBLE_REDI,
    L_DOUBLE_REDI,
    L_SIMPLE_REDI
} redir_type_t;

/**
 * @enum op_type_e
 * @brief Represents logical and pipe operators.
 */
typedef enum op_type_e {
    NONE,
    PIPE,
    SEPARATOR,
    AND,
    OR
} op_type_t;

/**
 * @struct command_s
 * @brief Represents a shell command with its arguments and properties.
 */
typedef struct command_s {
    char **args;                /** Array of arguments for the command */
    char *file;                 /** File for redirection, if applicable */
    op_type_t op;               /** Logical or pipe operator */
    redir_type_t redir;         /** Redirection type */
    struct command_s *next;     /** Pointer to the next command */
} command_t;

/**
 * @struct history_s
 * @brief Represents an entry in the command history.
 */
typedef struct history_s {
    char *command;              /** Command string */
    char *time;                 /** Timestamp of the command */
    int index;                  /** Index of the command in history */
    struct history_s *next;     /** Pointer to the next history entry */
} history_t;

/**
 * @struct alias_s
 * @brief Functions for alias
 */
typedef struct alias_s {
    char *alias;                //**New name of the command */
    char *value;                //**Which command choose */
    struct alias_s *next;       //**Pointer to the next alias */
} alias_t;

typedef struct easter_egg_s {
    FILE *dragon;               /** File descriptor of dragon.txt file */
    FILE *credits;              /** File descriptor of credits.txt file */
    FILE *epitech;              /** File descriptor of epitech.txt file */
} easter_egg_t;

/**
 * @struct shell_s
 * @brief Represents the state of the shell.
 */
typedef struct shell_s {
    char **environement;        /** Array of environment variables */
    int return_value;           /** Return value of the last command */
    history_t *history;         /** Command history */
    char *command;              /** Current command input */
    char *tmp_command;          /** Temporary buffer for the current command */
    char *prompt;               /** Editable prompt value */
    char *history_path;         /** History file path */
    alias_t *alias;             /** Alias linked list */
    int exit_value;             /** Exit value when choose in builtin exit */
    bool is_exit;               /** Is exit builtin executed */
    int repeat;                 /**   Number of the repeat command */
    easter_egg_t *file;         /** File descriptor of easter egg files */
} shell_t;

/**
 * @struct interaction_termios_s
 * @brief Represents terminal interaction settings and state.
 */
typedef struct interaction_termios_s {
    int direction;              /** Direction of navigation */
    int nb_line;                /** Number of lines in the history */
    int index;                  /** Current index in the history */
    int pos;                    /** Position in the command */
    char *history_command;      /** Command from the history */
    struct termios old;         /** Original terminal settings */
} interaction_termios_t;

/**
 * @struct builtins_s
 * @brief Functions pointer for builtins
 */
typedef struct {
    char *name;
    int (*builtins)(char **, env_t **, char **, shell_t *);
} builtins_t;

/**
 * @struct foreach_s
 * @brief Functions for the script foreach
 */
typedef struct foreach_s {
    char *line;             //**Line of the variable*/
    char **commands;        //**List of commands in the foreach*/
    char **list;            //**List of the variable*/
    int index_var;          //**Index in the list of varaible */
} foreach_t;

/**
 * @struct pipe_context_s
 * @brief Represents the context for piping commands.
 */
typedef struct pipe_context_s {
    int *prev_fd;       //**Previous file descriptor for piping */
    int tube[2];        //**Pipe file descriptors */
    env_t **env;        //**Environment variables */
    shell_t *shell;     //**Shell structure */
} pipe_context_t;

// Builtins
int exit_shell(char **tab, env_t **env, char **old_path, shell_t *shell);
int change_directory(char **tab, env_t **env, char **old_path, shell_t *shell);
int display_env(char **tab, env_t **env, char **old_path, shell_t *shell);
int set_env(char **tab, env_t **env, char **old_path, shell_t *shell);
int unset_env(char **tab, env_t **env, char **old_path, shell_t *shell);
int display_history(char **tab, env_t **env, char **old_path, shell_t *shell);
int handle_prompt(char **commands,
    env_t **env, char **old_path, shell_t *shell);
int display_easter_egg(char **tab,
    env_t **env, char **old_path, shell_t *shell);
int which(char **tab, env_t **env, char **old_path, shell_t *shell);
int find_foreach(char **tab, env_t **env, char **old_path, shell_t *shell);
int find_where(char **tabs, env_t **env, char **old_path, shell_t *shell);
int repeat_command(char **tab, env_t **env, char **old_path, shell_t *shell);

// Minishell Functions
env_t *from_array_to_list(env_t *list, char **env);
char **from_list_to_array(env_t **envi);
int execute_command(shell_t *shell, env_t **env, command_t *current);

// Minishell2 Functions

int handle_command_execution(command_t *cmd,
    command_t *tmp, shell_t *shell, env_t **env);
void remove_node(env_t **current, env_t **prev, env_t **head);
int check_arg_number(env_t **env, int nb_arg, char **arg);
int is_data_missing(char **arg, env_t **env);
int is_data_present(char **arg, env_t **env);
int check_redirection(command_t *commands, env_t **env, shell_t *shell);

// 42sh Functions

int check_builtins(command_t *current, env_t **linked_list, shell_t *shell);
env_t *add_linked_list(env_t *list, char **env);
char *put_space(char *full_command);
int parse_input(command_t **commands, char *input);
int init_redir(command_t *new, char *full_command, int i);
int parse(command_t **commands, char *input, int index, int i);
int count_nb_redir(char *full_command, int *len, int *nb_redir);
int split_fork(char *path_with_function, command_t *current, char **env);
void add_infos(command_t *new, char *input, int index, int end);
int return_status_last_command(command_t *commands, shell_t *shell);
int handle_operator(command_t **commands, char *input, int *index, int *i);
int handle_redir(command_t *new, char *full_command);
void set_redirection_file(command_t *new, char **args, int *redir);
void remove_redir_args(command_t *new, int i);
int verif_redirection_left(command_t *commands, env_t **env, shell_t *shell);
char *getpath(char **tab, char **env);
int verif_env_argument(char **tab, shell_t *shell);
int recover_node_args(shell_t *shell, env_t **env
    , command_t *node, char **tab);
void free_command(command_t **commands);
void free_linked_list(env_t **list);
char *check_dir(char *dir, char *path, char **tab, char *check);
int check_null_command(command_t *commands, shell_t *shell);
int check_operator(command_t **commands, env_t **env, shell_t *shell);
int execute_loop(command_t *tmp,
    command_t *commands, shell_t *shell, env_t **env);
int get_array_size(char **array);
const char *get_ansi_color(const char *color_flag);
int execute_command_line(shell_t *shell
    , char *line_replace, env_t **env);
int execute(env_t **env,
    shell_t *shell_arg, history_t **history);
int affect_value_env(env_t *current, char **env, int i);
int execute_parsed_commands(command_t *commands,
    shell_t *shell_arg, env_t **env);
int recup_line_command(shell_t *shell_arg, command_t **commands);
int simple_redir(char *full_command, char *new_command, int *i, int *j);
void check_previous_file(int *prev_fd);
int handle_input_and_parse(env_t **env,
    shell_t *shell_arg, history_t **history, command_t **commands);
int end_pipe(int prev_fd, int *status, shell_t *shell);
int double_redir(char *full_command, char *new_command, int *i, int *j);
int reformate_args(command_t *commands);

// History Functions
int count_pipes(char *input);
int create_files(shell_t *shell_arg);
int handle_input(shell_t *shell_arg, history_t **history, env_t **env);
int browse_history(shell_t *shell);
char *get_home_user(char *filename);
int get_length_last_space(char *buffer);
history_t *from_file_to_list(history_t **history, char *history_path);
int from_list_to_file(history_t **history, char *history_path);
int display_error(int status, char *file);
char *get_time_of_command(void);
int get_size_of_history_list(history_t **history);
int add_command_to_list(history_t **history, char *command,
    char *time, int index);
char *search_asked_command(int index, shell_t *shell);
void recup_history_command(shell_t *shell,
    char *buffer, interaction_termios_t *term);

// Termios Functions
void check_escape(char ch, interaction_termios_t *term);
void delete_command_line(char ch, interaction_termios_t *term,
    char *buffer, shell_t *shell);
void write_in_terminal(char ch, char *buffer,
    interaction_termios_t *term, shell_t *shell);
void start_termios(interaction_termios_t *term, shell_t *shell);
int verif_enter(char ch, char *buffer, interaction_termios_t term,
    shell_t *shell);

// lib
char **my_str_to_word_array(char const *str, char const *delimiters);

// Free Functions
void free_linked_list(env_t **list);
void free_command(command_t **commands);
void is_free(env_t **node, shell_t *shell_arg);
int free_foreach(char **tab, char **commands_line, char *line, int end);
void free_history(history_t *history, char *path_history);
int free_old_path(int return_value, char *old_path);
void free_array(char **array);

//GLOB
char *from_array_to_line(char **args);
char *change_globbins_in_line(char *line);
int check_globbins(command_t *commands, shell_t *shell);

//SCRIPT:
//WHICH / WHERE
int confirm_builtins_command(char **tabs, int *index_args);
int confirm_builtins(char **tabs, int *index_args);
int create_copy_path_env(char **copy, char *path_env
    , shell_t *shell, char **tab);
//FOREACH
int verify_first_argument(char **args, shell_t *shell);
char *replace_dollar(char *line, char *name, shell_t *shell, char **args);
int check_everything(command_t *commands, env_t **linked_list, shell_t *shell);
int verif_maloc(void *element, shell_t *shell);
int initialize_commands(foreach_t *foreach, shell_t *shell);

//PIPE
int execute_pipe_sequence(command_t *commands, env_t **env, shell_t *shell);
bool is_valid_cmd(command_t *cmd, env_t **env);

//ALIAS
int check_alias_cmd(alias_t **alias, char **tab, shell_t *shell);
int find_alias_in_cmd(alias_t *current, char **tab, shell_t *shell);
void modif_alias_cmd(alias_t **alias, char **tab, shell_t *shell);
int add_alias(alias_t **alias, char *alias_name, char *value);
void delete_alias_node(alias_t **alias, char **tab, int i);

//AUTO_COMPLETE
int check_for_tab(char ch, char *buffer,
    interaction_termios_t *term, shell_t *shell);

#endif /* !SHELL_H_ */
