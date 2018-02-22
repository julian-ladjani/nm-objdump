/*
** EPITECH PROJECT, 2018
** fill_symbol_struct
** File description:
** 	fill_symbol_struct file
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global_struct.h"
#include "global_function.h"

int strcmp_alphanum(char const *a, char const *b)
{
	int index_a = 0;
	int index_b = 0;

	while (a[index_a] != '\0' && b[index_b] != '\0') {
		while (char_is_letter(a[index_a]) > 1)
			index_a++;
		while (char_is_letter(b[index_b]) > 1)
			index_b++;
		if (tolower(a[index_a]) != tolower(b[index_b]))
			return (tolower(a[index_a]) - tolower(b[index_b]));
		if (a[index_a] != '\0')
			index_a++;
		if (b[index_b] != '\0')
			index_b++;
	}
	while (char_is_letter(a[index_a]) > 1)
		index_a++;
	while (char_is_letter(b[index_b]) > 1)
		index_b++;
	return (tolower(a[index_a]) - tolower(b[index_b]));
}

int compare_symbol(void const *a, void const *b)
{
	const symbol_t *pa = a;
	const symbol_t *pb = b;
	int cmp = 0;

	if (pa->name == pb->name)
		return (0);
	if (pa->name == NULL)
		return (1);
	if (pb->name == NULL)
		return (-1);
	cmp = strcmp_alphanum(pa->name, pb->name);
	if (cmp == 0)
		return ((int) strlen(pa->name) - (int) strlen(pb->name));
	return (cmp);
}
