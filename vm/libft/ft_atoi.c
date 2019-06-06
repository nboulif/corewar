/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:58:59 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 17:59:01 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	num;
	long	tmp;

	i = 0;
	num = 0;
	while (*(str + i) == '\f' || *(str + i) == '\t' || *(str + i) == '\n'
		|| *(str + i) == '\r' || *(str + i) == '\v' || *(str + i) == ' ')
		i++;
	neg = *(str + i) == '-' ? -1 : 1;
	*(str + i) == '-' || *(str + i) == '+' ? i++ : 0;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
	{
		tmp = num;
		num = num * 10 + (*(str + i++) - '0');
		if (num > 9223372036854775807 || num < tmp)
			return (neg == 1 ? -1 : 0);
	}
	return ((int)(num * neg));
}
