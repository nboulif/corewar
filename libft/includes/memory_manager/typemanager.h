/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typemanager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEMANAGER_H
# define TYPEMANAGER_H
# include <stdlib.h>
# include "array/array.h"

/*
** item : pointer to data
** next : pointer to next typeitem
** next_oldest : cf oldest in t_typeused
** i_typearray : index of the typearray which possess this typeitem
** n_used : countdown of all contiguous typeitems with the same typeitems in
** 		a t_typeused
*/
typedef struct			s_typeitem
{
	void				*item;
	struct s_typeitem	*next;
	struct s_typeitem	*next_oldest;
	struct s_typeitem	*next_recovery;
	size_t				i_typearray;
	size_t				n_used;
}						t_typeitem;

/*
** typeitem : LIFO pointers to used typeitems
** oldest : Taken all contiguous typeitems with the same i_typearray, the oldest
** 		one is an pointer of this LIFO (other elements are oldests with another
** 		i_typearray)
*/
typedef struct			s_typeused
{
	t_typeitem			*typeitem;
	t_typeitem			*oldest;
	t_typeitem			*recovery;
	t_typeitem			*last;
}						t_typeused;

/*
** array : memory allocation for data
** typeitems : memory allocation for typeitems
** unused : LIFO pointers to unused typeitems
** n_unused : length of unused
*/
typedef struct			s_typearray
{
	t_array				*array;
	t_array				*typeitems;
	t_typeitem			*unused;
	size_t				n_unused;
}						t_typearray;

/*
** typearrays : array of pointers to t_typearray
** i_available : smallest index in typearrays to t_typearray with n_unused > 0
*/
typedef struct			s_typemanager
{
	t_array				*typearrays;
	size_t				i_available;
}						t_typemanager;

/*
** free the t_typearray instance and all its content
*/
void					ft_typearray_free(t_typearray *typearray);

/*
** free the t_typemanager instance and all its content
*/
void					ft_typemanager_free(t_typemanager *typemanager);

/*
** create a t_typearray instance
** return :
**  t_typearray* : created instance
**  NULL : memory error
*/
t_typearray				*ft_typearray_construct(size_t size,
	size_t sizeof_item, size_t typeindex);

/*
** create a t_typemanager instance
** return :
**  t_typemanager* : created instance
**  NULL : memory error
*/
t_typemanager			*ft_typemanager_construct(size_t size,
	size_t sizeof_item);

/*
** this function should not be used externaly unless in case of controlled
** high memory usage
** extend the number of elements that the typearray is able to store
** return :
**  1 : success
**  0 : memory error
*/
int						ft_typemanager_extend_size(t_typemanager *typemanager,
	size_t new_size);

/*
** "free" the previously used items so that the typearray can provide them
** for ulterior usage without the need for actual free/malloc
** return :
**  void
*/
int						ft_typemanager_refill(t_typemanager *typemanager,
	t_typeused *used);

/*
** ask the typearray for a pointer to the stored data type. If none are
** available, double the size of the typearray.
** return :
**  void* : pointer to a fitting space for the data type handled by the
**  typearray
*/
void					*ft_typemanager_get(t_typemanager *typemanager,
	t_typeused *used);

void					*ft_typemanager_get_typeitem(
	t_typemanager *typemanager, t_typeused *used, t_typeitem **item);

void					ft_typeused_initialize(t_typeused *typeused);

void					ft_typeused_recover(t_typeused *typeused,
	t_typeitem *typeitem);

#endif
