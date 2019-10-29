/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:53:07 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/29 17:07:20 by nsondag          ###   ########.fr       */
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

t_prog	*skip_chars(t_prog *prog, char *charset)
{
	int i;

	i = 0;
	if (!prog->line || !*prog->line)
		return (prog);
	while (charset[i] && *prog->line)
	{
		if (*prog->line == charset[i])
		{
			prog->line++;
			prog->i++;
			i = 0;
		}
		else
			i++;
	}
	return (prog);
}

t_prog	*skip_nb_chars(t_prog *prog, int nb)
{
	if (!prog->line || !*prog->line)
		return (prog);
	prog->line += nb;
	prog->i += nb;
	return (prog);
}

t_prog	*skip_until(t_prog *prog, char *charset)
{	
	int i;

	i = 0;
	if (!prog->line || !*prog->line)
		return (prog);
	while (charset[i] && *prog->line)
	{
		printf("charset\n");
		if (*prog->line != charset[i])
		{
			printf("%s\n", prog->line);
			prog->line++;
			prog->i++;
			i = 0;
		}
		else
			i++;
	}
	return (prog);
}

char	*trim_comments_space(char *params)
{
	int i;

	i = 0;
	while (params && params[i] && params[i] != ' ' &&
			params[i] != '\t' && params[i] != '#')
		i++;
	if (i > 0)
		params = ft_strsub(params, 0, i);
	return (params);
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
