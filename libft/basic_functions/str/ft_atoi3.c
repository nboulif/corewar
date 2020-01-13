/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:56:45 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:21:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t		ft_atoi3(const char *str)
{
	intmax_t	result;
	size_t		i;
	char		sign;
	intmax_t	tmp;

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
		if (tmp != (intmax_t)0 && (tmp ^ result) < (intmax_t)0)
			return ((result < (intmax_t)0) ? INTMAX_POS : INTMAX_NEG);
	}
	return (result);
}
