/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:51:25 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 14:51:26 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_array_remove(t_array *array, size_t index,
	void *removed)
{
	if (index >= array->n_items)
		return (0);
	if (removed)
		ft_memmove(removed, &array->items[index * array->sizeof_item],
			array->sizeof_item);
	while (++index < array->n_items)
		ft_memmove(&array->items[(index - 1) * array->sizeof_item],
			&array->items[index * array->sizeof_item], array->sizeof_item);
	if (array->n_items > 0)
		array->n_items = array->n_items - 1;
	return (1);
}

int					ft_array_remove_first(t_array *array, void *item)
{
	size_t	i;

	i = ft_array_index(array, item);
	return (ft_array_remove(array, i, NULL) != 0);
}
