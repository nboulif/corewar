/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:19:24 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:19:30 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_tbtree_cut_leaf(t_tbtree *tbtree, t_tbnode *cut,
	t_tbnode **remain)
{
	t_tbnode		*dead_leaf;

	if (!cut->bnode.left->rank)
	{
		dead_leaf = (t_tbnode*)cut->bnode.left;
		*remain = (t_tbnode*)cut->bnode.right;
	}
	else if (!cut->bnode.right->rank)
	{
		dead_leaf = (t_tbnode*)cut->bnode.right;
		*remain = (t_tbnode*)cut->bnode.left;
	}
	else
		return (0);
	ft_typeused_recover(&tbtree->tused, dead_leaf->typeitem);
	return (1);
}

static int			ft_tbtree_cut_branch(t_tbtree *tbtree, t_tbnode *cut)
{
	t_tbnode		**referent;
	t_tbnode		*remain;

	if (!ft_tbtree_cut_leaf(tbtree, cut, &remain))
		return (0);
	referent = (t_tbnode**)ft_btree_bnode_referent((t_btree*)tbtree,
		(t_bnode*)cut);
	remain->bnode.up = cut->bnode.up;
	*referent = remain;
	ft_btree_rebalance_deleted((t_btree*)tbtree, (t_bnode*)remain);
	return (1);
}

t_tbnode			*ft_tbtree_remove_ext_tbnode(t_tbtree *tbtree,
	t_tbnode *target)
{
	t_tbnode		*swapper;
	void			*named;

	if (target->bnode.rank)
	{
		if (ft_tbtree_cut_branch(tbtree, target))
			return (target);
		swapper = (t_tbnode*)ft_btree_get_min_bnode(target->bnode.right);
		named = target->bnode.named;
		target->bnode.named = swapper->bnode.named;
		swapper->bnode.named = named;
		target = swapper;
		ft_tbtree_cut_branch(tbtree, target);
	}
	return ((target->bnode.rank) ? target : NULL);
}

void				*ft_tbtree_remove(t_tbtree *tbtree, void *key)
{
	t_tbnode		*target;
	void			*out;

	if (!tbtree || !key)
		return (NULL);
	target = ft_tbtree_remove_ext_tbnode(tbtree,
		(t_tbnode*)ft_btree_get_bnode((t_btree*)tbtree, key));
	if (target)
	{
		out = target->bnode.named;
		ft_typeused_recover(&tbtree->tused, target->typeitem);
	}
	else
		out = NULL;
	return (out);
}
