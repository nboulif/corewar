/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typemanager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:40 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:41 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void							ft_typemanager_free(t_typemanager *typemanager)
{
	size_t						i;

	if (!typemanager)
		return ;
	if (typemanager->typearrays)
	{
		i = 0;
		while (i < typemanager->typearrays->n_items)
		{
			ft_typearray_free(
				*(t_typearray**)ft_array_get(typemanager->typearrays, i));
			++i;
		}
		ft_array_free(typemanager->typearrays);
	}
	free(typemanager);
	return ;
}

static t_typemanager			*ft_typemanager_error(
	t_typemanager *typemanager)
{
	ft_typemanager_free(typemanager);
	return (NULL);
}

t_typemanager					*ft_typemanager_construct(size_t size,
	size_t sizeof_item)
{
	t_typemanager				*out;
	t_typearray					**injector;

	out = (t_typemanager*)malloc(sizeof(t_typemanager));
	if (!out || !(out->typearrays = ft_array_construct(1, sizeof(t_typearray*)))
		|| !(injector = (t_typearray**)ft_array_inject(out->typearrays))
		|| !(*injector = ft_typearray_construct(size, sizeof_item, 0)))
		return (ft_typemanager_error(out));
	out->i_available = 0;
	return (out);
}

int								ft_typemanager_extend_size(
	t_typemanager *typemanager, size_t new_size)
{
	t_typearray					**injector;

	if (!(injector = (t_typearray**)ft_array_inject(typemanager->typearrays)) ||
		!(*injector = ft_typearray_construct(new_size,
		(*(t_typearray**)ft_array_get(typemanager->typearrays,
			0))->array->sizeof_item,
		typemanager->typearrays->n_items - 1)))
		return (0);
	return (1);
}
