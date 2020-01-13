/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:24:01 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 16:24:02 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mbtree_add_ext_bnode(t_mbtree *mbtree, t_bnode *target,
	void *item)
{
	if (target->rank)
		return (-2);
	if (!ft_mbtree_construct_leaves(mbtree, target))
		return (0);
	target->named = item;
	target->rank = 1;
	ft_btree_rebalance_added((t_btree*)mbtree, target);
	return (1);
}

int					ft_mbtree_add(t_mbtree *mbtree, void *item)
{
	t_bnode			*target;

	if (!mbtree || !item)
		return (-1);
	target = ft_btree_get_bnode((t_btree*)mbtree, item);
	return (ft_mbtree_add_ext_bnode(mbtree, target, item));
}
