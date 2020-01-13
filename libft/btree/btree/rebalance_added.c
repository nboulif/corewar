/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebalance_added.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:05:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:05:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_btree_rebalance_added(t_btree *btree, t_bnode *bn)
{
	t_bnode			*sib;
	int				spin;

	while (bn->up && bn->up->rank == bn->rank)
	{
		spin = ft_bnode_sibling_spin(bn, &sib);
		if (bn->rank == bn->up->rank && bn->rank > sib->rank + 1)
		{
			if (((bn->left->rank - bn->right->rank) ^ spin) < 0)
			{
				sib = (spin == 1) ? bn->right : bn->left;
				sib->rank++;
				ft_btree_rotate(btree, sib, -1 * spin);
				ft_btree_rotate(btree, sib, spin);
			}
			else
				ft_btree_rotate(btree, bn, spin);
			return ;
		}
		bn->up->rank++;
		bn = bn->up;
	}
}
