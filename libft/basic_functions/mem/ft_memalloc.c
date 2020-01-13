/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:02:47 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:37:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	unsigned char	*out;
	size_t			i;

	if (size == 0)
		return (NULL);
	out = (unsigned char *)malloc(size);
	if (out == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
		out[i] = 0;
	return ((void *)out);
}
