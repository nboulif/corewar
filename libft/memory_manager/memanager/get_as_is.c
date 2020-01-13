/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_as_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 22:01:03 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/27 22:01:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				ft_sthmap_refill(t_memanager *mmng, t_sthmap *sthmap)
{
	ft_thmap_refill(&sthmap->addr_thmap);
	ft_typeused_recover(&mmng->array_used, sthmap->array_typeitem);
	ft_typeused_recover(&mmng->items_used, sthmap->items_typeitem);
	ft_typeused_recover(&mmng->sthm_used, sthmap->sthm_typeitem);
}

void					ft_memanager_get_as_is_refill(t_memanager *mmng,
	t_tbnode *tbnode_sthmap, t_tbtree *hash_tbt, t_tbnode *tbnode_addr)
{
	t_sthmap			*sthmap;

	sthmap = (t_sthmap*)tbnode_sthmap->bnode.named;
	if (ft_btree_is_empty((t_btree*)hash_tbt))
	{
		ft_tbtree_remove((t_tbtree*)sthmap->addr_thmap.hmap.hash_btree,
			hash_tbt);
		ft_tbtree_refill(hash_tbt);
		hash_tbt->tmng = NULL;
		if (ft_hmap_is_empty((t_hmap*)&sthmap->addr_thmap))
		{
			ft_sthmap_refill(mmng, sthmap);
			tbnode_sthmap = ft_tbtree_remove_ext_tbnode(&mmng->sthmap_tbt,
				tbnode_sthmap);
			ft_typeused_recover(&(&mmng->sthmap_tbt)->tused,
				tbnode_sthmap->typeitem);
		}
	}
	else
		ft_typeused_recover(&hash_tbt->tused, tbnode_addr->typeitem);
}

void					*ft_memanager_get_as_is_addr(t_memanager *mmng,
	t_tbnode *tbnode_sthmap, void *addr)
{
	t_sthmap			*sthmap;
	t_tbnode			*tbnode_addr;
	t_tbtree			*hash_tbt;

	sthmap = (t_sthmap*)tbnode_sthmap->bnode.named;
	hash_tbt = (t_tbtree*)ft_hmap_get_cell((t_hmap*)&sthmap->addr_thmap, addr);
	if (!hash_tbt->tmng)
		return (NULL);
	tbnode_addr = (t_tbnode*)ft_btree_get_bnode((t_btree*)hash_tbt, addr);
	if (!tbnode_addr->bnode.rank)
		return (NULL);
	tbnode_addr = ft_tbtree_remove_ext_tbnode(hash_tbt, tbnode_addr);
	ft_memanager_get_as_is_refill(mmng, tbnode_sthmap, hash_tbt,
		tbnode_addr);
	return (addr);
}
