/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typearray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:44 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void					ft_typearray_configure_items(t_typearray *typearray,
	size_t index, t_typeitem *prev, size_t i_typearray)
{
	t_typeitem				*typeitem;

	while (index < typearray->array->size)
	{
		typeitem = (t_typeitem*)ft_array_inject(typearray->typeitems);
		typeitem->item = ft_array_inject(typearray->array);
		typeitem->next = prev;
		typeitem->i_typearray = i_typearray;
		typeitem->n_used = 0;
		typeitem->next_oldest = NULL;
		typeitem->next_recovery = NULL;
		prev = typeitem;
		++index;
	}
	typearray->unused = prev;
	typearray->n_unused = index;
}

void						ft_typearray_free(t_typearray *typearray)
{
	if (!typearray)
		return ;
	ft_array_free(typearray->array);
	ft_array_free(typearray->typeitems);
	free(typearray);
}

static t_typearray			*ft_typearray_error(t_typearray *typearray)
{
	ft_typearray_free(typearray);
	return (NULL);
}

t_typearray					*ft_typearray_construct(size_t size,
	size_t sizeof_item, size_t typeindex)
{
	t_typearray				*out;

	out = (t_typearray*)malloc(sizeof(t_typearray));
	if (!out)
		return (NULL);
	out->array = ft_array_construct(size, sizeof_item);
	out->typeitems = ft_array_construct(size, sizeof(t_typeitem));
	if (!out->array || !out->typeitems)
		return (ft_typearray_error(out));
	ft_typearray_configure_items(out, 0, NULL, typeindex);
	return (out);
}
