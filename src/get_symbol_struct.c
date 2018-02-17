/*
** EPITECH PROJECT, 2018
** get_symbol_struct
** File description:
** 	get_symbol_struct file
*/

#include <stdlib.h>
#include <global_struct.h>
#include <string.h>
#include "global_define.h"
#include "global_function.h"
#include "global_struct.h"

int get_symbol_number(void *symbol_section, data_unit_t nb_bits)
{
	Elf64_Shdr *high_symbol_section = symbol_section;
	Elf64_Shdr *low_symbol_section = symbol_section;

	if (nb_bits == VAL64BITS)
		return (high_symbol_section->sh_size /
			high_symbol_section->sh_entsize);
	return (low_symbol_section->sh_size / low_symbol_section->sh_entsize);
}

char print_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char c;

	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	} else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
		   ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	} else if (sym.st_shndx == SHN_UNDEF)
		c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		c = 'C';
	else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
		c = 'R';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
		 && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = '?';
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}

static int compare_symbol(void const *a, void const *b)
{
	symbol_t *pa = a;
	symbol_t *pb = b;
	char *a_string = get_string_only_letter(pa->name);
	char *b_string = get_string_only_letter(pb->name);
	int cmp = 0;

	if (a_string == NULL)
		return (1);
	if (b_string == NULL)
		return (-1);
	cmp = strcasecmp(a_string, b_string);
	if (cmp == 0)
		return (strlen(pb->name) - strlen(pa->name));
	return (cmp);
}

static symbol_t *get_symbol_struct_high(void *elf,
					Elf64_Shdr *symbol_section,
					symbol_t *symbol,
					int section_index)
{
	Elf64_Sym *high_symbol;
	int offset_sym = 0;

	if (symbol == NULL)
		return (PTR_ERROR_RETURN);
	high_symbol = get_next_symbol(elf, symbol_section, VAL64BITS,
				      &offset_sym);
	for (int idx = 0; high_symbol != PTR_END_RETURN; idx++) {
		symbol[idx].address = high_symbol->st_value;
		symbol[idx].name = get_symbol_name(elf, VAL64BITS,
						   section_index,
						   high_symbol->st_name);
		high_symbol = get_next_symbol(elf, symbol_section, VAL64BITS,
					      &offset_sym);
	}
	qsort(symbol, get_symbol_number(symbol_section, VAL64BITS),
	      sizeof *symbol, compare_symbol);
	return (symbol);
}

static symbol_t *get_symbol_struct_low(void *elf,
				       Elf32_Shdr *symbol_section,
				       symbol_t *symbol,
				       int section_index)
{
	Elf32_Sym *low_symbol;
	int offset_sym = 0;

	if (symbol == NULL)
		return (PTR_ERROR_RETURN);
	low_symbol = get_next_symbol(elf, symbol_section, VAL64BITS,
				     &offset_sym);
	for (int idx = 0; low_symbol != PTR_END_RETURN; idx++) {
		symbol[idx].address = low_symbol->st_value;
		symbol[idx].name = get_symbol_name(elf, VAL64BITS,
						   section_index,
						   low_symbol->st_name);
		low_symbol = get_next_symbol(elf, symbol_section, VAL64BITS,
					     &offset_sym);
	}
	qsort(symbol, get_symbol_number(symbol_section, VAL32BITS),
	      sizeof *symbol, compare_symbol);
	return (symbol);
}

symbol_t *get_symbol_struct(void *elf,
			    data_unit_t nb_bits,
			    void *symbol_section,
			    int section_index)
{
	symbol_t *symbol = malloc(
		sizeof(symbol_t) * get_symbol_number(symbol_section, nb_bits));

	if (symbol == NULL)
		return (PTR_ERROR_RETURN);
	if (nb_bits == VAL32BITS) {
		return (get_symbol_struct_low(elf, symbol_section, symbol,
					      section_index));
	}
	return (get_symbol_struct_high(elf, symbol_section, symbol,
				       section_index));
}

symbol_t *get_symbol_section_struct(void *elf,
				    data_unit_t nb_bits,
				    int *size)
{

}
