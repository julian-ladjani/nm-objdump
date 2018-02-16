/*
** EPITECH PROJECT, 2018
** read_files
** File description:
** 	read_files file
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "global_define.h"

void *read_file(int fd)
{
	void *buf;
	struct stat s;

	if (fd != -1) {
		fstat(fd, &s);
		buf = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		close(fd);
		if (buf == MAP_FAILED)
			return (PTR_ERROR_RETURN);
		return (buf);
	}
	return (PTR_ERROR_RETURN);
}

int get_next_file(char **file_path_tab, int tab_size, int *offset)
{
	int fd = 0;

	for (int idx = *offset; idx < tab_size; idx++) {
		if (file_path_tab[idx] != NULL) {
			fd = open(file_path_tab[idx], O_RDONLY);
			*offset = idx + 1;
			return fd;
		}
	}
	return (INT_ERROR_RETURN);
}