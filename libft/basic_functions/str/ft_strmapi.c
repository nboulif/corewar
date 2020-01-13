/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:21:21 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/12 14:33:46 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	out = ft_strnew(ft_strlen(s));
	if (out == NULL)
		return (out);
	i = 0;
	while (s[i] != '\0')
	{
		out[i] = f(i, s[i]);
		if (++i == 0)
			return (out);
	}
	return (out);
}
