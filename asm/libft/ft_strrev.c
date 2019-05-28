/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:46:58 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/25 22:46:59 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	size_t		start;
	size_t		end;
	char		tmp;

	start = 0;
	end = ft_strlen(s);
	end = end ? --end : end;
	while (start < end)
	{
		tmp = s[end];
		s[end--] = s[start];
		s[start++] = tmp;
	}
	return (s);
}
