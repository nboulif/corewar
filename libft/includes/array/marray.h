/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:29:42 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:29:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARRAY_H
# define MARRAY_H
# include "array/array.h"
# include "memory_manager/memanager.h"

typedef struct			s_marray
{
	t_array				array;
	t_memanager			*mmng;
}						t_marray;

int						ft_marray_initialize(t_marray *marray, t_memanager
	*mmng, size_t size, size_t sizeof_item);

t_marray				*ft_marray_construct(t_memanager *mmng, size_t size,
	size_t sizeof_item);

void					ft_marray_empty(t_marray *marray);

void					ft_marray_free(t_marray *marray);

int						ft_marray_extend_size(t_marray *marray,
	size_t new_size);

int						ft_marray_add(t_marray *marray, void *item);

int						ft_marray_insert(t_marray *marray, size_t index,
	void *item);

void					*ft_marray_inject(t_marray *marray);

int						ft_marray_add_typecast(void *receiver, void *sent);

int						ft_array_fill_mcopy(t_array *old, t_marray *new_marray);

#endif
