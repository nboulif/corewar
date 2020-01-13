/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_of.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:07:37 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/24 17:43:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_index_of(const char *src, int c)
{
	ssize_t		i;

	if (src == NULL)
		return (-1);
	i = -1;
	while (src[++i] != '\0')
		if (src[i] == (char)c)
			return (i);
	return (((char)c == '\0') ? i : -1);
}
