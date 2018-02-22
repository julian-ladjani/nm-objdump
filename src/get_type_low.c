/*
** EPITECH PROJECT, 2018
** get_type
** File description:
** 	get_type file
*/

#include <elf.h>
#include "global_define.h"
#include "global_function.h"

static char get_type_st_bind_low(Elf32_Sym *sym, char c)
{
	if (c != INT_CONTINUE)
		return (c);
	switch (ELF32_ST_BIND(sym->st_info)) {
		case STB_GNU_UNIQUE:
			return ('u');
		case STB_WEAK:
			if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT) {
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

static char get_type_st_shndx_low(Elf32_Sym *sym, char c)
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

static char get_type_shdr_low(Elf32_Sym *sym, Elf32_Shdr *shdr, char c)
{
	if (c != INT_CONTINUE)
		return (c);
	if ((&shdr[sym->st_shndx])->sh_type == SHT_NOBITS)
		if (shdr[sym->st_shndx].sh_flags == (SHF_ALLOC + SHF_WRITE))
			return ('B');
	if ((&shdr[sym->st_shndx])->sh_type == SHT_PROGBITS) {
		if ((&shdr[sym->st_shndx])->sh_flags ==
			(SHF_ALLOC + SHF_WRITE))
			return ('D');
		if ((&shdr[sym->st_shndx])->sh_flags == (SHF_ALLOC +
			SHF_EXECINSTR))
			return ('T');
		return ('R');
	}
	if ((&shdr[sym->st_shndx])->sh_type == SHT_DYNAMIC &&
		(&shdr[sym->st_shndx])->sh_flags == (SHF_ALLOC + SHF_WRITE))
		return ('D');
	return ('T');
}

char get_type_low(Elf32_Sym *sym,
	Elf32_Shdr *shdr,
	__attribute__((unused)) elf_header_t *info)
{
	char c = INT_CONTINUE;

	c = get_type_st_bind_low(sym, c);
	c = get_type_st_shndx_low(sym, c);
	c = get_type_shdr_low(sym, shdr, c);
	if (c == INT_CONTINUE)
		c = '?';
	if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return c;
}