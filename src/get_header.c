/*
** EPITECH PROJECT, 2018
** get_headers
** File description:
** 	get_headers file
*/

#include <elf.h>
#include "global_define.h"
#include "global_struct.h"

void *get_program_header(void *elf, elf_header_t *info)
{
	if (info->architecture == VAL32BITS)
		return ((byte_t *) elf + ((Elf32_Ehdr *) elf)->e_phoff);
	return ((byte_t *) elf + ((Elf64_Ehdr *) elf)->e_phoff);
}

void *get_section_header(void *elf, elf_header_t *info)
{
	if (info->architecture == VAL32BITS) {
		return ((byte_t *) elf + ((Elf32_Ehdr *) elf)->e_shoff);
	}
	return ((byte_t *) elf + ((Elf64_Ehdr *) elf)->e_shoff);
}
