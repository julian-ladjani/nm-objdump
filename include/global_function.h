/*
** EPITECH PROJECT, 2018
** global_function
** File description:
** 	global_function header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H
#define PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H

#include <elf.h>
#include "linked_list.h"
#include "global_struct.h"
#include "global_define.h"

int get_next_file(char **file_path_tab, int tab_size, int *offset);

void *read_file(int fd, char *file_path);
void *get_program_header(void *elf, elf_header_t *info);
void *get_section_header(void *elf, elf_header_t *info);
void *get_section(void *elf, elf_header_t *info, int index);
void *get_next_symbol_section(void *elf, elf_header_t *info, int *offset);
void *get_next_symbol(void *elf,
		      void *symbol_section,
		      elf_header_t *info,
		      int *offset);

char *get_section_name(void *elf, elf_header_t *info, int offset);
char *get_symbol_name(void *elf,
		      elf_header_t *info,
		      int symbol_index,
		      int name_index);
char *get_string_only_letter(char *str);

Elf64_Ehdr *get_file_header(void *buf);
symbol_t *get_symbol_struct(void *elf,
			    elf_header_t *info,
			    void *symbol_section,
			    int section_index);
list_t *get_symbol_list(void *elf,
			elf_header_t *info);
int count_file(char **file_path_tab, int tab_size);
int char_is_letter(char c);
char get_type_high(Elf64_Sym *sym, Elf64_Shdr *shdr, elf_header_t *info);
char get_type_low(Elf32_Sym *sym, Elf32_Shdr *shdr, elf_header_t *info);
int get_symbol_number(void *symbol_section, elf_header_t *info);
int compare_symbol(void const *a, void const *b);

#endif //PSU_2017_NMOBJDUMP_GLOBAL_FUNCTION_H
