/*
** EPITECH PROJECT, 2018
** get_strings
** File description:
** 	get_strings file
*/

#include <elf.h>
#include <stdint.h>
#include <unistd.h>
#include "global_struct.h"
#include "global_function.h"

static char *get_section_name_table(void *elf, elf_header_t *info)
{
	Elf32_Shdr *low_bits_struct;
	Elf64_Shdr *high_bits_struct;
	Elf32_Ehdr *low_elf = elf;
	Elf64_Ehdr *high_elf = elf;

	if (info->architecture == VAL32BITS) {
		if (low_elf->e_shstrndx == SHN_UNDEF)
			return (PTR_ERROR_RETURN);
		low_bits_struct = get_section(elf, info,
			(int) low_elf->e_shstrndx);
		return ((char *) elf + low_bits_struct->sh_offset);
	}
	if (high_elf->e_shstrndx == SHN_UNDEF)
		return (PTR_ERROR_RETURN);
	high_bits_struct = get_section(elf, info,
		(int) high_elf->e_shstrndx);
	return ((char *) elf + high_bits_struct->sh_offset);
}

char *get_section_name(void *elf, elf_header_t *info, int offset)
{
	char *string_table = get_section_name_table(elf, info);

	if (string_table == PTR_ERROR_RETURN)
		return (PTR_ERROR_RETURN);
	return (string_table + offset);
}

char *get_symbol_name_table(void *elf, elf_header_t *info, int index)
{
	Elf32_Shdr *low_bits_struct;
	Elf64_Shdr *high_bits_struct;

	if (info->architecture == VAL32BITS) {
		low_bits_struct = get_section(elf, info, index);
		low_bits_struct = get_section(elf, info,
			low_bits_struct->sh_link);
		return ((char *) ((uintptr_t) (low_bits_struct->sh_offset)));
	}
	high_bits_struct = get_section(elf, info, index);
	high_bits_struct = get_section(elf, info,
		high_bits_struct->sh_link);
	return ((char *) ((uintptr_t) (high_bits_struct->sh_offset)));
}

char *get_symbol_name(void *elf,
	elf_header_t *info,
	int symbol_index,
	int name_index)
{
	char *str_p = get_symbol_name_table(elf, info, symbol_index);

	if (name_index == SHN_UNDEF)
		return (NULL);
	return (str_p + (uintptr_t) elf + name_index);
}