/*
** EPITECH PROJECT, 2018
** get_type
** File description:
** 	get_type file
*/

#include <elf.h>
#include "global_struct.h"
#include "global_function.h"

static const symbol_type_t symbol_type[] = {
	{SHT_NULL, STT_FUNC, 0, 'U'},
	{SHT_PROGBITS, STT_NOTYPE, 0, 'N'},
	{SHT_PROGBITS, STT_OBJECT, 0, 'N'},
	{SHT_PROGBITS, STT_NOTYPE, 2, 'R'},
	{SHT_PROGBITS, STT_NOTYPE, 50, 'R'},
	{SHT_PROGBITS, STT_OBJECT, 2, 'R'},
	{SHT_PROGBITS, STT_OBJECT, 50, 'R'},
	{SHT_PROGBITS, SHF_WRITE, 18, 'R'},
	{SHT_NOTE, STT_OBJECT, 2, 'R'},
	{SHT_PROGBITS, STT_NOTYPE, 3, 'D'},
	{SHT_DYNAMIC, STT_OBJECT, 3, 'D'},
	{SHT_PROGBITS, STT_OBJECT, 3, 'D'},
	{SHT_PROGBITS, STT_TLS, 1027, 'D'},
	{SHT_PROGBITS, STT_NOTYPE, 6, 'T'},
	{SHT_FINI_ARRAY, STT_NOTYPE, 3, 'T'},
	{SHT_INIT_ARRAY, STT_NOTYPE, 3, 'T'},
	{SHT_FINI_ARRAY, STT_OBJECT, 3, 'T'},
	{SHT_INIT_ARRAY, STT_OBJECT, 3, 'T'},
	{SHT_PROGBITS, STT_FUNC, 6, 'T'},
	{SHT_NOBITS, STT_OBJECT, 3, 'B'},
	{SHT_NOBITS, STT_NOTYPE, 3, 'B'},
	{SHT_NOBITS, STT_TLS, 1027, 'B'},
	{SHT_PROGBITS, STT_LOOS, 6, 'I'},
	{SHT_PROGBITS, STT_LOOS, 6, 'I'}
};

static char get_type_st_bind_high(Elf64_Sym *sym, char c)
{
	if (c != INT_CONTINUE)
		return (c);
	switch (ELF64_ST_BIND(sym->st_info)) {
		case STB_GNU_UNIQUE:
			return ('u');
		case STB_WEAK:
			if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
				if (sym->st_shndx == SHN_UNDEF)
					return ('v');
				return ('V');
			}
			if (sym->st_shndx == SHN_UNDEF)
				return ('w');
			return ('W');
		default :
			return (INT_CONTINUE);
	}
}

static char get_type_st_shndx_high(Elf64_Sym *sym, char c)
{
	if (c != INT_CONTINUE)
		return (c);
	switch (sym->st_shndx) {
		case SHN_UNDEF:
			return ('U');
		case SHN_ABS:
			return ('A');
		case SHN_COMMON:
			return ('C');
		default:
			return (INT_CONTINUE);
	}
}

static char get_type_shdr_high(Elf64_Sym *sym, Elf64_Shdr *shdr, char c)
{
	const symbol_type_t *type = symbol_type;
	int size = 24;

	if (c != INT_CONTINUE)
		return (c);
	for (int i = 0; i < size; i++) {
		if (ELF64_ST_TYPE(sym->st_info) == type[i].stt_type &&
			shdr[sym->st_shndx].sh_type == type[i].type &&
			shdr[sym->st_shndx].sh_flags == type[i].flags)
			return (type[i].value);
	}
	return (INT_CONTINUE);
}

char get_type_high(Elf64_Sym *sym,
	Elf64_Shdr *shdr,
	__attribute__((unused)) elf_header_t *info)
{
	char c = INT_CONTINUE;

	c = get_type_st_bind_high(sym, c);
	c = get_type_st_shndx_high(sym, c);
	c = get_type_shdr_high(sym, shdr, c);
	if (c == INT_CONTINUE)
		c = '?';
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}