/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:17:56 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/28 15:17:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_array_tbtree_initialize_root(void *receiver,
	void *sent)
{
	((t_tbtree*)sent)->btree.root = NULL;
	return (!receiver);
}

static void				ft_array_tbtree_initialize(t_array *array, size_t size)
{
	array->n_items = size;
	array->size = size;
	array->sizeof_item = sizeof(t_tbtree);
	ft_array_iteration(NULL, array, ft_array_tbtree_initialize_root);
}

static t_sthmap			*ft_sthmap_construct(t_memanager *mmng, size_t size)
{
	t_sthmap			*sthmap;
	t_array				*array;

	if (!size)
		return (NULL);
	if (!(sthmap = ft_typemanager_get(mmng->sthm_mng,
		&mmng->sthm_used)))
		return (NULL);
	sthmap->sthm_typeitem = mmng->sthm_used.last;
	sthmap->size.key = size;
	if (!(array = ft_typemanager_get_typeitem(mmng->array_mng,
		&mmng->array_used, &sthmap->array_typeitem)) ||
		!(array->items = ft_typemanager_get_typeitem(mmng->items_mng,
		&mmng->items_used, &sthmap->items_typeitem)))
		return (NULL);
	ft_array_tbtree_initialize(array, mmng->overlap);
	ft_thmap_initialize(&sthmap->addr_thmap, mmng->tbnode_mng, array,
		ft_hmap_hash_addr);
	return (sthmap);
}

int						ft_memanager_add_addr(t_memanager *mmng,
	void *addr, size_t sizeof_addr)
{
	t_sthmap			*sthmap;
	t_tbnode			*stbnode;

	stbnode = (t_tbnode*)ft_btree_get_bnode((t_btree*)&mmng->sthmap_tbt,
		&sizeof_addr);
	if (!stbnode->bnode.rank &&
		(!(sthmap = ft_sthmap_construct(mmng, sizeof_addr)) ||
			(1 > ft_tbtree_add_ext_tbnode(&mmng->sthmap_tbt, stbnode, sthmap))))
		return (0);
	else
		sthmap = (t_sthmap*)stbnode->bnode.named;
	return (ft_thmap_add(&sthmap->addr_thmap, addr));
}

t_array					*ft_memanager_extend_size(
	t_memanager *mmng, size_t chunk_size)
{
	t_array				**injector;

	if (!mmng)
		return (NULL);
	if (!(injector = (t_array**)ft_array_inject(mmng->memarrays)) ||
		!(*injector = ft_array_construct(chunk_size, sizeof(char))))
		return (NULL);
	return (ft_memanager_initialize_memarray(mmng,
		mmng->memarrays->n_items - 1));
}
