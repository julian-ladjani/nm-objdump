/*
** EPITECH PROJECT, 2018
** get_symbol_struct
** File description:
** 	get_symbol_struct file
*/

#include <stdlib.h>
#include "global_define.h"
#include "global_function.h"
#include "global_struct.h"

symbol_t *get_symbol_struct(void *elf,
			    data_unit_t nb_bits,
			    void *symbol_section)
{
	Elf32_Sym *low_symbol;
	Elf64_Sym *high_symbol;
	Elf32_Shdr *low_symbol_section = symbol_section;
	Elf64_Shdr *high_symbol_section = symbol_section;
	symbol_t *symbol =
		malloc(sizeof(symbol_t) * (low_symbol_section->sh_size /
					   low_symbol_section->sh_entsize));

}