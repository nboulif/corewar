/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:28:08 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:28:10 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_marray_extend_size(t_marray *marray, size_t new_size)
{
	char			*items;
	t_array			*array;

	array = (t_array*)marray;
	if (new_size <= array->size)
		return (0);
	if (!(items = ft_memanager_get(marray->mmng,
		new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * array->n_items);
	ft_memanager_refill(marray->mmng, array->items);
	array->items = items;
	array->size = new_size;
	return (1);
}

static int			ft_marray_extend_size_skip(t_marray *marray,
	size_t new_size, size_t skip_from)
{
	char			*items;
	t_array			*array;

	array = (t_array*)marray;
	if (new_size <= array->size || skip_from >= array->n_items)
		return (0);
	if (!(items = ft_memanager_get(marray->mmng,
		new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * skip_from);
	ft_memmove(&items[(skip_from + 1) * array->sizeof_item],
		&array->items[skip_from * array->sizeof_item],
		array->sizeof_item * (array->n_items - skip_from));
	ft_memanager_refill(marray->mmng, array->items);
	array->items = items;
	array->size = new_size;
	return (1);
}

int					ft_marray_add(t_marray *marray, void *item)
{
	t_array			*array;

	array = (t_array*)marray;
	if (!item)
		return (-1);
	if (array->n_items >= array->size && !ft_marray_extend_size(marray,
		2 * array->size))
		return (0);
	ft_memmove(&array->items[array->n_items * array->sizeof_item], item,
		array->sizeof_item);
	array->n_items++;
	return (1);
}

int					ft_marray_insert(t_marray *marray, size_t index,
	void *item)
{
	size_t			i;
	t_array			*array;

	array = (t_array*)marray;
	if (index > array->n_items)
		return (0);
	if (!item)
		return (-1);
	if (index == array->n_items)
		return (ft_marray_add(marray, item));
	i = array->n_items;
	if (array->n_items >= array->size)
	{
		if (!ft_marray_extend_size_skip(marray,
			2 * array->size, index))
			return (0);
	}
	else
		while (i-- > index)
			ft_memmove(&array->items[(i + 1) * array->sizeof_item],
				&array->items[i * array->sizeof_item], array->sizeof_item);
	ft_memmove(&array->items[index * array->sizeof_item], item,
		array->sizeof_item);
	array->n_items++;
	return (1);
}

void				*ft_marray_inject(t_marray *marray)
{
	t_array			*array;

	array = (t_array*)marray;
	if (array->n_items >= array->size && !ft_marray_extend_size(marray,
		2 * array->size))
		return (NULL);
	array->n_items++;
	return (ft_array_get(array, array->n_items - 1));
}
