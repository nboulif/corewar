/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_realloc_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:59:47 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 10:59:48 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	ft_str_realloc(char **in, ssize_t old, ssize_t new_s,
	ssize_t l)
{
	char		*out;

	out = (char*)malloc(l);
	if (!out)
		return (0);
	while (old-- > 0)
		out[old] = (*in)[old];
	out[new_s] = '\0';
	free(*in);
	*in = out;
	return (1);
}

unsigned char			ft_str_over_realloc(t_string *in, ssize_t old,
	ssize_t new_s)
{
	if (old < 0 || new_s < 0 || new_s < old || (in->s == NULL && old != 0))
		return (0);
	if (in->l >= new_s + 1)
	{
		(in->s)[new_s] = '\0';
		return (1);
	}
	if (in->l <= 0)
		in->l = 2;
	while (in->l < new_s + 1)
		in->l *= 2;
	return (ft_str_realloc(&(in->s), old, new_s, in->l));
}

ssize_t					ft_str_join(t_string *des, ssize_t ld, char *src,
	ssize_t ls)
{
	ssize_t		tmp;

	tmp = ls;
	if (ld < 0 || ls < 0 || !src || !ft_str_over_realloc(des, ld, ld + ls))
		return (-1);
	while (ls-- > 0)
		(des->s)[ld + ls] = src[ls];
	return (ld + tmp);
}
