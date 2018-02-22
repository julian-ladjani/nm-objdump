/*
** EPITECH PROJECT, 2018
** global_define
** File description:
** 	global_define header
*/

#ifndef PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H

	#define INT_ERROR_RETURN (-84)
	#define PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H
	#define INT_END_RETURN (-42)
	#define INT_CONTINUE (-24)
	#define PROGRAM_ERROR_EXIT (84)
	#define PTR_ERROR_RETURN ((void *) -1)
	#define PTR_END_RETURN ((void *) -2)

	#define DEFAULT_FILE "a.out"

typedef char byte_t;

typedef enum {
	VAL32BITS,
	VAL64BITS
} data_unit_t;

typedef enum {
	LITTLEENDIAN,
	BIGENDIAN
} endianness_t;

typedef enum {
	INFO,
	WARNING,
	ERROR,
	CRITICAL
} error_message_t;

#endif //PSU_2017_NMOBJDUMP_GLOBAL_DEFINE_H
