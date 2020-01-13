/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:24:08 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 16:24:09 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_mbtree_cut_leaf(t_mbtree *mbtree, t_bnode *cut,
	t_bnode **remain)
{
	t_bnode			*dead_leaf;

	if (!cut->left->rank)
	{
		dead_leaf = cut->left;
		*remain = cut->right;
	}
	else if (!cut->right->rank)
	{
		dead_leaf = cut->right;
		*remain = cut->left;
	}
	else
		return (0);
	ft_memanager_refill(mbtree->mmng, dead_leaf);
	return (1);
}

static int			ft_mbtree_cut_branch(t_mbtree *mbtree, t_bnode *cut)
{
	t_bnode			**referent;
	t_bnode			*remain;

	if (!ft_mbtree_cut_leaf(mbtree, cut, &remain))
		return (0);
	referent = ft_btree_bnode_referent((t_btree*)mbtree, cut);
	remain->up = cut->up;
	*referent = remain;
	ft_btree_rebalance_deleted((t_btree*)mbtree, remain);
	return (1);
}

t_bnode				*ft_mbtree_remove_ext_bnode(t_mbtree *mbtree,
	t_bnode *target)
{
	t_bnode			*swapper;
	void			*named;

	if (target->rank)
	{
		if (ft_mbtree_cut_branch(mbtree, target))
			return (target);
		swapper = ft_btree_get_min_bnode(target->right);
		named = target->named;
		target->named = swapper->named;
		swapper->named = named;
		target = swapper;
		ft_mbtree_cut_branch(mbtree, target);
	}
	return ((target->rank) ? target : NULL);
}

void				*ft_mbtree_remove(t_mbtree *mbtree, void *key)
{
	t_bnode			*target;
	void			*out;

	if (!mbtree || !key)
		return (NULL);
	target = ft_mbtree_remove_ext_bnode(mbtree,
		ft_btree_get_bnode((t_btree*)mbtree, key));
	if (target)
	{
		out = target->named;
		ft_memanager_refill(mbtree->mmng, target);
	}
	else
		out = NULL;
	return (out);
}
