/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thashmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:18:38 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:18:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_thmap_initialize(t_thmap *thmap,
	t_typemanager *tbnode_mng, t_array *array_tbtree,
	size_t (*hash)(void *s, size_t size))
{
	if (!thmap || !tbnode_mng || !array_tbtree || !hash ||
		array_tbtree->size < 2)
		return (-1);
	thmap->hmap.array = array_tbtree;
	thmap->hmap.hash_btree = (t_btree*)thmap->hmap.array->items;
	thmap->hmap.array->items =
		(void*)((char*)thmap->hmap.array->items + sizeof(t_tbtree));
	thmap->hmap.array->n_items--;
	thmap->hmap.array->size--;
	thmap->hmap.hash = hash;
	thmap->tbnode_mng = tbnode_mng;
	return (ft_tbtree_initialize((t_tbtree*)thmap->hmap.hash_btree, tbnode_mng,
		ft_btree_cmp_addr));
}

static int			ft_thmap_refill_tbtree(void *receiver, void *sent)
{
	if (!receiver)
	{
		ft_tbtree_refill((t_tbtree*)sent);
		return (1);
	}
	return (0);
}

void				ft_thmap_refill(t_thmap *thmap)
{
	if (!thmap)
		return ;
	ft_btree_bnode_iteration(NULL, thmap->hmap.hash_btree->root,
		ft_thmap_refill_tbtree);
	ft_tbtree_refill((t_tbtree*)thmap->hmap.hash_btree);
}
