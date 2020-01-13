/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_flags_support.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 20:21:48 by dabeloos          #+#    #+#             */
/*   Updated: 2019/03/05 18:11:50 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			size_length_modifier(char *in)
{
	size_t		pos;
	char		m;

	pos = -1;
	m = in[++pos];
	if (m == 'l' || m == 'h' || m == 'L' || m == 'j' || m == 'z')
	{
		m = in[++pos];
		if (m == in[pos - 1] && (m == 'h' || m == 'l'))
			++pos;
	}
	return (pos);
}

unsigned char	is_flag(char in)
{
	return (in == '-' || in == '0' || in == '+' || in == ' ' || in == '#');
}

unsigned char	is_number(char in)
{
	return (in >= '0' && in <= '9');
}

char			*pf_strncpy(char *dst, const char *src, size_t len)
{
	size_t		i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
	return (dst);
}

unsigned int	ft_atoui_limited(const char *str)
{
	unsigned int		result;
	size_t				i;
	unsigned int		tmp;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = result;
		result = result * 10 + str[i++] - '0';
		if (result < tmp)
			return (~((unsigned int)0));
	}
	return (result);
}
