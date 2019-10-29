/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:53:07 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/29 13:59:54 by nsondag          ###   ########.fr       */
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
		if (*prog->line != charset[i])
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
