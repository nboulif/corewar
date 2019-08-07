/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:19:21 by nsondag           #+#    #+#             */
/*   Updated: 2018/11/28 19:03:35 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		count_digit(int n)
{
	size_t count;

	count = 0;
	if (n == -2147483648)
		return (10);
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void			is_negatif(int *n, int *neg)
{
	if (*n < 0)
	{
		*neg = 1;
		*n *= -1;
	}
}

char				*ft_itoa(int n)
{
	int		neg;
	int		i;
	char	*nbr;

	neg = 0;
	is_negatif(&n, &neg);
	if (!(nbr = ft_strnew(count_digit(n) + neg)))
		return (0);
	i = (int)count_digit(n) - 1 + neg;
	if (n == -2147483648)
	{
		nbr[i--] = 8 + '0';
		n = 214748364;
	}
	while (i > 0 && n != -2147483648)
	{
		nbr[i--] = n % 10 + '0';
		n = n / 10;
	}
	if (neg)
		nbr[0] = '-';
	else
		nbr[0] = n % 10 + '0';
	return (nbr);
}
