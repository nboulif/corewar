/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 11:19:24 by nsondag           #+#    #+#             */
/*   Updated: 2018/11/28 19:34:21 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	valid_char(const char *str, int base)
{
	if (base < 11)
	{
		if (*str >= '0' && *str < '0' + base)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((*str >= 'a' && *str < 'a' + base - 10)
			|| (*str >= 'A' && *str < 'A' + base - 10)
			|| (*str >= '0' && *str <= '9'))
			return (1);
		else
			return (0);
	}
}

static int	chartodigit(const char *str)
{
	int	nbr;

	if (*str >= '0' && *str <= '9')
		nbr = *str - '0';
	else if (*str >= 'A' && *str <= 'F')
		nbr = *str - 'A' + 10;
	else if (*str >= 'a' && *str <= 'f')
		nbr = *str - 'a' + 10;
	else
		nbr = 0;
	return (nbr);
}

int			ft_atoi_base(const char *str, int base)
{
	int					sign;
	unsigned long long	nbr;

	sign = 1;
	nbr = 0;
	if (base < 2 || base > 16)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\v' \
			|| *str == '\n' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (valid_char(str, base))
		nbr = nbr * base + chartodigit(str++);
	return (sign * (int)nbr);
}
