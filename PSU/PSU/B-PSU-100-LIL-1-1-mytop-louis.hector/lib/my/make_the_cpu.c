/*
** EPITECH PROJECT, 2024
** make_the_cpu.c
** File description:
** the header for top with cpu
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "my.h"
#include <ncurses.h>
#include <dirent.h>
#include <string.h>
#include "../../include/mystruct.h"

void attribute_total(ProcessCpu_t *info
    , ProcessCpu_t *info_pre, int *total, int *total_diff)
{
    *total = info->user + info->nice + info->system + info->idle
        + info->iowait + info->irq + info->softirq + info->steal;
    *total_diff = (info->user - info_pre->user) + (info->nice - info_pre->nice)
        + (info->system - info_pre->system) + (info->idle - info_pre->idle)
        + (info->iowait - info_pre->iowait) + (info->irq - info_pre->irq)
        + (info->softirq - info_pre->softirq) +
        (info->steal - info_pre->steal);
}

void print_cpu(char *buffer, ProcessCpu_t *info_pre)
{
    ProcessCpu_t info = {0};
    int total = 0;
    int total_diff = 0;

    sscanf(buffer, "cpu %d %d %d %d %d %d %d %d",
        &info.user, &info.nice, &info.system, &info.idle,
        &info.iowait, &info.irq, &info.softirq, &info.steal);
    attribute_total(&info, info_pre, &total, &total_diff);
    mvprintw(2, 0, "%%Cpu(s): %.1f us,  %.1f sy,  %.1f ni,"
        "  %.1f id,  %.1f wa,  %.1f hi,  %.1f si,  %.1f st",
        (double)(info.user - info_pre->user) / total_diff * 100,
        (double)(info.system - info_pre->system) / total_diff * 100,
        (double)(info.nice - info_pre->nice) / total_diff * 100,
        (double)(info.idle - info_pre->idle) / total_diff * 100,
        (double)(info.iowait - info_pre->iowait) / total_diff * 100,
        (double)(info.irq - info_pre->irq) / total_diff * 100,
        (double)(info.softirq - info_pre->softirq) / total_diff * 100,
        (double)(info.steal - info_pre->steal) / total_diff * 100);
    *info_pre = info;
}

int my_cpu(void)
{
    static ProcessCpu_t info_pre = {0};
    int fd;
    char buffer[256];

    fd = open("/proc/stat", O_RDONLY);
    if (fd == -1)
        return -1;
    if (read(fd, buffer, sizeof(buffer) - 1) == -1) {
        perror("Failed to read /proc/stat");
        close(fd);
        return -1;
    }
    buffer[sizeof(buffer) - 1] = '\0';
    print_cpu(buffer, &info_pre);
    refresh();
    close(fd);
    return 0;
}
