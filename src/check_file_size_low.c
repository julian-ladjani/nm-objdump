/*
** EPITECH PROJECT, 2018
** check_file_size
** File description:
** 	check_file_size file
*/

#include <elf.h>
#include "global_struct.h"

static int check_all_sections(elf_header_t *info)
{
	Elf32_Ehdr *elf = (Elf32_Ehdr *) info->buffer;
	Elf32_Shdr *shdr = (Elf32_Shdr *) (info->buffer + elf->e_shoff);

	if (elf->e_ehsize + (elf->e_phnum * elf->e_phentsize) +
		(elf->e_shnum * elf->e_shentsize) > info->size)
		return (INT_ERROR_RETURN);
	if ((byte_t *) shdr > info->end)
		return (INT_ERROR_RETURN);
	if ((byte_t *) (shdr + (elf->e_shnum)) > info->end)
		return (INT_ERROR_RETURN);
	return (0);
}

int check_file_size_low(elf_header_t *info)
{
	if (check_all_sections(info) == INT_ERROR_RETURN)
		return (INT_ERROR_RETURN);
	return (0);
}