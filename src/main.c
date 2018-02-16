/*
** EPITECH PROJECT, 2018
** main
** File description:
** 	main file
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include <sys/stat.h>
#include "global_define.h"
#include "global_function.h"

void get_files(char **filepath_tab, int tab_size)
{
	int idx = 0;

	for (idx = 0; idx < tab_size; idx++) {
		if (filepath_tab[idx] != NULL) {

		}
	}
}

char            print_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char  c;

	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
	{
		c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'w';
	}
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
	{
		c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			c = 'v';
	}
	else if (sym.st_shndx == SHN_UNDEF)
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

int main(int argc, char **argv)
{
	int fd;
	void *buf;
	Elf64_Shdr *symbol_section;
	Elf64_Ehdr *elf;
	Elf64_Sym *symbol;
	int offset = 0;
	int offset_sym_section = 0;
	int offset_sym = 0;
	char *name;

	fd = get_next_file(argv, argc, &offset);
	fd = get_next_file(argv, argc, &offset);
	buf = read_file(fd);
	elf = buf;
	symbol_section = get_next_symbol_section(buf, VAL64BITS,
						 &offset_sym_section);
	symbol = get_next_symbol(buf, symbol_section, VAL64BITS, &offset_sym);
	while (symbol != PTR_END_RETURN) {
		if (symbol->st_value != 0)
			printf("%016lx ",
			       symbol->st_value);
		else
			printf("                 ");
		printf("%c ", print_type(*symbol, get_section_header(elf,
								     VAL64BITS)));
		name = get_symbol_name(elf, VAL64BITS, offset_sym_section - 1,
				       symbol->st_name);
		if (name != NULL)
			printf("%s\n", name);
		else
			printf("\n");
		symbol = get_next_symbol(buf, symbol_section, VAL64BITS,
					 &offset_sym);
	}
}

/*
 * if (buf != PTR_ERROR_RETURN) {
		printf("mmap(%s) : %8p\n", argv[1], buf);
		printf("elf size: %ld buf size: %ld\n", sizeof(*elf),
		       sizeof(buf));
		elf = buf;
		printf("Section Header Table : addr = %08lx, nb = %d\n",
		       elf->e_shoff, elf->e_shnum);
		shdr = buf + elf->e_shoff;
		phdr = buf + elf->e_phoff;
		for (int i = 0; i < elf->e_shnum; i++)
			if (shdr[i].sh_type == SHT_SYMTAB) {
				sym = (Elf64_Sym *) (buf + shdr[i].sh_offset);
				for (int j = 0; j < (shdr[i].sh_size / shdr[i]
					.sh_entsize); j++) {
					if (sym->st_name > SHN_UNDEF &&
						sym->st_info !=  4) {
						//printf("%u ", sym->st_size);
						if (sym->st_value != 0)
							printf("%016lx ",
							       sym->st_value);
						else
							printf("                 ");
						printf("%u ", sym->st_info);
						printf("%s\n",
						       get_symbol_name(elf,
								       VAL64BITS, i, sym->st_name));
					}
					sym++;
				}
			}
	}
 */