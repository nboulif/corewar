/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:01:29 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/28 15:01:31 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_memanager_free(t_memanager *mmng)
{
	size_t				i;

	if (!mmng)
		return ;
	if (mmng->memarrays)
	{
		i = 0;
		while (i < mmng->memarrays->n_items)
		{
			ft_array_free(*(t_array**)ft_array_get(mmng->memarrays, i));
			++i;
		}
		ft_array_free(mmng->memarrays);
	}
	if (mmng->sthm_mng)
		ft_typemanager_free(mmng->sthm_mng);
	if (mmng->array_mng)
		ft_typemanager_free(mmng->array_mng);
	if (mmng->items_mng)
		ft_typemanager_free(mmng->items_mng);
	if (mmng->tbnode_mng)
		ft_typemanager_free(mmng->tbnode_mng);
	free(mmng);
}

t_memanager				*ft_memanager_error(t_memanager *mmng)
{
	ft_memanager_free(mmng);
	return (NULL);
}
