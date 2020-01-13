/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:05:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:05:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_tbtree_add_ext_tbnode(t_tbtree *tbtree, t_tbnode *target,
	void *item)
{
	if (target->bnode.rank)
		return (-2);
	if (!ft_tbtree_construct_leaves(tbtree, target))
		return (0);
	target->bnode.named = item;
	target->bnode.rank = 1;
	ft_btree_rebalance_added((t_btree*)tbtree, (t_bnode*)target);
	return (1);
}

int					ft_tbtree_add(t_tbtree *tbtree, void *item)
{
	t_tbnode			*target;

	if (!tbtree || !item)
		return (-1);
	target = (t_tbnode*)ft_btree_get_bnode((t_btree*)tbtree, item);
	return (ft_tbtree_add_ext_tbnode(tbtree, target, item));
}
