/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_requests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:50 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							ft_typemanager_refill(t_typemanager *typemanager,
	t_typeused *used)
{
	t_typearray				*typearray;
	t_typeitem				*tmp;

	if (!used || !used->oldest || !used->typeitem)
		return (0);
	while (used->oldest)
	{
		typearray = *(t_typearray**)ft_array_get(typemanager->typearrays,
			used->oldest->i_typearray);
		if (!typearray)
			return (0);
		tmp = used->oldest->next;
		used->oldest->next = typearray->unused;
		typearray->unused = used->typeitem;
		typearray->n_unused += used->typeitem->n_used;
		if (used->typeitem->i_typearray < typemanager->i_available)
			typemanager->i_available = used->typeitem->i_typearray;
		used->typeitem = tmp;
		used->oldest = used->oldest->next_oldest;
		if (!used->typeitem && used->oldest)
			return (0);
	}
	return (1);
}

static void					*ft_typemanager_get_same_typearray(t_typeused *used,
	t_typearray *typearray)
{
	t_typeitem				*old;

	old = used->typeitem;
	if (!used->oldest)
		used->oldest = typearray->unused;
	used->typeitem = typearray->unused;
	typearray->unused = typearray->unused->next;
	typearray->n_unused--;
	used->typeitem->next = old;
	used->typeitem->n_used = (!old) ? 1 : old->n_used + 1;
	used->last = used->typeitem;
	return (used->last->item);
}

static void					*ft_typemanager_get_other_typearray(
	t_typeused *used, t_typearray *typearray)
{
	typearray->unused->next_oldest = used->oldest;
	used->oldest = typearray->unused;
	typearray->unused = typearray->unused->next;
	typearray->n_unused--;
	used->oldest->next = used->typeitem;
	used->typeitem = used->oldest;
	used->typeitem->n_used = 1;
	used->last = used->typeitem;
	return (used->last->item);
}

void						*ft_typemanager_get(t_typemanager *typemanager,
	t_typeused *used)
{
	t_typearray				*typearray;

	if (used->recovery)
	{
		used->last = used->recovery;
		used->recovery = used->recovery->next_recovery;
		return (used->last->item);
	}
	typearray = *(t_typearray**)ft_array_get(typemanager->typearrays,
		typemanager->i_available);
	while (!typearray->n_unused)
	{
		if (typemanager->i_available == typemanager->typearrays->n_items - 1 &&
			!ft_typemanager_extend_size(typemanager, typearray->array->size))
			return (NULL);
		typemanager->i_available++;
		typearray = *(t_typearray**)ft_array_get(typemanager->typearrays,
			typemanager->i_available);
	}
	if (!used->typeitem ||
		used->typeitem->i_typearray == typemanager->i_available)
		return (ft_typemanager_get_same_typearray(used, typearray));
	else
		return (ft_typemanager_get_other_typearray(used, typearray));
}

void						*ft_typemanager_get_typeitem(
	t_typemanager *typemanager, t_typeused *used, t_typeitem **item)
{
	void				*addr;

	addr = ft_typemanager_get(typemanager, used);
	*item = used->last;
	return (addr);
}
