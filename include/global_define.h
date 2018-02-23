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

	#define BFD_NO_FLAGS 0x00
	#define HAS_RELOC 0x01
	#define EXEC_P 0x02
	#define HAS_LINENO 0x04
	#define HAS_DEBUG 0x08
	#define HAS_SYMS 0x10
	#define HAS_LOCALS 0x20
	#define DYNAMIC 0x40
	#define WP_TEXT 0x80
	#define D_PAGED 0x100


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
