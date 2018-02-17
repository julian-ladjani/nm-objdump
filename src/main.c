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
#include <global_struct.h>
#include "linked_list.h"
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

/*int main(int argc, char **argv)
{
	int fd;
	void *buf;
	Elf64_Shdr *symbol_section;
	Elf64_Ehdr *elf;
	Elf64_Sym *symbol;
	int offset = 0;
	int offset_sym_section = 0;
	symbol_t *symbol_struct;

	fd = get_next_file(argv, argc, &offset);
	fd = get_next_file(argv, argc, &offset);
	buf = read_file(fd);
	elf = buf;
	symbol_section = get_next_symbol_section(buf, VAL64BITS,
						 &offset_sym_section);
	symbol_struct = get_symbol_struct(elf, VAL64BITS, symbol_section,
					  offset_sym_section - 1);
	for (int i = 0; i < get_symbol_number(symbol_section, VAL64BITS); i++) {
		if (symbol_struct[i].name != NULL) {
			if (symbol_struct[i].address != 0)
				printf("%016lx ",
				       symbol_struct[i].address);
			else
				printf("                 ");
			printf("%c ", 'A');
			printf("%s\n", symbol_struct[i].name);
		}
	}
	printf("%d\n", sizeof(symbol_struct) / sizeof(symbol_t));
	free(symbol_struct);
}*/

int main(int ac, char **av)
{
	list_t *list = NULL;
	list_t *tmp_list;
	for (int idx = 0; idx < ac; idx++) {
		list = list_add_elem_at_pos(list, av[idx], LIST_END);
	}
	//list_swap(list->next, list->next->next->next);
	//list_clean_at_pos(list, LIST_BEFORE);
	//list = list_sort(list, strcmp);
	list = list_delete_at_pos(list, LIST_AFTER);
	tmp_list = list;
	while (list != NULL) {
		if (list->elem == NULL)
			printf("%s\n", "deleted");
		else
			printf("%s\n", list->elem);
		list = list->next;
	}
	list_delete_all(tmp_list);
	//printf("%s\n", list_get_elem_at_pos(list, 1)->elem);
}