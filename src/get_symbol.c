/*
** EPITECH PROJECT, 2018
** get_symbol
** File description:
** 	get_symbol file
*/

#include <elf.h>
#include "global_struct.h"
#include "global_function.h"

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