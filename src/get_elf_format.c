/*
** EPITECH PROJECT, 2018
** get_elf_format
** File description:
** 	get_elf_format file
*/

#include <elf.h>

char *get_elf_sub_format_low(Elf32_Ehdr *elf)
{
	if (elf->e_ident[EI_DATA] == 2)
		return "big";
	if (elf->e_ident[EI_CLASS] == 2 &&
		elf->e_machine == 0x3e)
		return "x86-64";
	if (elf->e_ident[EI_CLASS] == 1 &&
		elf->e_machine == 0x03)
		return "i386";
	return "little";
}

char *get_elf_sub_format_high(Elf64_Ehdr *elf)
{
	if (elf->e_ident[EI_DATA] == 2)
		return "big";
	if (elf->e_ident[EI_CLASS] == 2 &&
		elf->e_machine == 0x3e)
		return "x86-64";
	if (elf->e_ident[EI_CLASS] == 1 &&
		elf->e_machine == 0x03)
		return "i386";
	return "little";
}

char *get_elf_architecture_low(Elf32_Ehdr *elf)
{
	if (elf->e_ident[EI_DATA] == 2)
		return "UNKNOWN!";
	if (elf->e_ident[EI_CLASS] == 2 && elf->e_machine == 0x3e)
		return "i386:x86-64";
	if (elf->e_ident[EI_CLASS] == 1 && elf->e_machine == 0x03)
		return "i386";
	return "UNKNOWN!";
}

char *get_elf_architecture_high(Elf64_Ehdr *elf)
{
	if (elf->e_ident[EI_DATA] == 2)
		return "UNKNOWN!";
	if (elf->e_ident[EI_CLASS] == 2 && elf->e_machine == 0x3e)
		return "i386:x86-64";
	if (elf->e_ident[EI_CLASS] == 1 && elf->e_machine == 0x03)
		return "i386";
	return "UNKNOWN!";
}
