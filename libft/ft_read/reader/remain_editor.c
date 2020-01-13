/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remain_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:59:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 10:59:42 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char			ft_empty_until(t_string *out, ssize_t *len, char *rmn,
		char end)
{
	ssize_t			i;
	ssize_t			j;

	i = 0;
	while (rmn[i] != '\0' && rmn[i] != end)
		i++;
	i = (rmn[i] == end) ? i + 1 : i;
	if (-1 == (*len = ft_str_join(out, *len, rmn, i)))
	{
		free(out->s);
		out->s = NULL;
		return (0);
	}
	j = i;
	while (rmn[j] != '\0')
	{
		rmn[j - i] = rmn[j];
		j++;
	}
	rmn[j - i] = '\0';
	return (*len != 0 && ((out->s)[*len - 1] == end) ? 1 : 0);
}

unsigned char			ft_empty_n(t_string *out, ssize_t *len, char *rmn,
	ssize_t n)
{
	ssize_t			i;
	ssize_t			j;

	if (*len >= n)
		return (1);
	i = 0;
	while (rmn[i] != '\0' && *len + i < n)
		i++;
	if (-1 == (*len = ft_str_join(out, *len, rmn, i)))
	{
		free(out->s);
		out->s = NULL;
		return (0);
	}
	j = i;
	while (rmn[j] != '\0')
	{
		rmn[j - i] = rmn[j];
		j++;
	}
	rmn[j - i] = '\0';
	return ((*len == n) ? 1 : 0);
}

unsigned char			ft_find_end(t_fe fe, ssize_t plen, ssize_t *len,
	char end)
{
	ssize_t			i;
	ssize_t			j;

	i = plen;
	while (i < *len && fe.out[i] != end)
		i++;
	if (fe.out[i++] == end)
	{
		j = 0;
		while (i + j < *len)
		{
			fe.rmn[j] = fe.out[i + j];
			j++;
		}
		fe.out[i] = '\0';
		fe.rmn[j] = '\0';
		*len = i;
		return (1);
	}
	return (0);
}

unsigned char			ft_find_n(t_fe fe, ssize_t *len, ssize_t n)
{
	ssize_t			i;

	if (*len < n)
		return (0);
	if (*len == n)
		return (1);
	i = 0;
	while (n + i < *len)
	{
		fe.rmn[i] = fe.out[n + i];
		i++;
	}
	fe.out[n] = '\0';
	fe.rmn[i] = '\0';
	*len = n;
	return (1);
}
