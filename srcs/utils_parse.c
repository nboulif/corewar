/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:01:00 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 14:01:53 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int			rev_int_byte(int nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
		(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

int			check_index(char *index)
{
	int i;

	i = 0;
	if (index[i] == '-' || index[i] == '+')
		i++;
	while (index[i])
		if (!ft_isdigit(index[i++]))
			return (0);
	return (1);
}

t_champ		*get_champ(int index, t_all *all)
{
	int		i;

	i = -1;
	while (++i < (int)all->nb_champ)
	{
		if (all->champ[i].index == index)
			return (&all->champ[i]);
	}
	return (NULL);
}
