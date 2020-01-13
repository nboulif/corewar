/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:06:51 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/28 15:06:53 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memanager_validate_amounts(size_t sizes,
	size_t addresses, size_t chunk_size, size_t overlap)
{
	if (!sizes || addresses < sizes || chunk_size < addresses || overlap < 1 ||
		overlap > addresses)
		return (-1);
	if (addresses / 3 < sizes)
		return (-2);
	if (chunk_size - addresses < 3 * sizeof(t_memjump) + sizeof(size_t) ||
		(chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t)) /
		sizeof(t_memjump) < sizes)
		return (-3);
	if (sizes > ((size_t)1 << (4 * sizeof(size_t) + 1)))
		return (-4);
	if (chunk_size - addresses - sizeof(t_memjump) - sizeof(size_t) -
		sizeof(t_memjump) * sizes < sizes / 2 * (sizes - 1))
		return (-5);
	return (1);
}
