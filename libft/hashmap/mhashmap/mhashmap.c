/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mhashmap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:18:38 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:18:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_array_mbtree_initialize_root(void *receiver, void *sent)
{
	((t_mbtree*)sent)->btree.root = NULL;
	return (!receiver);
}

int					ft_mhmap_initialize(t_mhmap *mhmap, t_memanager *mmng,
	size_t size, size_t (*hash)(void *s, size_t size))
{
	if (!mhmap || !mmng || !hash)
		return (-1);
	mhmap->hmap.array = (t_array*)ft_marray_construct(mmng, size,
		sizeof(t_mbtree));
	if (!mhmap->hmap.array)
		return (0);
	mhmap->hmap.array->n_items = size;
	ft_array_iteration(NULL, mhmap->hmap.array,
		ft_array_mbtree_initialize_root);
	mhmap->mmng = mmng;
	mhmap->hmap.hash = hash;
	return (NULL != (mhmap->hmap.hash_btree =
		(t_btree*)ft_mbtree_construct(mmng, ft_btree_cmp_addr)));
}

t_mhmap				*ft_mhmap_construct(t_memanager *mmng, size_t size,
	size_t (*hash)(void *s, size_t size))
{
	t_mhmap			*mhmap;

	if (!mmng ||
		!(mhmap = (t_mhmap*)ft_memanager_get(mmng, sizeof(t_mhmap))))
		return (NULL);
	if (1 > ft_mhmap_initialize(mhmap, mmng, size, hash))
	{
		ft_memanager_refill(mmng, mhmap);
		return (NULL);
	}
	return (mhmap);
}
