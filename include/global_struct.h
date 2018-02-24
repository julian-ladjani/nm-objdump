/*
** EPITECH PROJECT, 2018
** global_struct
** File description:
** 	global_struct header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H

	#include <stdint.h>
	#include <unistd.h>
	#include "global_define.h"

	#define PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H

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
	unsigned int flags;
	data_unit_t architecture;
	endianness_t endianness;
	off_t size;
} elf_header_t;

typedef struct {
	unsigned int type;
	unsigned int stt_type;
	unsigned int flags;
	char value;
} symbol_type_t;

typedef struct {
	char *name;
	size_t size;
	uintptr_t address;
	unsigned char *data;
	data_unit_t architecture;
} section_t;

#endif //PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H
