/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:06:55 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:06:56 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bnode				**ft_btree_bnode_referent(t_btree *btree, t_bnode *bnode)
{
	if (btree->root == bnode)
		return (&btree->root);
	if (bnode->up->right == bnode)
		return (&bnode->up->right);
	return (&bnode->up->left);
}

int					ft_bnode_sibling_spin(t_bnode *child, t_bnode **sibling)
{
	if (child->up->left == child)
	{
		*sibling = child->up->right;
		return (1);
	}
	*sibling = child->up->left;
	return (-1);
}

void				ft_btree_rotate(t_btree *btree, t_bnode *bn, int spin)
{
	t_bnode			*up;
	t_bnode			**referent;

	up = bn->up;
	referent = ft_btree_bnode_referent(btree, up);
	*referent = bn;
	bn->up = up->up;
	up->up = bn;
	if (spin == 1)
	{
		up->left = bn->right;
		bn->right->up = up;
		bn->right = up;
	}
	else
	{
		up->right = bn->left;
		bn->left->up = up;
		bn->left = up;
	}
	up->rank--;
	return ;
}

int					ft_bnode_has_two_leaves(t_bnode *bnode)
{
	if (!bnode->left || !bnode->right)
		return (0);
	return (!bnode->left->rank && !bnode->right->rank);
}
