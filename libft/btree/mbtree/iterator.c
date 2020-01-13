/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:00:44 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 19:00:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_mbtree_add_typecast(void *receiver, void *sent)
{
	return (ft_mbtree_add((t_mbtree*)receiver, sent));
}

int					ft_btree_fill_mcopy(t_btree *old, t_mbtree *new_mbt)
{
	return (ft_btree_bnode_iteration(new_mbt, old->root,
		ft_mbtree_add_typecast));
}
