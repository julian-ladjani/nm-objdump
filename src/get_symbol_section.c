/*
** EPITECH PROJECT, 2018
** PSU_2017_nmobjdump
** File description:
** 	get_symbol_section source file
*/

#include <elf.h>
#include "global_struct.h"
#include "global_function.h"

void *get_next_symbol_section_low(void *elf, elf_header_t *info, int *offset)
{
	Elf32_Shdr *low_bits_struct;
	Elf32_Ehdr *low_elf = elf;

	low_bits_struct = get_section_header(elf, info);
	for (int idx = *offset; idx < low_elf->e_shnum; idx++) {
		*offset = idx + 1;
		if (low_bits_struct[idx].sh_type == SHT_SYMTAB)
			return (&low_bits_struct[idx]);
	}
	return (PTR_END_RETURN);
}

void *get_next_symbol_section_high(void *elf, elf_header_t *info, int *offset)
{
	Elf64_Shdr *high_bits_struct;
	Elf64_Ehdr *high_elf = elf;

	high_bits_struct = get_section_header(elf, info);
	for (int idx = *offset; idx < high_elf->e_shnum; idx++) {
		*offset = idx + 1;
		if (high_bits_struct[idx].sh_type == SHT_SYMTAB)
			return (&high_bits_struct[idx]);
	}
	return (PTR_END_RETURN);
}

void *get_next_symbol_section(void *elf, elf_header_t *info, int *offset)
{
	if (info->architecture == VAL32BITS) {
		return (get_next_symbol_section_low(elf, info, offset));
	}
	return (get_next_symbol_section_high(elf, info, offset));
}
