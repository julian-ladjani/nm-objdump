/*
** EPITECH PROJECT, 2018
** get_symbol_list
** File description:
** 	get_symbol_list file
*/

#include <stdlib.h>
#include <string.h>
#include <global_struct.h>
#include <assert.h>
#include "linked_list.h"
#include "global_define.h"
#include "global_function.h"
#include "global_struct.h"

static list_t *symbol_struct_to_list(list_t *list,
				     symbol_t *symbol_struct,
				     void *symbol_section,
				     elf_header_t *info)
{

	if (symbol_struct != NULL && symbol_struct != PTR_END_RETURN
	    && symbol_struct != PTR_ERROR_RETURN)
		list = list_add_tab(list, (list_byte_t *) symbol_struct,
				    sizeof(symbol_t),
				    (size_t) get_symbol_number(symbol_section,
							       info));
	free(symbol_struct);
	return (list);
}

static list_t *get_symbol_list_high(void *elf, elf_header_t *info)
{
	Elf64_Shdr *symbol_section;
	int offset_sym_section = 0;
	list_t *list = NULL;
	symbol_t *symbol_struct;

	symbol_section = get_next_symbol_section(elf, info,
						 &offset_sym_section);
	while (symbol_section != NULL && symbol_section != PTR_END_RETURN &&
	       symbol_section != PTR_ERROR_RETURN) {
		symbol_struct = get_symbol_struct(elf, info,
						  symbol_section,
						  offset_sym_section - 1);
		list = symbol_struct_to_list(list, symbol_struct,
					     symbol_section, info);
		symbol_section = get_next_symbol_section(elf, info,
							 &offset_sym_section);
	}
	return (list);
}

static list_t *get_symbol_list_low(void *elf, elf_header_t *info)
{
	Elf32_Shdr *symbol_section;
	int offset_sym_section = 0;
	list_t *list = NULL;
	symbol_t *symbol_struct;

	symbol_section = get_next_symbol_section(elf, info,
						 &offset_sym_section);
	while (symbol_section != NULL && symbol_section != PTR_END_RETURN &&
	       symbol_section != PTR_ERROR_RETURN) {
		symbol_struct = get_symbol_struct(elf, info,
						  symbol_section,
						  offset_sym_section - 1);
		list = symbol_struct_to_list(list, symbol_struct,
					     symbol_section, info);
		symbol_section = get_next_symbol_section(elf, info,
							 &offset_sym_section);
	}
	return (list);
}

list_t *get_symbol_list(void *elf,
			elf_header_t *info)
{
	list_t *list = NULL;

	if (info->architecture == VAL32BITS)
		list = get_symbol_list_low(elf, info);
	else
		list = get_symbol_list_high(elf, info);
	list = list_sort(list, compare_symbol);
	return (list);
}
