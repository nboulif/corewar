/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 21:53:47 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/27 21:53:47 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				*ft_memanager_get_as_is(t_memanager *mmng,
	t_tbnode *tbnode_sthmap)
{
	t_sthmap			*sthmap;
	t_tbnode			*tbnode_addr;
	t_tbtree			*hash_tbt;
	void				*addr;

	sthmap = (t_sthmap*)tbnode_sthmap->bnode.named;
	hash_tbt = (t_tbtree*)sthmap->addr_thmap.hmap.hash_btree->root->named;
	addr = ((t_bnode*)hash_tbt->btree.root)->named;
	tbnode_addr = ft_tbtree_remove_ext_tbnode(hash_tbt,
		(t_tbnode*)hash_tbt->btree.root);
	ft_memanager_get_as_is_refill(mmng, tbnode_sthmap, hash_tbt,
		tbnode_addr);
	return (addr);
}

static int				ft_memanager_set_cut(t_memanager *mmng,
	size_t sizeof_item, void *addr)
{
	t_memjump			*start;
	t_memjump			*step;
	t_memjump			*end;
	void				*cut;

	start = (t_memjump*)((char*)addr - sizeof(t_memjump));
	step = (t_memjump*)((char*)addr + sizeof_item);
	end = start->next;
	start->next = step;
	step->prev = start;
	step->next = end;
	end->prev = step;
	cut = (void*)((char*)step + sizeof(t_memjump));
	return (ft_memanager_add_addr(mmng, cut,
		(size_t)((char*)end - (char*)cut)));
}

static void				*ft_memanager_get_cut(t_memanager *mmng,
	size_t sizeof_item, t_tbnode *tbnode_sthmap)
{
	void				*addr;

	addr = ft_memanager_get_as_is(mmng, tbnode_sthmap);
	if (!ft_memanager_set_cut(mmng, sizeof_item, addr))
		return (NULL);
	return (addr);
}

static void				*ft_memanager_get_extended(t_memanager *mmng,
	size_t sizeof_item)
{
	t_array				*memarray;
	void				*addr;

	if (sizeof_item > mmng->chunk_size - sizeof(size_t) -
		3 * sizeof(t_memjump) - 1)
	{
		if (!(memarray = ft_memanager_extend_size(mmng,
			sizeof_item + 2 * sizeof(t_memjump) + sizeof(size_t))))
			return (NULL);
		addr = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
		return (addr);
	}
	if (!(memarray = ft_memanager_extend_size(mmng, mmng->chunk_size)))
		return (NULL);
	addr = ft_array_get(memarray, sizeof(size_t) + sizeof(t_memjump));
	if (!ft_memanager_set_cut(mmng, sizeof_item, addr))
		return (NULL);
	return (addr);
}

void					*ft_memanager_get(t_memanager *mmng,
	size_t sizeof_item)
{
	t_tbnode			*tbnode_sthmap;

	if (!mmng || !sizeof_item)
		return (NULL);
	tbnode_sthmap = (t_tbnode*)ft_btree_get_min_equal_or_greater_bnode(
		(t_btree*)&mmng->sthmap_tbt, &sizeof_item);
	if (!tbnode_sthmap->bnode.rank)
		return (ft_memanager_get_extended(mmng, sizeof_item));
	if (((t_sthmap*)tbnode_sthmap->bnode.named)->size.key - sizeof_item >
		sizeof(t_memjump))
		return (ft_memanager_get_cut(mmng, sizeof_item, tbnode_sthmap));
	return (ft_memanager_get_as_is(mmng, tbnode_sthmap));
}
