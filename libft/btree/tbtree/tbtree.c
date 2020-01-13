/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbtree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:06:35 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 14:06:36 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_tbtree_initialize_leaf(t_tbnode *leaf, t_tbnode *parent,
	t_typeitem *typeitem)
{
	leaf->bnode.named = NULL;
	leaf->bnode.left = NULL;
	leaf->bnode.right = NULL;
	leaf->bnode.rank = 0;
	leaf->bnode.up = (t_bnode*)parent;
	leaf->typeitem = typeitem;
}

int					ft_tbtree_initialize(t_tbtree *tbtree,
	t_typemanager *tbnode_tmng, int (*cmp)(void *s1, void *s2))
{
	if (!tbtree || !tbnode_tmng || !cmp)
		return (-1);
	ft_typeused_initialize(&tbtree->tused);
	tbtree->btree.root = (t_bnode*)ft_typemanager_get(tbnode_tmng,
		&tbtree->tused);
	if (!tbtree->btree.root)
		return (0);
	ft_tbtree_initialize_leaf((t_tbnode*)tbtree->btree.root, NULL,
		tbtree->tused.last);
	tbtree->btree.cmp = cmp;
	tbtree->tmng = tbnode_tmng;
	return (1);
}

void				ft_tbtree_refill(t_tbtree *tbtree)
{
	ft_typemanager_refill(tbtree->tmng, &tbtree->tused);
}

static int			ft_tbtree_construct_leaf(t_tbtree *tbtree,
	t_tbnode *old_leaf, t_tbnode **leaf)
{
	*leaf = ft_typemanager_get(tbtree->tmng, &tbtree->tused);
	if (!*leaf)
		return (0);
	ft_tbtree_initialize_leaf(*leaf, old_leaf, tbtree->tused.last);
	return (1);
}

int					ft_tbtree_construct_leaves(t_tbtree *tbtree,
	t_tbnode *old_leaf)
{
	if (!ft_tbtree_construct_leaf(tbtree, old_leaf,
		(t_tbnode**)&old_leaf->bnode.left) ||
		!ft_tbtree_construct_leaf(tbtree, old_leaf,
		(t_tbnode**)&old_leaf->bnode.right))
		return (0);
	return (1);
}
