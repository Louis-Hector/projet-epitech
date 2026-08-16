/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** create_champions.c
*/

#include "op.h"
#include "my.h"
#include "corewar.h"

/**
 * @brief Reverses the bytes of a given memory block.
 *
 * This function takes a pointer to a memory block and reverses the order
 * of its bytes. It is typically used to handle endianness issues when
 * reading or writing binary data.
 *
 * @param ptr Pointer to the memory block to reverse.
 * @param size Size of the memory block in bytes.
 */
void reverse_bytes(void *ptr, size_t size)
{
    unsigned char *byte_ptr = (unsigned char *)ptr;
    unsigned char tmp = 0;
    size_t i = 0;

    for (; i < size / 2; i++) {
        tmp = byte_ptr[i];
        byte_ptr[i] = byte_ptr[size - 1 - i];
        byte_ptr[size - 1 - i] = tmp;
    }
}

/**
 * @brief Loads the champion's body into a buffer.
 *
 * This function reads the binary code of a champion from a file and
 * stores it in the player's `code` buffer. The size of the buffer is
 * determined by the `prog_size` field of the player structure.
 *
 * @param fd File descriptor of the champion file.
 * @param player Array of player structures.
 * @param i Index of the current player.
 * @return 0 on success, 84 on failure (e.g., memory allocation failure or
 *         read error).
 */
static int load_champion_body_to_buffer(FILE *fd, player_t *player, int i)
{
    size_t read_bytes = 0;

    player[i].code = malloc(player[i].prog_size);
    if (!player[i].code)
        return 84;
    read_bytes = fread(player[i].code, 1, player[i].prog_size, fd);
    if (read_bytes != (size_t)player[i].prog_size) {
        free(player[i].code);
        return 84;
    }
    return 0;
}

/**
 * @brief Retrieves information about a champion from its file.
 *
 * This function reads the header of a champion file to extract metadata
 * such as the program name, comment, and size. It also verifies the
 * magic number to ensure the file is valid. The champion's binary code
 * is then loaded into memory.
 *
 * @param player Array of player structures.
 * @param i Index of the current player.
 * @return 0 on success, 84 on failure (e.g., invalid file, memory allocation
 *         failure, or read error).
 */
int get_champion_infos(player_t player[4], int i)
{
    FILE *fd = fopen(player[i].path_file, "rb");
    header_t header = {0};

    if (fd == NULL)
        return 84;
    fread(&header, sizeof(header_t), 1, fd);
    reverse_bytes(&header.prog_size, 4);
    reverse_bytes(&header.magic, 4);
    player[i].name = my_strdup(header.prog_name);
    player[i].comment = my_strdup(header.comment);
    player[i].prog_size = header.prog_size;
    if (header.magic != COREWAR_EXEC_MAGIC) {
        mini_printf("Magic number errone\n");
        return 84;
    }
    if (load_champion_body_to_buffer(fd, player, i) == 84)
        return 84;
    fclose(fd);
    return 0;
}

/**
 * @brief Creates champions by loading their information and code.
 *
 * This function initializes the champions by reading their metadata and
 * binary code from their respective files. It iterates over all the
 * champions specified in the `globals` structure and stores their
 * information in the `player` array.
 *
 * @param player Array of player structures.
 * @param globals Pointer to the corewar global structure containing the
 *                number of champions and other global data.
 * @return 0 on success, 84 on failure (e.g., invalid champion file or
 *         initialization error).
 */
int create_champions(player_t player[4], corewar_t *globals)
{
    for (int i = 0; i < globals->nb_champions; i++) {
        if (get_champion_infos(player, i) == 84) {
            mini_printf("INIT: header error\n");
            return 84;
        }
        globals->player[i] = player[i];
    }
    return 0;
}
