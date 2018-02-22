/*
** EPITECH PROJECT, 2018
** global_struct
** File description:
** 	global_struct header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H
#define PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H

#include <stdint.h>
#include <unistd.h>
#include "global_define.h"

typedef struct {
	char *name;
	char type;
	char info;
	uintptr_t address;
	data_unit_t architecture;
} symbol_t;

typedef struct {
	byte_t *buffer;
	char *file_path;
	int fd;
	data_unit_t architecture;
	endianness_t endianness;
	off_t size;
} elf_header_t;

#endif //PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H
