/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:42:58 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:42:59 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mhmap_add(t_mhmap *mhmap, void *item)
{
	t_mbtree		*mbtree;

	if (!mhmap || !item)
		return (-1);
	mbtree = (t_mbtree*)ft_hmap_get_cell((t_hmap*)mhmap, item);
	if (!mbtree->btree.root &&
		(!ft_mbtree_initialize(mbtree, mhmap->mmng, ft_btree_cmp_addr) ||
		(1 > ft_mbtree_add((t_mbtree*)mhmap->hmap.hash_btree, mbtree))))
		return (0);
	return (ft_mbtree_add(mbtree, item));
}
