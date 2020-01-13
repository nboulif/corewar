/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:03:32 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/28 15:03:33 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array					*ft_memanager_initialize_memarray(
	t_memanager *mmng, size_t i_memarray)
{
	t_array				*memarray;
	t_memjump			*start;
	t_memjump			*end;
	size_t				*i_memarray_p;

	memarray = *(t_array**)ft_array_get(mmng->memarrays, i_memarray);
	memarray->n_items = memarray->size;
	i_memarray_p = (size_t*)ft_array_get(memarray, 0);
	start = (t_memjump*)ft_array_get(memarray, sizeof(size_t));
	end = (t_memjump*)ft_array_get(memarray,
		memarray->size - sizeof(t_memjump));
	if (!i_memarray_p || !start || !end)
		return (NULL);
	*i_memarray_p = i_memarray;
	start->prev = NULL;
	end->next = NULL;
	start->next = end;
	end->prev = start;
	return (memarray);
}

static int				ft_memanager_initialize_first_memarray(
	t_memanager *mmng)
{
	t_array				*memarray;

	memarray = ft_memanager_initialize_memarray(mmng, 0);
	return (ft_memanager_add_addr(mmng,
		ft_array_get(memarray, sizeof(t_memjump) + sizeof(size_t)),
		memarray->size - 2 * sizeof(t_memjump) - sizeof(size_t)));
}

int						ft_memanager_initialize(t_memanager *mmng)
{
	ft_typeused_initialize(&mmng->sthm_used);
	ft_typeused_initialize(&mmng->array_used);
	ft_typeused_initialize(&mmng->items_used);
	return (1 <= ft_tbtree_initialize(&mmng->sthmap_tbt, mmng->tbnode_mng,
		ft_btree_cmp_size) &&
		1 <= ft_memanager_initialize_first_memarray(mmng));
}
