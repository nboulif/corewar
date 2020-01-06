/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:27:44 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 17:59:54 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(dst = (char*)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	ft_strcpy(dst, s);
	while (dst[i] != '\0')
	{
		dst[i] = f(i, *s);
		s++;
		i++;
	}
	return (dst - ft_strlen(s));
}
