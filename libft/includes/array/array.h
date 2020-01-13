/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:30:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 13:30:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include <stdlib.h>
# include "basic_functions/basicft.h"

/*
** items : array of void*
** n_items : number of non-null items in items
** size : actual capacity of items (size >= n_items)
*/
typedef struct			s_array
{
	char				*items;
	size_t				n_items;
	size_t				size;
	size_t				sizeof_item;
}						t_array;

/*
** create a t_array instance
** return :
** 	t_array* : created instance
** 	NULL : error
*/
t_array					*ft_array_construct(size_t size,
	size_t sizeof_item);

/*
** free the t_array instance, but not the items
*/
void					ft_array_free(t_array *array);

/*
** this function should not be used externaly unless in case of controlled
** high memory usage
** extend the number of elements that the array is able to store
** return :
**  1 : success
**  0 : memory error
*/
int						ft_array_extend_size(t_array *array,
	size_t new_size);

/*
** add at the end of the array
** return :
** 	1 : success
** 	-1 : array was not modified
** 	0 : error
*/
int						ft_array_add(t_array *array, void *item);

/*
** insert at index in the array
** WARNING : should be a pointer to the item that has to be stored
** prefer using INJECT if the array has responsibility of the data persistency
** return :
** 	1 : success
** 	-1 : array was not modified
** 	0 : error
*/
int						ft_array_insert(t_array *array, size_t index,
							void *item);

/*
** remove at index in the array
** return :
** 	1 : item was removed
** 	0 : array does not contain item
*/
int						ft_array_remove(t_array *array, size_t index,
	void *removed);

/*
** get the index of item in the array
** return :
** 	unsigned int : index of item
** 	array->n_items : array does not contain item
*/
size_t					ft_array_index(t_array *array, void *item);

/*
** get the item at index
** return :
** 	void* : item at index
** 	NULL : error
*/
void					*ft_array_get(t_array *array, size_t index);

/*
** check if array contains item
** return :
** 	1 : array contains item
** 	0 : array does not contain item
*/
int						ft_array_contains(t_array *array, void *item);

/*
** remove first occurence of item in array
** return :
** 	1 : success
** 	0 : array does not contain item
*/
int						ft_array_remove_first(t_array *array, void *item);

/*
** increase the size of the array if necessary and return a pointer to the last
** element
** WARNING : this is a pointer to a memory segment of items
** return :
** 	void* : pointer to last element of the array
** 	NULL : error
*/
void					*ft_array_inject(t_array *array);

int						ft_array_iteration(void *receiver, t_array *source,
	int (*f)(void *receiver, void *sent));

int						ft_array_fill_copy(t_array *old, t_array *new_array);

int						ft_array_add_typecast(void *receiver, void *sent);

#endif
