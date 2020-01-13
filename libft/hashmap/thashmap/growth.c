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

int					ft_thmap_add(t_thmap *thmap, void *item)
{
	t_tbtree		*tbtree;

	if (!thmap || !item)
		return (-1);
	tbtree = (t_tbtree*)ft_hmap_get_cell((t_hmap*)thmap, item);
	if (!tbtree->btree.root &&
		(!ft_tbtree_initialize(tbtree, thmap->tbnode_mng, ft_btree_cmp_addr) ||
		(1 > ft_tbtree_add((t_tbtree*)thmap->hmap.hash_btree, tbtree))))
		return (0);
	return (ft_tbtree_add(tbtree, item));
}
