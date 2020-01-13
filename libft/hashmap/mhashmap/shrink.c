/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:43:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:43:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mhmap_remove(t_mhmap *mhmap, void *item)
{
	t_mbtree		*mbtree;

	if (!mhmap || !item)
		return (-1);
	mbtree = (t_mbtree*)ft_hmap_get_cell((t_hmap*)mhmap, item);
	if (!mbtree->btree.root)
		return (0);
	if (ft_mbtree_remove(mbtree, item))
	{
		if (ft_btree_is_empty((t_btree*)mbtree))
		{
			ft_mbtree_remove((t_mbtree*)mhmap->hmap.hash_btree, mbtree);
			ft_mbtree_empty(mbtree);
			mbtree->btree.root = NULL;
		}
		return (1);
	}
	return (0);
}
