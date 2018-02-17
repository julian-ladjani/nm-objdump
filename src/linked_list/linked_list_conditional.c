/*
** EPITECH PROJECT, 2018
** linked_list_conditional
** File description:
** 	linked_list_conditional file
*/

#include "linked_list.h"

list_t *list_get_elem_if_exist(list_t *list, list_t *elem)
{
	if (elem != NULL && list_get_elem(list, elem))
		return (elem);
	return (list);
}

list_t *list_get_elem_if_not_exist(list_t *list, list_t *elem)
{
	if (elem == NULL || list_get_elem(list, elem) == NULL)
		return (elem);
	return (list);
}