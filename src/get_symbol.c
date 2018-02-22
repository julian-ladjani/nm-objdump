/*
** EPITECH PROJECT, 2018
** get_symbol
** File description:
** 	get_symbol file
*/

#include <elf.h>
#include <global_struct.h>
#include "global_define.h"
#include "global_function.h"

void *get_next_symbol_section(void *elf, elf_header_t *info, int *offset)
{
	Elf32_Shdr *low_bits_struct;
	Elf64_Shdr *high_bits_struct;
	Elf32_Ehdr *low_elf = elf;
	Elf64_Ehdr *high_elf = elf;

	if (info->architecture == VAL32BITS) {
		low_bits_struct = get_section_header(elf, info);
		for (int idx = *offset; idx < low_elf->e_shnum; idx++) {
			*offset = idx + 1;
			if (low_bits_struct[idx].sh_type == SHT_SYMTAB)
				return (&low_bits_struct[idx]);
		}
	} else {
		high_bits_struct = get_section_header(elf, info);
		for (int idx = *offset; idx < high_elf->e_shnum; idx++) {
			*offset = idx + 1;
			if (high_bits_struct[idx].sh_type == SHT_SYMTAB)
				return (&high_bits_struct[idx]);
		}
	}
	return (PTR_END_RETURN);
}

static void *get_next_symbol_low(Elf32_Ehdr *elf,
	Elf32_Shdr *symbol_section,
	__attribute__((unused)) elf_header_t *info,
	int *offset)
{
	Elf32_Sym *symbol =
		(Elf32_Sym *) ((byte_t *) elf + symbol_section->sh_offset);
	int index = *offset;

	if (*offset < (int) (symbol_section->sh_size /
		symbol_section->sh_entsize)) {
		*offset = index + 1;
		return (&symbol[index]);
	}
	return (PTR_END_RETURN);
}

static void *get_next_symbol_high(Elf64_Ehdr *elf,
	Elf64_Shdr *symbol_section,
	__attribute__((unused)) elf_header_t *info,
	int *offset)
{
	Elf64_Sym *symbol =
		(Elf64_Sym *) ((byte_t *) elf + symbol_section->sh_offset);
	int index = *offset;

	if (*offset < (int) (symbol_section->sh_size /
		symbol_section->sh_entsize)) {
		*offset = index + 1;
		return (&symbol[index]);
	}
	return (PTR_END_RETURN);
}

void *get_next_symbol(void *elf,
	void *symbol_section,
	elf_header_t *info,
	int *offset)
{
	if (info->architecture == VAL32BITS)
		return (get_next_symbol_low(elf, symbol_section, info,
			offset));
	return (get_next_symbol_high(elf, symbol_section, info, offset));
}