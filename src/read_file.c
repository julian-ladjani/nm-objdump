/*
** EPITECH PROJECT, 2018
** read_files
** File description:
** 	read_files file
*/

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "global_define.h"

int count_file(char **file_path_tab, int tab_size)
{
	int nb_file = 0;

	for (int idx = 0; idx < tab_size; idx++) {
		if (file_path_tab[idx] != NULL &&
			file_path_tab[idx][0] != '-')
			nb_file++;
	}
	return (nb_file);
}

int open_file(char *file_path)
{
	int fd = 0;
	char *error_string = NULL;

	fd = open(file_path, O_RDONLY);
	if (fd == -1) {
		error_string = strerror(errno);
		if (strcmp(error_string, "No such file or directory") == 0)
			error_string = "No such file";
		printf("%s: '%s': %s\n", PROGRAM_NAME, file_path,
			error_string);
		return (INT_ERROR_RETURN);
	}
	return (fd);
}

static int check_file_type(struct stat *s, char *file_path)
{
	if (!S_ISREG(s->st_mode)) {
		printf("%s: Warning: '%s' %s\n", PROGRAM_NAME, file_path,
			"is not an ordinary file");
		return (INT_ERROR_RETURN);
	}
	return (0);
}

void *read_file(int fd, char *file_path)
{
	void *buf = MAP_FAILED;
	struct stat s;
	int error = 0;

	if (fd != INT_ERROR_RETURN && fd != INT_END_RETURN) {
		error = fstat(fd, &s);
		if (error == -1)
			printf("%s: '%s' %s\n", PROGRAM_NAME, file_path,
				strerror(errno));
		else
			error = check_file_type(&s, file_path);
		if (error == 0)
			buf = mmap(NULL, s.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0);
		if (buf == MAP_FAILED || ((char *) buf)[0] == 0)
			return (PTR_ERROR_RETURN);
		return (buf);
	}
	return (PTR_ERROR_RETURN);
}

int get_next_file(char **file_path_tab, int tab_size, int *offset)
{
	int fd = 0;

	if (tab_size == 1 && *offset == 1) {
		fd = open_file(DEFAULT_FILE);
		*offset += 1;
		return fd;
	}
	for (int idx = *offset; idx < tab_size; idx++) {
		*offset = idx + 1;
		if (file_path_tab == NULL) {
			fd = open_file(DEFAULT_FILE);
			return fd;
		} else if (file_path_tab[idx] != NULL &&
			file_path_tab[idx][0] != '-') {
			fd = open_file(file_path_tab[idx]);
			return fd;
		}
	}
	return (INT_END_RETURN);
}