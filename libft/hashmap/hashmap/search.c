/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:43:02 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:43:03 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree				*ft_hmap_get_cell(t_hmap *hmap, void *item)
{
	return ((t_btree*)ft_array_get(hmap->array,
		hmap->hash(item, hmap->array->size)));
}

int					ft_hmap_contains(t_hmap *hmap, void *item)
{
	t_btree		*btree;

	if (!hmap || !item)
		return (-1);
	btree = (t_btree*)ft_hmap_get_cell(hmap, item);
	return ((btree->root) ? ft_btree_contains(btree, item) : 0);
}

int					ft_hmap_is_empty(t_hmap *hmap)
{
	if (!hmap)
		return (-1);
	return (ft_btree_is_empty(hmap->hash_btree));
}

void				*ft_hmap_get(t_hmap *hmap, void *key,
	int (*equals)(void *s1, void *s2))
{
	t_hmap_wrapper	wrapper;
	t_btree			*btree;

	wrapper.item = key;
	wrapper.f = equals;
	btree = ft_hmap_get_cell(hmap, key);
	if (!btree->root)
		wrapper.item = NULL;
	else
	{
		ft_btree_bnode_iteration(&wrapper, btree->root,
			ft_hmap_cell_identification);
		if (wrapper.item == key)
			wrapper.item = NULL;
	}
	return (wrapper.item);
}

int					ft_hmap_contains_key(t_hmap *hmap, void *key,
	int (*equals)(void *s1, void *s2))
{
	return (ft_hmap_get(hmap, key, equals) != NULL);
}
