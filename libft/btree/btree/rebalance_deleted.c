/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebalance_deleted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:17:22 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:17:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_btree_rebalance_deleted_double_rotate(t_btree *btree,
	t_bnode *bn, t_bnode *sib, int spin)
{
	bn->up->rank--;
	bn = (spin == 1) ? sib->left : sib->right;
	bn->rank++;
	ft_btree_rotate(btree, bn, spin);
	ft_btree_rotate(btree, bn, -1 * spin);
	bn->rank++;
}

static void			ft_btree_rebalance_deleted_single_rotate(t_btree *btree,
	t_bnode *bn, t_bnode *sib, int spin)
{
	bn = bn->up;
	sib->up->rank++;
	ft_btree_rotate(btree, sib->up, -1 * spin);
	if (ft_bnode_has_two_leaves(bn))
		bn->rank = 1;
}

static void			ft_btree_rebalance_deleted_to_leaf(t_btree *btree,
	t_bnode **bn)
{
	t_bnode			*sib;

	if (!(*bn)->rank && btree->root != *bn)
	{
		ft_bnode_sibling_spin(*bn, &sib);
		if (!sib->rank)
		{
			bn = &(*bn)->up;
			(*bn)->rank = 1;
		}
	}
}

void				ft_btree_rebalance_deleted(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	ft_btree_rebalance_deleted_to_leaf(btree, &bn);
	while (bn->up && bn->up->rank - bn->rank == 3)
	{
		spin = ft_bnode_sibling_spin(bn, &sib);
		if (sib->rank - bn->rank == 2)
		{
			if (sib->left->rank - sib->right->rank == spin)
			{
				ft_btree_rebalance_deleted_double_rotate(btree, bn, sib, spin);
				return ;
			}
			sib = (spin == 1) ? sib->right : sib->left;
			if (sib->up->rank - sib->rank == 1)
			{
				ft_btree_rebalance_deleted_single_rotate(btree, bn, sib, spin);
				return ;
			}
			sib->up->rank--;
		}
		bn->up->rank--;
		bn = bn->up;
	}
}
