/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** corewar
*/

#include "op.h"
#include "my.h"
#include "corewar.h"
#include "instructions.h"
#include "op_c.h"

/**
 * @brief Prints the help message for the Corewar program.
 *
 * This function displays the usage and description of the Corewar program,
 * including the available flags and their purposes.
 *
 * @return 0 on success.
 */
int print_help(void)
{
    mini_printf("USAGE\n");
    mini_printf("./corewar [-dump nbr_cycle] [[-n prog_number] "
        "[-a load_address] prog_name] ...\n");
    mini_printf("DESCRIPTION\n");
    mini_printf("-dump nbr_cycle dumps the memory "
        "after the nbr_cycle execution (if the round isn't\n");
    mini_printf("already over) with the following format: "
        "32 bytes/line in hexadecimal (A0BCDEFE1DD3...\n");
    mini_printf("-n prog_number sets the next program's number. "
        "By default, the first free number in the\n");
    mini_printf("parameter order\n");
    mini_printf("-a load_address sets the next program's loading address."
        " When no address is specified,\n");
    mini_printf("optimize the addresses so that the processes "
        "are as far away from each other as\n");
    mini_printf("possible. The addresses are MEM_SIZE modulo.\n");
    return 0;
}

/**
 * @brief Executes the instruction for the current process.
 *
 * This function checks the instruction at the program counter of the
 * current process and executes it if it matches a valid instruction.
 * If no valid instruction is found, the program counter is incremented.
 *
 * @param process_actual Pointer to the current process structure.
 * @param global Pointer to the corewar global structure.
 * @return 0 on success, 1 if the instruction is invalid.
 */
int make_instruction(processes_t *process_actual, corewar_t *global)
{
    process_actual->pc = (process_actual->pc + MEM_SIZE) % MEM_SIZE;
    for (int i = 0; i < 16; i++) {
        if (global->arena[process_actual->pc] == instruct[i].name)
            return instruct[i].function(global, process_actual);
    }
    process_actual->pc = (process_actual->pc + 1) % MEM_SIZE;
    return 0;
}

/**
 * @brief Advances the process to the next instruction.
 *
 * This function executes the current instruction for the process. If the
 * instruction is invalid, the program counter is incremented.
 *
 * @param proc Pointer to the current process structure.
 * @param global Pointer to the corewar global structure.
 */
static void step_forward(processes_t *proc, corewar_t *global)
{
    if (make_instruction(proc, global) == 1)
        proc->pc = (proc->pc + 1) % MEM_SIZE;
}

/**
 * @brief Executes a single cycle of the Corewar virtual machine.
 *
 * This function iterates through all processes and executes their
 * instructions. If a process is waiting, its wait time is decremented.
 *
 * @param global Pointer to the corewar global structure.
 */
static void execute_cycle(corewar_t *global)
{
    processes_t *proc = global->process_list;

    while (proc != NULL) {
        if (proc->wait == 0) {
            step_forward(proc, global);
        } else
            proc->wait -= 1;
        proc = proc->next;
    }
}

/**
 * @brief Launches the Corewar virtual machine.
 *
 * This function runs the Corewar game loop, executing cycles until all
 * processes are terminated or the specified number of cycles is reached.
 * It also manages the cycle-to-die checks and prints the winner at the end.
 *
 * @param global Pointer to the corewar global structure.
 */
static void launch_vm(corewar_t *global)
{
    int current_cycle = 0;
    int since_check = 0;

    global->last_alive = -1;
    while (global->process_list != NULL) {
        global->current_cycle = current_cycle;
        execute_cycle(global);
        since_check++;
        if (global->cycle_to_die > 0 && since_check >= global->cycle_to_die) {
            check_hunger_games(global);
            since_check = 0;
        }
        if (global->nbr_cycle > 0 && current_cycle == global->nbr_cycle)
            break;
        if (global->process_list == NULL || global->nbr_cycle == 0)
            break;
        current_cycle++;
    }
    print_winner(global);
    return;
}

/**
 * @brief Entry point for the Corewar program.
 *
 * This function initializes the Corewar game, parses the arguments,
 * creates the players and processes, and starts the virtual machine.
 *
 * @param ac Number of arguments.
 * @param av Array of arguments.
 * @return 0 on success, 84 if an error occurs.
 */
int main(int ac, char **av)
{
    player_t player[4] = {0};
    corewar_t global = {0};
    processes_t *start_process = {0};

    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return print_help();
    if (parsing_flags(ac, av, player, &global) == 84)
        return 84;
    if (create_champions(player, &global) == 84)
        return 84;
    for (int i = 0; i < global.nb_champions; i++)
        if (initialize_process(&start_process, global, i) == 84)
            return 84;
    global.cycle_to_die = CYCLE_TO_DIE;
    global.process_list = start_process;
    if (create_arena_with_player(&global) == 84)
        return 84;
    launch_vm(&global);
    free_struct(global, start_process, player);
    return 0;
}
