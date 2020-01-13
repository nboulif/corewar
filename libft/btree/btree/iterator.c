/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:21:09 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:21:13 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_btree_bnode_iteration(void *receiver, t_bnode *sent,
	int (*f)(void *receiver, void *sent))
{
	int				out;

	out = (sent->rank) ? 1 : -1;
	if (out > 0 && sent->left->rank)
		out = ft_btree_bnode_iteration(receiver, sent->left, f);
	if (out > 0)
		out = f(receiver, sent->named);
	if (out > 0 && sent->right->rank)
		out = ft_btree_bnode_iteration(receiver, sent->right, f);
	return (out);
}

int					ft_btree_fill_array(t_btree *btree, t_array *array)
{
	return (ft_btree_bnode_iteration(array, btree->root,
		ft_array_add_typecast));
}
