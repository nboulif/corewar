/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:59:37 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 10:59:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	ft_read_input(t_string *out, ssize_t *len, size_t sread)
{
	static char		buff[YMAX_RDSZ + 1];
	ssize_t			nread;

	if (sread >= YMAX_RDSZ)
		sread = YMAX_RDSZ;
	if ((nread = read(YINPUT, buff, sread)))
	{
		if (nread < 0 || -1 == (*len = ft_str_join(out, *len, buff, nread)))
		{
			free(out->s);
			return (0);
		}
	}
	return ((nread) ? 1 : 0);
}

static char				*ft_read_until(char end, char *rmn)
{
	ssize_t			len;
	t_string		out;
	ssize_t			plen;
	t_fe			fe;
	size_t			sread;

	out.s = NULL;
	out.l = 0;
	len = 0;
	if (ft_empty_until(&out, &len, rmn, end))
		return (out.s);
	if (!out.s)
		return (NULL);
	plen = len;
	sread = YREAD_SIZE;
	while (ft_read_input(&out, &len, sread))
	{
		fe = (t_fe){out.s, rmn};
		if (ft_find_end(fe, plen, &len, end))
			return (out.s);
		plen = len;
		sread = (2 * sread < YMAX_RDSZ) ? 2 * sread : sread;
	}
	return (out.s);
}

static char				*ft_read_n(ssize_t n, char *rmn)
{
	ssize_t			len;
	t_string		out;
	t_fe			fe;
	size_t			sread;

	out.s = NULL;
	out.l = 0;
	len = 0;
	if (ft_empty_n(&out, &len, rmn, n))
		return (out.s);
	if (!out.s)
		return (NULL);
	sread = YREAD_SIZE;
	while (ft_read_input(&out, &len, sread))
	{
		fe = (t_fe){out.s, rmn};
		if (ft_find_n(fe, &len, n))
			return (out.s);
		sread = (2 * sread < YMAX_RDSZ) ? 2 * sread : sread;
	}
	return (out.s);
}

char					*ft_read(ssize_t n, char *end)
{
	static char		rmn[YMAX_RDSZ + 1];

	if (end != NULL)
		return (ft_read_until(*end, rmn));
	if (n > 0)
		return (ft_read_n(n, rmn));
	return (NULL);
}
