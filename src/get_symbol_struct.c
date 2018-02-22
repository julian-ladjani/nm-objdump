/*
** EPITECH PROJECT, 2018
** get_symbol_struct
** File description:
** 	get_symbol_struct file
*/

#include <stdlib.h>
#include <string.h>
#include <global_struct.h>
#include "linked_list.h"
#include "global_define.h"
#include "global_function.h"
#include "global_struct.h"

int get_symbol_number(void *symbol_section, elf_header_t *info)
{
	Elf64_Shdr *high_symbol_section = symbol_section;
	Elf32_Shdr *low_symbol_section = symbol_section;

	if (info->architecture == VAL64BITS)
		return (high_symbol_section->sh_size /
			high_symbol_section->sh_entsize);
	return (low_symbol_section->sh_size / low_symbol_section->sh_entsize);
}

static symbol_t *get_symbol_struct_high(void *elf,
	Elf64_Shdr *symbol_section,
	elf_header_t *info,
	int section_index)
{
	Elf64_Sym *high_symbol;
	int offset_sym = 0;
	symbol_t *symbol = malloc(
		sizeof(symbol_t) * get_symbol_number(symbol_section, info));

	if (symbol == NULL)
		return (PTR_ERROR_RETURN);
	high_symbol = get_next_symbol(elf, symbol_section, info,
		&offset_sym);
	for (int idx = 0; high_symbol != PTR_END_RETURN; idx++) {
		symbol[idx].address = high_symbol->st_value;
		symbol[idx].info = high_symbol->st_info;
		symbol[idx].type = get_type_high(high_symbol,
			get_section_header(elf, info),
			info);
		symbol[idx].architecture = info->architecture;
		symbol[idx].name = get_symbol_name(elf, info,
			section_index,
			high_symbol->st_name);
		high_symbol = get_next_symbol(elf, symbol_section, info,
			&offset_sym);
	}
	return (symbol);
}

static symbol_t *get_symbol_struct_low(void *elf,
	Elf32_Shdr *symbol_section,
	elf_header_t *info,
	int section_index)
{
	Elf32_Sym *low_symbol;
	int offset_sym = 0;
	symbol_t *symbol = malloc(
		sizeof(symbol_t) * get_symbol_number(symbol_section, info));

	if (symbol == NULL)
		return (PTR_ERROR_RETURN);
	low_symbol = get_next_symbol(elf, symbol_section, info,
		&offset_sym);
	for (int idx = 0; low_symbol != PTR_END_RETURN; idx++) {
		symbol[idx].address = low_symbol->st_value;
		symbol[idx].info = low_symbol->st_info;
		symbol[idx].type = get_type_low(low_symbol,
			get_section_header(elf, info),
			info);
		symbol[idx].architecture = info->architecture;
		symbol[idx].name = get_symbol_name(elf, info,
			section_index,
			low_symbol->st_name);
		low_symbol = get_next_symbol(elf, symbol_section, info,
			&offset_sym);
	}
	return (symbol);
}

symbol_t *get_symbol_struct(void *elf,
	elf_header_t *info,
	void *symbol_section,
	int section_index)
{
	if (info->architecture == VAL32BITS) {
		return (get_symbol_struct_low(elf, symbol_section, info,
			section_index));
	}
	return (get_symbol_struct_high(elf, symbol_section, info,
		section_index));
}
