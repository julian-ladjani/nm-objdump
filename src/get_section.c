/*
** EPITECH PROJECT, 2018
** get_structs
** File description:
** 	get_structs file
*/

#include <elf.h>
#include <global_struct.h>
#include "global_define.h"
#include "global_function.h"

void *get_section(void *elf, elf_header_t *info, int index)
{
	Elf32_Shdr *low_bits_struct;
	Elf64_Shdr *high_bits_struct;

	if (info->architecture == VAL32BITS) {
		low_bits_struct = get_section_header(elf, info);
		return (&low_bits_struct[index]);
	}
	high_bits_struct = get_section_header(elf, info);
	return (&high_bits_struct[index]);
}