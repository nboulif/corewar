/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:51:16 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 14:51:17 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_array_extend_size(t_array *array, size_t new_size)
{
	char			*items;

	if (new_size <= array->size)
		return (0);
	if (!(items = malloc(new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * array->n_items);
	free(array->items);
	array->items = items;
	array->size = new_size;
	return (1);
}

static int			ft_array_extend_size_skip(t_array *array,
	size_t new_size, size_t skip_from)
{
	char			*items;

	if (new_size <= array->size || skip_from >= array->n_items)
		return (0);
	if (!(items = malloc(new_size * array->sizeof_item)))
		return (0);
	ft_memmove(items, array->items, array->sizeof_item * skip_from);
	ft_memmove(&items[(skip_from + 1) * array->sizeof_item],
		&array->items[skip_from * array->sizeof_item],
		array->sizeof_item * (array->n_items - skip_from));
	free(array->items);
	array->items = items;
	array->size = new_size;
	return (1);
}

int					ft_array_add(t_array *array, void *item)
{
	if (!item)
		return (-1);
	if (array->n_items >= array->size && !ft_array_extend_size(array,
		2 * array->size))
		return (0);
	ft_memmove(&array->items[array->n_items * array->sizeof_item], item,
		array->sizeof_item);
	array->n_items++;
	return (1);
}

int					ft_array_insert(t_array *array, size_t index,
	void *item)
{
	size_t			i;

	if (index > array->n_items)
		return (0);
	if (!item)
		return (-1);
	if (index == array->n_items)
		return (ft_array_add(array, item));
	i = array->n_items;
	if (array->n_items >= array->size)
	{
		if (!ft_array_extend_size_skip(array,
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

void				*ft_array_inject(t_array *array)
{
	if (array->n_items >= array->size && !ft_array_extend_size(array,
		2 * array->size))
		return (NULL);
	array->n_items++;
	return (ft_array_get(array, array->n_items - 1));
}
