/*
** EPITECH PROJECT, 2018
** get_headers
** File description:
** 	get_headers file
*/

#include <elf.h>
#include <stdint.h>
#include "global_define.h"

void *get_program_header(void *elf, data_unit_t nb_bits)
{
	if (nb_bits == VAL32BITS)
		return ((byte_t *) elf + ((Elf32_Ehdr *) elf)->e_phoff);
	return ((byte_t *) elf + ((Elf64_Ehdr *) elf)->e_phoff);
}

void *get_section_header(void *elf, data_unit_t nb_bits)
{
	if (nb_bits == VAL32BITS) {
		return ((byte_t *) elf + ((Elf32_Ehdr *) elf)->e_shoff);
	}
	return ((byte_t *) elf + ((Elf64_Ehdr *) elf)->e_shoff);
}
