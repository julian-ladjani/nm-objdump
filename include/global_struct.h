/*
** EPITECH PROJECT, 2018
** global_struct
** File description:
** 	global_struct header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H
#define PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H

#include <stdint.h>

typedef struct {
	char *name;
	char type;
	uintptr_t address;
} symbol_t;

#endif //PSU_2017_NMOBJDUMP_GLOBAL_STRUCT_H
