/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:21:33 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/09 12:42:49 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t			l;

	l = ft_strlen(s) + 1;
	while (l-- > 0)
		if (s[l] == (char)c)
			return ((char *)s + l);
	return (NULL);
}
