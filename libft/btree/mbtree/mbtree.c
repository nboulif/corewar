/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:24:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 16:24:05 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_mbtree			*ft_mbtree_construct(t_memanager *mmng,
	int (*cmp)(void *s1, void *s2))
{
	t_mbtree		*mbtree;

	if (!mmng ||
		!(mbtree = (t_mbtree*)ft_memanager_get(mmng, sizeof(t_mbtree))))
		return (NULL);
	if (1 > ft_mbtree_initialize(mbtree, mmng, cmp))
	{
		ft_memanager_refill(mmng, mbtree);
		return (NULL);
	}
	return (mbtree);
}

void				ft_mbtree_free(t_mbtree *mbtree)
{
	if (!mbtree)
		return ;
	ft_mbtree_empty(mbtree);
	ft_memanager_refill(mbtree->mmng, mbtree);
}

static int			ft_mbtree_construct_leaf(t_mbtree *mbtree,
	t_bnode *old_leaf, t_bnode **leaf)
{
	*leaf = (t_bnode*)ft_memanager_get(mbtree->mmng, sizeof(t_bnode));
	if (!*leaf)
		return (0);
	ft_mbtree_initialize_leaf(*leaf, old_leaf);
	return (1);
}

int					ft_mbtree_construct_leaves(t_mbtree *mbtree,
	t_bnode *old_leaf)
{
	if (!ft_mbtree_construct_leaf(mbtree, old_leaf, &old_leaf->left) ||
		!ft_mbtree_construct_leaf(mbtree, old_leaf, &old_leaf->right))
		return (0);
	return (1);
}
