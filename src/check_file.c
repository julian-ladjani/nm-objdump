/*
** EPITECH PROJECT, 2018
** check_file
** File description:
** 	check_file file
*/

#include <stdio.h>
#include "global_struct.h"
#include "global_function.h"

static int check_file_size(int fd, elf_header_t *info)
{
	info->size = lseek(fd, 0, SEEK_END);
	if ((off_t) info->size < (off_t) sizeof(Elf64_Ehdr)) {
		printf("%s: %s: File truncated\n",
			PROGRAM_NAME, info->file_path);
		return (INT_ERROR_RETURN);
	}
	return (0);
}

static int check_file_type(Elf64_Ehdr *elf, elf_header_t *info)
{
	if (elf->e_ident[EI_MAG0] != 0x7F || elf->e_ident[EI_MAG1] != 'E' ||
		elf->e_ident[EI_MAG2] != 'L' ||
		elf->e_ident[EI_MAG3] != 'F') {
		printf("%s: %s: File format not recognized\n",
			PROGRAM_NAME, info->file_path);
		return (INT_ERROR_RETURN);
	}
	return (0);
}

int check_file_size_all(elf_header_t *info)
{
	int error = 0;

	if (info->architecture == VAL32BITS)
		error = check_file_size_low(info);
	else
		error = check_file_size_high(info);
	if (error == INT_ERROR_RETURN)
		printf("%s: %s: File truncated\n",
			PROGRAM_NAME, info->file_path);
	return (error);
}

int check_file(int fd, elf_header_t *info)
{
	Elf64_Ehdr *elf;

	info->buffer = read_file(fd, info->file_path);
	info->flags = 0;
	if (info->buffer == PTR_ERROR_RETURN)
		return (INT_ERROR_RETURN);
	elf = (Elf64_Ehdr *) info->buffer;
	if (check_file_size(fd, info))
		return (INT_ERROR_RETURN);
	close(fd);
	if (check_file_type(elf, info) == INT_ERROR_RETURN)
		return (INT_ERROR_RETURN);
	info->architecture =
		(elf->e_ident[EI_CLASS] == 1) ? VAL32BITS : VAL64BITS;
	info->endianness =
		(elf->e_ident[EI_DATA] == 1) ? LITTLEENDIAN : BIGENDIAN;
	info->end = info->buffer + info->size;
	return (check_file_size_all(info));
}
