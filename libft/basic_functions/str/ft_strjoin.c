/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:47:43 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 15:23:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*out;
	size_t		l_s1;
	size_t		l_s2;

	l_s1 = (s1 == NULL) ? 0 : ft_strlen(s1);
	l_s2 = (s2 == NULL) ? 0 : ft_strlen(s2);
	out = ft_strnew(l_s1 + l_s2);
	if (out == NULL)
		return (out);
	ft_memmove(out, s1, l_s1);
	ft_memmove(out + l_s1, s2, l_s2);
	return (out);
}
