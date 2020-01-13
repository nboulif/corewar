/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:28:14 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:28:15 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_marray_initialize(t_marray *marray, t_memanager *mmng,
	size_t size, size_t sizeof_item)
{
	if (!marray || !mmng)
		return (-1);
	if (size > 0 && sizeof_item > 0)
	{
		marray->array.items = ft_memanager_get(mmng, size * sizeof_item);
		marray->array.size = size;
		marray->array.sizeof_item = sizeof_item;
	}
	else
	{
		marray->array.items = ft_memanager_get(mmng, sizeof(void*));
		marray->array.size = 1;
		marray->array.sizeof_item = sizeof(void*);
	}
	if (!marray->array.items)
		return (0);
	marray->array.n_items = 0;
	marray->mmng = mmng;
	return (1);
}

t_marray			*ft_marray_construct(t_memanager *mmng, size_t size,
	size_t sizeof_item)
{
	t_marray		*marray;

	if (!mmng ||
		!(marray = (t_marray*)ft_memanager_get(mmng, sizeof(t_marray))))
		return (NULL);
	if (1 > ft_marray_initialize(marray, mmng, size, sizeof_item))
	{
		ft_memanager_refill(mmng, marray);
		return (NULL);
	}
	return (marray);
}

void				ft_marray_empty(t_marray *marray)
{
	if (!marray)
		return ;
	ft_memanager_refill(marray->mmng, marray->array.items);
}

void				ft_marray_free(t_marray *marray)
{
	ft_marray_empty(marray);
	ft_memanager_refill(marray->mmng, marray);
}
