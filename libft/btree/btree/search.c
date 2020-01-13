/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 15:47:43 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 15:47:44 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bnode				*ft_btree_get_bnode(t_btree *btree, void *key)
{
	t_bnode			*cur;
	int				cmpr;

	cur = btree->root;
	while (cur->rank && (cmpr = btree->cmp(key, cur->named)))
	{
		if (cmpr < 0)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return (cur);
}

void				*ft_btree_get(t_btree *btree, void *key)
{
	t_bnode			*target;

	if (!btree || !key)
		return (NULL);
	target = ft_btree_get_bnode(btree, key);
	return ((!target->rank) ? NULL : target->named);
}

int					ft_btree_contains(t_btree *btree, void *key)
{
	t_bnode			*bnode;

	if (!btree || !key)
		return (-1);
	bnode = ft_btree_get_bnode(btree, key);
	return (bnode->rank != 0);
}

t_bnode				*ft_btree_get_min_bnode(t_bnode *bnode)
{
	while (bnode->left->rank)
		bnode = bnode->left;
	return (bnode);
}

t_bnode				*ft_btree_get_min_equal_or_greater_bnode(t_btree *btree,
	void *key)
{
	t_bnode			*greater;
	t_bnode			*cur;
	int				cmpr;

	greater = NULL;
	cur = btree->root;
	while (cur->rank && (cmpr = btree->cmp(key, cur->named)))
	{
		if (cmpr < 0)
		{
			greater = cur;
			cur = cur->left;
		}
		else
			cur = cur->right;
	}
	return ((greater && !cur->rank) ? greater : cur);
}
