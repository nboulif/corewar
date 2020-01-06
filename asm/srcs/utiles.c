/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:25:24 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:40:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*skip_chars2(char *s, char *charset)
{
	int i;

	i = 0;
	if (!s || !*s)
		return (s);
	while (charset[i] && *s)
	{
		if (*s == charset[i])
		{
			s++;
			i = 0;
		}
		else
			i++;
	}
	return (s);
}

int		skip_chars(char *line, int *i, char *charset)
{
	int j;
	int tmp_i;

	tmp_i = *i;
	j = 0;
	if (!line || !line[*i])
		return (0);
	while (charset[j] && line[*i])
	{
		if (line[*i] == charset[j])
		{
			*i += 1;
			j = 0;
		}
		else
			j++;
	}
	return (*i - tmp_i);
}

int		skip_until(char *line, int *i, char *charset)
{
	int j;
	int tmp_i;

	tmp_i = *i;
	if (!line || !line[*i])
		return (0);
	while (line[*i])
	{
		j = 0;
		while (charset[j])
		{
			if (line[*i] != charset[j])
				j++;
			else
				return (*i - tmp_i);
		}
		if (!charset[j])
			*i += 1;
	}
	return (*i - tmp_i);
}

int		count_digit_string(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	return (i);
}
