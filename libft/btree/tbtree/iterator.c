/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:00:39 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:00:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_tbtree_add_typecast(void *receiver, void *sent)
{
	return (ft_tbtree_add((t_tbtree*)receiver, sent));
}

int					ft_btree_fill_tcopy(t_btree *old, t_tbtree *new_tbt)
{
	return (ft_btree_bnode_iteration(new_tbt, old->root,
		ft_tbtree_add_typecast));
}
