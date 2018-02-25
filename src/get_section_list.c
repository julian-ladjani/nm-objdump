/*
** EPITECH PROJECT, 2018
** get_section_list
** File description:
** 	get_section_list file
*/

#include "linked_list.h"
#include "global_struct.h"
#include "global_function.h"

list_t *get_section_list(elf_header_t *info)
{
	section_t *section = get_section_struct(info);
	list_t *list = NULL;

	if (section == PTR_ERROR_RETURN || section == NULL)
		return (NULL);
	list = list_add_tab(list, (list_byte_t *) section, sizeof(section_t),
		(size_t) get_section_number(info));
	free(section);
	return (list);
}