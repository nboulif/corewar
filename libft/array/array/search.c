/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:51:20 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 14:51:21 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_array_index(t_array *array, void *item)
{
	size_t	i;

	if (item == NULL)
		return (array->n_items);
	i = 0;
	while (i < array->n_items)
	{
		if (!ft_memcmp(&array->items[i * array->sizeof_item], item,
			array->sizeof_item))
			return (i);
		i++;
	}
	return (i);
}

int					ft_array_contains(t_array *array, void *item)
{
	return (ft_array_index(array, item) != array->n_items);
}

void				*ft_array_get(t_array *array, size_t index)
{
	if (index >= array->n_items)
		return (NULL);
	return (&array->items[index * array->sizeof_item]);
}
