/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:42:58 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:42:59 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_hmap_cell_bnode_iteration(void *receiver, void *sent)
{
	t_hmap_wrapper	*wrapper;
	t_btree			*btree;

	wrapper = (t_hmap_wrapper*)receiver;
	btree = (t_btree*)sent;
	return (ft_btree_bnode_iteration(wrapper->item, btree->root, wrapper->f));
}

int					ft_hmap_bnode_iteration(void *receiver, t_hmap *source,
	int (*f)(void *receiver, void *sent))
{
	t_hmap_wrapper	wrapper;

	wrapper.item = receiver;
	wrapper.f = f;
	return (ft_btree_bnode_iteration(&wrapper, source->hash_btree->root,
		ft_hmap_cell_bnode_iteration));
}

int					ft_hmap_cell_identification(void *receiver, void *sent)
{
	t_hmap_wrapper	*wrapper;

	wrapper = (t_hmap_wrapper*)receiver;
	if (wrapper->f(wrapper->item, sent))
	{
		wrapper->item = sent;
		return (0);
	}
	return (1);
}
