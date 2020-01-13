/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:14:43 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/10 13:15:40 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	size_t		len;
	size_t		i;
	char		tmp;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = -1;
	while (--len > ++i)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
	}
	return (str);
}
