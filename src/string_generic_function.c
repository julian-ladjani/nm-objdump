/*
** EPITECH PROJECT, 2018
** string_generic_function
** File description:
** 	string_generic_function file
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int char_is_letter(char c)
{
	if (c == '\0')
		return (0);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '0'))
		return (1);
	return (2);
}

char *get_string_only_letter(char *str)
{
	char *str_only_letter = NULL;
	int str_only_letter_idx = 0;
	int len;

	if (str == NULL)
		return (NULL);
	len = strlen(str);
	if (len <= 0)
		return (NULL);
	str_only_letter = malloc(len * sizeof(char) + 1);
	if (str_only_letter == NULL)
		return (NULL);
	memset(str_only_letter, 0, len * sizeof(char) + 1);
	for (int idx = 0; str[idx] != '\0'; idx++) {
		if (char_is_letter(str[idx]) == 1) {
			str_only_letter[str_only_letter_idx] = str[idx];
			str_only_letter_idx++;
		}
	}
	return (str_only_letter);
}