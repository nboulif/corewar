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

int					ft_thmap_remove(t_thmap *thmap, void *item)
{
	t_tbtree		*tbtree;

	if (!thmap || !item)
		return (-1);
	tbtree = (t_tbtree*)ft_hmap_get_cell((t_hmap*)thmap, item);
	if (!tbtree->btree.root)
		return (0);
	if (ft_tbtree_remove(tbtree, item))
	{
		if (ft_btree_is_empty((t_btree*)tbtree))
		{
			ft_tbtree_remove((t_tbtree*)thmap->hmap.hash_btree, tbtree);
			ft_tbtree_refill(tbtree);
			tbtree->btree.root = NULL;
		}
		return (1);
	}
	return (0);
}
