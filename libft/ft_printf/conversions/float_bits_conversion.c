/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bits_conversion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 17:53:15 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:22:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ldouble_bits_tostr(long double in, t_str *head)
{
	unsigned char	*bits;
	size_t			index;
	size_t			dots;

	bits = store_ldouble_bits(in);
	if (!bits)
		return ;
	head->len = sizeof(char) * 80 + 3 * sizeof(char);
	head->txt = (char*)malloc(sizeof(char) * head->len);
	if (!bits)
		return ;
	index = -1;
	dots = 0;
	while (++index < head->len - 3)
	{
		head->txt[index + dots] = '0' +
			(char)((bits[(head->len - 2) / 8 - 1 - index / 8] &
			(((unsigned char)1) << (7 - index % 8))) >> (7 - index % 8));
		if (index == 0 || index == 15 || index == 16)
			head->txt[index + ++dots] = '.';
	}
	free(bits);
}

void					double_bits_tostr(double in, t_str *head)
{
	unsigned char	*bits;
	size_t			index;
	size_t			dots;

	bits = store_double_bits(in);
	if (!bits)
		return ;
	head->len = sizeof(in) * 8 + 2 * sizeof(char);
	head->txt = (char*)malloc(sizeof(char) * head->len);
	if (!bits)
		return ;
	index = -1;
	dots = 0;
	while (++index < head->len - 2)
	{
		head->txt[index + dots] = '0' +
			(char)((bits[(head->len - 2) / 8 - 1 - index / 8] &
			(((unsigned char)1) << (7 - index % 8))) >> (7 - index % 8));
		if (index == 0 || index == 11)
			head->txt[index + ++dots] = '.';
	}
	free(bits);
}
