/*
** EPITECH PROJECT, 2018
** get_structs
** File description:
** 	get_structs file
*/

#include <elf.h>
#include "global_define.h"
#include "global_function.h"

void *get_section(void *elf, data_unit_t nb_bits, int index)
{
	Elf32_Shdr *low_bits_struct;
	Elf64_Shdr *high_bits_struct;

	if (nb_bits == VAL32BITS) {
		low_bits_struct = get_section_header(elf, nb_bits);
		return (&low_bits_struct[index]);
	}
	high_bits_struct = get_section_header(elf, nb_bits);
	return (&high_bits_struct[index]);
}