/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:33:59 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/27 21:34:00 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_memjump		*ft_memanager_refill_right(t_memanager *mmng,
	void *addr)
{
	void				*out;
	t_memjump			*start;
	t_memjump			*end;
	t_tbnode			*tbnode_sthmap;
	size_t				sizeof_out;

	start = (t_memjump*)((char*)addr - sizeof(t_memjump));
	start = start->next;
	if (!(end = start->next))
		return (start);
	out = (void*)((char*)start + sizeof(t_memjump));
	sizeof_out = (size_t)((char*)end - (char*)out);
	tbnode_sthmap = (t_tbnode*)ft_btree_get_bnode(
		(t_btree*)&mmng->sthmap_tbt, &sizeof_out);
	if (tbnode_sthmap->bnode.rank &&
		ft_memanager_get_as_is_addr(mmng, tbnode_sthmap, out))
		return (end);
	return (start);
}

static t_memjump		*ft_memanager_refill_left(t_memanager *mmng, void *addr)
{
	void				*out;
	t_memjump			*end;
	t_memjump			*start;
	t_tbnode			*tbnode_sthmap;
	size_t				sizeof_out;

	end = (t_memjump*)((char*)addr - sizeof(t_memjump));
	if (!(start = end->prev))
		return (end);
	out = (void*)((char*)start + sizeof(t_memjump));
	sizeof_out = (size_t)((char*)end - (char*)out);
	tbnode_sthmap = (t_tbnode*)ft_btree_get_bnode(
		(t_btree*)&mmng->sthmap_tbt, &sizeof_out);
	if (tbnode_sthmap->bnode.rank &&
		ft_memanager_get_as_is_addr(mmng, tbnode_sthmap, out))
		return (start);
	return (end);
}

static void				ft_memanager_free_empty_memarray(t_memanager *mmng,
	size_t i_memarray_p)
{
	size_t				*i_new_memarray_p;
	t_array				**memarray;

	memarray = (t_array**)ft_array_get(mmng->memarrays, i_memarray_p);
	ft_array_free(*memarray);
	*memarray = NULL;
	ft_array_remove(mmng->memarrays,
		mmng->memarrays->n_items - 1, (void*)memarray);
	if (i_memarray_p < mmng->memarrays->n_items)
	{
		i_new_memarray_p = (size_t*)ft_array_get(*memarray, 0);
		*i_new_memarray_p = i_memarray_p;
	}
}

int						ft_memanager_refill(t_memanager *mmng, void *addr)
{
	t_memjump			*left;
	t_memjump			*right;
	size_t				i_memarray_p;

	if (!mmng || !addr)
		return (-1);
	left = ft_memanager_refill_left(mmng, addr);
	right = ft_memanager_refill_right(mmng, addr);
	left->next = right;
	right->prev = left;
	addr = (void*)((char*)left + sizeof(t_memjump));
	if (!left->prev && !right->next && mmng->memarrays->n_items > 1)
	{
		i_memarray_p = *(size_t*)((char*)left - sizeof(size_t));
		ft_memanager_free_empty_memarray(mmng, i_memarray_p);
		return (2);
	}
	return (ft_memanager_add_addr(mmng, addr,
		(size_t)((char*)right - (char*)addr)));
}
