/*
** EPITECH PROJECT, 2018
** print_content
** File description:
** 	print_content file
*/

#include <stdio.h>
#include <ctype.h>
#include <global_struct.h>
#include "objdump_function.h"

static void print_list_ascii(section_t *section, int index, int index_start)
{
	int spaces = index;
	while (spaces % 16 != 0) {
		if (spaces % 4 == 0 && spaces % 16 > 0)
			printf(" ");
		printf("  ");
		spaces++;
	}
	printf("  ");
	while (index_start < index) {
		if (isprint(section->data[index_start]))
			printf("%c", section->data[index_start]);
		else
			printf(".");
		index_start++;
	}
	printf("\n");
}

static int check_section(section_t *section)
{
	if (section->size != 0 &&
		strcmp(section->name, ".bss") != 0 &&
		strcmp(section->name, ".strtab") != 0 &&
		strcmp(section->name, ".shstrtab") != 0 &&
		strcmp(section->name, ".symtab") != 0) {
		return (1);
	}
	return (0);
}

void print_list(void *elem)
{
	section_t *section = (section_t *) elem;
	unsigned int i = 0;
	int i_start = i;

	if (check_section(elem) == 0)
		return;
	printf("Contents of section %s:\n", section->name);
	while (i < section->size) {
		if (i % 16 == 0)
			printf(" %04x ", (unsigned) (section->address + i));
		printf("%02x", section->data[i]);
		i++;
		if (i % 4 == 0 && i % 16 > 0 && i < section->size)
			printf(" ");
		if (i % 16 == 0 || i >= section->size) {
			print_list_ascii(section, i, i_start);
			i_start = i;
		}
	}
}
