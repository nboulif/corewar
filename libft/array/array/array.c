/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array				*ft_array_construct(size_t size,
	size_t sizeof_item)
{
	t_array			*out;

	out = (t_array*)malloc(sizeof(t_array));
	if (!out)
		return (NULL);
	if (size > 0 && sizeof_item > 0)
	{
		out->items = malloc(size * sizeof_item);
		out->size = size;
		out->sizeof_item = sizeof_item;
	}
	else
	{
		out->items = malloc(sizeof(void*));
		out->size = 1;
		out->sizeof_item = sizeof(void*);
	}
	if (!out->items)
	{
		free(out);
		return (NULL);
	}
	out->n_items = 0;
	return (out);
}

void				ft_array_free(t_array *array)
{
	if (!array)
		return ;
	free(array->items);
	free(array);
}
