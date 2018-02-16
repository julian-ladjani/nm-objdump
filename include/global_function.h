/*
** EPITECH PROJECT, 2018
** global_function
** File description:
** 	global_function header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H
#define PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H

#include <elf.h>

int get_next_file(char **file_path_tab, int tab_size, int *offset);

void *read_file(int fd);
void *get_program_header(void *elf, data_unit_t nb_bits);
void *get_section_header(void *elf, data_unit_t nb_bits);
void *get_section(void *elf, data_unit_t nb_bits, int index);
void *get_next_symbol_section(void *elf, data_unit_t nb_bits, int *offset);
void *get_next_symbol(void *elf,
		      void *symbol_section,
		      data_unit_t nb_bits,
		      int *offset);

char *get_section_name(void *elf, data_unit_t nb_bits, int offset);
char *get_symbol_name(void *elf,
		      data_unit_t nb_bits,
		      int symbol_index,
		      int name_index);

Elf64_Ehdr *get_file_header(void *buf);

#endif //PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H
