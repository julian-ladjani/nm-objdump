/*
** EPITECH PROJECT, 2018
** main
** File description:
** 	main file
*/

#include <stdio.h>
#include <global_struct.h>
#include "global_struct.h"
#include "global_function.h"

void clean_func(void *symbol_void)
{
	symbol_t *symbol = symbol_void;

	if (symbol != NULL)
		free(symbol);
}

void print_list(void *elem)
{
	symbol_t *symbol = (symbol_t *) elem;
	int nb_address_char = 0;

	if (symbol->name != NULL && symbol->info != 4) {
		nb_address_char = (symbol->architecture == VAL64BITS) ? 16 : 8;
		if (symbol->type != 'w' && symbol->type != 'U' &&
			symbol->type != 'u')
			printf("%0*lx ", nb_address_char,
				symbol->address);
		else
			printf("%*s ", nb_address_char, "");
		printf("%c ", symbol->type);
		printf("%s\n", symbol->name);
	}
}

void print_file(elf_header_t *info, int nb_file)
{
	list_t *list = NULL;

	if (info->buffer != PTR_ERROR_RETURN &&
		info->endianness != BIGENDIAN) {
		list = get_symbol_list(info->buffer, info);
		if (list != NULL && list != PTR_ERROR_RETURN) {
			if (nb_file > 1)
				printf("%s:\n", info->file_path);
			list_dump(list, print_list);
			list_delete_all(list, clean_func);
		}
	}
}

int main(int ac, char **av)
{
	int av_offset = 1;
	int nb_file = count_file(av + 1, ac - 1);
	int file_index = 0;
	int fd;
	elf_header_t info;
	int error = 0;

	fd = get_next_file(av, ac, &av_offset);
	while (fd != INT_END_RETURN) {
		file_index++;
		info.file_path = (ac < 2) ? DEFAULT_FILE : av[av_offset - 1];
		if (fd != INT_ERROR_RETURN)
			error = check_file(fd, &info);
		if (fd != INT_ERROR_RETURN && error == 0) {
			if (file_index != 1)
				printf("\n");
			print_file(&info, nb_file);
		}
		fd = get_next_file(av, ac, &av_offset);
	}
}