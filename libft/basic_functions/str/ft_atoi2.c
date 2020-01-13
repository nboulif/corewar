/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:56:45 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:21:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_atoi2(const char *str)
{
	long		result;
	size_t		i;
	char		sign;
	long		tmp;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		++i;
	if (str[i] == '+' || (str[i] == '-' && (sign = -1)))
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = result * 10 + sign * (str[i++] - '0');
		if (tmp != (long)0 && (tmp ^ result) < (long)0)
			return ((result < (long)0) ?
					(long)((~((unsigned long)0)) >> 1) :
					(long)(~((~((unsigned long)0)) >> 1)));
	}
	return (result);
}
