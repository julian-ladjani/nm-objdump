/*
** EPITECH PROJECT, 2018
** get_section_struct
** File description:
** 	get_section_struct file
*/

#include <elf.h>
#include <global_struct.h>
#include "global_struct.h"
#include "global_function.h"

static section_t *get_section_struct_low(elf_header_t *info)
{
	section_t *section_struct = NULL;
	int nb_section = get_section_number(info);
	Elf32_Shdr *section = NULL;

	section_struct = malloc(sizeof(section_t) * nb_section);
	if (section_struct == NULL)
		return (PTR_ERROR_RETURN);
	for (int i = 1; i <= nb_section; i++) {
		section = get_section(info->buffer, info, i);
		section_struct[i - 1].name = get_section_name(info->buffer,
			info, section->sh_name);
		section_struct[i - 1].address = section->sh_addr;
		section_struct[i - 1].data =
			(unsigned char *) info->buffer + section->sh_offset;
		section_struct[i - 1].size = section->sh_size;
	}
	return (section_struct);
}

static section_t *get_section_struct_high(elf_header_t *info)
{
	section_t *section_struct = NULL;
	int nb_section = get_section_number(info);
	Elf64_Shdr *section = NULL;

	section_struct = malloc(sizeof(section_t) * nb_section);
	if (section_struct == NULL)
		return (PTR_ERROR_RETURN);
	for (int i = 1; i <= nb_section; i++) {
		section = get_section(info->buffer, info, i);
		section_struct[i - 1].name = get_section_name(info->buffer,
			info, section->sh_name);
		section_struct[i - 1].address = section->sh_addr;
		section_struct[i - 1].data =
			(unsigned char *) info->buffer + section->sh_offset;
		section_struct[i - 1].size = section->sh_size;
	}
	return (section_struct);
}

section_t *get_section_struct(elf_header_t *info)
{
	if (info->architecture == VAL32BITS)
		return (get_section_struct_low(info));
	return (get_section_struct_high(info));
}