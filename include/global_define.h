/*
** EPITECH PROJECT, 2018
** global_define
** File description:
** 	global_define header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H
#define PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H

#define INT_ERROR_RETURN (-84)
#define PROGRAM_ERROR_EXIT 84
#define PTR_ERROR_RETURN ((void *) -1)
#define PTR_END_RETURN ((void *) -2)

typedef char byte_t;

typedef enum {
	VAL32BITS,
	VAL64BITS
} data_unit_t;

#endif //PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H
