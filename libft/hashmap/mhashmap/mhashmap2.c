/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mhashmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:18:38 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:18:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_mhmap_empty_mbtree(void *receiver, void *sent)
{
	if (!receiver)
	{
		ft_mbtree_empty((t_mbtree*)sent);
		return (1);
	}
	return (0);
}

void				ft_mhmap_empty(t_mhmap *mhmap)
{
	if (!mhmap)
		return ;
	ft_btree_bnode_iteration(NULL, mhmap->hmap.hash_btree->root,
		ft_mhmap_empty_mbtree);
	ft_marray_free((t_marray*)mhmap->hmap.array);
	ft_mbtree_free((t_mbtree*)mhmap->hmap.hash_btree);
}

void				ft_mhmap_free(t_mhmap *mhmap)
{
	ft_mhmap_empty(mhmap);
	ft_memanager_refill(mhmap->mmng, mhmap);
}
