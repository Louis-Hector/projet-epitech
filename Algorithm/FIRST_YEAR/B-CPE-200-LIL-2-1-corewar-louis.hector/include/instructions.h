/*
** EPITECH PROJECT, 2025
** CPE
** File description:
** INCLUDE pointer to instrcution
*/

#include "corewar.h"

#ifndef INSTRUCTION_H_
    #define INSTRUCTION_H_

const instruction_t instruct[] = {
    {0x01, make_live}, /** ok */
    {0x02, make_ld}, /** ok */
    {0x03, make_st}, /** 50 */
    {0x04, make_add}, /** ok */
    {0x05, make_sub}, /** ok */
    {0x06, make_and}, /** ok */
    {0x07, make_or}, /** ok */
    {0x08, make_xor}, /** ok% */
    {0x09, make_zjmp}, /** ok */
    {0x0A, make_ldi}, /** no */
    {0x0B, make_sti}, /** 50% */
    {0x0C, make_fork}, /** no */
    {0x0D, make_lld}, /** no */
    {0x0E, make_lldi}, /** no */
    {0x0F, make_lfork}, /** no */
    {0x10, make_aff} /** no */
};

#endif /* !INSTRUCTION_H */
