/*
** EPITECH PROJECT, 2024
** cowerar
** File description:
** corewar.h
*/


#ifndef MY_COR
    #define MY_COR
    #include "my.h"
    #include "op.h"
    #include <stdbool.h>

typedef struct parsing_position_s {
    int pos;
    int flag_dump_detected;
    int actual_champion;
} parsing_position_t;

typedef struct player_s {
    int number;
    char *name;
    char *comment;
    int prog_size;
    uint8_t *code;
    char *path_file;
    int load_address;
    int live_cycle;
} player_t;

typedef struct processes_s {
    int id_player;
    int carry;
    int pc;
    int registre[REG_NUMBER];
    int live_cycle;
    int wait;
    bool is_ready;
    struct processes_s *next;
} processes_t;

typedef struct corewar_s {
    int nbr_cycle;
    int nb_champions;
    unsigned char *arena;
    player_t player[MAX_ARGS_NUMBER];
    processes_t *process_list;
    int current_cycle;
    int cycle_to_die;
    int number_live;
    int last_alive;
    char *name_alive;
} corewar_t;

typedef struct instruction_s {
    unsigned char name;
    int (*function)(corewar_t *, processes_t *);
} instruction_t;

typedef struct argument_value_s {
    args_type_t param;
    int value_regi;
    int value_direct;
} argument_value_t;

typedef struct params_values_s {
    argument_value_t args[3];
    int position;
    int command;
    int modulo_command;
} params_values_t;


//Main
void reverse_bytes(void *ptr, size_t size);
//

//Parsing
int parsing_flags(int ac, char **av, player_t player[4], corewar_t *globals);
//

//Champions
int create_champions(player_t player[4], corewar_t *globals);
//

//Virtual_machine
int create_arena_with_player(corewar_t *global);
void print_arena(corewar_t *global);
//

//INSTRUCTIONS
int make_add(corewar_t *global, processes_t *process);
int make_aff(corewar_t *global, processes_t *process);
int make_and(corewar_t *global, processes_t *process);
int make_fork(corewar_t *global, processes_t *process);
int make_ld(corewar_t *global, processes_t *process);
int make_ldi(corewar_t *global, processes_t *process);
int make_lfork(corewar_t *global, processes_t *process);
int make_live(corewar_t *global, processes_t *process);
int make_lld(corewar_t *global, processes_t *process);
int make_lldi(corewar_t *global, processes_t *process);
int make_or(corewar_t *global, processes_t *process);
int make_st(corewar_t *global, processes_t *process);
int make_sti(corewar_t *global, processes_t *process);
int make_sub(corewar_t *global, processes_t *process);
int make_xor(corewar_t *global, processes_t *process);
int make_zjmp(corewar_t *global, processes_t *process);
int read_value(params_values_t values, processes_t *process,
    corewar_t *global, bool is_lldi);

//TYPES AND PC
int get_arg_type(unsigned char coding_byte, int pos);

//PROCESSES
int initialize_process(processes_t **instr, corewar_t global, int i);
int calculate_new_pc(params_values_t values, int number_args, int command);
int recover_direct_value(corewar_t *global, int position, int size);
int check_type(params_values_t *values
    , corewar_t *global, processes_t *process, int i);
int size_param(unsigned char coding_byte, int pos);
void change_carry(int data, processes_t *proces);
int recover_dir_size(int command);
int recover_indirect(corewar_t *global
    , int pc, int decal, params_values_t values);
processes_t *add_new_process(corewar_t *global
    , processes_t *process, int new_pc);
int recover_registre(int position
    , corewar_t *global, processes_t *process);

//FREE
void free_struct(corewar_t global, processes_t *start_process,
    player_t player[4]);

//WIN
void check_hunger_games(corewar_t *global);
void print_winner(corewar_t *global);
#endif
