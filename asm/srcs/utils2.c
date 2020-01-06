/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:25:24 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:40:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

t_op			*identify_opc(char *line)
{
	int i;

	i = -1;
	if (!*line)
		return (&g_op_tab[16]);
	while (++i < 16)
	{
		if (!ft_strcmp(line, g_op_tab[i].name))
			return (&g_op_tab[i]);
	}
	return (NULL);
}

int				valid_char(const char *str, int base)
{
	if (base < 11)
	{
		if (*str >= '0' && *str < '0' + base)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((*str >= 'a' && *str < 'a' + base - 10)
			|| (*str >= 'A' && *str < 'A' + base - 10)
			|| (*str >= '0' && *str <= '9'))
			return (1);
		else
			return (0);
	}
}
