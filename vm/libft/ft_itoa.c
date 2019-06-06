/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:44:37 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	size_t			len;
	int				neg;
	char			*str;
	long long int	n2;

	neg = n < 0 ? 1 : 0;
	len = ft_intlen(n) + (n <= 0 ? 1 : 0);
	if (!(str = ft_strnew(len)))
		return (NULL);
	n2 = n;
	n2 = n < 0 ? -n2 : n2;
	while (len--)
	{
		str[len] = n2 % 10 + '0';
		n2 = n2 / 10;
	}
	neg ? str[0] = '-' : 0;
	return (str);
}
