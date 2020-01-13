/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memanager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:35:40 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:35:41 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_memanager_internal_construct(t_memanager *mmng,
	size_t sizes, size_t addresses)
{
	t_array				**injector;

	return ((mmng->sthm_mng = ft_typemanager_construct(sizes,
			sizeof(t_sthmap))) &&
		(mmng->array_mng = ft_typemanager_construct(sizes,
			sizeof(t_array))) &&
		(mmng->items_mng = ft_typemanager_construct(sizes,
			sizeof(t_tbtree) * mmng->overlap)) &&
		(mmng->tbnode_mng = ft_typemanager_construct(addresses +
			sizes * mmng->overlap, sizeof(t_tbnode))) &&
		(mmng->memarrays = ft_array_construct(1, sizeof(t_array*))) &&
		(injector = (t_array**)ft_array_inject(mmng->memarrays)) &&
		(*injector = ft_array_construct(mmng->chunk_size, sizeof(char))));
}

/*
** overlap + 1 because the first element of each hashmap array will be used
** as the global btree for the hashmap (see ft_thmap_initialize)
*/

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size, size_t overlap)
{
	t_memanager			*out;

	if (ft_memanager_validate_amounts(sizes, addresses, chunk_size,
		overlap) < 0)
		return (NULL);
	out = (t_memanager*)malloc(sizeof(t_memanager));
	if (!out)
		return (NULL);
	out->chunk_size = chunk_size;
	out->overlap = overlap + 1;
	if (!ft_memanager_internal_construct(out, sizes, addresses) ||
		!ft_memanager_initialize(out))
		return (ft_memanager_error(out));
	return (out);
}

t_memanager				*ft_memanager_construct_default(void)
{
	return (ft_memanager_construct(MMNG_DEFAULT_SIZE_COUNT,
		MMNG_DEFAULT_ADDR_COUNT,
		MMNG_DEFAULT_CHUNK_SIZE,
		MMNG_DEFAULT_OVRLP_SIZE));
}
