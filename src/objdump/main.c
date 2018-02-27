/*
** EPITECH PROJECT, 2018
** main
** File description:
** 	main file
*/

#include <stdio.h>
#include "global_struct.h"
#include "objdump_function.h"

void clean_func(void *section_void)
{
	section_t *section = section_void;

	if (section != NULL)
		free(section);
}

void print_header_low(elf_header_t *info)
{
	Elf32_Ehdr *elf = (Elf32_Ehdr *) info->buffer;

	printf("\n%s:%5cfile format %s-%s\n", info->file_path, ' ',
		"elf32", get_elf_sub_format_low(elf));
	printf("architecture: %s, flags 0x%08x:\n",
		get_elf_architecture_low(elf), info->flags);
	get_flags_string(info->flags);
	printf("start address 0x%08x\n\n", elf->e_entry);
}

void print_header_high(elf_header_t *info)
{
	Elf64_Ehdr *elf = (Elf64_Ehdr *) info->buffer;

	printf("\n%s:%5cfile format %s-%s\n", info->file_path, ' ',
		"elf64", get_elf_sub_format_high(elf));
	printf("architecture: %s, flags 0x%08x:\n",
		get_elf_architecture_high(elf), info->flags);
	get_flags_string(info->flags);
	printf("start address 0x%016lx\n\n", elf->e_entry);
}

void print_file(__attribute((unused)) elf_header_t *info,
	__attribute((unused)) int nb_file)
{
	if (info->buffer != PTR_ERROR_RETURN &&
		info->endianness != BIGENDIAN) {
		list_t *list = get_section_list(info);
		if (info->architecture == VAL32BITS)
			print_header_low(info);
		else
			print_header_high(info);
		list_dump(list, print_list);
		list_delete_all(list, clean_func);
	}
}

int main(int ac, char **av)
{
	int av_offset = 1;
	int nb_file = count_file(av + 1, ac - 1);
	int file_index = 0;
	int fd;
	elf_header_t info;
	int return_value = 0;

	fd = get_next_file(av, ac, &av_offset);
	while (fd != INT_END_RETURN) {
		file_index++;
		info.file_path = (ac < 2) ? DEFAULT_FILE : av[av_offset - 1];
		if (fd != INT_ERROR_RETURN && check_file(fd, &info) == 0)
			print_file(&info, nb_file);
		else
			return_value = PROGRAM_ERROR_EXIT;
		fd = get_next_file(av, ac, &av_offset);
	}
	return (return_value);
}
